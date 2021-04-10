  int windhaancode(){

  windrichting = analogRead(A3);
  //Serial.println(windrichting);
  switch (windrichting) {
    case 780 ... 790:
      coordinaat = 1;

      break;
    case 400 ... 410:
      coordinaat = 2;

      break;
    case 455 ... 465:
      coordinaat = 3;

      break;
    case 78 ... 87:
      coordinaat = 4;

      break;
    case 88 ... 97:
      coordinaat = 5;

      break;
    case 60 ... 70:
      coordinaat = 6;

      break;
    case 179 ... 189:
      coordinaat = 7;

      break;
    case 121 ... 131:
      coordinaat = 8;

      break;
    case 281 ... 291:
      coordinaat = 9;

      break;
    case 238 ... 248:
      coordinaat = 10;

      break;
    case 625 ... 635:
      coordinaat = 11;

      break;
    case 594 ... 604:
      coordinaat = 12;

      break;
    case 945 ... 955:
      coordinaat = 13;

      break;
    case 826 ... 836:
      coordinaat = 14;

      break;
    case 885 ... 895:
      coordinaat = 15;

      break;
    case 701 ... 711:
      coordinaat = 16;

      break;
  }
}
