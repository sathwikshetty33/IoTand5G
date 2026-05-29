from machine import Pin
import dht
import time

dht_sensor = dht.DHT22(Pin(17))

buzzer_pin = Pin(15, Pin.OUT)
led = Pin(2, Pin.OUT)

TEMP_THRESHOLD = 30  

def buzz(frequency, duration):
    period = 1 / frequency
    cycles = int(frequency * duration)
    
    for _ in range(cycles):
        buzzer_pin.on()
        time.sleep(period / 2)
        buzzer_pin.off()
        time.sleep(period / 2)

while True:
    try:
        dht_sensor.measure()
        temperature = dht_sensor.temperature()
        humidity = dht_sensor.humidity()

        print(f'Temperature: {temperature}°C, Humidity: {humidity}%')

        if temperature > TEMP_THRESHOLD:
            # Activate alarm (Buzzer and LED)
            buzz(1000, 0.5)  
            led.on()
            time.sleep(0.2) 
            led.off()
            time.sleep(0.2)  
            print("RUNNN SAVE YOUR LIFE!!") 
        else:
            led.off()

    except Exception as e:
        print("Error reading from sensor:", e)

    time.sleep(2)
