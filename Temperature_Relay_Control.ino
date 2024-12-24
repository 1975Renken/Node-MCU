void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

#define aref_voltage 3.3 /*Reference Voltage*/

/*Temp & Humidity Pin Variables*/
int tempPin = 1; /*DHT11 Data Cable leading into ESP8622 module at pin D1*/
int tempReading; /* Temperature reading from DHT11 */
int humidReading; /*Humidity reading from DHT11 */

/*Relay Pin Variable*/
int relayPin = 0; /*Relay Data Cable leading into ESP8622 module at pin D0 */


/*Temperature Range*/
float maxTemperature = 84;
float minTemperature = 74;


void setup() {
  Serial.begin(115200); /* Allows to interface with Serial output module after 2minutes? */
  pinMode(relayPin, OUTPUT);
}

void loop() {
  float temperature = getTemperature();
  if(temperature >= maxTemperature) {
    powerOnRelay();
  } else if (temperature <= minTemperature) {
    powerOffRelay();
  }
  delay(1000); /*Checks temperature every second?*/
}

 void powerOnRelay() {
  digitalWrite(relayPin, HIGH);
  Serial.println("Current Flowing...Relay is on");
 }

 void powerOffRelay() {
  digitalWrite(relayPin, LOW);
  Serial.println("Current not flowing...Relay is off");
 }

 float getTemperature() {
  tempReading = analogRead(tempPin);
  float voltage = tempReading * aref_voltage;
  voltage /= 1024.0;

  float temperatureC = (voltage - 0.5)*100; /*converting from 10 mV per degree with 500 mV offset to degrees ((voltage - 500mV) x 100 */
  Serial.print(temperatureC);
  Serial.println("Degrees C"); /*Debugging Purposes */

  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF);
  Serial.println("Degrees F");

  return temperatureF;
 }
