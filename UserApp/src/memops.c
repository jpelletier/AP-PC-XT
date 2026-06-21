/*---------------------------------------------------------------------------*
 * memops.c                                                                  *
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

void fillMemory(void)
{
	char c;
	uint16_t start, end;
	uint16_t i;
	uint8_t segment, data_byte;

	Uart_sendstring("Fill segment: ");

	c = setbyte(&segment);

	if (c != 'Q')
	{
		Uart_sendstring(" start: ");

		c = setword(&start);

		if (c != 'Q')
		{
			Uart_sendstring(" to end: ");
			c = setword(&end);
			if (c != 'Q')
			{
				Uart_sendstring(" value: ");
				c = setbyte(&data_byte);
				if (c != 'Q')
				{
					for (i = start; i <= end; i++)
					{
						TargetMemWr(0,segment,i,data_byte);
					}
				}
			}
		}
	}
}

void moveMemory(void)
{
	char c;
	uint16_t start = 0, end = 0, dest = 0;
	uint16_t i, length;
	uint8_t segment, data_byte;

	Uart_sendstring("Move segment: ");

	c = setbyte(&segment);

	if (c != 'Q')
	{
		Uart_sendstring(" start: ");

		c = setword(&start);

		if (c != 'Q')
		{
			Uart_sendstring(" to end: ");
			c = setword(&end);
			if (c != 'Q')
			{
				Uart_sendstring(" dest: ");
				c = setword(&dest);
				if (c != 'Q')
				{
					//Check for move
					if (start != dest)
					{
						length = end - start + 1;

						//Check direction to support overlap
						if (dest > start)
						{
							dest += (length -1);

							// From end to start
							i = length;
							do
							{
								putchar('-');
								data_byte = TargetMemRd(0,segment,end--);
								TargetMemWr(0,segment,dest--,data_byte);
							} while (--i);
						}
						else
						{
							// From start to end
							i = length;
							do
							{
								putchar('+');
								data_byte = TargetMemRd(0,segment,start++);
								TargetMemWr(0,segment,dest++,data_byte);
							} while (--i);
						}
						Uart_sendstring("Move done!\r\n");
					}
					else
					{
						Uart_sendstring("No move: source = dest\r\n");
					}
				}
				else
				{
					Uart_sendstring("Cancelled move\r\n");
				}
			}
		}
	}

	GetAnyKey();
}

#if 0
void loadIntelHex(void)
{
	char line_input[128];
    char Data_Str[128];

	char *str;

	unsigned int nb_record;
	ushort BytesTotal;
	int result;

	unsigned int address;
	unsigned int nb_bytes, record_type;
	unsigned int data_byte, checksum;

	bool checksumBad = false;

	Uart_sendstring("\r\nWaiting for Hex file transfer\r\n");

	nb_record = 0;
	BytesTotal = 0;

	do
    {
		Uart_write('\021');	//XON
		serial_gets(line_input);

#ifdef USE_CODE_DEBUG_INTEL_HEX
		Uart_sendstring(line_input);
#endif

		Uart_write('\023');	//XOFF

    	nb_record++;

        /* Remove carriage return/line feed at the end of line. */
    	removeStringTrailingNewline(line_input);

    	result = sscanf(line_input, ":%02X%04X%02X%s", &nb_bytes, &address, &record_type, Data_Str);
    	if (result != 4)
    	{
#ifdef USE_CODE_DEBUG_INTEL_HEX
			serial_printf("\r\nLine %d: data record, address: %04X, nb bytes: %d\r\n", nb_record, address, nb_bytes);
			serial_printf("Data_Str: %s\r\n", Data_Str);
#endif
    		serial_printf("%d: Error in line %d of hex file\n", __LINE__, nb_record);
    	}

    	checksum = nb_bytes + (address >> 8) + (address & 0xff) + record_type;
		str = Data_Str;

		switch(record_type)
		{
			case 0x00:
#ifdef USE_CODE_DEBUG_INTEL_HEX
				serial_printf("\r\nLine %d: data record, address: %04X, nb bytes: %d\r\n", nb_record, address, nb_bytes);
#endif
				// data records
				do
				{
					result = sscanf(str, "%02X", &data_byte);
					if (result != 1) serial_printf("%d: Error in line %d of hex file\r\n", __LINE__, nb_record);

					//store each byte
					TargetMemWr(0,address++,data_byte);

					BytesTotal++;
					str += 2;

					//calculate checksum
					checksum += data_byte;
				} while (--nb_bytes);

#ifdef USE_CODE_DEBUG_INTEL_HEX
				serial_printf("nb_bytes: %d, calculated checksum: %02X\r\n", nb_bytes, checksum & 0xFF);
#endif
				//get checksum
				result = sscanf(str, "%02X", &data_byte);
				if (result != 1) serial_printf("%d: Error %d in line %d of hex file\n", __LINE__, result, nb_record);

				//verify checksum
				checksum += data_byte;

				if ((checksum & 0xFF) == 0)
				{
					Uart_write('.');
				}
				else
				{
					serial_printf("%d: Checksum error in line %d: should be %02X\n",
							__LINE__, nb_record, (256 - checksum) & 0xFF);

					checksumBad = true;
					Uart_write('x');
				}
				if ((nb_record & 0x1F) == 0) Uart_sendstring("\r\n");
				break;

			case 0x01:
#ifdef USE_CODE_DEBUG_INTEL_HEX
				serial_printf("\r\nLine %d: last record, address: %04X, nb bytes: %d\r\n", nb_record, address, nb_bytes);
#endif
				//last record
				//get checksum
				sscanf(str, "%02X", &data_byte);

				//verify checksum
				checksum += data_byte;

#ifdef USE_CODE_DEBUG_INTEL_HEX
				serial_printf("nb_bytes: %d, calculated checksum: %02X\r\n", nb_bytes, checksum & 0xFF);
#endif
				checksumBad = ((checksum & 0xFF) != 0);

				//hex_end
				if (checksumBad)
				{
					Uart_sendstring("\r\nChecksum bad\r\n");
				}
				else
				{
					serial_printf("\r\nTransfer completed, number of bytes received: %d\r\n",BytesTotal);
				}
				return;

			default:
				;
		}
    } while (true);

	//Turn back on the flow control
	Uart_write('\021');	//XON
}
#endif // 0





