#include <stdio.h>
#include <string.h>
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "board.h"
#include "lis3dh.h"


void lis3dh_init(t_lis3dh *accel, uint8_t reg1)
{
    uint8_t buff[8];

    memset(accel, 0, sizeof(t_lis3dh));

    i2c_init(I2C_DEVICE, I2C_SPEED);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    /* CTRL_REG1 */
    buff[0] = CTRL_REG1;
    buff[1] = reg1;
    i2c_write_blocking(I2C_DEVICE, LIS3DH_ADDRESS, buff, 2, false);
}

void lis3dh_read_raw_accel(t_lis3dh *accel, int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t buff[8];

    buff[0] = OUT_X_L | 0x80;  // OUT_X_L + Autoincrement
    i2c_write_blocking(I2C_DEVICE, LIS3DH_ADDRESS, buff, 1, true);
    i2c_read_blocking(I2C_DEVICE, LIS3DH_ADDRESS, buff, 6, false);

    *x = (buff[1] << 8 ) | buff[0];
    *y = (buff[3] << 8 ) | buff[2];
    *z = (buff[5] << 8 ) | buff[4];
}