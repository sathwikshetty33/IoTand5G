from machine import Pin, ADC, PWM
import time


gas_sensor = ADC(26)

buzzer = PWM(Pin(15))

step = Pin(2, Pin.OUT)
direction = Pin(3, Pin.OUT)
enable = Pin(4, Pin.OUT)

enable.value(0)

direction.value(0)

threshold = 35000

def rotate_fan():

    step.value(1)
    time.sleep_ms(8)
    step.value(0)
    time.sleep_ms(8)

while True:

    gas_value = gas_sensor.read_u16()
    print("Gas Level:", gas_value)

    if gas_value > threshold:


        buzzer.freq(1000)
        buzzer.duty_u16(30000)


        rotate_fan()

    else:

        buzzer.duty_u16(0)

    time.sleep(0.1)