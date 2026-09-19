#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <string>

class Chip8 {
public:
    uint8_t memory[4096];  
    uint8_t V[16];      
    uint16_t I;
    uint16_t pc;     
    uint8_t DT = 0;
    uint8_t ST = 0;
    uint8_t sp = 0;
    uint16_t stack[16] = {0};
    bool teclado[16] = {false};
    uint8_t gfx[32][64];
      

    Chip8();

    bool loadROM(const std::string& caminhoArquivo);
    void cycle();

};

#endif