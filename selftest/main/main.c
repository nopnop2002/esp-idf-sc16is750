/* The example of SC16IS750
 *
 * This code is in the public domain.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "sc16is750.h"

#define TAG "MAIN"

void single_channel(void *pvParameters)
{
	SC16IS750_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is I2C");
	ESP_LOGI(TAG, "CONFIG_I2C_ADDRESS=0x%x",CONFIG_I2C_ADDRESS);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, CONFIG_I2C_ADDRESS, SC16IS750_SINGLE_CHANNEL);
	SC16IS750_i2c(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d",CONFIG_MISO_GPIO);
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, CONFIG_CS_GPIO, SC16IS750_SINGLE_CHANNEL);
	SC16IS750_spi(&dev, CONFIG_MOSI_GPIO, CONFIG_MISO_GPIO, CONFIG_SCLK_GPIO);
#endif // CONFIG_SPI_INTERFACE

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_CHANNEL_NONE, 14745600UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	while(1) {
		SC16IS750_write(&dev, SC16IS750_CHANNEL, 0x55);
		delay(20); // same as vTaskDelay(2)

		if (SC16IS750_available(&dev, SC16IS750_CHANNEL)==0) {
			ESP_LOGE(TAG, "serial communication error 1");
			break;
		}
		if (SC16IS750_read(&dev, SC16IS750_CHANNEL)!=0x55) {
			ESP_LOGE(TAG, "serial communication error 2");
			break;
		}	
		delay(200);

		SC16IS750_write(&dev, SC16IS750_CHANNEL, 0xAA);
		delay(20); // same as vTaskDelay(2)

		if (SC16IS750_available(&dev, SC16IS750_CHANNEL)==0) {
			ESP_LOGE(TAG, "serial communication error 3");
			break;
		}
		if (SC16IS750_read(&dev, SC16IS750_CHANNEL)!=0xAA) {
			ESP_LOGE(TAG, "serial communication error 4");
			break;
		}	
		delay(200);
	}
	vTaskDelete(NULL);
}

void dual_channel(void *pvParameters)
{
	SC16IS750_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is I2C");
	ESP_LOGI(TAG, "CONFIG_I2C_ADDRESS=0x%x",CONFIG_I2C_ADDRESS);
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_I2C, CONFIG_I2C_ADDRESS, SC16IS750_DUAL_CHANNEL);
	SC16IS750_i2c(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_MISO_GPIO=%d",CONFIG_MISO_GPIO);
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	SC16IS750_init(&dev, SC16IS750_PROTOCOL_SPI, CONFIG_CS_GPIO, SC16IS750_DUAL_CHANNEL);
	SC16IS750_spi(&dev, CONFIG_MOSI_GPIO, CONFIG_MISO_GPIO, CONFIG_SCLK_GPIO);
#endif // CONFIG_SPI_INTERFACE

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, SC16IS750_DEFAULT_SPEED, SC16IS750_DEFAULT_SPEED, 1843200UL); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	while(1) {
		SC16IS750_write(&dev, SC16IS750_CHANNEL_A, 0x55);
		delay(20); // same as vTaskDelay(2)

		if (SC16IS750_available(&dev, SC16IS750_CHANNEL_B)==0) {
			ESP_LOGE(TAG, "serial communication error 1");
			break;
		}
		if (SC16IS750_read(&dev, SC16IS750_CHANNEL_B)!=0x55) {
			ESP_LOGE(TAG, "serial communication error 2");
			break;
		}	
		delay(200);

		SC16IS750_write(&dev, SC16IS750_CHANNEL_B, 0xAA);
		delay(20); // same as vTaskDelay(2)

		if (SC16IS750_available(&dev, SC16IS750_CHANNEL_A)==0) {
			ESP_LOGE(TAG, "serial communication error 3");
			break;
		}
		if (SC16IS750_read(&dev, SC16IS750_CHANNEL_A)!=0xAA) {
			ESP_LOGE(TAG, "serial communication error 4");
			break;
		}	
		delay(200);
	}
	vTaskDelete(NULL);
}

void app_main()
{
#if CONFIG_SINGLE_CHANNEL
	ESP_LOGI(TAG, "UART is SINGLE CHANNEL");
	xTaskCreate(&single_channel, "SINGLE", 1024*2, NULL, 2, NULL);
#else
	ESP_LOGI(TAG, "UART is DUAL CHANNEL");
	xTaskCreate(&dual_channel, "DUAL", 1024*2, NULL, 2, NULL);
#endif

}
