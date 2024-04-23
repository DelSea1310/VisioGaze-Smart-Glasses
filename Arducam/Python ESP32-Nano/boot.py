# This file is executed on every boot (including wake-boot from deepsleep)
#import esp
#esp.osdebug(None)
#import webrepl
#webrepl.start()
#from machine import Pin, SPI, reset
from Camera import *

import socket
import network



import uos
import ujson

sck = Pin(48, Pin.OUT)
mosi = Pin(38, Pin.OUT)
miso = Pin(47, Pin.IN)
cs = Pin(21, Pin.OUT)

SPI(1, baudrate=5000000)
spi = SPI(1, baudrate=8000000, sck=sck, mosi=mosi, miso=miso)