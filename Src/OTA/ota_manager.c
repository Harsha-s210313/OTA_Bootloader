#include<OTA/ota_manager.h>

static uint8_t expected_hash[32];
static uint32_t bytes_received;
static uint32_t ota_staging_addr;
static uint32_t ota_firmware_length;
static OTA_STATE ota_state;


void OTA_init(uint32_t staging_addr, uint32_t length){
	ota_staging_addr = staging_addr;
	ota_firmware_length = length;
	ota_state = OTA_IDLE;
	uart_init(115200);
}

void OTA_run(){
	packet_struct packet;
	switch(ota_state){
	   case OTA_IDLE: ota_state = OTA_HANDSHAKE;
	   break;
	   case OTA_HANDSHAKE:
		   uart_tx_byte(0xAA);
		   if(uart_rx_byte() == (0x55)){
			   uart_rx_buffer(expected_hash, 32);
			   ota_state = OTA_RECIEVE_DATA;
		   }
		   else{
			   ota_state = OTA_ERROR;
		   }
	   break;
	   case OTA_RECIEVE_DATA :
		   uart_rx_buffer((uint8_t *)&packet, sizeof(packet_struct));
		   if((packet.start_byte == OTA_START_BYTE) && (packet.stop_byte == OTA_STOP_BYTE)){
			   flash_write(ota_staging_addr + bytes_received, packet.payload, packet.payload_length);
			   uart_tx_byte(OTA_ACK);
			   bytes_received += packet.payload_length;
			   if(bytes_received >= ota_firmware_length){
				   ota_state = OTA_VERIFY_HASH;
			   }
		   }
		   else{
			   uart_tx_byte(OTA_NACK);
			   ota_state = OTA_ERROR;
		   }
	   break;
	   case OTA_VERIFY_HASH:
		   uint8_t computed_hash[32];
		   mbedtls_sha256((uint8_t *)ota_staging_addr, ota_firmware_length, computed_hash, 0);
		   if(memcmp(computed_hash, expected_hash, 32)== 0 ){
			   ota_state = OTA_WRITE_TO_FLASH;
		   }
		   else{
			   ota_state = OTA_ERROR;
		   }
	   break;
	   case OTA_WRITE_TO_FLASH:
		   flash_erase(5);
		   flash_erase(6);
		   flash_erase(7);
		   if((flash_write(application_start_addr, (uint8_t *)ota_staging_addr, ota_firmware_length)) == 1){
			   ota_state = OTA_WRITE_COMPLETE;
		   }
		   else{
			   ota_state = OTA_ERROR;
		   }
	   break;
	   case OTA_ERROR:
		   uart_tx_byte(OTA_NACK);
		   ota_state = OTA_IDLE;
		   bytes_received = 0;
	   break;
	   case OTA_WRITE_COMPLETE:
		   jump_to_app();

	   break;
	}
}

