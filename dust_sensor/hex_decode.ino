int checkSumTot() {
  int16_t checksum = 0;
  for ( int i = 0; i < ZH03B_datalength - 2; i++) {
    // Serial.print(res[i], HEX);Serial.print(" ");
    checksum += buffe[i];
  }

  return checksum;
}
int combine_hex (int highBytes, int lowBytes)// urutan digit awal highbyte dan digit akhir lowbyte pada masukan serial
{
  int16_t FB = buffe[highBytes] << 8 ;
  int16_t SB = buffe[lowBytes];
  int16_t aWord = FB + SB;
  return aWord;
}
