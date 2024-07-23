The code:
from machine import Pin
import time
led=Pin(16,Pin.OUT)
sensor=Pin(15,Pin.IN)
def light_onboard_led():
led = machine.Pin('LED'
, machine.Pin.OUT)
led.on();
light_onboard_led()
try:
while True:
if sensor.value() == 1:
led.value(0)
else:
led.value(1)
except:
pass
