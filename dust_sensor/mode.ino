void getData() {
  Serial2.write(request,ZH03B_Modelength);
  while (Serial2.available() > 0) {
    int input = Serial2.readBytesUntil('\n', buff, ZH03B_Modelength);
    Serial.print("Dust sensor send: ");
    for (int i = 0; i < input ; i++) {
      Serial.print("ke:");
      Serial.print(i);
      Serial.print(">");
      Serial.println(buff[i], HEX);
      //      Serial.print(buff[i], HEX);
    }
    Serial.println("");
    int16_t checksumCount = checksumMode();// checksum from counting all the variable with formula
    int16_t checksumSer = buff[8];// checksum from serial

    Serial.print("nilai checksum : "); 
    Serial.println(checksumSer, HEX);    
    Serial.println(checksumCount, HEX);
    if (checksumSer == checksumCount) {
      Serial.println("checksum right!");
      dustPM10  = combine_hex2(6, 7);
      dustPM25  = combine_hex2(2, 3);
      dustPM100 = combine_hex2(4, 5);
    }else{
      Serial.println("checksum false");
    }

  }
 
}
