#include <iostream>
#include <cmath>
#include <vector>

#include "sort.h"

const int iterations = 100000, N = 500;

int main(int argc, const char *argv[]) {

    double bwar = 0, qwar = 0;
    int bodch, qodch;

    auto b_est = [] (int n) {return 0.75*n*n;};
    auto q_est = [] (int n) {return 1.9*n*log(n);};

    for (int i = 0; i < iterations; i++) {

        std::cout << "\033c" << "iteracja: " << i << "/" << iterations << std::endl;

        std::vector<int> temp(N);
        Sort::populate(temp.begin(), temp.end());

        bwar += pow(Sort::use_sort("bubble sort", temp) - b_est(N),2);
        qwar += pow(Sort::use_sort("quick sort", temp) - q_est(N),2);

    }

    bodch = (int)sqrt(bwar/iterations);
    qodch = (int)sqrt(qwar/iterations);


    std::cout << "Wrażliwość sortowania bąbelkowego wynosi: "<< bodch << std::endl;
    std::cout << "Wrażliwość sortowania szybkiego wynosi: "<< qodch << std::endl;
}