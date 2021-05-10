#define SU2 A1
#define SU1 A0
#define ST A2
#include <Thermistor.h> 
Thermistor temp(ST);
int vet_envio[4] = {0,0,0,0};
void setup() {
  pinMode(SU1, INPUT);
  pinMode(SU2, INPUT);
  Serial.begin(9600);
}

int leituraSolo(int sensor){
  if(sensor == 0){
    return(analogRead(SU1));  
  }else{
    return (analogRead(SU2));
  }
}

void loop() {
  vet_envio[0] = leituraSolo(0) / 4;
  vet_envio[1] = leituraSolo(1) / 4;
  vet_envio[2] = temp.getTemp();
  delay(1000);
  Serial.write(vet_envio[0]);
  Serial.write(vet_envio[1]);
  Serial.write(vet_envio[2]);
  Serial.write(vet_envio[3]);
}
