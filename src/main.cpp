#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "lcd.h"
#include "i2c.h"

LCD lcd;

extern "C"{
    void app_main();
}

void app_main(){
    printf("BOOT\n");
    i2c.init(7,6);
    lcd.init();
    lcd.print("Hello, world!");
    printf("Hello, world!");
    while(1){
        vTaskDelay(1000);
    }
}