/*
 * LaunchPad.h
 *
 *Created on: Apr 3, 2013
 *      Author: Jordan Retz
 *Revised on: Oct 23, 2014
 *      Author: jnjuguna
 *
 *  Note: Make sure that C:/ti/TivaWare_C_Series-2.1.0.12573 is located under the "Includes" drop down
 *  in the Project. If not:
 *  	1. Go to Properties->Include Options and add this location
 *
 */



#ifndef LAUNCHPAD_H_
#define LAUNCHPAD_H_

#include <time.h>

#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/asmdefs.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_adc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_can.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_comp.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_eeprom.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_epi.h"
//#include "inc/hw_ethernet.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_fan.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_flash.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_gpio.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_hibernate.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_i2c.h"
//#include "inc/hw_i2s.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_ints.h"
//#include "inc/hw_lpc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_memmap.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_nvic.h"
//#include "inc/hw_peci.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_pwm.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_qei.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_ssi.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_sysctl.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_sysexc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_timer.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_types.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_uart.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_udma.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_usb.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/inc/hw_watchdog.h"

/*
 * Include All Peripheral Driver Headers
 */
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/adc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/can.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/comp.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/cpu.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/debug.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/eeprom.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/epi.h"
//#include "driverlib/ethernet.h"
//#include "driverlib/fan.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/flash.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/fpu.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/gpio.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/hibernate.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/i2c.h"
//#include "driverlib/i2s.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/interrupt.h"
//#include "driverlib/lpc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/mpu.h"
//#include "driverlib/peci.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/pin_map.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/pwm.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/qei.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/rom_map.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/rom.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/rtos_bindings.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/ssi.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/sysctl.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/sysexc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/systick.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/timer.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/uart.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/udma.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/usb.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/watchdog.h"

/*
 * Include All Utility Drivers
 */
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/cmdline.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/cpu_usage.h"
//#include "utils/crc.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/flash_pb.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/isqrt.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/ringbuf.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/scheduler.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/sine.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/softi2c.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/softssi.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/softuart.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/uartstdio.h"
#include "C:/ti/TivaWare_C_Series-2.1.0.12573/utils/ustdlib.h"

/*
 * On board button (switch) definitions
 */
#define lpSWPort	GPIO_PORTF_BASE
#define lpSW1Port	GPIO_PORTF_BASE
#define lpSW2Port	GPIO_PORTF_BASE
#define lpSW1		GPIO_PIN_4
#define lpSW2		GPIO_PIN_0




#endif /* LAUNCHPAD_H_ */
