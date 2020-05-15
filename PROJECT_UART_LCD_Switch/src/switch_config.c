#include "STD_TYPES.h"
#include "switch_interface.h"
#include "GPIO.h"
#include "switch_config.h"

/* each object is defined by:
 * GPIO_t: object of GPIO,
 * activeState: SWITCH_ACTIVE_LOW, SWITCH_ACTIVE_HIGH */
Switch_cfg_t const sw_cfg[SWITCH_COUNT] = {
   {
      .switchIO = {
			.pin = GPIO_PIN11_SELECT,
			.port = GPIO_PIN11_PORTA,
			.mode = GPIO_PIN11_MODE_INPUT_PULL_UP_DOWN,
			.speed = GPIO_PIN11_SPEED_NONE,
      },

	  .activeState = SWITCH_ACTIVE_LOW,
   },
};
