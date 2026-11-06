#include "../../controller.h"

void run() {
	Controller controller(&huart1);
	ControllerValues values;
	
	while(true) {
		values = controller.getValues();

		if (values.isValid) {
			printf("Throttle: %f\n", values.throttle);
			printf("Left Pot: %f\n", values.leftPot);
			printf("Right Pot: %f\n", values.rightPot);
			printf("Pitch: %f\n", values.pitch);
			printf("Roll: %f\n", values.roll);
			printf("Yaw: %f\n", values.yaw);
		} else {
			printf("Not valid\n");
		}

		HAL_Delay(100);
	}
}