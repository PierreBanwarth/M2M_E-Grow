    // Hardware requirement
// Soil http://dx.com/p/soil-humidity-moisture-detection-sensor-module-blue-black-white-200142
// DHT http://dx.com/p/arduino-digital-temperature-humidity-sensor-module-121350
// Photocell https://www.sparkfun.com/products/9088
// Extra sensors:
// http://air.imag.fr/index.php/SEN-08942
// http://dx.com/p/rain-raindrops-sensor-module-for-arduino-black-works-with-official-arduino-boards-228260

#include "DHT.h"

int SOIL_DIGITAL_PIN=2;
int SOIL_ANALOG_PIN=A0;  

int LIGHT_ANALOG_PIN=A1;

int DHT_PIN=4;

#define DHT_TYPE DHT11   // DHT 11 
//#define DHT_TYPE DHT22   // DHT 22  (AM2302)
//#define DHT_TYPE DHT21   // DHT 21 (AM2301)

// Connect middle pin of the sensor breadout to +5V
// Connect pin S of the sensor to whatever your DHTPIN is
// Connect pin - (on the right) of the sensor to GROUND

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
 
  pinMode(SOIL_DIGITAL_PIN, INPUT);
  dht.begin();
}

void loop() {

    Serial.print("-/soil/humidity ");
    Serial.print(map(analogRead(SOIL_ANALOG_PIN),200,1023,100,0));
//    Serial.print("/soil/alert ");
//    Serial.println(digitalRead(SOIL_DIGITAL_PIN));
    Serial.println();

  delay(1000);

  int lightSensorValue = analogRead(LIGHT_ANALOG_PIN);
  Serial.print("-/light/intensity ");
  Serial.print(map(lightSensorValue,0,1023,10,0));
  Serial.println();

  delay(1000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("-/error DHT");
  } else {
    Serial.print("-/air/humidity ");
    Serial.print(humidity);
    Serial.println();
    Serial.print("-/air/temperature ");
    Serial.print(temperature);
    Serial.println();
    Serial.print("-/air/dewpoint ");
    Serial.print(dewPoint(temperature, humidity));
    Serial.println();
  }
  delay(1000); 
}


// from http://arduino-info.wikispaces.com/DHT11-Humidity-TempSensor


/*-----( Declare User-written Functions )-----*/
//
//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
        return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
        return celsius + 273.15;
}

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm 
double dewPoint(double celsius, double humidity)
{
        double A0= 373.15/(273.15 + celsius);
        double SUM = -7.90298 * (A0-1);
        SUM += 5.02808 * log10(A0);
        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
        SUM += log10(1013.246);
        double VP = pow(10, SUM-3) * humidity;
        double T = log(VP/0.61078);   // temp var
        return (241.88 * T) / (17.558-T);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
        double a = 17.271;
        double b = 237.7;
        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
        double Td = (b * temp) / (a - temp);
        return Td;
}
