## 串口通讯

UART（Universal Asynchronous Receiver/Transmitter），通用异步收发传输器。
### 上位机winows10
```Python
#!/usr/bin/env python
# -*- coding:utf-8 -*-
# pip install pyserial

# https://www.cnblogs.com/dongxiaodong/p/9992083.html
import serial #导入模块
import serial.tools.list_ports

# 打印出所有可用端口
def Print_Used_Com():
        port_list = list(serial.tools.list_ports.comports())
        for i in port_list:
            print(i)
        
Print_Used_Com() 


try:
  portx="COM4"
  bps=115200
  #超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
  timex=None

  ser=serial.Serial(portx,bps,timeout=timex)
  print("串口详情参数：")
  print(ser)

  #十六进制的发送
  #result=ser.write(chr(0x06).encode("utf-8"))#写数据
  #print("写总字节数:",result)
  while True:
    if ser.in_waiting:
        
        #十六进制的读取
        print(ser.read(ser_in_waiting).decode('gbk'))#读一个字节

  print("---------------")
  ser.close()#关闭串口

except Exception as e:
    print("---异常---：",e)
```

用putty和sscom都可以进行串口通讯，但我们用自己写的python可以以ASCII方式进行显示。

![zero](images/header-photo-zero-large.png)
![zero](images/header-zero-large.png)
![zero](images/ttl.jpg)

买一根TTL线，连接到树莓派上，直接将USB口插入电脑就可以进行串口通讯，树莓派无需额外供电，适合没有HDMI屏幕的环境，而且开发简单。

### 树莓派代码

功能都写在uart.c文件中。

```C++
void uart_irq_handler ( void );
void uart_init();   /*初始化串口*/
void uart_putc ( u32 c );
int notmain ( void );
void uart_printstr (const char *str)
```
主要就是上述4个功能，串口通讯可以采用中断方式，也可以用轮询，轮询比较简单。

