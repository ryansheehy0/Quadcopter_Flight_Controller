#pragma once

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <cstdio>

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

class Controller {
	private:
		UART_HandleTypeDef* uart_;
		
		RotationRates maxRotationRates_;

		uint16_t combineBytes_(uint8_t lsb, uint8_t msb) const { return (uint16_t(msb) << 8) | lsb; }
		
	public: 
		Controller (UART_HandleTypeDef* uart);

		ControllerValues getValues();
};