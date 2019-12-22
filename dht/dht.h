#ifndef __DHT_PLUGIN_H__
#define __DHT_PLUGIN_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "DHT22_lib.h"
#include "esp_log.h"

class DHT : public Device {
	private:
		int dht_pin = 0;

		float humidity = 0.0;
		float temperature = 0.0;

	public:
		TickType_t tickcnt;

		// constructor
		DHT(int pin);

		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);

		// method
		float getHumidity();
		float getTemperature();
};

#endif
