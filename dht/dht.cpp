#include "esp_system.h"
#include "kidbright32.h"
#include "dht.h"

DHT::DHT(int pin) {
	this->dht_pin = pin;

	error = false;
	initialized = true;
}

void DHT::init(void) {
	error = false;
	initialized = true;

	tickcnt = get_tickcnt();
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
		setDHTgpio(this->dht_pin);

		if (readDHT() == DHT_OK) {
			this->humidity = getHumidity();
			this->temperature = getTemperature();
		} else {
			this->humidity = 999;
			this->temperature = 999;
		}

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

