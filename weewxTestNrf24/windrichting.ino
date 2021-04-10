uint8_t coordinaat;
//Declaraties windhaan
const byte windhaan = A3;

uint8_t windhaancode() {

  unsigned int windrichting = analogRead(windhaan);
  //Serial.println(windrichting);
#ifdef DEBUG
  Serial.print("windrichting: ");
  Serial.println(windrichting, DEC);
#endif
  switch (windrichting) {
    case 742 ... 792:       //Noorden
      coordinaat = 8;
      break;
    case 410 ... 460:       //Noordoost
      coordinaat = 7;
      break;
    case 58 ... 108:       //Oost
      coordinaat = 6;
      break;
    case 143 ... 193:       //Zuidoost
      coordinaat = 5;
      break;
    case 240 ... 290:       //Zuiden
      coordinaat = 4;
      break;
    case 580 ... 630:       //Zuidwest
      coordinaat = 3;
      break;
    case 912 ... 962:       //West
      coordinaat = 2;
      break;
    case 850 ... 900:       //Noordwest
      coordinaat = 1;
      break;
    default:                //Error
      coordinaat = 0;
      break;
  }
#ifdef DEBUG
  Serial.print("coordinaat: ");
  Serial.println(coordinaat, DEC);
#endif
  return coordinaat;
}
