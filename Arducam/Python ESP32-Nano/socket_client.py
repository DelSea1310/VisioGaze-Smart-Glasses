from machine import Pin
import network
import config
import socket
from time import sleep
#import Camera  # Ajusta según la biblioteca específica que uses

cam=Camera(spi, cs)

cam.resolution='640x480'
cam.set_pixel_format(cam.CAM_IMAGE_PIX_FMT_JPG)
cam.set_brightness_level(cam.BRIGHTNESS_PLUS_4)
cam.set_contrast(cam.CONTRAST_MINUS_3)

# Configuración del LED
led = Pin(48, Pin.OUT)

# Configuración de la conexión WiFi
wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(config.WIFI_SSID, config.WIFI_PASSWORD)

while not wifi.isconnected():
    pass

print("Wifi connected")

# Configuración del socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.166.106', 1234))

while True:
    try:
        data = s.recv(1024)
        print(data)

        if data == b'1':
            led.on()
        elif data == b'0':
            led.off()
        elif data == b'pedir_foto':
            try:
                cam.capture_jpg()
                RAW = cam.read_image_data()
                
                base64_image = cam.convert_to_base64(RAW)
                
                # Enviar la imagen codificada en base64
                s.send(base64_image)
                    
            except Exception as e:
                print(f"Error capturing image: {e}")

    except KeyboardInterrupt:
        break
