import _thread
import time
import sys
import machine

"""     '320x240'
        '640x480'
        '1280x720'
        '1600x1200'
        '1920x1080'
        '2592x1944'
        '96X96'
        '128X128'
        '320X320'  """

cam = Camera(spi, cs)

R_LED = Pin(46, Pin.OUT)
G_LED = Pin(0, Pin.OUT)
B_LED = Pin(45, Pin.OUT)

cam.resolution = '1280x720'
cam.set_pixel_format(cam.CAM_IMAGE_PIX_FMT_JPG)
cam.set_brightness_level(cam.BRIGHTNESS_PLUS_4)
cam.set_contrast(cam.CONTRAST_MINUS_3)


while True:
    caracter = input("Presiona P para tomar una foto o Q para salir: ")
    G_LED.on()
    if caracter.lower() == 'p':
        R_LED.off()
        start_time_capture = utime.ticks_ms()
        cam.capture_jpg()
        
        RAW = cam.read_image_data()
        total_time_ms = utime.ticks_diff(utime.ticks_ms(), start_time_capture)
        R_LED.on()
        G_LED.off()
    
        
        print('Tiempo de captura: {}s'.format(total_time_ms/1000))
        
        cam.convert_to_base64(RAW)
        start_time_capture = utime.ticks_ms()
        
    elif caracter.lower() == 'q':
        print("Saliendo del programa.")
        sys.exit()
        