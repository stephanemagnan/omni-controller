# omni-controller
Control an omni-directional robot with a traditional hobby-style RF controller.

## Technical details
This algthm is intended to provide directional control to a four-wheeled robot using a hobbiest controller. The omni robot has one wheel on each of the four faces and uses traditional up-down-left-right joystick inputs to balance the motor loading in the desired direction. 

## Getting started
The project was initially written in Python to test the balance control algorithm. The current implamentation uses an arduino to constantly monitor the voltage state of the inut channels to determine the PWM duty cycles and thus the inputs that should be scaled to output voltages to each motor. Verify the input and output pins at the start of the file to ensure compatibility with your microcontroller of choice. Current proof of concept uses polling rather than interrupts - this will be changed eventually.

Details on the algorithm and scaling including computation of the output loads is provided in an excel file in the project folder. 
