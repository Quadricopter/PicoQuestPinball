#ifndef __LIS3DH_H__
#define __LIS3DH_H__

#define LIS3DH_ADDRESS  0x18  // 7-bit!

/*
 * LIS3DH registers
 * Source: https://www.st.com/resource/en/datasheet/lis3dh.pdf
 */

#define STATUS_REG_AUX  0x07
#define OUT_ADC1_L      0x08
#define OUT_ADC1_H      0x09
#define OUT_ADC2_L      0x0A
#define OUT_ADC2_H      0x0B
#define OUT_ADC3_L      0x0C
#define OUT_ADC3_H      0x0D
#define WHO_AM_I        0x0F
#define CTRL_REG0       0x1E
#define TEMP_CFG_REG    0x1F
#define CTRL_REG1       0x20
#define CTRL_REG2       0x21
#define CTRL_REG3       0x22
#define CTRL_REG4       0x23
#define CTRL_REG5       0x24
#define CTRL_REG6       0x25
#define REFERENCE       0x26
#define STATUS_REG      0x27
#define OUT_X_L         0x28
#define OUT_X_H         0x29
#define OUT_Y_L         0x2A
#define OUT_Y_H         0x2B
#define OUT_Z_L         0x2C
#define OUT_Z_H         0x2D
#define FIFO_CTRL_REG   0x2E
#define FIFO_SRC_REG    0x2F
#define INT1_CFG        0x30
#define INT1_SRC        0x31
#define INT1_THS        0x32
#define INT1_DURATION   0x33
#define INT2_CFG        0x34
#define INT2_SRC        0x35
#define INT2_THS        0x36
#define INT2_DURATION   0x37
#define CLICK_CFG       0x38
#define CLICK_SRC       0x39
#define CLICK_THS       0x3A
#define TIME_LIMIT      0x3B
#define TIME_LATENCY    0x3C
#define TIME_WINDOW     0x3D
#define ACT_THS         0x3E
#define ACT_DUR         0x3F

/*
 * CTRL_REG1
 */

#define CTRL_REG1_X_ENABLE  (1<<0)
#define CTRL_REG1_Y_ENABLE  (1<<1)
#define CTRL_REG1_Z_ENABLE  (1<<2)
#define CTRL_REG1_LOW_POWER (1<<3)
#define CTRL_REG1_ODR0      (1<<4)
#define CTRL_REG1_ODR1      (1<<5)
#define CTRL_REG1_ODR2      (1<<6)
#define CTRL_REG1_ODR3      (1<<7)

#define CRTL_REG1_200HZ     (CTRL_REG1_ODR2 | CTRL_REG1_ODR1)
#define CRTL_REG1_XYZ       (CTRL_REG1_Z_ENABLE | CTRL_REG1_Y_ENABLE | CTRL_REG1_X_ENABLE)

/*
 *
 */

typedef struct {

}   t_lis3dh;


void lis3dh_init(t_lis3dh *, uint8_t reg1);
void lis3dh_read_raw_accel(t_lis3dh *accel, int16_t *x, int16_t *y, int16_t *z);


#endif /*__LIS3DH_H__*/
