#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>

struct ControllerValues {
	bool isValid;
	// Normalized from 0 to 1
	float throttle;
	float leftPot;
	float rightPot;
	// In degrees/sec
	float pitch;
	float roll;
	float yaw;
};

struct RotationRates { // In degrees/sec
	float pitch;
	float roll;
	float yaw;
};

// Instructions
// 1. Set up UART via CubeMX
// 2. Connect top right pin(of the top row when looking face on at the pins) of FS-iA6B to pin A10(RX pin)
// 3. Connect the next pin to the left of the top right pin to 5v
//    Note: 5v may not be at 5 volts if powered through ST-LINK. This will beep your controller.
// 4. Connect the next pin to the left of that to G
// So the top right 3 pins of the top row should all be connected.

// Uses for left and right pots
// 1. PD values
//    Left: P values
//    Right: D values
// 2. Max rotation rates
//    Left: Pitch & Roll
//    Right: Yaw
// NOTE: The code knows the controller has disconnected if the left and right pots are both set to 0.
//       Do not have the normal use case for both pots be set in 0 positions.

class Controller {
	private:
		UART_HandleTypeDef* uart_;
		
		RotationRates maxRotationRates_;

		uint16_t combineBytes_(uint8_t lsb, uint8_t msb) const { return (uint16_t(msb) << 8) | lsb; }
		
	public: 
		Controller (UART_HandleTypeDef* uart);

		ControllerValues getValues();
};