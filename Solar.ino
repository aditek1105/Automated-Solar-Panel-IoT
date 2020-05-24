#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int sum=0;
float voltage=0.0;

Servo horizontal; // horizontal servo
int servoh = 90; // stand horizontal servo

Servo vertical; // vertical servo 
int servov = 0; // stand vertical servo

int ldrlt = 0; //LDR top left //exchange top and bottom of left and right
int ldrrt = 1; //LDR top rigt
int ldrld = 2; //LDR down left
int ldrrd = 3; //ldr down rigt

void setup()
{
  Serial.begin(9600);
   lcd.begin(16, 2);
horizontal.attach(9);
  vertical.attach(10);
  vertical.write(servov);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
   


  int dtime =10;
int tol = 50;
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; 
int dhoriz = avl - avr;

if (-1*tol > dvert || dvert > tol) 
{
if (avt > avd)
{
servov = ++servov;
if (servov > 70)
{
servov = 70;
}
}
else if (avt < avd)
{
servov= --servov;
if (servov < 0)
{
servov = 0;
}
}
vertical.write(servov);
}

if (-1*tol > dhoriz || dhoriz > tol) 
{
if (avl > avr)
{
servoh = --servoh;
if (servoh < 0)
{
servoh = 0;
}
}
else if (avl < avr)
{
servoh = ++servoh;
if (servoh > 180)
{
servoh = 180;
}
}
else if (avl == avr)
{
// nothing
}
horizontal.write(servoh);
}
   int sample1;
 for(int i=0;i<150;i++)
{
sample1=sample1+analogRead(A4); //read the voltage from the divider circuit

}
sample1=sample1/150;
voltage=4.669*2*sample1/1000;
if(voltage<0)
{
voltage=0;

lcd.print("Voltage=");
lcd.print(voltage);
lcd.print("V");
}
else
{
lcd.print("Voltage=");
lcd.print(voltage);
Serial.print(voltage);
lcd.print("V");
}
delay(1000);
lcd.clear();


} 


