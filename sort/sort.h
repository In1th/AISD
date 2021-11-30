//
// Created by kruk on 21/10/2021.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H

#include <iostream>

int count = 0;

const int a = 1, b = 1.e6;

class Sort
{

    static bool compare(bool logical_value)
    {
        count++;
        return logical_value;
    }

    template <typename Iter>
    static void swap(Iter x1, Iter x2)
    {
        count++;
        auto buf = *x1;
        *x1 = *x2;
        *x2 = buf;
    }

public:

    template<typename Iter> static void populate(Iter beg, Iter end) {
        srand(time(nullptr));

        for (Iter it = beg; it != end; it++) {
            *it = (rand() % b) + a;
        }

    }

    template <typename Iter>
    static void qsort(Iter beg, Iter end)
    {
        if (end - beg <= 1)
            return;
        else
        {
            Iter pivot = beg;
            Iter store = beg + 1;

            for (Iter it = store; it != end; it++)
            {
                if (compare(*it <= *pivot))
                {
                    swap(it, store);
                    store++;
                }
            }
            swap(pivot, store - 1);

            qsort(beg, store - 1);
            qsort(store, end);
        }
    }

    template <typename Iter>
    static void bsort(Iter beg, Iter end)
    {
        Iter before_end = end;
        do
        {
            before_end--;

            for (Iter it = beg; it != before_end; it++) {

                if (compare(*it > *(it + 1)))
                    swap(it, it + 1);
            }
        } while (before_end != beg);
    }

    template <class Container>
    static int use_sort(std::string sorting_algorithm, Container container)
    {
        count = 0;
        if (sorting_algorithm == "bubble sort")
            bsort(container.begin(), container.end());
        else if (sorting_algorithm == "quick sort")
            qsort(container.begin(), container.end());

        return count;
    }
};

#endif //SORT_SORT_H
