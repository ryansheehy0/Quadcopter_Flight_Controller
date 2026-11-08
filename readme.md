# Quadcopter Flight Controller
A quadcopter flight controller using STM32 Black Pill.

<!--Image of drone-->
<!--Video of drone flying-->

<!--Steps on how to build it and flash the code-->

- Acro mode run loop
	- Get gyro data
	- Get controller data
	- If controller data isn't valid, set motors to 0 after a short delay of 1.5sec
	- PID with gyro being measured and controller being set point
		- PID outputs clamped to -1 to 1 for pitch, roll, and yaw.
	- Motor mixing
		- In the setMotor function, negative values become 0 and values above 1 become 1.
		
- Future features
	- Change the controller data to interrupts instead of blocking.