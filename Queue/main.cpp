#include <iostream>

#include "Queue.h"

int main() {
    int x = 0;
    int e;
    Queue<int> *queue = nullptr;
    std::cout << "Wybierz 0 (stos tablicowy) lub 1 (stos listowy):";
    std::cin >> x;

    if (x == 0) queue = new ArrayQueue<int>();
    else if (x == 1) queue = new PointerQueue<int>();

    while (x != 5){

        queue->print();
        std::cout << "Wpisz:" << std::endl;
        std::cout << "1 - put(e)"<< std::endl;
        std::cout << "2 - poll()"<< std::endl;
        std::cout << "3 - isFull()"<< std::endl;
        std::cout << "4 - isEmpty()"<< std::endl;
        std::cout << "5 - wyjdź"<< std::endl;
        std::cin >> x;

        if (x == 1)
            std::cout << "Podaj element: ";

        switch (x) {
            case 1:
                std::cin >> e;
                queue->put(e);
                break;
            case 2:
                std::cout << "Wyciągnięto: " << queue->poll() << std::endl;
                break;
            case 3:
                std::cout << "Czy jest pełen: " << queue->isFull() << std::endl;
                break;
            case 4:
                std::cout << "Czy jest pusty: " << queue->isEmpty() << std::endl;
                break;
            default: break;
        }
    }
    delete queue;
    return 0;
}
