
//****************************LIBRERIAS**********************
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include<LiquidCrystal_I2C.h>
#include <DHT.h>
//********************************************DHT***************
#define DHTPIN 6//definicion del pin del dht
#define DHTTYPE DHT11//cambiar el DHT QUE SEA NECESARIO
DHT dht(DHTPIN, DHTTYPE);//creacion del elemento dht(ponle el nombre que gustes)
//**********************************LCD I2C*************************
LiquidCrystal_I2C lcd(0x027,16,2);//lcd(16,2)(20,4) cambiar segun sea necesario
//*******************************************BMP**************************
Adafruit_BMP085 bmp;//nombrar tu bmp

//*****************************BOTON Y MODOS***********************
int bot =5;
 int state=0;
  int modo=0;
//********************************RELAYS***********************
int rel1 = 12;
 int rel2 = 11;
  int rel3 = 10;
   int rel4 = 9;
//*******************************VALORES DE HUMEDAD*****************

int hum1;
 int hum2;
  int hum3;
   int hum4;

void setup() {

  pinMode(bot, INPUT_PULLUP);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  bmp.begin();
 // ********************RELAYS**********************
  pinMode(rel1,OUTPUT);
  pinMode(rel2,OUTPUT);
  pinMode(rel3,OUTPUT);
  pinMode(rel4,OUTPUT);

  digitalWrite(rel1, 1);
  digitalWrite(rel2, 1);
  digitalWrite(rel3, 1);
  digitalWrite(rel4, 1);
  //******************PINES DE HUMEDAD DE SUELO**************
    // analogRead(A0);
    // analogRead(A1);
    // analogRead(A2);
    // analogRead(A3);

  //***********************menu de inicio*********************
  //  lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("*INVERNADERO*V1");
  // lcd.setCursor(1, 1);
  // lcd.print("---BMP & DHT---");
  // delay(2000);
}
void loop() {
//***************************************************SUELO*************
  int valor1=analogRead(A0);
   int valor2=analogRead(A1);
    int valor3=analogRead(A2);
     int valor4=analogRead(A3);

  hum1=map(valor1, 270,1023,100,0);
   hum2=map(valor2, 270,1023,100,0);
    hum3=map(valor3, 270,1023,100,0);
     hum4=map(valor4, 270,1023,100,0);

  Serial.println("");
  Serial.print("HUM1:");
  Serial.println(hum1);
    Serial.print("HUM2:");
    Serial.println(hum2);
      Serial.print("HUM3:");
      Serial.println(hum3);
        Serial.print("HU4:");
        Serial.println(hum4);
         

//********************************************************DHT*************
  float temp =dht.readTemperature();
  float humd=dht.readHumidity();
  Serial.print("temp:");
  Serial.print(temp,1);
    Serial.print("hum:");
  Serial.print(humd,1);

//****************************************ESTADO DEL LCD******************
  state= digitalRead(bot);
  Serial.print("state ");
   Serial.println(state);
    Serial.print("modo ");
   Serial.println(modo);

//*******************************************CONDICIONES**************************
if(hum1>=20){//******************area 1****************
  digitalWrite(rel1, 1);
  delay(100);
  }
  if(hum1<=30){
  digitalWrite(rel1, 0);
  delay(100);
  }
  if(hum2>=20){//******************area 2****************
  digitalWrite(rel2, 1);
  delay(100);
  }
  if(hum2<=30){
  digitalWrite(rel2, 0);
  delay(100);
  }
  if(hum3>=20){//******************area 3****************
  digitalWrite(rel3, 1);
  delay(100);
  }
  if(hum3<=30){
  digitalWrite(rel3, 0);
  delay(100);
  }
  if(hum4>=20){//******************area 4****************
  digitalWrite(rel4, 1);
  delay(100);
  }
  if(hum4<=30){
  digitalWrite(rel4, 0);
  delay(100);
  }
  
if(state==0){//configuracion de menu
  state=1;
  modo+=1;
  delay(10);
  }
//************************MODO VALORES DHT Y BMP
if(modo==0){
    dhtxx();
    bmp1();
    delay(500);
}
//************************MODO SUELO
if(modo==1){
  
    lcd.setCursor(0,0);
    lcd.print("riego");
    suelo();
    delay(1000);
  
  }

if(modo==2){
    modo=0;
    delay(1000);

  }
  delay(100);
}
//************************************FUNCIONES
void bmp1(){

    int press;
    Serial.print("Pressure = ");
    press= bmp.readPressure() /100;
    Serial.print(press);
    Serial.println(" Pa");
    // SEGÚN TU REGIÓN DEBES CAMBIAR EL VALOR DE-----bmp.readAltitude(>>>>101300 <<<< este es el valor a cambiar)-------
    //buscar "presión atmosférica de tu departamento" y a ese valor multiplicarlo por 100
    //POR EJEMPLO, en Lima la presión atmosférica es de 1013 * 100 = 101300
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101300));
    Serial.println(" meters");

    lcd.setCursor(0,0);
    lcd.print("msnm:");
    lcd.setCursor(5,0);
    lcd.print(bmp.readAltitude(101300),0);

    lcd.setCursor(0,1);
    lcd.print("Pa:");
    lcd.setCursor(3,1);
    lcd.print(press);
}
void dhtxx(){
  float temp =dht.readTemperature();
  float humd=dht.readHumidity();

  lcd.setCursor(9,0);
  lcd.print("T:");
  lcd.setCursor(11,0);
  lcd.print(temp,1); 
  lcd.setCursor(15,0);
  lcd.print("C");

  lcd.setCursor(11,1);
  lcd.print(humd,1); 
  lcd.setCursor(6,1);
  lcd.print(" Hum:");
   lcd.setCursor(15,1);
  lcd.print("%");
}
void suelo(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hum1:");
  lcd.setCursor(6,0);
  lcd.print(hum1);

  lcd.setCursor(9,0);
  lcd.print("Hum2:");
  lcd.setCursor(14,0);
  lcd.print(hum2);

  lcd.setCursor(0,1);
  lcd.print("Hum3:");
  lcd.setCursor(6,1);
  lcd.print(hum3);

  lcd.setCursor(9,1);
  lcd.print("Hum4:");
  lcd.setCursor(14,1);
  lcd.print(hum4);
}
