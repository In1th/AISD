

#include <algorithm>
#include <memory>

template<class T>
void Set<T>::insert(T value) noexcept {
    if (head == nullptr) {
        head = new Node<T>(value);
        size++;
        return;
    }

    node_ptr node = head;

    while(node->next != nullptr && node->next->value < value) {
        node = node->next;
    }

    auto new_node = new Node<T>(value,node->next);

    if(node->next != nullptr && node->next->value == value) {
        delete new_node;
        return;
    }

    if(node->value > value){
        new_node->next = head;
        head = new_node;
        return;

    }

    node->next = new_node;
    size++;
}

template<class T>
void Set<T>::remove(T value) noexcept {
    node_ptr node = head;

    if (node == nullptr) return;

    while(node->next != nullptr && node->next->value < value) {
        node = node->next;
    }

    if (node == head && node->value == value){
        head = node->next;
        delete node;
        size--;
        return;
    }

    if (node->next == nullptr || node->next->value != value) return;


    auto tmp = node->next;
    node->next = node->next->next;
    size--;
    delete tmp;
}

template<class T>
bool Set<T>::contains(T value) const noexcept {
    node_ptr node = head;
    while(node != nullptr){
        if (node->value == value) return true;
        node = node->next;
    }
    return false;
}

template<class T>
void Set<T>::Union(const Set<T> &other) noexcept {
    node_ptr node = other.head;
    while (node != nullptr){
        insert(node->value);
        node = node->next;
    }
}

template<class T>
void Set<T>::intersection(const Set<T> &other) noexcept {
    node_ptr node = head;
    while (node != nullptr){
        T val = node->value;
        node = node->next;
        if (!other.contains(val))
            remove(val);
    }
}

template<class T>
void Set<T>::difference(const Set<T> &other) noexcept {
    node_ptr node = other.head;
    while (node != nullptr){
        remove(node->value);
        node = node->next;
    }
}

template<class T> typename Set<T>::node_ptr Set<T>::getHead() noexcept {
    return head;
}

template <class T>
Set<T>& Set<T>::operator=(const Set<T>&& s) noexcept{
    this->clear();
    node_ptr node = s.getHead();
    while (node != nullptr){
        this->insert(node->value);
        node = node->next;
    }
    return *this;
}

template<class T>
void Set<T>::clear() noexcept {
    node_ptr node = head;
    while(node != nullptr){
        auto tmp = node->next;
        delete node;
        node = tmp;
    }
}

template<class T>
constexpr bool Set<T>::isEmpty() noexcept {
    return head == nullptr;
}


