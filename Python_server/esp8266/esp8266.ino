#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "IQOO Z9s Pro 5G";
const char* password = "qwerty123";
const char* serverIP = "http://10.215.249.65:5000";

uint8_t hash_buffer[32];
uint8_t sig_buffer[256];
uint8_t fw_buffer[65536];
int sig_len = 0;
int fw_len = 0;

void downloadHash(){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, String(serverIP) + "/hash");
    if(http.GET() == 200){
        WiFiClient* stream = http.getStreamPtr();
        stream->readBytes(hash_buffer, 32);
    }
    http.end();
}

void downloadSignature(){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, String(serverIP) + "/signature");
    if(http.GET() == 200){
        sig_len = http.getSize();
        WiFiClient* stream = http.getStreamPtr();
        stream->readBytes(sig_buffer, sig_len);
    }
    http.end();
}

void downloadFirmware(){
    WiFiClient client;
    HTTPClient http;
    http.begin(client, String(serverIP) + "/firmware");
    if(http.GET() == 200){
        fw_len = http.getSize();
        WiFiClient* stream = http.getStreamPtr();
        stream->readBytes(fw_buffer, fw_len);
    }
    http.end();
}

void sendToSTM32(){
    // Send hash first
    Serial1.write(hash_buffer, 32);

    // Send firmware in packets
    int offset = 0;
    uint16_t seq = 0;
    while(offset < fw_len){
        uint16_t chunk = min(512, fw_len - offset);

        Serial1.write(0xAA);                          // start byte
        Serial1.write((uint8_t*)&seq, 2);             // sequence number
        Serial1.write((uint8_t*)&chunk, 2);           // payload length
        Serial1.write(fw_buffer + offset, chunk);     // payload
        Serial1.write(0x55);                          // stop byte

        // Wait for ACK
        while(!Serial1.available());
        uint8_t ack = Serial1.read();
        if(ack != 0xBB){
            Serial.println("NACK received - aborting");
            return;
        }
        offset += chunk;
        seq++;
    }
    Serial.println("Firmware sent successfully");
}

void setup(){
    Serial.begin(115200);
    Serial1.begin(115200);

    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");

    downloadHash();
    downloadSignature();
    downloadFirmware();
    sendToSTM32();
}

void loop(){
}