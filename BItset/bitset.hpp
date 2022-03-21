

template <const int MIN, const int MAX>
struct BitArr {
    unsigned char arr[(MAX - MIN)/8 + 1]{};
    const unsigned int size = (MAX - MIN)/8 + 1;
};

template<const int MIN=0, const int MAX=15>
class BitSet {
    BitArr<MIN,MAX> array{};

    bool inline constexpr isInBounds(int val) const;

public:
    void clear() noexcept;
    bool constexpr isEmpty() noexcept;

    void insert(int value) noexcept;
    void remove(int value) noexcept;
    bool contains(int value) const noexcept;

    void Union(const BitSet<MIN,MAX> & other) noexcept;
    void intersection(const BitSet<MIN,MAX> & other) noexcept;
    void difference(const BitSet<MIN,MAX> & other) noexcept;

    void print() const;

};

#include "bitset.tpp"

