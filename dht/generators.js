Blockly.JavaScript['dht_init'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var dropdown_type = block.getFieldValue('type');
	return 'DEV_IO.DHT(' + dropdown_pin + ').init(' + dropdown_type + ');';
};

Blockly.JavaScript['dht_get_humidity'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.DHT(' + dropdown_pin + ').getHumidity()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['dht_get_temperature'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.DHT(' + dropdown_pin + ').getTemperature()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
