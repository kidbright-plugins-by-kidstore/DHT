#include "esp_system.h"
#include "kidbright32.h"
#include "dht.h"

DHT::DHT(int pin) {
	this->dht_pin = pin;

	error = false;
	initialized = true;
}

void DHT::init(void) {

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
		DHT_status ^= 0x01; // toggle status
		gpio_set_level(BT_LED_GPIO, DHT_status);
		// get current tickcnt
		tickcnt = get_tickcnt();
	}
}

void DHT::start(void) {
	DHT_status = 0;
	gpio_set_level(BT_LED_GPIO, DHT_status); // active low
	// get current tickcnt
	tickcnt = get_tickcnt();
	DHT_flag = true;
}

void DHT::stop(void) {
	DHT_flag = false;
	DHT_status = 1;
	gpio_set_level(BT_LED_GPIO, DHT_status); // active low
}
