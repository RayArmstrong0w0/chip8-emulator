#include <iostream>
#include <cstdint> // Necessário para usar tipos com tamanho fixo (ex: uint8_t)

class Chip8 {
public:
    uint8_t memory[4096];    // Memória RAM de 4KB (4096 bytes)
    uint8_t V[16];           // 16 registradores de 8 bits (V0 até VF)
    uint16_t I;              // Registrador de índice (guarda endereços de memória)
    uint16_t pc;             // Program Counter (indica em qual byte da memória estamos)

    // Construtor: roda automaticamente quando o CHIP-8 é criado
    Chip8() {
        pc = 0x200;     // No CHIP-8, todos os jogos começam no endereço 512 (0x200) da RAM
        I = 0;

        // Limpa a memória RAM preenchendo tudo com 0
        for (int i = 0; i < 4096; i++){
            memory[i] = 0;
        }
    }

    void cycle() {
        
        // 1. FETCH (Busca de 2 bytes)
        uint16_t opcode = (memory[pc] << 8) | memory[pc + 1]; // 1. Monta o opcode
        pc += 2; // 2. Avança o PC em 2 para a próxima instrução

        // 2. DECODE (Fatiamento)
        uint8_t tipoComando = (opcode & 0xF000) >> 12; // Resultado: 0xA (ou 10)
        uint16_t nnn = opcode & 0x0FFF;                // Resultado: 0x2F0
        uint8_t x = (opcode & 0x0F00) >> 8;
        uint8_t nn = opcode & 0x00FF;

        // 3. EXECUTE (Tomada de decisão)
        switch (tipoComando) {

            case 0x1:
            pc = nnn;
            std::cout << "Instrucao 0x1: Pulo (Jump) para o endereco 0x"
                      <<std::hex << nnn << std::dec << std::endl;
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

    // Para testar, vamos colocar dois bytes de teste na memória

    //teste case

    emulador.memory[0x200] = 0x12;
    emulador.memory[0x201] = 0x06;

    emulador.memory[0x206] = 0x60;
    emulador.memory[0x207] = 0x0A;

    // Roda um ciclo da CPU

    // Roda 1º ciclo (executa o Pulo para 0x206)
    emulador.cycle();

    // Roda 2º ciclo (lê a gaveta 0x206 onde o pulo aterrissou)
    emulador.cycle();

    std::cout << "Emulador CHIP-8 inicializado com sucesso!" << std::endl;
    std::cout <<"Program Counter (PC) posicionado em: 0x"
              << std::hex << emulador.pc << std::dec << std::endl;

    return 0;
}