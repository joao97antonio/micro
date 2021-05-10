#include <SPI.h>
#include <Ethernet.h>
int vet_receb[4] = {2,2,2,2};
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(10,0,0,130);          
IPAddress gateway(10,0,0,1);     
IPAddress subnet(255, 255, 255, 0);
EthernetServer server(80);

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(24,OUTPUT);
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}
void comunicaServidor(){
  EthernetClient client = server.available();
  if(client){
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == 'n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 2");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<table width=\"467\" border=\"1px>\"");
          client.print("<font color=#FF0000>");
          client.print("<tr>");
          client.print("<td>");
          client.print("Controle de Horta:");
          client.print("</td>");
          client.print("</tr>");
          client.print("</font>");
          client.print("<tr>");
          client.print("<td>");
          client.print("Sensor de Umidade 1: ");
          client.print("</td>");
          client.print("<td>");
          client.print(vet_receb[0]);
          client.print("</td>");
          client.print("</tr>");
          client.print("<tr>");
          client.print("<td>");
          client.print("Sensor de Umidade 2: ");
          client.print("</td>");
          client.print("<td>");
          client.print(vet_receb[1]);
          client.print("</td>");
          client.print("</tr>");
          client.println("</html>");
          client.print("<tr>");
          client.print("<td>");
          client.print("Temperatura: ");
          client.print("</td>");
          client.print("<td>");
          client.print(vet_receb[2]);
          client.print("</td>");
          client.print("</tr>");
          client.print("</table>");
          client.println("<br />");
          client.println("<br />");
          client.println("</b></html>");
          break;
        }
        if (c == 'n') {
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          currentLineIsBlank = false;
        }
      }
    }
    delay(5);
    client.stop();
  }else{
    Serial.print("ERRO!!");
  }
}
void loop() {
  digitalWrite(24,HIGH);
  if(Serial1.available()){
  vet_receb[0] = Serial1.read() * 4;
  vet_receb[1] = Serial1.read() * 4;
  vet_receb[2] = Serial1.read();
  vet_receb[3] = Serial1.read();
 }
  delay(2000);
  Serial.println(vet_receb[0]);
  Serial.println(vet_receb[1]);
  if((vet_receb[0]>512) && (vet_receb[1]>512)){
    digitalWrite(24,LOW);
    delay(5000);
    digitalWrite(24,HIGH);
 }
 delay(1000);
 comunicaServidor();
}
