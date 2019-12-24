#ifndef __DHT_PLUGIN_H__
#define __DHT_PLUGIN_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>
#include <string.h>

#define DHT_OK 0
#define DHT_CHECKSUM_ERROR -1
#define DHT_TIMEOUT_ERROR -2

class DHT : public Device {
	private:
		uint8_t dht_pin = 0;
		uint8_t type = 11;

		float humidity = 0.0;
		float temperature = 0.0;

		int getSignalLevel(int usTimeOut, bool state) ;
		int readDHT() ;

	public:
		TickType_t tickcnt;

		// constructor
		DHT(int pin);

		// override
		void init(void) ;
		void init(uint8_t type) ;
		void process(Driver *drv) ;
		int prop_count(void) ;
		bool prop_name(int index, char *name) ;
		bool prop_unit(int index, char *unit) ;
		bool prop_attr(int index, char *attr) ;
		bool prop_read(int index, char *value) ;
		bool prop_write(int index, char *value) ;

		// method
		float getHumidity() ;
		float getTemperature() ;
};

#endif
