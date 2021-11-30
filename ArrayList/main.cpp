#include <iostream>

#include "ArrayList.h"

int main() {
    int x;
    ArrayList<int> *arr = nullptr;
    std::cout << "Wybierz 0 (lista jednokierunkowa) lub 1 (lista dwukierunkowa):";
    std::cin >> x;

    if (x == 0) arr = new OneWayArrayList<int>();
    else if (x == 1) arr = new TwoWayArrayList<int>();

    std::string message;
    bool isIn;
    int e, i;

    while(x != 7 && arr != nullptr){

        std::cout << "\033c";
        if (x == 5){
            message = (isIn)?("tak"):("nie");
            std::cout<<"Czy "<<e<<" jest w liście? "<<message<<std::endl;
        }
        arr->print();
        std::cin >> x;

        if (x > 0 && x < 6){
            std::cout << "Podaj argumenty: ";

            switch (x) {
                case 1:
                    std::cin >> e;
                    arr->add(e);
                    break;
                case 2:
                    std::cin >> e >> i;
                    arr->add(e,i);
                    break;
                case 3:
                    std::cin >> e;
                    arr->remove_e(e);
                    break;
                case 4:
                    std::cin >> i;
                    arr->remove_i(i);
                    break;
                case 5:
                    std::cin >> e;
                    isIn = arr->contains(e);
                    break;
            }
        }
        else if (x == 6) {
            arr->sort();
        }

    }


    delete arr;
    return 0;
}
