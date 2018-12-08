// initial themes.h file created by circuitdigest.com
// basically created my own tune and tempo, so code below is all custom-made


//##############**"Titanic" **##############//
int Titanic_note[] = {
NOTE_E4, NOTE_FS4, NOTE_GS4, 
NOTE_A4, NOTE_GS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_B4, 
NOTE_A4, NOTE_GS4, NOTE_E4, 
NOTE_CS4, NOTE_B3, 
NOTE_E4, NOTE_FS4, NOTE_GS4, 
NOTE_A4, NOTE_GS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_B4, 
NOTE_GS4, NOTE_B4, NOTE_CS5, 
NOTE_B4, NOTE_FS4


};
int Titanic_duration[] = {
1,1,6,1,1,1,1,1,7,1,1,4,3,8,1,1,6,1,1,1,1,1,7,1,1,3,3,8



};
//###########End of Titanic#############//



//##############**"London Bridge is Falling Down" **##############//
int London_note[] = {
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_C5, 
NOTE_G4, NOTE_A4, NOTE_AS4, 
NOTE_A4, NOTE_AS4, NOTE_C5, 
NOTE_C5, NOTE_D5, NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_C5, 
NOTE_G4, NOTE_C5, NOTE_A4, NOTE_F4



};
int London_duration[] = {
1,1,1,1,1,1,2,
1,1,2,
1,1,2,
1,1,1,1,1,1,2,
2,2,1,3



};
//###########End of London#############//

/*
 * [1]: https://bikeshedeffect.weebly.com/arduino-piezo-sounds.html
 * ^ obtained code from above, modified to make it work with current theme.h format
  tone(8,NOTE_E6,125);
  delay(130);
  tone(8,NOTE_G6,125);
  delay(130);
  tone(8,NOTE_E7,125);
  delay(130);
  tone(8,NOTE_C7,125);
  delay(130);
  tone(8,NOTE_D7,125);
  delay(130);
  tone(8,NOTE_G7,125);
  delay(125);
  noTone(8);
*/
int Powerup_note[] = {
NOTE_E6, NOTE_G6, NOTE_E7, NOTE_C7, NOTE_D7, NOTE_G7
};
int Powerup_duration[] = {
1,1,1,1,1,1
}
