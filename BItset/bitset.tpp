//
// Created by kruk on 14/03/2022.
//

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::clear() noexcept{
    for (auto &arrBlock: array.arr){
        arrBlock = 0;
    }
}
template<const int MIN, const int MAX>
bool constexpr BitSet<MIN,MAX>::isEmpty() noexcept{
    for (auto arrBlock: array.arr){
        if (arrBlock > 0) return false;
    }
    return true;
}

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::insert(int value) noexcept{
    if (!isInBounds(value)) return;
    array.arr[(value - MIN)/8] |= 1 << ((value - MIN)%8);
}

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::remove(int value) noexcept{
    if (!isInBounds(value)) return;
    array.arr[(value - MIN)/8] &= ~(1 << (value - MIN)%8);
}

template<const int MIN, const int MAX>
bool BitSet<MIN,MAX>::contains(int value) const noexcept{
    if (!isInBounds(value)) return false;
    bool x = (array.arr[(value - MIN)/8] >> (value - MIN)%8) & 1;
    return x;
}

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::Union(const BitSet<MIN,MAX> & other) noexcept{
    for (int i = MIN; i <= MAX; i++){
        if (other.contains(i)){
            insert(i);
        }
    }
}

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::intersection(const BitSet<MIN,MAX> & other) noexcept{
    for (int i = MIN; i <= MAX; i++){
        if ( !( other.contains(i) && contains(i) ) ){
            remove(i);
        }
    }
}

template<const int MIN, const int MAX>
void BitSet<MIN,MAX>::difference(const BitSet<MIN,MAX> & other) noexcept{
    for (int i = MIN; i <= MAX; i++){
        if (other.contains(i)){
            remove(i);
        }
    }
}

template<const int MIN, const int MAX>
bool constexpr inline BitSet<MIN, MAX>::isInBounds(int val) const{
    return val >= MIN && val <= MAX;
}

template<const int MIN, const int MAX>
void BitSet<MIN, MAX>::print() const{
    std::string str;
    for (u_int i = 0; i < array.size; i++){
       for(int j = 0; j < 8; j++){
           str = std::to_string(contains(MIN + 8*i + j)) + str;
       }
       str = " " + str;
    }
    std::cout << str << std::endl;
}
