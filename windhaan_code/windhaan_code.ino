int windhaan = A3;
int windrichting;
int coordinaat;

void setup() {
 // pinMode(A3, INPUT);
 Serial.begin(9600);
 }

int windhaancode(){
  windrichting = analogRead(A3);
  //Serial.println(windrichting);
  switch (windrichting) {
    case 780 ... 790:
      coordinaat = 1;
      Serial.println(coordinaat);
      break;
    case 400 ... 410:
      coordinaat = 2;
      Serial.println(coordinaat);
      break;
    case 455 ... 465:
      coordinaat = 3;
      Serial.println(coordinaat);
      break;
    case 78 ... 87:
      coordinaat = 4;
      Serial.println(coordinaat);
      break;
    case 88 ... 97:
      coordinaat = 5;
      Serial.println(coordinaat);
      break;
    case 60 ... 70:
      coordinaat = 6;
      Serial.println(coordinaat);
      break;
    case 179 ... 189:
      coordinaat = 7;
      Serial.println(coordinaat);
      break;
    case 121 ... 131:
      coordinaat = 8;
      Serial.println(coordinaat);
      break;
    case 281 ... 291:
      coordinaat = 9;
      Serial.println(coordinaat);
      break;
    case 238 ... 248:
      coordinaat = 10;
      Serial.println(coordinaat);
      break;
    case 625 ... 635:
      coordinaat = 11;
      Serial.println(coordinaat);
      break;
    case 594 ... 604:
      coordinaat = 12;
      Serial.println(coordinaat);
      break;
    case 945 ... 955:
      coordinaat = 13;
      Serial.println(coordinaat);
      break;
    case 826 ... 536:
      coordinaat = 14;
      Serial.println(coordinaat);
      break;
    case 885 ... 895:
      coordinaat = 15;
      Serial.println(coordinaat);
      break;
    case 701 ... 711:
      coordinaat = 16;
      Serial.println(coordinaat);
      break;
  }
  delay(1000);
}

void loop() {
  windhaancode();
}
