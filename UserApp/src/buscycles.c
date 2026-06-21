/*---------------------------------------------------------------------------*
 * buscycles.c                                                               *
 * Copyright (C) 2022  Jacques Pelletier                                     *
 *                                                                           *
 * This program is free software; you can redistribute it and *or            *
 * modify it under the terms of the GNU General Public License               *
 * as published by the Free Software Foundation; either version 2            *
 * of the License, or (at your option) any later version.                    *
 *                                                                           *
 * This program is distributed in the hope that it will be useful,           *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 * GNU General Public License for more details.                              *
 *                                                                           *
 * You should have received a copy of the GNU General Public License         *
 * along with this program; if not, write to the Free Software Foundation,   *
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.           *
 *---------------------------------------------------------------------------*/
#include <target_probe.h>

void wait_half_cycle(void)
{
	asm("NOP");
	asm("NOP");
}

void wait_1_cycle(void)
{
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
}

//AD0-7		C0-7
//A8-15		D8-15
//A16-19	D0-3
void TargetMemWr(size_t param, uint16_t segment, uint16_t address, uint8_t data)
{
	GPIOA->ODR = segment;
	GPIOD->ODR = address;
	GPIOC->ODR = data;

	//MEMW = 0
	GPIOC->ODR = data | 0b1111111000000000;

	//set data direction out
	GPIOC->MODER = 0x55555555;

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	//MEMW = 0
	GPIOC->ODR = data | 0b1111111000000000;

	//Check wait input
	if ((GPIOF->IDR & GPIO_PIN_4) == 0)
	{
		wait_1_cycle();
	}

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	//INACTIVE
	GPIOC->ODR = 0xFF00;

	asm("NOP");
	asm("NOP");

	//set data direction in
	GPIOC->MODER = 0x55550000;
}

//AD0-7		C0-7
//A8-15		D8-15
//A16-19	D0-3
uint8_t TargetMemRd(size_t param, uint16_t segment, uint16_t address)
{
	uint8_t data_bus;
	uint8_t addr_low;

	addr_low = (uint8_t) (address & 0x00ff);

	GPIOA->ODR = segment;
	GPIOD->ODR = address ;

	// ALE


	//MEMR = 0
//	GPIOC->ODR = 0b1111110100000000;

	//set data direction in
	GPIOC->MODER = 0x55550000;

	wait_1_cycle();
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	//Check Ready input
	if ((GPIOE->IDR & GPIO_PIN_4) == 0)
	{
		wait_1_cycle();
	}

	data_bus = GPIOC->IDR;

	asm("NOP");
	asm("NOP");

	//INACTIVE
	GPIOC->ODR = 0xFF00;

	return data_bus;
}

void TargetIoWr(size_t param, uint16_t address, uint8_t io_data)
{
	GPIOD->ODR = address;

	//IORQ = 0, WR = 0
	GPIOC->ODR = io_data | 0b1111010100000000;

	//set data direction out
	GPIOC->MODER = 0x55555555;

	wait_1_cycle();

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	//Check wait input
	if ((GPIOF->IDR & GPIO_PIN_4) == 0)
	{
		wait_1_cycle();
	}

	//INACTIVE
	GPIOC->ODR = 0xFF00;

	//set data direction in
	GPIOC->MODER = 0x55550000;
}

uint8_t TargetIoRd(size_t param, uint16_t address)
{
uint8_t io_data;

	GPIOD->ODR = address;

	//set data direction in
	GPIOC->MODER = 0x55550000;

	//IORQ = 0, RD = 0
	GPIOC->ODR = 0b1111011000000000;

	wait_1_cycle();

	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");
	asm("NOP");

	//Check wait input
	if ((GPIOF->IDR & GPIO_PIN_4) == 0)
	{
		wait_1_cycle();
	}

	io_data = GPIOC->IDR;

	asm("NOP");
	asm("NOP");

	//INACTIVE
	GPIOC->ODR = 0xFF00;

	return io_data;
}

