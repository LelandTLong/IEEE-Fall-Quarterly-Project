
#include <EEPROM.h>

//The time between each EEPROM write function call in ms
#define SAMPLE_TIME 2000  

const int analogInPin = A0; 
int sensorValue = 0; 
int sensorValue1 = 0;
const int turbPin=A1;
unsigned long int avgValue; 
float b;
int buf[10],temp;
float min = 1000000000000;
float max = 0;
boolean varSet = false;
float volt; 
float ntu;


void setup(void) {
 Serial.begin(9600);
}
 
void loop(void) {
 for(int i=0;i<10;i++) 
 { 
  
  buf[i]=analogRead(analogInPin); 
  
  delay(100);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {  
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 
 avgValue=0;
 float pHAverage = 0;
 
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float pHValue = -5.70 * pHVol + 24.34;
 
 
 pHAverage += pHValue; 
 

 if(min > pHValue){
    min = pHValue; 
 }
 if(max < pHValue){
    max = pHValue;
 }
 
 Serial.print(pHValue);
 Serial.println(" ");
 
 //print max and min pH levels overall
 //Serial.print("Highest pH = ");
 Serial.print(max);
 Serial.println(" ");
 //Serial.print("Lowest pH = ");
 Serial.print(min);
 Serial.println(" ");
 //prints the average pH
 //Serial.print("Average pH: ");
 Serial.println(pHAverage); 

 //message to interpret pH level
 //if(pHAverage > 4 && pHAverage < 9) {
  //Serial.println("Water levels are normal!");
 //}
 //else if (pHAverage <= 4) {
  //Serial.println("Water is too acidic!");
// }
 //else if (pHAverage >= 9) {
  //Serial.println("Water is too basic!");
 //}

 Serial.print(", ");
 delay(3000); 

 float sensorValue1 = analogRead(turbPin);

 //Serial.print("Turbidity: ");
 Serial.print(sensorValue1 / 500);
 
 Serial.println();
 delay (3000);

 
 }//end loop

 float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}


 
