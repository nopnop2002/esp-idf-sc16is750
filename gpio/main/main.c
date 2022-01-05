/* The example of SC16IS750
 *
 * This code is in the public domain.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/gpio.h"

#include "sc16is750.h"

#define TAG "MAIN"

// global stuff
bool isInterrupt = false;

#if CONFIG_GPIO_OUTPUT
void output(void *pvParameters)
{
#if CONFIG_SINGLE_CHANNEL
	ESP_LOGI(TAG, "UART is SINGLE CHANNEL");
	int channels = SC16IS750_SINGLE_CHANNEL;
	long crystal_freq = 14745600UL;
#else
	ESP_LOGI(TAG, "UART is DUAL CHANNEL");
	int channels = SC16IS750_DUAL_CHANNEL;
	long crystal_freq = 1843200UL;
#endif

	SC16IS750_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is I2C");
	ESP_LOGI(TAG, "CONFIG_I2C_ADDRESS=0x%x",CONFIG_I2C_ADDRESS);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, CONFIG_I2C_ADDRESS, channels);
	SC16IS750_i2c(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d",CONFIG_MISO_GPIO);
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, CONFIG_CS_GPIO, channels);
	SC16IS750_spi(&dev, CONFIG_MOSI_GPIO, CONFIG_MISO_GPIO, CONFIG_SCLK_GPIO);
#endif // CONFIG_SPI_INTERFACE

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_CHANNEL_NONE, crystal_freq); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	ESP_LOGI(TAG, "CONFIG_SC16IS750_GPIO=%d",CONFIG_SC16IS750_GPIO);
	int gpio = CONFIG_SC16IS750_GPIO;
	SC16IS750_pinMode(&dev, gpio, OUTPUT);

	while (1) {
		SC16IS750_digitalWrite(&dev, gpio, HIGH);
		delay(1000);
		SC16IS750_digitalWrite(&dev, gpio, LOW);
		delay(1000);
	}
	vTaskDelete(NULL);
}
#endif // CONFIG_GPIO_OUTPUT


#if CONFIG_GPIO_INPUT
void input(void *pvParameters)
{
#if CONFIG_SINGLE_CHANNEL
	ESP_LOGI(TAG, "UART is SINGLE CHANNEL");
	int channels = SC16IS750_SINGLE_CHANNEL;
	long crystal_freq = 14745600UL;
#else
	ESP_LOGI(TAG, "UART is DUAL CHANNEL");
	int channels = SC16IS750_DUAL_CHANNEL;
	long crystal_freq = 1843200UL;
#endif

	SC16IS750_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is I2C");
	ESP_LOGI(TAG, "CONFIG_I2C_ADDRESS=0x%x",CONFIG_I2C_ADDRESS);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, CONFIG_I2C_ADDRESS, channels);
	SC16IS750_i2c(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d",CONFIG_MISO_GPIO);
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, CONFIG_CS_GPIO, channels);
	SC16IS750_spi(&dev, CONFIG_MOSI_GPIO, CONFIG_MISO_GPIO, CONFIG_SCLK_GPIO);
#endif // CONFIG_SPI_INTERFACE

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_CHANNEL_NONE, crystal_freq); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	ESP_LOGI(TAG, "CONFIG_SC16IS750_GPIO=%d",CONFIG_SC16IS750_GPIO);
	int gpio = CONFIG_SC16IS750_GPIO;
	SC16IS750_pinMode(&dev, gpio, INPUT);

	while (1) {
		uint8_t value = SC16IS750_digitalRead(&dev, gpio);
		ESP_LOGI(TAG, "value=%d", value);
		delay(500);
	}
	vTaskDelete(NULL);
}
#endif // CONFIG_GPIO_INPUT

#if CONFIG_GPIO_INTERRUPT
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
	//uint32_t gpio_num = (uint32_t) arg;
	isInterrupt = true;
}

#define ESP_INTR_FLAG_DEFAULT 0

void interrupt(void *pvParameters)
{
#if CONFIG_SINGLE_CHANNEL
	ESP_LOGI(TAG, "UART is SINGLE CHANNEL");
	int channels = SC16IS750_SINGLE_CHANNEL;
	long crystal_freq = 14745600UL;
#else
	ESP_LOGI(TAG, "UART is DUAL CHANNEL");
	int channels = SC16IS750_DUAL_CHANNEL;
	long crystal_freq = 1843200UL;
#endif

	SC16IS750_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is I2C");
	ESP_LOGI(TAG, "CONFIG_I2C_ADDRESS=0x%x",CONFIG_I2C_ADDRESS);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, CONFIG_I2C_ADDRESS, channels);
	SC16IS750_i2c(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d",CONFIG_MISO_GPIO);
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, CONFIG_CS_GPIO, channels);
	SC16IS750_spi(&dev, CONFIG_MOSI_GPIO, CONFIG_MISO_GPIO, CONFIG_SCLK_GPIO);
#endif // CONFIG_SPI_INTERFACE

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_CHANNEL_NONE, crystal_freq); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	ESP_LOGI(TAG, "CONFIG_IRQ_GPIO=%d",CONFIG_IRQ_GPIO);
	//zero-initialize the config structure.
	gpio_config_t io_conf = {};
	//interrupt of rising edge
	io_conf.intr_type = GPIO_INTR_ANYEDGE;
	//bit mask of the pins, use GPIO4/5 here
	io_conf.pin_bit_mask = (1ULL<<CONFIG_IRQ_GPIO);
	//set as input mode
	io_conf.mode = GPIO_MODE_INPUT;
	//enable pull-up mode
	io_conf.pull_up_en = 1;
	//configure GPIO with the given settings
	gpio_config(&io_conf);

	//install gpio isr service
	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	//hook isr handler for specific gpio pin
	gpio_isr_handler_add(CONFIG_IRQ_GPIO, gpio_isr_handler, (void*)CONFIG_IRQ_GPIO);

	ESP_LOGI(TAG, "CONFIG_SC16IS750_GPIO=%d",CONFIG_SC16IS750_GPIO);
	int gpio = CONFIG_SC16IS750_GPIO;
	SC16IS750_pinMode(&dev, gpio, INPUT);
	SC16IS750_SetPinInterrupt(&dev, 0xff);

	while (1) {
		if (isInterrupt) {
			int16_t event = SC16IS750_InterruptEventTest(&dev, SC16IS750_CHANNEL_BOTH);

			if (event == SC16IS750_INPUT_PIN_CHANGE_STATE) {
				uint8_t value = SC16IS750_digitalRead(&dev, gpio);
				ESP_LOGI(TAG, "value=%d", value);
			}
			isInterrupt = false;
		}
		delay(10);
	}
	vTaskDelete(NULL);
}
#endif // CONFIG_GPIO_INTERRUPT


void app_main()
{
#if CONFIG_GPIO_OUTPUT
	ESP_LOGI(TAG, "GPIO is OUTPUT");
	xTaskCreate(&output, "OUTPUT", 1024*2, NULL, 2, NULL);
#elif CONFIG_GPIO_INPUT
	ESP_LOGI(TAG, "GPIO is INPUT using polling");
	xTaskCreate(&input, "INPUT", 1024*2, NULL, 2, NULL);
#elif CONFIG_GPIO_INTERRUPT
	ESP_LOGI(TAG, "GPIO is INPUT using interruptL");
	xTaskCreate(&interrupt, "INTERRUPT", 1024*2, NULL, 2, NULL);
#endif

}
