#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>

class LCD {
   public:
    void print(const char*, int line = 1);
    void clr();
    void init(int num = 0, int contrast = 12);
    void write(uint8_t, uint8_t);
    void printf(int, const char*, ...);
    LCD();

   private:
    const int LCD_ADRS = 0x3E;
    const int ONELINE = 1;
    const int TWOLINES = 0;
    const int DATA = 0x40;
    const int CMD = 0x00;
};