#ifndef BCM2835_H
#define BCM2835_H

/* 引入我们定义的类型文件 */
#include "stdtype.h"

/*! 引脚高电压, 3.3v */
#define HIGH        0x1
/*! 引脚低电压, 0。0v */
#define LOW         0x0

/*! 返回两数中的较小值 */
#ifndef MIN
#define MIN(a, b) (a < b ? a : b)
#endif

/*! 核心频率 */
#define BCM2835_CORE_CLK_HZ     250000000	/*!< 250 MHz */

/*! Peripherals起始地址 */
#define BCM2835_PERI_BASE       0x20000000

/*! 其余外围设备(Peripherals)的偏移地址 */
#define BCM2835_ST_BASE         0x3000
/*! Base Address of the Pads registers */
#define BCM2835_GPIO_PADS       0x100000
/*! Base Address of the Clock/timer registers */
#define BCM2835_CLOCK_BASE      0x101000
/*! Base Address of the GPIO registers */
#define BCM2835_GPIO_BASE       0x200000
/*! Base Address of the SPI0 registers */
#define BCM2835_SPI0_BASE       0x204000
/*! Base Address of the BSC0 registers */
#define BCM2835_BSC0_BASE       0x205000
/*! Base Address of the PWM registers */
#define BCM2835_GPIO_PWM        0x20C000
/*! Base Address of the AUX registers */
#define BCM2835_AUX_BASE        0x215000
/*! Base Address of the AUX_SPI1 registers */
#define BCM2835_SPI1_BASE       0x215080
/*! Base Address of the AUX_SPI2 registers */
#define BCM2835_SPI2_BASE       0x2150C0
/*! Base Address of the BSC1 registers */
#define BCM2835_BSC1_BASE       0x804000
/*! Base address of the SMI registers */
#define BCM2835_SMI_BASE        0x600000



/*! GPIO register offsets from BCM2835_GPIO_BASE. 
  Offsets into the GPIO Peripheral block in bytes per 6.1 Register View 
*/
#define BCM2835_GPFSEL0                      0x0000 /*!< GPIO Function Select 0 */
#define BCM2835_GPFSEL1                      0x0004 /*!< GPIO Function Select 1 */
#define BCM2835_GPFSEL2                      0x0008 /*!< GPIO Function Select 2 */
#define BCM2835_GPFSEL3                      0x000c /*!< GPIO Function Select 3 */
#define BCM2835_GPFSEL4                      0x0010 /*!< GPIO Function Select 4 */
#define BCM2835_GPFSEL5                      0x0014 /*!< GPIO Function Select 5 */
#define BCM2835_GPSET0                       0x001c /*!< GPIO Pin Output Set 0 */
#define BCM2835_GPSET1                       0x0020 /*!< GPIO Pin Output Set 1 */
#define BCM2835_GPCLR0                       0x0028 /*!< GPIO Pin Output Clear 0 */
#define BCM2835_GPCLR1                       0x002c /*!< GPIO Pin Output Clear 1 */
#define BCM2835_GPLEV0                       0x0034 /*!< GPIO Pin Level 0 */
#define BCM2835_GPLEV1                       0x0038 /*!< GPIO Pin Level 1 */
#define BCM2835_GPEDS0                       0x0040 /*!< GPIO Pin Event Detect Status 0 */
#define BCM2835_GPEDS1                       0x0044 /*!< GPIO Pin Event Detect Status 1 */
#define BCM2835_GPREN0                       0x004c /*!< GPIO Pin Rising Edge Detect Enable 0 */
#define BCM2835_GPREN1                       0x0050 /*!< GPIO Pin Rising Edge Detect Enable 1 */
#define BCM2835_GPFEN0                       0x0058 /*!< GPIO Pin Falling Edge Detect Enable 0 */
#define BCM2835_GPFEN1                       0x005c /*!< GPIO Pin Falling Edge Detect Enable 1 */
#define BCM2835_GPHEN0                       0x0064 /*!< GPIO Pin High Detect Enable 0 */
#define BCM2835_GPHEN1                       0x0068 /*!< GPIO Pin High Detect Enable 1 */
#define BCM2835_GPLEN0                       0x0070 /*!< GPIO Pin Low Detect Enable 0 */
#define BCM2835_GPLEN1                       0x0074 /*!< GPIO Pin Low Detect Enable 1 */
#define BCM2835_GPAREN0                      0x007c /*!< GPIO Pin Async. Rising Edge Detect 0 */
#define BCM2835_GPAREN1                      0x0080 /*!< GPIO Pin Async. Rising Edge Detect 1 */
#define BCM2835_GPAFEN0                      0x0088 /*!< GPIO Pin Async. Falling Edge Detect 0 */
#define BCM2835_GPAFEN1                      0x008c /*!< GPIO Pin Async. Falling Edge Detect 1 */
#define BCM2835_GPPUD                        0x0094 /*!< GPIO Pin Pull-up/down Enable */
#define BCM2835_GPPUDCLK0                    0x0098 /*!< GPIO Pin Pull-up/down Enable Clock 0 */
#define BCM2835_GPPUDCLK1                    0x009c /*!< GPIO Pin Pull-up/down Enable Clock 1 */

/*!   \brief bcm2835PortFunction
  Port function select modes for bcm2835_gpio_fsel()
*/
typedef enum
{
    BCM2835_GPIO_FSEL_INPT  = 0x00,   /*!< Input 0b000 */
    BCM2835_GPIO_FSEL_OUTP  = 0x01,   /*!< Output 0b001 */
    BCM2835_GPIO_FSEL_ALT0  = 0x04,   /*!< Alternate function 0 0b100 */
    BCM2835_GPIO_FSEL_ALT1  = 0x05,   /*!< Alternate function 1 0b101 */
    BCM2835_GPIO_FSEL_ALT2  = 0x06,   /*!< Alternate function 2 0b110, */
    BCM2835_GPIO_FSEL_ALT3  = 0x07,   /*!< Alternate function 3 0b111 */
    BCM2835_GPIO_FSEL_ALT4  = 0x03,   /*!< Alternate function 4 0b011 */
    BCM2835_GPIO_FSEL_ALT5  = 0x02,   /*!< Alternate function 5 0b010 */
    BCM2835_GPIO_FSEL_MASK  = 0x07    /*!< Function select bits mask 0b111 */
} bcm2835FunctionSelect;

/*! \brief bcm2835PUDControl
  Pullup/Pulldown defines for bcm2835_gpio_pud()
*/
typedef enum
{
    BCM2835_GPIO_PUD_OFF     = 0x00,   /*!< Off ? disable pull-up/down 0b00 */
    BCM2835_GPIO_PUD_DOWN    = 0x01,   /*!< Enable Pull Down control 0b01 */
    BCM2835_GPIO_PUD_UP      = 0x02    /*!< Enable Pull Up control 0b10  */
} bcm2835PUDControl;



extern "C" {
    /*! Sets the Function Select register for the given pin, which configures
      the pin as Input, Output or one of the 6 alternate functions.
      \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
      \param[in] mode Mode to set the pin to, one of BCM2835_GPIO_FSEL_* from \ref bcm2835FunctionSelect
    */
    extern void bcm2835_gpio_fsel(u8 pin, u8 mode);

    /*! Sets the specified pin output to 
      HIGH.
      \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
      \sa bcm2835_gpio_write()
    */
    extern void bcm2835_gpio_set(u8 pin);

    /*! Sets the specified pin output to 
      LOW.
      \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
      \sa bcm2835_gpio_write()
    */
    extern void bcm2835_gpio_clr(u8 pin);



        /*! Start I2C operations.
      Forces RPi I2C pins P1-03 (SDA) and P1-05 (SCL)
      to alternate function ALT0, which enables those pins for I2C interface.
      You should call bcm2835_i2c_end() when all I2C functions are complete to return the pins to
      their default functions
      \return 1 if successful, 0 otherwise (perhaps because you are not running as root)
      \sa  bcm2835_i2c_end()
    */
    extern int bcm2835_i2c_begin(void);

    /*! End I2C operations.
      I2C pins P1-03 (SDA) and P1-05 (SCL)
      are returned to their default INPUT behaviour.
    */
    extern void bcm2835_i2c_end(void);

    /*! Sets the I2C slave address.
      \param[in] addr The I2C slave address.
    */
    extern void bcm2835_i2c_setSlaveAddress(u8 addr);

    /*! Sets the I2C clock divider and therefore the I2C clock speed.
      \param[in] divider The desired I2C clock divider, one of BCM2835_I2C_CLOCK_DIVIDER_*,
      see \ref bcm2835I2CClockDivider
    */
    extern void bcm2835_i2c_setClockDivider(u16 divider);

    /*! Sets the I2C clock divider by converting the baudrate parameter to
      the equivalent I2C clock divider. ( see \sa bcm2835_i2c_setClockDivider)
      For the I2C standard 100khz you would set baudrate to 100000
      The use of baudrate corresponds to its use in the I2C kernel device
      driver. (Of course, bcm2835 has nothing to do with the kernel driver)
    */
    extern void bcm2835_i2c_set_baudrate(u32 baudrate);

    /*! Transfers any number of bytes to the currently selected I2C slave.
      (as previously set by \sa bcm2835_i2c_setSlaveAddress)
      \param[in] buf Buffer of bytes to send.
      \param[in] len Number of bytes in the buf buffer, and the number of bytes to send.
      \return reason see \ref bcm2835I2CReasonCodes
    */
    extern u8 bcm2835_i2c_write(const char * buf, u32 len);

    /*! Transfers any number of bytes from the currently selected I2C slave.
      (as previously set by \sa bcm2835_i2c_setSlaveAddress)
      \param[in] buf Buffer of bytes to receive.
      \param[in] len Number of bytes in the buf buffer, and the number of bytes to received.
      \return reason see \ref bcm2835I2CReasonCodes
    */
    extern u8 bcm2835_i2c_read(char* buf, u32 len);

    /*! Allows reading from I2C slaves that require a repeated start (without any prior stop)
      to read after the required slave register has been set. For example, the popular
      MPL3115A2 pressure and temperature sensor. Note that your device must support or
      require this mode. If your device does not require this mode then the standard
      combined:
      \sa bcm2835_i2c_write
      \sa bcm2835_i2c_read
      are a better choice.
      Will read from the slave previously set by \sa bcm2835_i2c_setSlaveAddress
      \param[in] regaddr Buffer containing the slave register you wish to read from.
      \param[in] buf Buffer of bytes to receive.
      \param[in] len Number of bytes in the buf buffer, and the number of bytes to received.
      \return reason see \ref bcm2835I2CReasonCodes
    */
    extern u8 bcm2835_i2c_read_register_rs(char* regaddr, char* buf, u32 len);

    /*! Allows sending an arbitrary number of bytes to I2C slaves before issuing a repeated
      start (with no prior stop) and reading a response.
      Necessary for devices that require such behavior, such as the MLX90620.
      Will write to and read from the slave previously set by \sa bcm2835_i2c_setSlaveAddress
      \param[in] cmds Buffer containing the bytes to send before the repeated start condition.
      \param[in] cmds_len Number of bytes to send from cmds buffer
      \param[in] buf Buffer of bytes to receive.
      \param[in] buf_len Number of bytes to receive in the buf buffer.
      \return reason see \ref bcm2835I2CReasonCodes
    */
    extern u8 bcm2835_i2c_write_read_rs(char* cmds, u32 cmds_len, char* buf, u32 buf_len);
}


#endif /* BCM2835_H */