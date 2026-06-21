#ifndef UTILS_H_
#define UTILS_H_

int fputc(int ch, FILE *f);

/* reads the data in the rx_buffer and increment the tail count in rx_buffer */
int Uart_read(void);
/* writes the data to the tx_buffer and increment the head count in tx_buffer */
void Uart_write(int c);
/* function to send the string to the uart */
void Uart_sendstring(const char *s);

/* Checks if the data is available to read in the rx_buffer */
int IsDataAvailable(void);

void serial_gets(char *buffer);
char serial_getchar(void);
int serial_printf(char *format, ...);

void removeStringTrailingNewline(char *str);
void GetAnyKey(void);

void AnsiClearDisplay(void);
void AnsiEraseLine(void);
void AnsiSaveCursorPosition(void);
void AnsiRestoreCursorPosition(void);
void AnsiHideCursor(void);
void AnsiShowCursor(void);

int getBit(int bit, int value);
uint8_t revert_bits(uint8_t in);
uint16_t revert_word(uint16_t in);

char in_b_k(uint8_t *data);
char setbyte(uint8_t *data);
char setword(uint16_t *address);

bool Ascii2Hex(char *c);
bool SerialGetAsciiuint8_t(uint8_t *data);
bool SerialGetAsciiWord(uint16_t *addr);

#endif /* UTILS_H_ */
