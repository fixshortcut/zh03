

#define ZH03B_datalength 24  // datalength of initiative upload received value
#define ZH03B_Modelength 9 // datalength of mode changing and q&a mode

byte buffe[ZH03B_datalength];
byte request[ZH03B_Modelength] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; //request to get dust value
byte qamode[ZH03B_Modelength]  = {0xFF, 0x01, 0x78, 0x41, 0x00, 0x00, 0x00, 0x00, 0x46}; //set to Q&A mode
byte initmode[ZH03B_Modelength] = {0xFF, 0x01, 0x78, 0x40, 0x00, 0x00, 0x00, 0x00, 0x47}; //set to initiative upload mode
byte buff[ZH03B_Modelength];
int16_t dustPM25, dustPM10, dustPM100;
unsigned long printMil;
String dataSerial;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  printMil = millis();
}

void loop() {
  while (Serial.available() > 0) {
    Serial.setTimeout(100);
    String StringRead = Serial.readString();
    dataSerial += StringRead;
    Serial.println(dataSerial);
    if (dataSerial == "mode_qa") { //set mode to q&a mode
      Serial2.write(qamode,ZH03B_Modelength);
      delay(100);
    } else if (dataSerial == "mode_auto") { //set mode to initiative upload mode
      Serial2.write(initmode,ZH03B_Modelength);
      delay(100);
    } else if (dataSerial == "get_data") {
      getData();
    }
  }
  while (Serial2.available() > 0) {
    int input = Serial2.readBytesUntil('\n', buffe, ZH03B_datalength);
    Serial.print("Dust sensor send: ");
    for (int i = 0; i < input ; i++) {
      Serial.print("ke:");
      Serial.print(i);
      Serial.print(">");
      Serial.println(buffe[i], HEX);
      //      Serial.print(buffe[i], HEX);
    }
    Serial.println("");

    int16_t checksumSer = combine_hex(22, 23); // checksum from serial
    int16_t checksum = checkSumTot(); // checksum from counting all the variable with formula
    Serial.print("nilai checksum : ");
    Serial.println(checksumSer, HEX);
    Serial.println(checksum, HEX);
    if (checksumSer == checksum) {
      Serial.println("checksum right!");
      dustPM10  = combine_hex(10, 11);
      dustPM25  = combine_hex(12, 13);
      dustPM100 = combine_hex(14, 15);
    }


  }
  if (millis() >= printMil + 500) {
    Serial.printf("PM1.0 : %d\n", dustPM10);
    Serial.printf("PM2.5 : %d\n", dustPM25);
    Serial.printf("PM10  : %d\n", dustPM100);

  }


}
