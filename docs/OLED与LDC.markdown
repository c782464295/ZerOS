# OLED与LCD的区别
LCD每一个像素点由3个子像素，其发光用的是统一的发光背板，所以通过调节液晶层来调节光线通过率从而控制颜色。

这样的一个主要问题就是发光背板要一直通电，所以即便屏幕显示黑色，耗电量仍然不小。

而OLED是有机发光二极管，相当于是许多小LED组成的，通过控制LED开关，显示不同颜色，比较省电，还支持折叠。

LCD背板是硬的，不能折叠。

但OLED的主要问题是寿命，而且OLED调节明暗不能通过电压大小来调节，是通过显示时间来调节，这样对一些眼睛敏感的人会感到不舒服。

![图片](images/screen.jpg)
![图片](images/screen2.jpg)


应该是连接了3.3V SDL SCL GND这4个引脚。

![IO](images/io.jpg)

Pi OLED 配备 0.9 英寸迷你单色屏，128×32 分辨率，白光像素点。拥有极高的对比度，显示清晰极易辨识。
OLED 仅使用树莓派的 I2C 和电源引脚，无需独立供电，即插即用。

不能接反VCC和GND，否则会烧坏屏幕。


开始信号：SCL 为高电平时，SDA 由高电平向低电平跳变，开始传送数据。
结束信号：SCL 为高电平时，SDA 由低电平向高电平跳变，结束传送数据。
应答信号：接收数据的 IC 在接收到 8bit 数据后，向发送数据的 IC 发出特定 的低电平脉
冲，表示已收到数据。CPU 向受控单元发出一个信号后，等待受控单元发出一个应答信号，CPU 接收到应答信号后，根据实际情况作出是否继续传递信号的判断。若未收到应答信号，由判断为 受控单元出现故障。
这些信号中，开始信号是必需的，结束信号和应答信号，都可以不要


打开OLED的步骤
1. 0x8D 设置电荷泵
2. 0x14 开启电荷泵
3. 0xAF OLED唤醒
4. 0xA7 翻转显示
此时，OLED应全屏亮。
```C++
  *I2C1_C=0x8000;      // Enable I2C
  *I2C1_DIV=2560;
  *I2C1_C=0x8030;      // Enable I2C, FIFO CLR

  *I2C1_DLEN=2;        // Write 2 bytes
  *I2C1_A=0x3C;        // Address = OLED
  *I2C1_FIFO=0x80;     // OLED C0=1, D/C=0
  *I2C1_FIFO=0xAF;     // OLED CMD = active (not sleep)
  *I2C1_C=0x8080;      // Start write

  for(d=0;d!=10;d++)  led_flash(100000); // Delay

  *I2C1_DLEN=2;        // Write 2 bytes
  *I2C1_A=0x3C;        // Address = OLED
  *I2C1_FIFO=0x80; 
  *I2C1_FIFO=0xA7;     // OLED CMD = invert display
  *I2C1_C=0x8080;      // Start write
```
[stm32 oled](https://blog.csdn.net/keilert/article/details/82787960)

[OLED屏幕的IIC驱动程序](https://blog.csdn.net/gengyuchao/article/details/86743908)