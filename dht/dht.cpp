#include "esp_system.h"
#include "kidbright32.h"
#include "dht.h"

static const char* TAG = "DHT";

DHT::DHT(int pin) {
	this->dht_pin = pin;

	error = false;
	initialized = true;
}

void DHT::init(void) {
	error = false;
	initialized = true;

	tickcnt = get_tickcnt();

	esp_log_level_set("*", ESP_LOG_INFO);
}

int DHT::prop_count(void) {
	// not supported
	return 0;
}

bool DHT::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool DHT::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool DHT::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool DHT::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool DHT::prop_write(int index, char *value) {
	// not supported
	return false;
}

void DHT::process(Driver *drv) {
	if (is_tickcnt_elapsed(tickcnt, 500)) {
		vTaskSuspendAll();
		if (this->readDHT() != DHT_OK) {
			this->humidity = 999;
			this->temperature = 999;
		}
		xTaskResumeAll();

		// get current tickcnt
		tickcnt = get_tickcnt();
	}
}

float DHT::getHumidity() {
	return this->humidity;
}

float DHT::getTemperature() {
	return this->temperature;
}

int DHT::getSignalLevel(int usTimeOut, bool state) {
	int uSec = 0;
	while (gpio_get_level((gpio_num_t)this->dht_pin) == state) {
		if(uSec > usTimeOut) return -1;
		
		++uSec;
		ets_delay_us(1);		// uSec delay
	}
	
	return uSec;
}

int DHT::readDHT() {
	ESP_LOGI( TAG, "Start DHT");

	int uSec = 0;

	uint8_t dhtData[5];
	uint8_t byteInx = 0;
	uint8_t bitInx = 7;

	memset(dhtData, 0, 5);

	// == Send start signal to DHT sensor ===========

	gpio_set_direction((gpio_num_t)this->dht_pin, GPIO_MODE_OUTPUT);

	// pull down for 3 ms for a smooth and nice wake up 
	gpio_set_level((gpio_num_t)this->dht_pin, 0);
	ets_delay_us(3000);			

	// pull up for 25 us for a gentile asking for data
	gpio_set_level((gpio_num_t)this->dht_pin, 1);
	ets_delay_us(25);

	gpio_set_direction((gpio_num_t)this->dht_pin, GPIO_MODE_INPUT);		// change to input mode
	// gpio_set_pull_mode((gpio_num_t)this->dht_pin, GPIO_PULLUP_ONLY);
  
	// == DHT will keep the line low for 80 us and then high for 80us ====

    // Wait Start
	uSec = getSignalLevel(20000, 1);
	ESP_LOGI(TAG, "Response HIGH wait start bit = %d", uSec );
	if(uSec < 0) return DHT_TIMEOUT_ERROR; 

	uSec = getSignalLevel(200, 0);
	ESP_LOGI(TAG, "Response LOW = %d", uSec );
	if(uSec < 0) return DHT_TIMEOUT_ERROR; 

	// -- 80us up ------------------------

	uSec = getSignalLevel(200, 1);
	ESP_LOGI(TAG, "Response HIGH = %d", uSec );
	if(uSec < 0) return DHT_TIMEOUT_ERROR;

	// == No errors, read the 40 data bits ================
  
	for( int k = 0; k < 40; k++ ) {

		// -- starts new data transmission with >50us low signal

		uSec = getSignalLevel(100, 0);
		if(uSec < 0) return DHT_TIMEOUT_ERROR;

		// -- check to see if after >70us rx data is a 0 or a 1

		uSec = getSignalLevel(200, 1);
		if(uSec < 0) return DHT_TIMEOUT_ERROR;

		// add the current read to the output data
		// since all dhtData array where set to 0 at the start, 
		// only look for "1" (>28us us)
	
		if (uSec > 40) {
			dhtData[ byteInx ] |= (1 << bitInx);
			}
	
		// index to next byte

		if (bitInx == 0) { bitInx = 7; ++byteInx; }
		else bitInx--;
	}

	// == get humidity from Data[0] and Data[1] ==========================

	this->humidity = dhtData[0];
	// humidity *= 0x100;					// >> 8
	// humidity += dhtData[1];
	// humidity /= 10;						// get the decimal

	// == get temp from Data[2] and Data[3]
	
	this->temperature = dhtData[2] & 0x7F;	
	// temperature *= 0x100;				// >> 8
	// temperature += dhtData[3];
	// temperature /= 10;

	if(dhtData[2] & 0x80) 			// negative temp, brrr it's freezing
		this->temperature *= -1;


	ESP_LOGI( TAG, "Data 0 = %d", dhtData[0] );
	ESP_LOGI( TAG, "Data 1 = %d", dhtData[1] );
	ESP_LOGI( TAG, "Data 2 = %d", dhtData[2] );
	ESP_LOGI( TAG, "Data 3 = %d", dhtData[3] );
	ESP_LOGI( TAG, "Data 4 = %d", dhtData[4] );


	// == verify if checksum is ok ===========================================
	// Checksum is the sum of Data 8 bits masked out 0xFF
	
	if (dhtData[4] == ((dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]) & 0xFF)) 
		return DHT_OK;

	else 
		return DHT_CHECKSUM_ERROR;
}
