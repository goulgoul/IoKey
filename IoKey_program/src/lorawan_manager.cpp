#include <lorawan_manager.hpp>
#include <global_config.h>

LoRaWANManager::LoRaWANManager(void)
    : _device_eui(nullptr), _application_eui(nullptr), _application_key(nullptr), _hw_config()
{
    _device_eui = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        _device_eui[i] = 0x00;
    }

    _application_eui = new uint8_t[8];
    for (int i = 0; i < 8; i++)
    {
        _application_eui[i] = 0x00;
    }

    _application_key = new uint8_t[16];
    for (int i = 0; i < 16; i++)
    {
        _application_key[i] = 0x00;
    }
    
}

LoRaWANManager* LoRaWANManager::get_instance(void)
{
    if (_instance == nullptr)
    {
        _instance = new LoRaWANManager();
    }
    return _instance;
}

lorawan_manager_error_t LoRaWANManager::begin(const uint8_t dev_eui[8], const uint8_t app_eui[8], const uint8_t app_key[16])
{
    if (_instance == nullptr)
    {
        return NO_INSTANCE_INITIALISED;
    }
    for (int i = 0; i < 8; i++)
    {
        _device_eui[i] = dev_eui[i];
    }

    for (int i = 0; i < 8; i++)
    {
        _application_eui[i] = app_eui[i];
    }

    for (int i = 0; i < 16; i++)
    {
        _application_key[i] = app_key[i];
    }

	// Define the HW configuration between MCU and SX126x
	_hw_config.CHIP_TYPE = SX1262_CHIP;	// Example uses an eByte E22 module with an SX1262
	_hw_config.PIN_LORA_RESET = LORA_RESET; // LORA RESET
	_hw_config.PIN_LORA_NSS = LORA_NSS;	  // LORA SPI CS
	_hw_config.PIN_LORA_SCLK = LORA_SCLK;	  // LORA SPI CLK
	_hw_config.PIN_LORA_MISO = LORA_MISO;	  // LORA SPI MISO
	_hw_config.PIN_LORA_DIO_1 = LORA_DIO_1; // LORA DIO_1
	_hw_config.PIN_LORA_BUSY = LORA_BUSY;	  // LORA SPI BUSY
	_hw_config.PIN_LORA_MOSI = LORA_MOSI;	  // LORA SPI MOSI
	_hw_config.USE_DIO2_ANT_SWITCH = false;	// LORA DIO2 does not control antenna
	_hw_config.USE_DIO3_TCXO = true;	// LORA DIO3 controls oscillator voltage (e.g. eByte E22 module)
	_hw_config.USE_DIO3_ANT_SWITCH = false;	// LORA DIO3 does not control antenna

    // Initialize LoRa chip.
	uint32_t err_code = lora_hardware_init(_hw_config);
	if (err_code != 0)
	{
        return SX1262_INIT_ERROR;
	}

    // Setup the EUIs and Keys
	lmh_setDevEui(_device_eui);
	lmh_setAppEui(_application_eui);
	lmh_setAppKey(_application_key);

    err_code = lmh_init(&lora_callbacks, lora_param_init, OTAA_ENABLED, CLASS_A, LORAWAN_REGION_IOKEY);
	if (err_code != 0)
	{
		Serial.printf("lmh_init failed - %d\n", err_code);
        return SX1262_INIT_ERROR;

	}

    lmh_setSubBandChannels(2);


    return OKAY;
}

void LoRaWANManager::print_parameters(void)
{
    Serial.print("Device EUI: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_device_eui[i], HEX);
    }
    Serial.print('\n');

    Serial.print("Application EUI: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_application_eui[i], HEX);
    }
    Serial.print('\n');

    Serial.print("Application key: ");
    for (int i = 0; i < 8; i++)
    {
        Serial.print(_application_key[i], HEX);
    }
    Serial.print('\n');
}

lorawan_manager_error_t LoRaWANManager::join(void)
{
    Serial.println("Attempting to join TTN...");
    lmh_join();
    lmh_class_request(CLASS_A);


    int join_counter = 0;

	while (lmh_join_status_get() != LMH_SET)
	{
        join_counter++;
        if (join_counter >= LORAWAN_JOIN_TIMEOUT_S)
        {
            return JOINING_TIMEOUT;
        }
		delay(1000);
	}


    return OKAY;
}

lorawan_manager_error_t LoRaWANManager::send_data(const uint8_t data[LORAWAN_FRAME_LENGTH], const uint8_t frame_length)
{
    Serial.println("Attempting to send data...");
    // Building the message to send
    uint8_t lorawan_frame_buffer[LORAWAN_APP_DATA_BUFF_SIZE]; // Lora user application data buffer.
    lmh_app_data_t lorawan_frame_struct = {lorawan_frame_buffer, 0, 0, 0, 0};	 // Lora user application data structure.

	lorawan_frame_struct.port = LORAWAN_APP_PORT;
    for (int i = 0; i < frame_length; i++)
    {
        lorawan_frame_struct.buffer[i] = data[i];
    }
    lorawan_frame_struct.buffsize = frame_length;



	lmh_error_status error = lmh_send(&lorawan_frame_struct, LMH_UNCONFIRMED_MSG);
    if (error == LMH_ERROR)
    {
        return FRAME_NOT_SENT;
    }

    return OKAY;
}





LoRaWANManager::~LoRaWANManager()
{
    _device_eui = NULL;
    _application_eui = NULL;
    _application_key = NULL;

    delete[] _device_eui;
    delete[] _application_eui;
    delete[] _application_key;
}