#include "lcd.h"
#include "i2c.h"



const int Custom_Char5x8[] = {
    // 0x00, 通常は使わない
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x01
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x02
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x03
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x04
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x05
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x06
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    // 0x07
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000

};

LCD::LCD() {}

void LCD::write(uint8_t command, uint8_t t_data) {
  uint8_t cmd[2];
  cmd[0] = command;
  cmd[1] = t_data;
  i2c.write(LCD_ADRS,cmd,2);
  vTaskDelay(1/portTICK_PERIOD_MS);
}

void LCD::print(const char* c, int line) {
  this->write(CMD, 0x02);
  if (line == 2) {
    this->write(CMD, 0x40 + 0x80);
  }
  unsigned char i, str;
  for (i = 0; i < strlen(c); i++) {
    str = c[i];
    this->write(DATA, str);
  }
}

void LCD::clr() {
  this->write(CMD, 0x01);
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x02);
  vTaskDelay(1/portTICK_PERIOD_MS);
}

void LCD::init(int num, int contrast) {
  vTaskDelay(1/portTICK_PERIOD_MS);
  if (num == 1) {
    this->write(CMD, 0b00111100);
  } else {
    this->write(CMD, 0b00111000);  // Function Set
  }
  if (num == 1) {
    this->write(CMD, 0b00111101);
  } else {
    this->write(CMD, 0b00111001);  // Function Set
  }
  vTaskDelay(1/portTICK_PERIOD_MS);
  if (num == 1) {
    this->write(CMD, 0b00111101);
  } else {
    this->write(CMD, 0b00111001);  // Function Set
  }
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x14);  // Internal OSC Freq
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0b01110000 | (contrast & 0b001111));  // Contrast Set
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0b01010100 | (contrast >> 4));  // P/I/C Control
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x6C);  // Follower Control
  vTaskDelay(1/portTICK_PERIOD_MS);
  if (num == 1) {
    this->write(CMD, 0b00111100);
  } else {
    this->write(CMD, 0b00111000);  // Function Set
  }
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x01);  // Clear Display
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x0C);  // On/Off Control
  vTaskDelay(1/portTICK_PERIOD_MS);
  this->write(CMD, 0x40);  // Set CGRAM
  vTaskDelay(1/portTICK_PERIOD_MS);
  int i;
  for (i = 0; i < 64; i++) {
    this->write(DATA, Custom_Char5x8[i]);  // Set CGRAM
    vTaskDelay(1/portTICK_PERIOD_MS);
  }
  vTaskDelay(1/portTICK_PERIOD_MS);
}

void LCD::printf(int line, const char* format, ...) {
  char buf[32];
  va_list ap;
  va_start(ap, format);
  vsprintf(buf, format, ap);
  va_end(ap);
  this->print(buf, line);
}