#include <iostream>
#include <vector>
#include <cmath>

#include "sort.h"

#include "matplotlib.h"

namespace plt = matplotlibcpp;

const int NMAX = 500, iterations = 1000;


int main(int argc, const char *argv[]) {


    std::vector<int> x;
    std::vector<double> y1, y2;
    std::vector<double> y1_ocz, y2_ocz;

    for (int i = 1; i <= NMAX; i++){
        int bsum = 0, qsum = 0;

        for (int j = 0; j < iterations; j++){

            std::cout << "\033c" << "N: " << i <<"/"<<NMAX << " iteracja: " << j << "/" << iterations << std::endl;

            std::vector<int> temp(i);
            Sort::populate(temp.begin(), temp.end());

            bsum += Sort::use_sort("bubble sort",temp);
            qsum += Sort::use_sort("quick sort",temp);
        }

        x.push_back(i);

        y1.push_back(bsum*1.0f/iterations );
        y1_ocz.push_back(0.75*i*i);

        y2.push_back (qsum*1.0f/iterations );
        y2_ocz.push_back(1.9*i*log(i));
    }

    plt::figure_size(1200, 780);
    plt::title("Wykres ilości operacji dla dwóch algorytmów sortowania");
    plt::xlabel("Wielkość tablicy n");
    plt::ylabel("Ilość operacji dominujących T(n)");

    plt::named_plot("bubble sort",x,y1,"b");
    plt::named_plot("quick sort",x,y2,"r");

    plt::named_plot("0.75*n^2",x,y1_ocz,"g--");
    plt::named_plot("1.9*nlog(n)",x,y2_ocz,"y--");

    plt::xlim(0,NMAX);

    plt::legend();

    std::cout << "Generowanie wykresu się powiodło!" << std::endl;

    plt::save("wykres.png");
    plt::show();

    return 0;
}



