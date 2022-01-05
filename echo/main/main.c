/* The example of SC16IS750
 *
 * This code is in the public domain.
 */

#include <ctype.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "sc16is750.h"

#define TAG "MAIN"

void echo(void *pvParameters)
{
#if CONFIG_SINGLE_CHANNEL
	ESP_LOGI(TAG, "UART is SINGLE CHANNEL");
	int channels = SC16IS750_SINGLE_CHANNEL;
	long crystal_freq = 14745600UL;
	uint32_t baud_A = CONFIG_BAUDRATE1;
	uint32_t baud_B = SC16IS750_CHANNEL_NONE;
#else
	ESP_LOGI(TAG, "UART is DUAL CHANNEL");
	int channels = SC16IS750_DUAL_CHANNEL;
	long crystal_freq = 1843200UL;
	uint32_t baud_A = CONFIG_BAUDRATE1;
	uint32_t baud_B = CONFIG_BAUDRATE2;
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

	ESP_LOGI(TAG, "Communication speed of channel 1 is %d", CONFIG_BAUDRATE1);
#if CONFIG_DUAL_CHANNEL
	ESP_LOGI(TAG, "Communication speed of channel 2 is %d", CONFIG_BAUDRATE2);
#endif

	// SC16IS750 Initialization
	SC16IS750_begin(&dev, baud_A, baud_B, crystal_freq); //baudrate&frequency setting
	if (SC16IS750_ping(&dev)!=1) {
		ESP_LOGE(TAG, "device not found");
		while(1) { vTaskDelay(1); }
	} else {
		ESP_LOGI(TAG, "device found");
	}
	ESP_LOGI(TAG, "start serial communication");

	char buffer_A[64] = {0};
	int index_A = 0;
#if CONFIG_DUAL_CHANNEL
	char buffer_B[64] = {0};
	int index_B = 0;
#endif

	char c;
	while(1) {
		if (SC16IS750_available(&dev, SC16IS750_CHANNEL_A)) {
			c = SC16IS750_read(&dev, SC16IS750_CHANNEL_A);
#if 0
			if (c < 0x20) {
				printf("c_A= (0x%02x)\n",c);
			} else {
				printf("c_A=%c(0x%02x)\n",c,c);
			}
#endif
			if (index_A < sizeof(buffer_A)-1) {
				if (isupper(c)) {
					buffer_A[index_A++] = tolower(c);
				} else {
					buffer_A[index_A++] = toupper(c);
				}
				buffer_A[index_A] = 0;
			}
		} else {
			for (int i=0;i<index_A;i++) {
				SC16IS750_write(&dev, SC16IS750_CHANNEL_A, buffer_A[i]);
			}
			index_A = 0;
		} // end CHENNEL_A

#if CONFIG_DUAL_CHANNEL
		if (SC16IS750_available(&dev, SC16IS750_CHANNEL_B)) {
			c = SC16IS750_read(&dev, SC16IS750_CHANNEL_B);
#if 0
			if (c < 0x20) {
				printf("c_B= (0x%02x)\n",c);
			} else {
				printf("c_B=%c(0x%02x)\n",c,c);
			}
#endif
			if (index_B < sizeof(buffer_B)-1) {
				if (isupper(c)) {
					buffer_B[index_B++] = tolower(c);
				} else {
					buffer_B[index_B++] = toupper(c);
				}
				buffer_B[index_B] = 0;
			}
		} else {
			for (int i=0;i<index_B;i++) {
				SC16IS750_write(&dev, SC16IS750_CHANNEL_B, buffer_B[i]);
			}
			index_B = 0;
		} // end CHANNEL_B
#endif
		delay(10); // same as vTaskDelay(1)
	} // end while
	vTaskDelete(NULL);
}

void app_main()
{
	xTaskCreate(&echo, "ECHO", 1024*4, NULL, 2, NULL);
}
