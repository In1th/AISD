#include <iostream>

#include "PointerList.h"

int main() {
    int x;
    PointerList<int> *list = nullptr;
    std::cout << "Wybierz 0 (lista jednokierunkowa) lub 1 (lista dwukierunkowa):";
    std::cin >> x;

    if (x == 0) list = new OneWayPointerList<int>();
    else if (x == 1) list = new TwoWayPointerList<int>();

    std::string message;
    bool isIn;
    int e, i;

    while(x != 7 && list != nullptr){

        std::cout << "\033c";
        if (x == 5){
            message = (isIn)?("tak"):("nie");
            std::cout<<"Czy "<<e<<" jest w liście? "<<message<<std::endl;
        }
        list->print();
        std::cout << "Wpisz:" << std::endl;
        std::cout << "1 - add(e)"<< std::endl;
        std::cout << "2 - add(e,i)"<< std::endl;
        std::cout << "3 - remove(e)"<< std::endl;
        std::cout << "4 - remove(i)"<< std::endl;
        std::cout << "5 - contains(e)"<< std::endl;
        std::cout << "6 - sort()"<< std::endl;
        std::cout << "7 - wyjdź"<< std::endl;
        std::cin >> x;

        if (x > 0 && x < 6){
            std::cout << "Podaj argumenty: ";

            switch (x) {
                case 1:
                    std::cin >> e;
                    list->add(e);
                    break;
                case 2:
                    std::cin >> e >> i;
                    list->add(e, i);
                    break;
                case 3:
                    std::cin >> e;
                    list->remove_e(e);
                    break;
                case 4:
                    std::cin >> i;
                    list->remove_i(i);
                    break;
                case 5:
                    std::cin >> e;
                    isIn = list->contains(e);
                    break;
            }
        }
        else if (x == 6) {
            list->sort();
        }

    }


    return 0;
}
