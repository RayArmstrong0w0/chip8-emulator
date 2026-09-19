#include <iostream>
#include <cstdint> 

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
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t y = (opcode & 0x00F0) >> 4;
        uint16_t nnn = opcode & 0x0FFF; 
        uint8_t nn = opcode & 0x00FF;

        switch (tipoComando) {

            case 0x0:
            switch(opcode & 0x00FF){

                case 0xE0:
                break;

                case 0xEE:
                sp--;
                pc = stack[sp];
                break;
            }

            case 0x1:
            pc = nnn;
            std::cout << "Instrucao 0x1: Pulo (Jump) para o endereco 0x"
                      <<std::hex << nnn << std::dec << std::endl;
            break;

            case 0x2:
            stack[sp] = pc;
            sp++;
            pc = nnn;
            std::cout << "Instrucao 0x2: Chamando subrotina em 0x" 
                      << std::hex << nnn << std::dec << std::endl;
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
            std::cout << "Instrucao 0x4: Se V[" << (int)x << "] !a= 0x"
                      << std::hex << (int)nn << std::dec << std::endl;
            break;

            case 0x5:
            if(V[x] == V[y]){
                pc += 2;
            }
            std::cout << "Instrução 0x5: Se V[" << (int)x << "] == V[" << (int)y << "]" << std::endl;
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

            case 0x8:
            switch (opcode & 0x000F){
                case 0x0:
                V[x] = V[y];
                std::cout << "Instrucao 0x8XY0: V[" << (int)x << "] = V[" << (int)y << "]" << std::endl;
                break;

                case 0x1:
                V[x] = V[x] | V[y];
                std::cout << "Instrucao 0x8XY1: V[" << (int)x << "] |= V[" << (int)y << "]" << std::endl;
                break;

                case 0x2:
                V[x] = V[x] & V[y];
                std::cout << "Instrucao 0x8XY2: V[" << (int)x << "] &= V[" << (int)y << "]" << std::endl;
                break;

                case 0x3:
                V[x] = V[x] ^ V[y];
                std::cout << "Instrucao 0x8XY3: V[" << (int)x << "] ^= V[" << (int)y << "]" << std::endl;
                break;

                case 0x4:
                if(V[x] + V[y] > 255){
                    V[0xF] = 1;
                } else {
                    V[0xF] = 0;
                }
                V[x] += V[y];
                std::cout << "Instrucao 0x8XY4: V[" << (int)x << "] += V[" << (int)y << "] (Carry: " << (int)V[0xF] << ")" << std::endl;
                break;

                case 0x5:
                if(V[x] >= V[y]){
                    V[0xF] = 1;
                } else {
                    V[0xF] = 0;
                }
                V[x] -= V[y];
                std::cout << "Instrucao 0x8XY5: V[" << (int)x << "] -= V[" << (int)y << "] (NOT Borrow: " << (int)V[0xF] << ")" << std::endl;
                break;

                case 0x6:
                V[0xF] = V[x] & 1;
                V[x] = V[x] >> 1;
                std::cout << "Instrucao 0x8XY6: V[" << (int)x << "] >>= 1 (LSB: " << (int)V[0xF] << ")" << std::endl;
                break;

                case 0x7:
                if(V[y] >= V[x]){
                    V[0xF] = 1;
                } else {
                    V[0xF] = 0;
                }
                V[x] = V[y] - V[x];
                std::cout << "Instrucao 0x8XY7: V[" << (int)x << "] = V[" << (int)y << "] - V[" << (int)x << "] (NOT Borrow: " << (int)V[0xF] << ")" << std::endl;
                break;

                case 0xE:
                V[0xF] = (V[x] & 0x80) >> 7;
                V[x] = V[x] << 1;
                std::cout << "Instrucao 0x8XYE: V[" << (int)x << "] <<= 1 (MSB: " << (int)V[0xF] << ")" << std::endl;
                break;
            };
            break;

            case 0x9:
            if(V[x] != V[y]){
                pc += 2;
            }
            std::cout << "Instrução 0x9: Se V[" << (int)x << "] != V[" << (int)y << "]" << std::endl;
            break;

            case 0xA:
            I = nnn;
            std::cout << "Instruções 0xA: Registradores I atualizado para 0x"
                      <<  std::hex << I << std::dec << std::endl;
            break;

            case 0xB:
            pc = nnn + V[0];
            std::cout << "Instrucao 0xB: Pulo (Jump) para 0x" 
                      << std::hex << nnn << " + V[0]" << std::dec << std::endl;
            break;

            case 0xF:
            switch (opcode & 0x00FF){
                case 0x7:
                V[x] = DT;
                std::cout << "Instrucao 0xFX07: V[" << (int)x << "] recebeu valor do DT (" << (int)DT << ")" << std::endl;
                break;

                case 0x0A: {
                bool teclaPressionada = false;

                for(int i = 0; i < 16; i++){
                    if (teclado[i]){
                        V[x] = i;
                        teclaPressionada = true;
                        break;
                    }
                }

                if (!teclaPressionada){
                    pc -= 2;
                }
                std::cout << "Instrucao 0xFX0A: Aguardando entrada de tecla..." << std::endl;
                break;
            }

                case 0x15:
                DT = V[x];
                std::cout << "Instrucao 0xFX15: DT atualizado para 0x" 
                          << std::hex << (int)V[x] << std::dec << " via V[" << (int)x << "]" << std::endl;
                break;

                case 0x18:
                ST = V[x];
                break;

                case 0x1E:
                I = I + V[x];
                break;

                case 0x29:
                I = 0x050 + (V[x] * 5);
                std::cout << "Instrucao 0xFX29: Registrador I apontado para a fonte do digito 0x" 
                          << std::hex << (int)V[x] << std::dec << std::endl;
                break;

                case 0x33:
                memory[I] = V[x] / 100;
                memory[I+1] = (V[x] / 10) % 10;
                memory[I+2] = V[x] % 10;
                std::cout << "Instrucao 0xFX33: BCD de V[" << (int)x << "] (" << (int)V[x] 
                          << ") salvo em memory[" << std::hex << I << "]" << std::dec << std::endl;
                break;

                case 0x55:
                for(int i = 0; i <= x; i++){
                    memory[I + i] = V[i];
                }
                std::cout << "Instrucao 0xFX55: Registradores V0 ate V[" << (int)x 
                          << "] salvos na memoria a partir de 0x" << std::hex << I << std::dec << std::endl;
                break;

                case 0x65:
                for(int i = 0; i <= x; i++){
                    V[i] = memory[I + i];
                }
                std::cout << "Instrucao 0xFX65: Registradores V0 ate V[" << (int)x 
                          << "] carregados a partir da memoria (0x" << std::hex << I << std::dec << ")" << std::endl;
                break;
            }

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

    std::cout << "Emulador CHIP-8 inicializado com sucesso!" << std::endl;
    std::cout <<"Program Counter (PC) posicionado em: 0x"
              << std::hex << emulador.pc << std::dec << std::endl;

    return 0;
}