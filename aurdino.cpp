#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define I2C_ADDR 0x3F //I2C adress, you should use the code to scan the adress first (0x27) here
#define BACKLIGHT_PIN 3 // Declaring LCD Pins
#define En_pin 9

#define Rs_pin 10
#define D4_pin 4
#define D5_pin 6
#define D6_pin 7
#define D7_pin 8
#define echoPin 2           // defining pins and variables
#define trigPin 3
int long duration;
int distance;

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin); 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int motor= 5;             // pin connected to base of npn transistor

void setup()
{
  pinMode(echoPin,INPUT);        // defining pin modes
  pinMode(trigPin,OUTPUT);  
  pinMode(motor, OUTPUT);  
  mlx.begin();
  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH); //Lighting backlight
  lcd.home ();
}

void loop()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.017);   // now you got the distance 
  lcd.setCursor(0,0);
  lcd.print("Ambient ");
  lcd.print(mlx.readAmbientTempC());
  lcd.print(" C");
 
  lcd.setCursor(0,1);
  lcd.print("Target  ");
  lcd.print(mlx.readObjectTempC());
  lcd.print(" C");

 delay(1000);

  if(distance<=20)               // checking the presence of hands in 20 cm limit
  {  
    digitalWrite(motor,HIGH);    // if present motor operates for some time
    delay(400);                  // delay value to changes the operating time
    digitalWrite(motor,LOW);     // pump stop working for some time
    delay(1000);                 // some delay prevents continous operation
  }
  else 
  {
    digitalWrite(motor,LOW);     // if no hands detected - no operation
  }
}