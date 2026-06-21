/*---------------------------------------------------------------------------*
 * binedit.c                                                                 *
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

const char msg_help[] =
		"\033[46m"
		"\033[3;71H+: incr  "
		"\033[4;71H-: decr  "
		"\033[5;71H!: invert"
		"\033[6;71H~: negate"

		"\033[7;71HR: revers"
		"\033[8;71HBSP: SHR "
		"\033[9;71HZ: 00    "
		"\033[10;71HX: exit  "

		"\033[11;71HSP: store"
		"\033[12;71HCR: store"

		"\033[45m"
		"\033[13;71HT: L=00  "
		"\033[14;71HH: ->H   "

		"\033[15;71HL: ->L   "
		"\033[16;71HG: jmp   "
		"\033[17;71HU: ->HL  "
		"\033[18;71HM: cmds  "

		"\033[20;1H"
        "J: Jump relative\r\n"
        "N: Next 256 block\r\n"
        "P: Prev 256 block\r\n\033[m";

void move_cursor(uint16_t segment, uint16_t hl)
{
uint8_t row = ((hl & 0xff) >> 4) + 3;
uint8_t column = 3 * (hl & 0x0f) + 8; //6;

	serial_printf("\033[%d;%dH",row,column);
}

void restore_color(uint16_t segment,uint16_t address)
{
	serial_printf("\b\b\033[m%02X",TargetMemRd(0,segment,address));
}

uint16_t move_left(uint16_t segment, uint16_t hl)
{
	restore_color(segment,hl);

	//roll decrement
	hl = ((hl - 1) & 0x0f) | (hl & 0xfff0);
    move_cursor(segment,hl);

    return hl;
}

uint16_t move_right(uint16_t segment, uint16_t hl)
{
	restore_color(segment,hl);

	//roll increment
	hl = ((hl + 1) & 0x0f) | (hl & 0xfff0);
    move_cursor(segment,hl);

    return hl;
}

uint16_t move_up(uint16_t segment, uint16_t hl)
{
	restore_color(segment,hl);

	//roll decrement
	hl = ((hl - 0x10) & 0xff) | (hl & 0xff00);
    move_cursor(segment,hl);

    return hl;
}

uint16_t move_down(uint16_t segment, uint16_t hl)
{
	restore_color(segment,hl);

	//roll increment
	hl = ((hl + 0x10) & 0xff) | (hl & 0xff00);
    move_cursor(segment,hl);

    return hl;
}

void mem_dump(uint16_t segment, uint16_t address)
{
	uint8_t a,b;
	uint16_t hl;

	hl = address & 0xFF00;

	Uart_sendstring("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

    do
    {
		serial_printf("%04X ",hl);

		b = 16;
		do
		{
			serial_printf("%02X ",TargetMemRd(0,segment,hl++));
		} while (--b);

		hl -= 16;

		b = 16;
		do
		{
			a = TargetMemRd(0,segment,hl++);

			if ((a < 0x20) || (a > 0x7f)) a = '.';
			Uart_write(a);
		} while (--b);

		Uart_sendstring("\r\n");

    } while (hl & 0x00f0);
}

void update_dump(uint16_t segment, uint16_t hl)
{
	//home
	Uart_sendstring("\033[m\033[2;1H");

	//redraw
	mem_dump(segment,hl & 0xff00);
	Uart_sendstring(msg_help);
	move_cursor(segment,hl);
}

//Byte edit
//+      increment
//-      decrement
//!      invert
//~      negate
//R      reverse/swap bits 7:0 -> 0:7
//bsp    remove previous hex
//Z      00

//enter  accept byte and exit byte edit
//Q      scrap byte and exit byte edit
//
//c-A    left
//c-D    right
//c-W    up
//c-X    down
//T      L = 00
//H		 value -> L
//L      value -> L
//P      previous 256-byte block
//N      next 256-byte block
//X      exit binary editor

void binary_ed(uint16_t segment, uint16_t address)
{
	uint16_t hl = address;
	uint8_t a,b;

	restore_color(segment,hl);

	Uart_sendstring("\033[2JBinary editor\r\n");
    mem_dump(segment,address);
	Uart_sendstring(msg_help);
    //Uart_sendstring("\r\nLeft: \033[37;42mctl-A\033[m  right: \033[37;42mctl-D\033[m  down: \033[37;42mctl-X\033[m up: \033[37;42mctl-W\033[m\r\n");
    //Uart_sendstring("High: \033[37;42mH\033[m  low: \033[37;42mL\033[m  Relative jump: \033[37;42mJ\033[m  Absolute jump: \033[37;42mG\033[m\r\n");
    //Uart_sendstring("Previous block: \033[37;42mP\033[m  next block: \033[37;42mN\033[m  store value: \033[37;42menter\033[m  exit editor: \033[37;42mX\033[m\r\n");

    //goto row 3 column 6
    Uart_sendstring("\033[3;6H");

    do
    {
        Uart_sendstring("\033[44m");

        b = TargetMemRd(0,segment,hl);

        //byte edit
        a = in_b_k(&b);

        switch(a)
        {
        	//c-A arrow left
        	case 0x01:
        		hl = move_left(segment,hl);
				break;

        	//c-D arrow right
        	case 0x04:
        		hl = move_right(segment,hl);
				break;

        	//c-X arrow down
        	case 0x18:
        		hl = move_down(segment,hl);
				break;

        	//c-W arrow up
        	case 0x17:
        		hl = move_up(segment,hl);
				break;

        	case 0x1B:
        		a = serial_getchar();

        		if (a == '[')
        		{
            		a = serial_getchar();

            		switch(a)
            		{
            		case 'A':
                		hl = move_up(segment,hl);
        				break;
            		case 'B':
                		hl = move_down(segment,hl);
        				break;
            		case 'C':
                		hl = move_right(segment,hl);
        				break;
            		case 'D':
                		hl = move_left(segment,hl);
        				break;
            		}
        		}
        		break;

        	// absolute jump
        	case 'G':
        		hl = b | (TargetMemRd(0,segment,hl+1) << 8);

				update_dump(segment,hl);
				break;

			case 'T':
            	restore_color(segment,hl);
            	hl = hl & 0xff00;
				move_cursor(segment,hl);
				break;

            // high -> H = b
        	case 'H':
				hl = b << 8;
				update_dump(segment,hl);
				break;

			case 'L':
            	restore_color(segment,hl);
            	hl = (hl & 0xff00) | b;
				move_cursor(segment,hl);
				break;

            //relative jump
            case 'J':
            	restore_color(segment,hl);

        		hl = hl + b + 1;
            	if (b > 0x7f) hl -= 0x100;

				update_dump(segment,hl);
            	break;

            //previous 256-byte block
            case 'P':
            	hl -= 256;
				//keep color
				update_dump(segment,hl);
            	break;

            //next 256-byte block
            case 'N':
            	hl += 256;
				//keep color
				update_dump(segment,hl);
            	break;

            case 'X':
            	//exit editor
            	restore_color(segment,hl);
            	AnsiClearDisplay();
            	return;

            case 0x0d:
            case ' ':
            	TargetMemWr(0,segment,hl,b);

        		hl = move_right(segment,hl);
            	break;

            default:
            	;
		}

        Uart_write('\b');
    	Uart_write('\b');

    } while (true);
}

