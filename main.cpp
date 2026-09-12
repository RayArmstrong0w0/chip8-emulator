#include <iostream>
#include <cstdint> 

class Chip8 {
public:
    uint8_t memory[4096];  
    uint8_t V[16];      
    uint16_t I;
    uint16_t pc;            

    Chip8() {
        pc = 0x200;    
        I = 0;

        for (int i = 0; i < 4096; i++){
            memory[i] = 0;
        }
    }

    void cycle() {
        
        uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
        pc += 2;

        uint8_t tipoComando = (opcode & 0xF000) >> 12;
        uint16_t nnn = opcode & 0x0FFF;          
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = opcode & 0x00FF;

        switch (tipoComando) {

            case 0x1:
            pc = nnn;
            std::cout << "Instrucao 0x1: Pulo (Jump) para o endereco 0x"
                      <<std::hex << nnn << std::dec << std::endl;
            break;

            case 0x3:
            if (V[x] == nn) {
                pc += 2;
            }
            std::cout << "Instrucao 0x3: Se V[" << (int)x << "] == 0x"
                      << std::hex << (int)nn << std::dec << std::endl;
            break;

            case 0x4:
            if(V[x] != nn){
                pc += 2;
            }
            std::cout << "Instrucao 0x4: Se V[" << (int)x << "] != 0x"
                      << std::hex << (int)nn << std::dec << std::endl;
            break;

            case 0x6:
            V[x] = nn;
            std::cout << "Instrucao 0x6: Registrador V["<< (int)x <<"] recebeu o valor 0x"
                      << std::hex << (int)V[x] << std::dec << std::endl;
            break;

            case 0x7:
            V[x] += nn;
            std::cout << "Instrucao 0x7: Registrador V["<< (int)x <<"] somou o valor 0x"
                      << std::hex << (int)V[x] << std::dec << std::endl;
            break;

            case 0xA:
            I = nnn;
            std::cout << "Instruções 0xA: Registradores I atualizado para 0x"
                      <<  std::hex << I << std::dec << std::endl;
            break;

            default:
                std::cout << "Intruções não reconhecido"
                          <<std::hex << opcode << std::dec << std::endl;
            break;
        }

        std::cout << "Opcode lido: x0" << std::hex << opcode << std::dec << std::endl;
    };
};

int main() {
    Chip8 emulador;

    emulador.memory[0x200] = 0x60;
    emulador.memory[0x201] = 0x05;

    emulador.memory[0x202] = 0x40;
    emulador.memory[0x203] = 0x0A;

    emulador.memory[0x204] = 0x60;
    emulador.memory[0x205] = 0x09;

    emulador.memory[0x206] = 0x70;
    emulador.memory[0x207] = 0x01;

    emulador.cycle();
    emulador.cycle();
    emulador.cycle();

    std::cout << "Emulador CHIP-8 inicializado com sucesso!" << std::endl;
    std::cout <<"Program Counter (PC) posicionado em: 0x"
              << std::hex << emulador.pc << std::dec << std::endl;

    return 0;
}