/**
 * @author Armstrong H G Ramalho
 * @date 2022-04-19
 * Instruções:
 * Em ambiente linux deve-se por no console: g++ ARP_Armstrong.cpp -lpthread -o ARP_Armstrong && ./ARP_Armstrong
 */

#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

void lerFila(std::queue<std::string> &fila) {

    static std::mutex mutex;

    while (fila.size() != 0) {

        mutex.lock();
        
        std::cout << fila.front() << " lida" << std::endl;
        fila.pop();

        mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}

void colocarNaFila(std::queue<std::string> &fila) {
    static std::mutex mutex;
    static int contador = 1;

    while (true) {
        if (fila.size() == 10) {
            break;
        } else {
            mutex.lock();
            fila.push("Armstrong Puc " + std::to_string(contador++));
            mutex.unlock();
        }
    }
}

int main()
{
    std::queue<std::string> filaDeString;

    std::thread ThreadEscrever1(colocarNaFila, std::ref(filaDeString));
    std::thread ThreadEscrever2(colocarNaFila, std::ref(filaDeString));
    std::thread ThreadEscrever3(colocarNaFila, std::ref(filaDeString));

    ThreadEscrever1.join();
    ThreadEscrever2.join();
    ThreadEscrever3.join();

    std::thread ThreadLeitura(lerFila, std::ref(filaDeString));

    ThreadLeitura.join();

    return 0;
}