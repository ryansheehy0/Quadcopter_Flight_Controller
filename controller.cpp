#include "./controller.h"

// Constructor -----------------------------------------------------------------
Controller::Controller(UART_HandleTypeDef* uart) {
	uart_ = uart;
	
	maxRotationRates_.pitch = 200;
	maxRotationRates_.roll = 200;
	maxRotationRates_.yaw = 150;
}

// Public ---------------------------------------------------------------------
ControllerValues Controller::getValues() {
	ControllerValues controllerValues;
	controllerValues.isValid = false;
	
	// Check start byte
	uint8_t startByte;
	if (HAL_UART_Receive(uart_, &startByte, 1, 2) != HAL_OK) return controllerValues;
	if (startByte != 0x20) return controllerValues;

	// Load remaining 31 bytes
	uint8_t buffer[31];
	if (HAL_UART_Receive(uart_, buffer, 31, 10) != HAL_OK) return controllerValues;
	// Validate second header byte
	if (buffer[0] != 0x40) return controllerValues;
	
	// Validate checksum
	uint16_t calculatedChecksum = 0xFFFF - 0x20;
	for (int i = 0; i < 29; i++) {
		calculatedChecksum -= buffer[i];
	}
	uint16_t receivedChecksum = combineBytes_(buffer[29], buffer[30]);
	if (receivedChecksum != calculatedChecksum) return controllerValues;

	// Extract channels
	uint16_t channels[6];
	for (int i = 0; i < 6; i++) {
		channels[i] = combineBytes_(
			buffer[(i * 2) + 1],
			buffer[(i * 2) + 2]
		);
	}

	// Convert channels to controller values
	controllerValues.throttle = (channels[2] - 1000) / 1000.0f;
	controllerValues.leftPot  = (channels[4] - 1000) / 1000.0f;
	controllerValues.rightPot = (channels[5] - 1000) / 1000.0f;
	// Normalize from -1 to 1
	float normalizedPitch = (static_cast<int>(channels[1]) - 1500) / 500.0f;
	float normalizedRoll  = (static_cast<int>(channels[0]) - 1500) / 500.0f;
	float normalizedYaw   = (static_cast<int>(channels[3]) - 1500) / 500.0f;
	// -maxRotationRate to maxRotationRate
	controllerValues.pitch = normalizedPitch * maxRotationRates_.pitch;
	controllerValues.roll  = normalizedRoll * maxRotationRates_.roll;
	controllerValues.yaw   = normalizedYaw * maxRotationRates_.yaw;

	controllerValues.isValid = true;
	return controllerValues;
}