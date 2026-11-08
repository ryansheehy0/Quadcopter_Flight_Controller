#include "stm32f4xx_hal.h"
#include "usbd_cdc_if.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern UART_HandleTypeDef huart1;

void run();
int _write(int file, char *ptr, int len);

#ifdef __cplusplus
}
#endif