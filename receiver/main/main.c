/* The example of SC16IS750
 *
 * This code is in the public domain.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "sc16is750.h"

#define TAG "MAIN"

#if CONFIG_INPUT_END_CHARACTER
void character(void *pvParameters)
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

	ESP_LOGI(TAG, "Character at the end of input is 0x%02X", CONFIG_END_CHARACTER);
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
			if (c == CONFIG_END_CHARACTER) {
				ESP_LOGI(TAG, "[CH_A] %s",buffer_A);
				index_A = 0;
			} else {
				if (index_A < sizeof(buffer_A)-1) {
					buffer_A[index_A++] = c;
					buffer_A[index_A] = 0;
				}
			}
		}

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
			if (c == CONFIG_END_CHARACTER) {
				ESP_LOGI(TAG, "[CH_B] %s",buffer_B);
				index_B = 0;
			} else {
				if (index_B < sizeof(buffer_B)-1) {
					buffer_B[index_B++] = c;
					buffer_B[index_B] = 0;
				}
			}
		}
#endif
		delay(10); // same as vTaskDelay(1)
	} // end while
	vTaskDelete(NULL);
}
#endif // CONFIG_INPUT_END_CHARACTER

#if CONFIG_INPUT_END_TIMEOUT
void timeout(void *pvParameters)
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

	ESP_LOGI(TAG, "Time-out millisecond at the end of input is %d", CONFIG_END_TIMEOUT);
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

	SC16IS750_setTimeout(&dev, CONFIG_END_TIMEOUT);

	int16_t c;
	uint8_t channel;
	while(1) {
		c = SC16IS750_readwithtimeout(&dev, &channel);
#if 0
		printf("SC16IS750_readwithtimeout=%d %d\n", c, channel);
#endif
		if (c != -1) {
			if (channel == SC16IS750_CHANNEL_A) {
				if (index_A < sizeof(buffer_A)-1) {
					buffer_A[index_A++] = c;
					buffer_A[index_A] = 0;
				}
#if CONFIG_DUAL_CHANNEL
			} else {
				if (index_B < sizeof(buffer_B)-1) {
					buffer_B[index_B++] = c;
					buffer_B[index_B] = 0;
				}
#endif
			}
		} else {
			ESP_LOGI(TAG, "[CH_A] %s",buffer_A);
			index_A = 0;
			buffer_A[0] = 0;
#if CONFIG_DUAL_CHANNEL
			ESP_LOGI(TAG, "[CH_B] %s",buffer_B);
			index_B = 0;
			buffer_B[0] = 0;
#endif
		}
	} // end while
	vTaskDelete(NULL);
}
#endif // CONFIG_INPUT_END_TIMEOUT

void app_main()
{
#if CONFIG_INPUT_END_CHARACTER
	ESP_LOGI(TAG, "Input ends with a specific character");
	xTaskCreate(&character, "CHARACTER", 1024*4, NULL, 2, NULL);
#else
	ESP_LOGI(TAG, "Input ends with a timeout");
	xTaskCreate(&timeout, "TIMEOUT", 1024*4, NULL, 2, NULL);
#endif

}
