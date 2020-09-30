#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "inttypes.h"
#include <stdlib.h>
#include <driver/adc.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/queue.h"
#include "sdkconfig.h"
#include <esp_types.h>
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"
//#include "gds.c"
//#include "gds_text.c"
//#include "gds_image.c"
//#include "gds_font.c"
//#include "gds_draw.c"
//#include "SSD132x.c"
//#include "default_if_i2c.c"
//#include "default_if_spi.c"
//#include "font_droid_sans_fallback_15x17.c"
//#include "Font_line_2.c"
//#include "Font_droid_sans_fallback_11x13.c"
//#include "Font_line_1.c"


#define GPIO_INPUT_0	4
#define GPIO_INPUT_1	2
#define SDA_PIN			21
#define SCL_PIN			22



static char tag[] = "adc1";
int counter = 0;

int getJoystick(){
			int xvalue = adc1_get_raw(ADC1_CHANNEL_7);
			int yvalue = adc1_get_raw(ADC1_CHANNEL_6);
			ESP_LOGD(tag, "xvalue: %d", xvalue);
			printf("xvalue: %d\n", xvalue);
			ESP_LOGD(tag, "yvalue: %d", yvalue);
			printf("yvalue: %d\n", yvalue);
			return 0;

}

int getButtonState(){
		int buttonState = gpio_get_level(GPIO_INPUT_0);
		printf("button state: %d\n", buttonState);
		return 0;
}

int getSwitchState(){
		int switchState = gpio_get_level(GPIO_INPUT_1);
		printf("switch state: %d\n\n\n\n", switchState);
		return 0;
}

void app_main(void){
	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, ESP_INTR_FLAG_LEVEL6);
	i2c_set_pin(I2C_NUM_0, SDA_PIN, SCL_PIN, 1, 1, I2C_MODE_MASTER);
	i2c_cmd_handle_t cmd_handle = i2c_cmd_link_create();
	i2c_master_start(cmd_handle);
	i2c_master_write_byte(cmd_handle, '3', 1);
	i2c_master_stop(cmd_handle);
	i2c_master_cmd_begin(I2C_NUM_0, cmd_handle, 4);
	ESP_LOGD(tag, "adc1");
	adc1_config_width(ADC_WIDTH_12Bit);
	adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_11db);
	adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_11db);
	//int sda_io_num = SDA_PIN;
	//int scl_io_num = SCL_PIN;

	while(1){
		getJoystick();
		getButtonState();
		getSwitchState();
		vTaskDelay(20/portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

#ifdef __cplusplus
}
#endif
