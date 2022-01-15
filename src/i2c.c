#include "i2c.h"
#include "gpio.h"
#define	CONTROL_READ				0x0001
#define CONTROL_CLEAR_FIFO	0x0010
#define CONTROL_START				0x0080
#define CONTROL_ENABLE			0x8000

#define STATUS_TRANSFER_ACTIVE	0x001
#define STATUS_TRANSFER_DONE		0x002
#define STATUS_FIFO_NEED_WRITE	0x004
#define STATUS_FIFO_NEED_READ		0x008
#define STATUS_FIFO_CAN_WRITE		0x010
#define STATUS_FIFO_CAN_READ		0x020
#define STATUS_FIFO_EMPTY				0x040
#define STATUS_FIFO_FULL				0x080
#define STATUS_ERROR_SLAVE_ACK	0x100
#define STATUS_TIMEOUT					0x200
// I2C registers
struct I2C {
    int control;
    int status;
    int data_length;
    int slave_address;
    int data_fifo;
    int clock_divider;
    int data_delay;
    int clock_stretch_timeout;
};

typedef enum{
    BCM2835_GPIO_FSEL_INPT  = 0x00,   /*!< Input 0b000 */
    BCM2835_GPIO_FSEL_OUTP  = 0x01,   /*!< Output 0b001 */
    BCM2835_GPIO_FSEL_ALT0  = 0x04,   /*!< Alternate function 0 0b100 */
    BCM2835_GPIO_FSEL_ALT1  = 0x05,   /*!< Alternate function 1 0b101 */
    BCM2835_GPIO_FSEL_ALT2  = 0x06,   /*!< Alternate function 2 0b110, */
    BCM2835_GPIO_FSEL_ALT3  = 0x07,   /*!< Alternate function 3 0b111 */
    BCM2835_GPIO_FSEL_ALT4  = 0x03,   /*!< Alternate function 4 0b011 */
    BCM2835_GPIO_FSEL_ALT5  = 0x02,   /*!< Alternate function 5 0b010 */
    BCM2835_GPIO_FSEL_MASK  = 0x07    /*!< Function select bits mask 0b111 */
}bcm2835FunctionSelect;

static volatile struct I2C *i2c = (struct I2C *) BSC_BASE;

void i2c_init(void) {
    bcm2835FunctionSelect mode = BCM2835_GPIO_FSEL_ALT0;
    gpio_mode(GPIO_SDA, mode);
    gpio_mode(GPIO_SCL, mode);
    i2c->control = CONTROL_ENABLE;
}



void i2c_read(unsigned slave_address, char *data, int data_length){

}

void i2c_write(unsigned slave_address, char *data, int data_length){

}