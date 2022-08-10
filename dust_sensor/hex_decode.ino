int checkSumTot() {
  int16_t checksum = 0;
  for ( int i = 0; i < ZH03B_datalength - 2; i++) {
    // Serial.print(res[i], HEX);Serial.print(" ");
    checksum += buffe[i];
  }

  return checksum;
}
int checksumMode() {
  int totalRep;
  int16_t checksum = 0;
  for (int j = 1; j < ZH03B_Modelength - 1; j++) {
    totalRep += buff[j];
  }
  checksum = (buff[0] - totalRep ) + 1;
             return checksum;
}
int combine_hex (int highBytes, int lowBytes)// urutan digit awal highbyte dan digit akhir lowbyte pada masukan serial
{
  int16_t FB = buffe[highBytes] << 8 ;
  int16_t SB = buffe[lowBytes];
  int16_t aWord = FB + SB;
  return aWord;
}
int combine_hex2 (int highBytes, int lowBytes)// urutan digit awal highbyte dan digit akhir lowbyte pada masukan serial
{
  int16_t FB = buff[highBytes] << 8 ;
  int16_t SB = buff[lowBytes];
  int16_t aWord = FB + SB;
  return aWord;
}
