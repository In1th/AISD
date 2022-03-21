#include <iostream>

#include "Stack.h"

int main() {
    int x = 0;
    int e;
    Stack<int> *stack = nullptr;
    std::cout << "Wybierz 0 (stos tablicowy) lub 1 (stos listowy):";
    std::cin >> x;

    if (x == 0) stack = new ArrayStack<int>();
    else if (x == 1) stack = new PointerStack<int>();

    while (x != 5){

    stack->print();
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
                stack->put(e);
                break;
            case 2:
                std::cout << "Wyciągnięto: " << stack->poll() << std::endl;
                break;
            case 3:
                std::cout << "Czy jest pełen: " << stack->isFull() << std::endl;
                break;
            case 4:
                std::cout << "Czy jest pusty: " << stack->isEmpty() << std::endl;
                break;
        }
    }
    delete stack;
    return 0;
}
