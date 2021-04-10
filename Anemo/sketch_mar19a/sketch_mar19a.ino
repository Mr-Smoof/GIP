int verkeerslicht[15] ={1, 2, 3, 4, 5, 6, 7, 8, 9, A0, A1, A2, A3, A4, A5};
char startknop = 0;
char sensor1 = 10;
char sensor2 = 11;
char sensor3 = 12;
char sensor4 = 13;
int tijd = 5000;

bool start = false;
bool ACG = false;
bool ACR = false;

void setup(){
  for(char i = 0; i <=14; i++){
    pinMode(verkeerslicht[i], OUTPUT);
  }
  pinMode(defect, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
}

void loop(){
  if(startknop == HIGH){
    
  }
}
