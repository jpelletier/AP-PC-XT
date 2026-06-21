/*---------------------------------------------------------------------------*
 * menus.c                                                               *
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

void mainMenu(void)
{
	char c;

	//Turns on software flow control
	Uart_sendstring("\021\033[2JXT Bus Alien probe\r\n\n");
	Uart_sendstring(
			"A: Bit test\r\n"
			"B: Bus transactions\r\n"
			"C: Bus repeated transactions\r\n"
			"D: Memory operations\r\n"
			);
	c = toupper(serial_getchar());
	switch(c)
	{
		case 'A':
			BitTestMenu();
			break;
		case 'B':
			BusTransactionsMenu();
			break;
		case 'C':
			BusRepeatTransactionsMenu();
			break;
		case 'D':
			MemoryOperationsMenu();
			break;
		default:
			;
	}
}


/*
Bit test
 */

void BitTestMenu(void)
{
	char c;

	//INACTIVE
	GPIOC->ODR = 0xFF00;

	Uart_sendstring("\033[2J\033[?25lBit test\r\n\n");
	AnsiSaveCursorPosition();

	do
	{
		Uart_sendstring("S ADDR DATA    S ADDR DATA\r\n");
		serial_printf("\033[44m%1X:%04X %02X\033[m      ",(GPIOE->ODR & 0x0F)>>12,GPIOD->ODR,GPIOC->ODR & 0xFF);
		serial_printf("\033[36m%1X:%04X %02X\033[m\r\n",(GPIOE->IDR & 0x0F)>>12,GPIOD->IDR,GPIOC->IDR & 0xFF);

		Uart_sendstring("JIHG:FEDC BA98 7654 3210  7654 3210\r\n");
		serial_printf("\033[44m%1d%1d%1d%1d:%1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d  %1d%1d%1d%1d %1d%1d%1d%1d\033[m\r\n",
				getBit(15,GPIOE->ODR), //A19-16
				getBit(14,GPIOE->ODR),
				getBit(13,GPIOE->ODR),
				getBit(12,GPIOE->ODR),
				getBit(15,GPIOD->ODR), //A15-0
				getBit(14,GPIOD->ODR),
				getBit(13,GPIOD->ODR),
				getBit(12,GPIOD->ODR),
				getBit(11,GPIOD->ODR),
				getBit(10,GPIOD->ODR),
				getBit( 9,GPIOD->ODR),
				getBit( 8,GPIOD->ODR),
				getBit( 7,GPIOD->ODR),
				getBit( 6,GPIOD->ODR),
				getBit( 5,GPIOD->ODR),
				getBit( 4,GPIOD->ODR),
				getBit( 3,GPIOD->ODR),
				getBit( 2,GPIOD->ODR),
				getBit( 1,GPIOD->ODR),
				getBit( 0,GPIOD->ODR),
				getBit( 7,GPIOC->ODR), //D7-0
				getBit( 6,GPIOC->ODR),
				getBit( 5,GPIOC->ODR),
				getBit( 4,GPIOC->ODR),
				getBit( 3,GPIOC->ODR),
				getBit( 2,GPIOC->ODR),
				getBit( 1,GPIOC->ODR),
				getBit( 0,GPIOC->ODR));

		Uart_sendstring("JIHG:FEDC BA98 7654 3210  7654 3210\r\n");
		serial_printf("\033[36m%1d%1d%1d%1d:%1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d %1d%1d%1d%1d  %1d%1d%1d%1d %1d%1d%1d%1d\033[m\r\n",
				getBit(15,GPIOE->IDR), //A19-16
				getBit(14,GPIOE->IDR),
				getBit(13,GPIOE->IDR),
				getBit(12,GPIOE->IDR),
				getBit(15,GPIOD->IDR), //A15-0
				getBit(14,GPIOD->IDR),
				getBit(13,GPIOD->IDR),
				getBit(12,GPIOD->IDR),
				getBit(11,GPIOD->IDR),
				getBit(10,GPIOD->IDR),
				getBit( 9,GPIOD->IDR),
				getBit( 8,GPIOD->IDR),
				getBit( 7,GPIOD->IDR),
				getBit( 6,GPIOD->IDR),
				getBit( 5,GPIOD->IDR),
				getBit( 4,GPIOD->IDR),
				getBit( 3,GPIOD->IDR),
				getBit( 2,GPIOD->IDR),
				getBit( 1,GPIOD->IDR),
				getBit( 0,GPIOD->IDR),

				getBit(7,GPIOC->IDR),
				getBit(6,GPIOC->IDR),
				getBit(5,GPIOC->IDR),
				getBit(4,GPIOC->IDR),
				getBit(3,GPIOC->IDR),
				getBit(2,GPIOC->IDR),
				getBit(1,GPIOC->IDR),
				getBit(0,GPIOC->IDR));

		serial_printf("MEMW \033[44m%1d\033[m  IOW \033[44m%1d\033[m  ALE \033[44m%1d\033[m  AEN \033[44m%1d\033[m  |\r\n",
				getBit(BIT_MEMW,GPIOC->ODR),
				getBit(BIT_IOW,GPIOC->ODR),
				getBit(BIT_ALE,GPIOC->ODR),
				getBit(BIT_AEN,GPIOC->ODR));

		serial_printf("MEMR \033[44m%1d\033[m  IOR \033[44m%1d\033[m  RST \033[44m%1d\033[m         | IORDY \033[36m%1d\033[m  IOCHK \033[36m%1d\033[m  TC \033[36m%1d\033[m\r\n",
				getBit(BIT_MEMR,GPIOC->ODR),
				getBit(BIT_IOR,GPIOC->ODR),
				getBit(BIT_RESET,GPIOB->ODR),
				getBit(BIT_IORDY,GPIOB->IDR),
				getBit(BIT_IOCHK,GPIOB->IDR),
				getBit(BIT_TC,GPIOE->IDR));

		Uart_sendstring(
				"0-F: toggle address lines 0-15\r\n"
				"G-J: toggle segment lines 16-19\r\n"
				"K-R: toggle data lines 0-7\r\n"
				"S: toggle MEMW      T: toggle MEMR\r\n"
				"U: toggle IOW       V: toggle IOR\r\n"
				"W: toggle ALE       Y: toggle AEN         Z: toggle RESET\r\n"
				"-: input            +: output\r\n"
				"\033[32mESC: return to previous menu\033[m\r\n\n"
				);

		if (IsDataAvailable()) {
			c = toupper(serial_getchar());
			switch(c)
			{
				case 'J':
					GPIOE->ODR ^= 0x8000;
					break;
				case 'I':
					GPIOE->ODR ^= 0x4000;
					break;
				case 'H':
					GPIOE->ODR ^= 0x2000;
					break;
				case 'G':
					GPIOE->ODR ^= 0x1000;
					break;
				case 'F':
					GPIOD->ODR ^= 0x8000;
					break;
				case 'E':
					GPIOD->ODR ^= 0x4000;
					break;
				case 'D':
					GPIOD->ODR ^= 0x2000;
					break;
				case 'C':
					GPIOD->ODR ^= 0x1000;
					break;
				case 'B':
					GPIOD->ODR ^= 0x0800;
					break;
				case 'A':
					GPIOD->ODR ^= 0x0400;
					break;
				case '9':
					GPIOD->ODR ^= 0x0200;
					break;
				case '8':
					GPIOD->ODR ^= 0x0100;
					break;
				case '7':
					GPIOD->ODR ^= 0x0080;
					break;
				case '6':
					GPIOD->ODR ^= 0x0040;
					break;
				case '5':
					GPIOD->ODR ^= 0x0020;
					break;
				case '4':
					GPIOD->ODR ^= 0x0010;
					break;
				case '3':
					GPIOD->ODR ^= 0x0008;
					break;
				case '2':
					GPIOD->ODR ^= 0x0004;
					break;
				case '1':
					GPIOD->ODR ^= 0x0002;
					break;
				case '0':
					GPIOD->ODR ^= 0x0001;
					break;
				case 'K':
					GPIOC->ODR ^= 0x01;
					break;
				case 'L':
					GPIOC->ODR ^= 0x02;
					break;
				case 'M':
					GPIOC->ODR ^= 0x04;
					break;
				case 'N':
					GPIOC->ODR ^= 0x08;
					break;
				case 'O':
					GPIOC->ODR ^= 0x10;
					break;
				case 'P':
					GPIOC->ODR ^= 0x20;
					break;
				case 'Q':
					GPIOC->ODR ^= 0x40;
					break;
				case 'R':
					GPIOC->ODR ^= 0x80;
					break;
				case 'S':
					GPIOC->ODR ^= MASK_MEMW;
					break;
				case 'T':
					GPIOC->ODR ^= MASK_MEMR;
					break;
				case 'U':
					GPIOC->ODR ^= MASK_IOW;
					break;
				case 'V':
					GPIOC->ODR ^= MASK_IOR;
					break;
				case 'W':
					GPIOC->ODR ^= MASK_ALE;
					break;
				case 'Y':
					GPIOC->ODR ^= MASK_AEN;
					break;
				case 'Z':
					GPIOB->ODR ^= MASK_RESET;
					break;
				case '-':
					//set data direction in
					GPIOC->MODER = 0x55550000;
					break;
				case '+':
					//set data direction out
					GPIOC->MODER = 0x55555555;
					break;
				case ESC:
					Uart_sendstring("\033[?25h\033[m\r\n");
					return;
				default:
					;
			}
		}
		else
		{
			HAL_Delay(100);
		}

		AnsiRestoreCursorPosition();

	} while (true);
}

void BusTransactionsMenu(void)
{
	char c;
	uint16_t address;
	uint8_t segment, data_byte;

	segment = 0;
	address = 0;
	data_byte = 0;

	Uart_sendstring("\033[2JBus transactions\r\n");
	Uart_sendstring(
			"                              Byte/Word edit\r\n"
			"A: set address                + increment\r\n"
			"B: set data                   - decrement\r\n"
			"C: set segment                Z reset to zero\r\n"
			"D: do 1 memory read cycle     ! invert bits\r\n"
			"E: do 1 memory write cycle    ~ negate          (value = -value)\r\n"
			"F: do 1 IO port read cycle    R reverse bits    (0..7 -> 7..0)\r\n"
			"G: do 1 IO port write cycle  ⌫  remove nibble   (3F - 03)\r\n"
			"ESC: quit                     Q abandon changes\r\n\n"
			);

	AnsiSaveCursorPosition();

	do
	{
		serial_printf("[%02X:%04X] %02X\r\n", segment & 0x0F, address, data_byte);

		c = toupper(serial_getchar());
		switch(c)
		{
			case 'A':
				Uart_sendstring("\033[12;5H\033[37;44m"); //Address
				setword(&address);
				Uart_sendstring("\033[m");
				break;
			case 'B':
				Uart_sendstring("\033[12;11H\033[37;44m"); //Data
				setbyte(&data_byte);
				Uart_sendstring("\033[m");
				break;
			case 'C':
				Uart_sendstring("\033[12;2H\033[37;44m"); //Segment
				setbyte(&segment);
				segment &= 0x0F;
				Uart_sendstring("\033[m");
				break;
			case 'D':
				data_byte = TargetMemRd(0, segment, address);
				break;
			case 'E':
				TargetMemWr(0,segment,address,data_byte);
				break;
			case 'F':
				data_byte = TargetIoRd(0,address);
				break;
			case 'G':
				TargetIoWr(0,address, data_byte);
				break;
			case ESC:
				return;
		}

		AnsiRestoreCursorPosition();

	} while (true);
}

/* hardware diag with scope */
void BusRepeatTransactionsMenu(void)
{
	char c;
	uint16_t address = 0;
	uint8_t data_byte = 0;
	uint8_t segment = 0;

	Uart_sendstring("\033[2JBus transaction loops\r\n\n");
	Uart_sendstring(
			"A: set address\r\n"
			"B: set data\r\n"
			"C: set segment\r\n"
			"D: memory read cycles\r\n"
			"E: memory write cycles\r\n"
			"F: IO port read cycles\r\n"
			"G: IO port write cycles\r\n"
			"ESC: quit\r\n\n"
			);

	do
	{
		serial_printf("[%02X:%04X] %02X\r\n", segment, address, data_byte);

		c = toupper(serial_getchar());
		switch(c)
		{
			case 'A':
				Uart_sendstring("\033[12;5H\033[37;44m"); //Address
				setword(&address);
				Uart_sendstring("\033[m");
				break;
			case 'B':
				Uart_sendstring("\033[12;11H\033[37;44m"); //Data
				setbyte(&data_byte);
				Uart_sendstring("\033[m");
				break;
			case 'C':
				Uart_sendstring("\033[12;2H\033[37;44m"); //Segment
				setbyte(&segment);
				Uart_sendstring("\033[m");
				break;
			case 'D':
				AnsiSaveCursorPosition();
				AnsiHideCursor();
				do
				{
					serial_printf("Mem read at [%04X:%04X] %02X\r\n", segment, address, TargetMemRd(0, segment, address));
					AnsiRestoreCursorPosition();
				} while (!IsDataAvailable());
				AnsiEraseLine();
				break;
			case 'E':
				AnsiSaveCursorPosition();
				AnsiHideCursor();
				do
				{
					serial_printf("Mem write at [%04X:%04X] %02X\r\n", segment, address, data_byte);
					TargetMemWr(0, segment, address, data_byte);
					AnsiRestoreCursorPosition();
				} while (!IsDataAvailable());
				AnsiEraseLine();
				break;
			case 'F':
				AnsiSaveCursorPosition();
				AnsiHideCursor();
				do
				{
					serial_printf("IO read at %04X: %02X\r\n", address, TargetIoRd(0,address));
					AnsiRestoreCursorPosition();
				} while (!IsDataAvailable());
				AnsiEraseLine();
				break;
			case 'G':
				AnsiSaveCursorPosition();
				AnsiHideCursor();
				do
				{
					serial_printf("IO write at %04X: %02X\r\n", address, data_byte);
					TargetIoWr(0,address, data_byte);
					AnsiRestoreCursorPosition();
				} while (!IsDataAvailable());
				AnsiEraseLine();
				break;

			case ESC:
				AnsiShowCursor();
				return;
			default:
				;
		}
		// Go to 12:1
		Uart_sendstring("\033[12;1H");

	} while (true);
}

void MemoryOperationsMenu(void)
{
	char c;
	uint8_t data_byte;
	uint8_t port;

	AnsiSaveCursorPosition();

	do
	{
		Uart_sendstring("\033[2JMemory operations\r\n\n");
		Uart_sendstring(
				"E: edit memory\r\n"
//				"L: load Intel hex file\r\n"
				"F: fill memory\r\n"
				"M: move memory\r\n"
				"I: input\r\n"
				"O: output\r\n"
				"Q: quit\r\n\n"
				);
		c = toupper(serial_getchar());
		switch(c)
		{
			case 'E':
				binary_ed(0,0);
				break;
//			case 'L':
//				loadIntelHex();
//				GetAnyKey();
//				break;
			case 'F':
				fillMemory();
				break;
			case 'M':
				moveMemory();
				break;
			case 'I':
				Uart_sendstring("Input port: ");
				c = setbyte(&port);
				if (c != 'Q')
				{
					data_byte = TargetIoRd(0, port);
					serial_printf(" %02X\r\n",data_byte);
				}
				break;
			case 'O':
				Uart_sendstring("Output port: ");
				c = setbyte(&port);
				if (c != 'Q')
				{
					putchar(' ');
					c = setbyte(&data_byte);
					if (c != 'Q')
					{
						TargetIoWr(0,port, data_byte);
						Uart_sendstring("\r\n");
					}
				}
				break;
			case 'Q':
				return;
		}

		AnsiRestoreCursorPosition();

	} while (true);
}
