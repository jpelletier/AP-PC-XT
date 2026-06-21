#ifndef BUSCYCLES_H_
#define BUSCYCLES_H_

void TargetMemWr(size_t param, uint16_t segment, uint16_t address, uint8_t data);
uint8_t TargetMemRd(size_t param, uint16_t segment, uint16_t address);
void TargetIoWr(size_t param, uint16_t address, uint8_t io_data);
uint8_t TargetIoRd(size_t param, uint16_t address);

#endif /* BUSCYCLES_H_ */
