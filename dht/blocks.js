Blockly.Blocks['dht_init'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.DHT_INIT_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.DHT_INIT_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['dht_get_humidity'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.DHT_GET_HUMIDITY_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}],
			"output": [
				"Number"
			],
			"colour": 180,
			"tooltip": Blockly.Msg.DHT_GET_HUMIDITY_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['dht_get_temperature'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.DHT_GET_TEMP_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}],
			"output": [
				"Number"
			],
			"colour": 180,
			"tooltip": Blockly.Msg.DHT_GET_TEMP_TOOLTIP,
			"helpUrl": ""
		});
	}
};


