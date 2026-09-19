#include <iostream>
#include <fstream>
#include "Chip8.h"

int main() {
    
    std::ofstream arquivoTeste("teste.ch8", std::ios::binary);
    
    uint8_t romTeste[] = {
        0x00, 0xE0,
        0xA0, 0x50,
        0x12, 0x00
    };

    arquivoTeste.write(reinterpret_cast<char*>(romTeste), sizeof(romTeste));
    arquivoTeste.close();

    Chip8 emulador;

    if (emulador.loadROM("teste.ch8")) {
        for (int i = 0; i < 3; i++) {
            emulador.cycle();
        }
    }

    return 0;
}