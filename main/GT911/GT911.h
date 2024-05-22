#ifndef GT911_H
#define GT911_H

#define GT911_REG_MODULE_SWITCH1 0x804D
/* Product ID, 0x8140 ~ 0x8143, 4bytes */
#define GT911_REG_PRODUCT_ID     0x8140
/* Firmware Version, 0x8144 ~ 0x8145, 2bytes */
#define GT911_REG_FIRMWARE_VER   0x8144
/* x coordinate resolution, 0x8146 ~ 0x8147, 2bytes */
#define GT911_REG_X_RES          0x8146
/* y coordinate resolution, 0x8148 ~ 0x8149, 2bytes */
#define GT911_REG_Y_RES          0x8148
#define GT911_REG_VENDOR_ID      0x814A
/* bit7: is there a touch, bit3~0: number of touch points*/
#define GT911_REG_STATUS         0x814E
/* Point 1*/
#define GT911_REG_POINT1         0x814F
/* Point 2*/
#define GT911_REG_POINT2         0x8157
/* Point 3*/
#define GT911_REG_POINT3         0x815F
/* Point 4*/
#define GT911_REG_POINT4         0x8167
/* Point 5*/
#define GT911_REG_POINT5         0x816F
/**
 * @brief gt911的初始化函数
*/
void GT911_init(void);
#endif