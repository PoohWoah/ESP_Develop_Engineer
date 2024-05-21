#ifndef PINOUT_H
#define PINOUT_H

// LCD panel parameter
#define LCD_PCLK_HZ 23000000
#define LCD_H_RES   800
#define LCD_HSYNC_PULSE_WIDTH   4
#define LCD_HSYNC_BACK_PORCH    8
#define LCD_HSYNC_FRONT_PORCH   8
#define LCD_V_RES   480
#define LCD_VSYNC_PULSE_WIDTH   4
#define LCD_VSYNC_BACK_PORCH    16
#define LCD_VSYNC_FRONT_PORCH   16
// LCD pinout
// #define LCD_LR_PIN    45
// #define LCD_UD_PIN    46
#define LCD_DISP_PIN  -1
#define LCD_PCLK_PIN  5
#define LCD_HSYNC_PIN -1
#define LCD_VSYNC_PIN -1
#define LCD_DE_PIN 38
#define LCD_B3_PIN 17
#define LCD_B4_PIN 18
#define LCD_B5_PIN 48
#define LCD_B6_PIN 47
#define LCD_B7_PIN 39
#define LCD_G2_PIN 11
#define LCD_G3_PIN 12
#define LCD_G4_PIN 13
#define LCD_G5_PIN 14
#define LCD_G6_PIN 15
#define LCD_G7_PIN 16
#define LCD_R3_PIN 6
#define LCD_R4_PIN 7
#define LCD_R5_PIN 8
#define LCD_R6_PIN 9
#define LCD_R7_PIN 10


// GT911 Touch
#define I2C0_SPEED    400000
#define I2C0_SCL_PIN  1
#define I2C0_SDA_PIN  2
#define GT911_I2C     I2C_NUM_0
#define GT911_IRQ_PIN 40
#define GT911_RST_PIN 41

// PWM
#define LCD_RESET_PIN      46
#define LCD_BL_PIN         21
//  #define LCD_BL_CHANNEL     0 // Group: 0, Channel: 0, Timer: 0
//  #define LCD_BL_FREQ        5000 // 5KHz
//  #define LCD_BL_RESOLUTION  8 // 0~255

#endif
