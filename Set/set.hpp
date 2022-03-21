

template <class T> class Node {
public:
    T value;
    Node<T>* next{nullptr};

    explicit Node<T>(T val){
        value = val;
    }

    Node<T>(T val, Node<T>* ptr){
        value = val;
        next = ptr;
    }
};

template <class T>
class Set {

public:
    typedef Node<T>* node_ptr;

private:
    node_ptr head{nullptr};
    std::size_t size{0};

public:
    node_ptr getHead() noexcept;
    void clear() noexcept;
    bool constexpr isEmpty() noexcept;

    void insert(T value) noexcept;
    void remove(T value) noexcept;
    bool contains(T value) const noexcept;

    void Union(const Set<T> & other) noexcept;
    void intersection(const Set<T> & other) noexcept;
    void difference(const Set<T> & other) noexcept;

    Set& operator=(const Set<T>&& s) noexcept;
};


#include "set.tpp"