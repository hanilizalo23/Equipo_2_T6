/**
	\file
	\brief
		This is a starter file to implement a function able to produce an accurate delay
		using the PIT module.
	\author PhD. José Luis Pizano Escalante
	\completed by Nelida Paulina Hernández Moya
	\date	19/02/2022
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (0.000001F)

int main(void)
{
	uint8_t pit_inter_status = FALSE;

	gpio_pin_control_register_t pin_control_register_bit_d_0 = GPIO_MUX1;
	GPIO_clock_gating(GPIO_D);
	GPIO_pin_control_register(GPIO_D, bit_0, &pin_control_register_bit_d_0);
	GPIO_data_direction_pin(GPIO_D,GPIO_OUTPUT, bit_0);
	GPIO_set_pin(GPIO_D, bit_0);

	PIT_clock_gating();
	PIT_enable();

	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_global_enable_interrupts;

	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);

	while(1)
	{
		do
		{
			pit_inter_status =  PIT_get_interrupt_flag_status();
		}
		while(FALSE == pit_inter_status);

		GPIO_toogle_pin(GPIO_D, bit_0);

		PIT_clear_interrupt_flag();
	}
	return 0;
}
