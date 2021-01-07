#include <Arduino_LSM9DS1.h>

char wake_key = 'A';

void setup()
{
	// Initialise Serial communication
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Started serial communication");

	// Initialise IMU
	if(!IMU.begin()){
		Serial.println("Failed to start IMU!");
		while(1);
	}

	pinMode(LED_BUILTIN, OUTPUT);

	// Serial.print("Accelerometer sample rate = ");
	// Serial.print(IMU.accelerationSampleRate());
	// Serial.println(" Hz");

	Serial.println("X\tY\tZ");
}

void loop()
{
	if(Serial.available()){
		char input = Serial.read();
		if(input == wake_key)
			read_imu();
	}
}


// Record 100 samples for approx. 4 sec
void read_imu()
{
	float x, y, z;
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.print("\n\n\n\n\n\n");
	Serial.println("-, -, -");

	for(int i=0; i < 100; i++){
		if(IMU.accelerationAvailable()){
			IMU.readAcceleration(x, y, z);
			Serial.print(x);
			Serial.print('\t');
			Serial.print(y);
			Serial.print('\t');
			Serial.println(z);
			delay(40);
		}
	}
	digitalWrite(LED_BUILTIN, LOW);
}
