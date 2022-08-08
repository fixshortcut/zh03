#include <SoftwareSerial.h>

#define ZH03B_datalength 24
#define RX_softSer 36
#define TX_softSer 23

SoftwareSerial softSer;

byte buffe[ZH03B_datalength];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  softSer.begin(9600, SWSERIAL_8N1, TX_softSer, RX_softSer, false);

  if (!softSer) { // If the object did not initialize, then its configuration is invalid
    Serial.println("Invalid SoftwareSerial pin configuration, check config");
    while (1) { // Don't continue with invalid configuration
      delay (1000);
    }
  }
}

void loop() {
  while (Serial.available() > 0) {
    int input = Serial.readBytesUntil('\n', buffe, ZH03B_datalength);
    Serial.print("Dust sensor send: ");
    for (int i = 0; i < input ; i++) {
      Serial.print("ke:");
      Serial.print(i);
      Serial.print(">");
      Serial.println(buffe[i], HEX);
      //      Serial.print(buffe[i], HEX);
    }
    Serial.println("");

    int16_t checksumDust = combine_hex(22, 23);
    Serial.print("nilai checksum : ");
    Serial.println(checksumDust, HEX);
    int16_t checksum = checkSumTot();
    Serial.println(checksum,HEX);
    if (checksumDust == checksum) {
      Serial.println("nilai checksum benar");
    }
    int16_t dustPM25 = combine_hex(12, 13);
    Serial.print("nilai sensor pm2.5 : ");
    Serial.println(dustPM25);

  }

}
