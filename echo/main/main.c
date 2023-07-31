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
#if CONFIG_MODEL_SC16IS750
	ESP_LOGI(TAG, "Your module is SC16IS750");
	int channels = SC16IS750_SINGLE_CHANNEL;
	long crystal_freq = 14745600UL;
	uint32_t baud_A = CONFIG_BAUDRATE1;
	uint32_t baud_B = SC16IS750_CHANNEL_NONE;
#else
	ESP_LOGI(TAG, "Your module is SC16IS752");
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
#if CONFIG_MODEL_SC16IS752
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

#if CONFIG_AUTO_RS1
	ESP_LOGI(TAG, "CHANNEL_A is Auto RS-485 RTS control");
#if CONFIG_INVERT_RS1
	ESP_LOGI(TAG, "CHANNEL_A is WITH_INVERT_RTS_SIGNAL");
	SC16IS750_EnableRs485(&dev, SC16IS750_CHANNEL_A, WITH_INVERT_RTS_SIGNAL);
#else
	ESP_LOGI(TAG, "CHANNEL_A is NO_INVERT_RTS_SIGNAL");
	SC16IS750_EnableRs485(&dev, SC16IS750_CHANNEL_A, NO_INVERT_RTS_SIGNAL);
#endif // CONFIG_INVERT_RS1
#endif // CONFIG_AUTO_RS1

#if CONFIG_MODEL_SC16IS752
#if CONFIG_AUTO_RS2
	ESP_LOGI(TAG, "CHANNEL_B is Auto RS-485 RTS control");
#if CONFIG_INVERT_RS2
	ESP_LOGI(TAG, "CHANNEL_B is WITH_INVERT_RTS_SIGNAL");
	SC16IS750_EnableRs485(&dev, SC16IS750_CHANNEL_B, WITH_INVERT_RTS_SIGNAL);
#else
	ESP_LOGI(TAG, "CHANNEL_A is NO_INVERT_RTS_SIGNAL");
	SC16IS750_EnableRs485(&dev, SC16IS750_CHANNEL_B, NO_INVERT_RTS_SIGNAL);
#endif // CONFIG_INVERT_RS2
#endif // CONFIG_AUTO_RS2
#endif // CONFIG_MODEL_SC16IS752


	char buffer_A[64] = {0};
	int index_A = 0;
#if CONFIG_MODEL_SC16IS752
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
				if (c != 0) {
					buffer_A[index_A++] = (c);
					buffer_A[index_A] = 0;
				}
			}
		} else {
			if (index_A != 0) ESP_LOGI(TAG, "buffer_A=[%s]", buffer_A);
			for (int i=0;i<index_A;i++) {
				if (isupper((int)buffer_A[i])) {
					buffer_A[i] = tolower(buffer_A[i]);
				} else {
					buffer_A[i] = toupper(buffer_A[i]);
				}
				SC16IS750_write(&dev, SC16IS750_CHANNEL_A, buffer_A[i]);
			}
			buffer_A[0] = 0;
			index_A = 0;

			// Wait for transmission to complete
			while(1) {
				uint8_t state = SC16IS750_linestate(&dev, SC16IS750_CHANNEL_A);
				if ( (state & 0x40) == 0x40) break; // THR and TSR empty.
				ESP_LOGI(TAG, "Channel_A state=0x%02X", state);
				vTaskDelay(1);
			} // end while

		} // end CHENNEL_A

#if CONFIG_MODEL_SC16IS752
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
				if (c != 0) {
					buffer_B[index_B++] = (c);
					buffer_B[index_B] = 0;
				}
			}
		} else {
			if (index_B != 0) ESP_LOGI(TAG, "buffer_B=[%s]", buffer_B);
			for (int i=0;i<index_B;i++) {
				if (isupper((int)buffer_B[i])) {
					buffer_B[i] = tolower(buffer_B[i]);
				} else {
					buffer_B[i] = toupper(buffer_B[i]);
				}
				SC16IS750_write(&dev, SC16IS750_CHANNEL_B, buffer_B[i]);
			}
			buffer_B[0] = 0;
			index_B = 0;

			// Wait for transmission to complete
			while(1) {
				uint8_t state = SC16IS750_linestate(&dev, SC16IS750_CHANNEL_B);
				if ( (state & 0x40) == 0x40) break; // THR and TSR empty.
				ESP_LOGI(TAG, "Channel_B state=0x%02X", state);
				vTaskDelay(1);
			} // end while

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
