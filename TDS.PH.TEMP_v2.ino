#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
#define SENSOR_PIN A0
// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

#define TDS_PIN A1




// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//////////
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp=0;
///////////

void setup(void)
{
  lcd.init();
  lcd.clear();         
  lcd.backlight();
   Serial.begin(9600);
   lcd.begin(16, 2);      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("MINI");
  
  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("PROJECT - 2");
delay(500);
 lcd.clear();
sensors.begin();  // Start up the library
  Serial.begin(9600);
    // Initialize the LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

}

void loop(void)
{ 
  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  
  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.print((char)176);//shows degrees character
  Serial.println("F");
 // lcd.clear();
 lcd.setCursor(1,0);   //Move cursor to character 2 on line 1
  lcd.print("Temp");

lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print(sensors.getTempCByIndex(0));
  
  delay(50);
///////////
for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
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
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = 3.5* pHVol  ;
 phValue=phValue+1;
 //float phValue = -3.0 * pHVol+17.5;
 //Serial.print("sensor = ");
 //Serial.println(phValue);
 //lcd.clear();
  lcd.setCursor(5, 0); 
  lcd.print("|");
  lcd.setCursor(5, 1);
  lcd.print("|");
 lcd.setCursor(7,0);  
 lcd.print("PH");
 lcd.setCursor(6,1);  
 lcd.print(phValue);
 
 delay(20);
 
//////////
  // Read analog value from TDS sensor
  int sensorValue = analogRead(TDS_PIN);

  // Convert analog reading to TDS value (example conversion, please refer to your sensor's datasheet)
  float tdsValue = map(sensorValue, 1, 1023, 1, 1100); // adjust 2000 according to your sensor's range

  // Print the TDS value to the serial monitor
  Serial.print("TDS Value: ");
  Serial.println(tdsValue);
 // Clear the LCD
  lcd.setCursor(12, 0); // Set cursor to first row, first column
  lcd.print("Tds:");
  lcd.setCursor(10, 0); 
  lcd.print("|");
  lcd.setCursor(10, 1);
  lcd.print("|");
  lcd.setCursor(11, 1);
  lcd.print(tdsValue);
 

  delay(50);

 lcd.setCursor(12, 0); // Set cursor to first row, first column
  lcd.print("Tds:");
  lcd.setCursor(10, 0); 
  lcd.print("|");
  lcd.setCursor(10, 1);
  lcd.print("|");
  lcd.setCursor(11, 1);
  lcd.print(tdsValue);
 

  delay(50);

  
}
