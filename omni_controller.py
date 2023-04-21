from machine import Pin
import utime



# Initialize state variables
state_fa=True
state_lat=False
state_rot=False

rise_time=0
fall_time_fa=0
fall_time_lat=0
fall_time_rot=0

# Define pins used for PWM IN signals
gpio_fa=5
gpio_lat=6
gpio_rot=7
pin_fa=Pin(gpio_fa, Pin.IN, Pin.PULL_DOWN)
pin_lat=Pin(gpio_lat, Pin.IN, Pin.PULL_DOWN)
pin_rot=Pin(gpio_rot, Pin.IN, Pin.PULL_DOWN)

def fa_event(pin):
    global state_fa, state_lat, state_rot, rise_time, fall_time_fa
    if (time.ticks_ms()-debounce_time) > 500:
        interrupt_flag= 1
        debounce_time=time.ticks_ms()

def lat_event(pin):
    global state_lat, fall_time_lat
    if (time.ticks_ms()-debounce_time) > 500:
        interrupt_flag= 1
        debounce_time=time.ticks_ms()
        
def rot_event(pin):
    global state_rot, fall_time_rot
    if (time.ticks_ms()-debounce_time) > 500:
        interrupt_flag= 1
        debounce_time=time.ticks_ms()

# Attach interrupts to the PWM IN pins. Interrupt functions must be called before this.
pin_fa.irq(trigger=Pin.IRQ_FALLING | Pin.IRQ_RISING, handler=callback)
pin_lat.irq(trigger=Pin.IRQ_FALLING, handler=callback)
pin_rot.irq(trigger=Pin.IRQ_FALLING, handler=callback)

led = Pin(25, Pin.OUT)
led.low()

while True:
    led.toggle()
    print("Toggle")
    utime.sleep(1)