#include "run.h"
#include "../../controller.h"
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

void run() {
	Controller controller(&huart1);
	ControllerValues values;
	
	while(true) {
		values = controller.getValues();

		if (values.isValid) {
			printf("Throttle: %f\r\n", values.throttle);
			printf("Left Pot: %f\r\n", values.leftPot);
			printf("Right Pot: %f\r\n", values.rightPot);
			printf("Pitch: %f\r\n", values.pitch);
			printf("Roll: %f\r\n", values.roll);
			printf("Yaw: %f\r\n", values.yaw);
		} else {
			printf("Not valid\r\n");
		}

		HAL_Delay(100);
	}
}

int _write(int file, char *ptr, int len) {
	CDC_Transmit_FS((uint8_t*)ptr, len);
	return len;
}

#ifdef __cplusplus
}
#endif