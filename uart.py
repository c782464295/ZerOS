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