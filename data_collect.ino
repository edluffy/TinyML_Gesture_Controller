#include <PDM.h>

short sample_buf[256];

volatile int sample_cnt;

void setup()
{
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Started serial communication");

	PDM.onReceive(on_pdm);

	// 1 channel, 16kHz sample rate
	if (!PDM.begin(1, 16000)){
		Serial.println("Failed to start PDM!");
		while(1);
	}
}

void loop()
{
	if(sample_cnt){
		for(int i=0; i < sample_cnt; i++){
			Serial.println(sample_buf[i]);
		}
		sample_cnt = 0;
	}
}


void on_pdm()
{
	int bytes_avail = PDM.available();
	PDM.read(sample_buf, bytes_avail);
	sample_cnt = bytes_avail / 2;
}
