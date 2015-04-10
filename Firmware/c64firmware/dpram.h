#ifndef DPRAM_H
#define DPRAM_H 1

void DPRAM_init();
void DPRAM_clear( uint16_t addr, uint16_t len);
void DPRAM_write( uint16_t addr, uint8_t byte );
uint8_t DPRAM_read( uint16_t addr);
uint8_t DPRAM_verify(uint16_t addr, uint16_t len);
uint16_t DPRAM_size();



#endif
