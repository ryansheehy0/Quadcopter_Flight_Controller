# Quadcopter Flight Controller
A quadcopter flight controller using STM32 Black Pill.

<!--Image of drone-->
<!--Video of drone flying from YT-->

## Building the drone

## Acro mode run loop
- Get gyro data
- Get controller data
- If controller data isn't valid, set motors to 0 after a short delay of 1.5sec
- PID with gyro being measured and controller being the set point
	- PID outputs clamped to -1 to 1 for pitch, roll, and yaw.
- Motor mixing
	- Motor values get clamped to 0 to 1. (Negative becomes 0 and above 1 becomes 1).
		
## Future features
- Stabilized mode
- When controller disconnects, hover in place and slowly decrease throttle.
- Camera(Option between regular and thermal)
- Show battery voltage on camera feed
	