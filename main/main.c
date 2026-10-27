#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_intsup.h>
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "hal/adc_types.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_oneshot.h"
#include "MLP.h"

#define ADC_CHANNEL_VP  ADC_CHANNEL_0
#define ADC_CHANNEL_VN  ADC_CHANNEL_3

//Leds bitmask
adc_oneshot_unit_handle_t adc1;

static const char *TAG = "MAIN";

static void init_gpio()
{
    //Initialice ADC
    adc_oneshot_unit_init_cfg_t init = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_new_unit(&init, &adc1);
    
    adc_oneshot_chan_cfg_t channel = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    adc_oneshot_config_channel(adc1, ADC_CHANNEL_VP, &channel);
    adc_oneshot_config_channel(adc1, ADC_CHANNEL_VN, &channel);

}
static bool get_entrance_1()
{
    //Gets POT#1 lecture
    int lecture;
    bool IN;
    adc_oneshot_read(adc1, ADC_CHANNEL_VP, &lecture);

    if(lecture < 2048)
    {
        IN = 0;
    }
    if(lecture >= 2048)
    {
        IN = 1;
    }
    ESP_LOGI(TAG, "Entrada 1: %d",lecture);
    return IN;
}
static bool get_entrance_2()
{
    //Gets POT#2 lecture
    int lecture;
    bool IN;
    adc_oneshot_read(adc1, ADC_CHANNEL_VN, &lecture);

    if(lecture < 2048)
    {
        IN = 0;
    }
    if(lecture >= 2048)
    {
        IN = 1;
    }
    ESP_LOGI(TAG, "Entrada 2: %d",lecture);
    return IN;
}

void app_main(void)
{
    init_gpio();
    while(1)
    {
        printf("\033[2J\033[H");   // borra la pantalla y pone el cursor arriba
        uint32_t IN1 = get_entrance_1();
        uint32_t IN2 = get_entrance_2();
        //Calls component function of the MLP
        process(IN1, IN2);
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}