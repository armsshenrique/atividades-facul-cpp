/**
 * @Aluno: Armstrong H G Ramalho
 
 Exercicio: Em ambientes profissionais, não é raro encontrar Stacks para armazenamento de dados durante o
 processamento de tarefas, Nesta atividade sua tarefa será criar uma Stack usado std::stack para armazenar
 cem itens do tipo string. Esta Stack deve ser lida por dois threads distíntos e escrita por outro dois de forma
 assíncrona(não ao mesmo tempo). Para Isso você deverá, obrigatoriamente, utilizar a linguagem de programação C++ e as técnicas
 estudadas nesta disciplina.

* PARA RODAR EM LINUX DIGITAR NO CONSOLE: 
 1º Etapa: g++ ArmsVer2.cpp -lpthread -o ArmsVer2.out
 2º Etapa: ./ArmsVer2.out
 */
#include <iostream>
#include <string>
#include <thread>
#include <stack>
#include <mutex>
#include <chrono>

int LimiteDaStack = 100;

void EscrevendoStack(std::stack<std::string> & MinhaStack) {

    static std::mutex TravarEscrita;
    std::thread::id idThread = std::this_thread::get_id();

    while (true) {

        TravarEscrita.lock();

        if (MinhaStack.size() < LimiteDaStack) {
            std::cout << "Escrevendo Stack: [" << MinhaStack.size() << " PUCPR] - Thread utilizada: " << idThread << std::endl;
            MinhaStack.push(std::to_string(MinhaStack.size()) + " PUCPR");
        }

        TravarEscrita.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (MinhaStack.size() >= LimiteDaStack) {
            std::cout << "*** STACK ESCRITA ***" << std::endl;
            break;
        }
    }
}

void LendoStack(std::stack<std::string> & MinhaStack) {

    static std::mutex TravarLeitura;
    std::thread::id idThread = std::this_thread::get_id();

    while (true) {
       
        TravarLeitura.lock();

        if (MinhaStack.size() > 0) {
            std::cout << "Lendo Stack: [" << MinhaStack.top() << "] - Thread utilizada: " << idThread << std::endl;
            MinhaStack.pop();
        }

        TravarLeitura.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (MinhaStack.size() <= 0) {
            std::cout << "*** LEITURA FINALIZADA ***" << std::endl;
            break;
        }
    }
}

int main() {

    std::stack<std::string> MinhaStack;

    std::cout << "* Iniciando escrita da Stack" << std::endl;

    std::thread ThreadEscrever1(EscrevendoStack, std::ref(MinhaStack));
    std::thread ThreadEscrever2(EscrevendoStack, std::ref(MinhaStack));

    ThreadEscrever1.join();
    ThreadEscrever2.join();

    std::cout << "* Tamanho da Stack criada: " << MinhaStack.size() << std::endl; 
    std::cout << "* Iniciando leitura da Stack" << std::endl;

    std::thread ThreadLer1(LendoStack, std::ref(MinhaStack));
    std::thread ThreadLer2(LendoStack, std::ref(MinhaStack));

    ThreadLer1.join();
    ThreadLer2.join();
    
//    getchar();  # Adicione caso não consiga visualizar o resultado no executavel. 
    return 0;
}
