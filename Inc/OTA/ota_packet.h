/*
 * ota_packet.h
 *
 *  Created on: 28-Feb-2026
 *      Author: HARSHA
 */

#ifndef OTA_OTA_PACKET_H_
#define OTA_OTA_PACKET_H_

#define OTA_PACKET_SIZE				512
#define OTA_START_BYTE    			(0xAAU)
#define OTA_STOP_BYTE    	 		(0x55U)
#define OTA_ACK 					(0xBBU)
#define OTA_NACK					(0xCCU)

typedef struct{
	uint8_t start_byte;
	uint16_t sequence_number;
	uint16_t payload_length;
	uint8_t payload[OTA_PACKET_SIZE];
	uint32_t crc;
	uint8_t stop_byte;
}packet_struct;

#endif /* OTA_OTA_PACKET_H_ */
