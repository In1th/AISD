/**
    Created by Mateusz Kruk on 29/12/2021.
*/


/**BinNode methods overrides*/

constexpr inline int max(int a, int b) noexcept{
    return (a > b)? a : b;
}

template<class T>
BinNode<T>::BinNode(T val) {
    this->val = val;
}

template<class T>
constexpr int BinNode<T>::numberOfChildren() noexcept {
    int out = 0;
    if (left != nullptr) out++;
    if (right != nullptr) out++;
    return out;
}


/**BinTree find method (the same for every tree)*/

template<class T>
BinNode<T>* BinTree<T>::find(T val) {

    typename BinNode<T>::node_ptr current = root;
    while(current != nullptr){
        auto [value,left,right,height] = *current;
        if (value > val) current = left;
        else if (value < val) current = right;
        else return current;
    }
    return nullptr;
}

/**BinTree constructor*/

template <class T>
BinTree<T>::BinTree() {root = nullptr;}

template<class T>
int BinTree<T>::getHeight(BinNode<T>* node) noexcept {
    if (node == nullptr) return 0;
    return node->height;
}

template<class T>
BinNode<T> *BinTree<T>::insideInsert(T val, BinNode<T> *node) noexcept {
    typedef typename BinNode<T>::node_ptr node_ptr;
    if (node == nullptr) {
        return new BinNode<T>(val);
    }

    auto &[value,left,right,height] = *node;

    if (val < value)
        left = insideInsert(val,left);
    else if (val > value)
        right = insideInsert(val,right);
    else return node;

    node->height = max(this->getHeight(left),this->getHeight(right)) + 1;

    return node;
}

template<class T>
BinNode<T> *BinTree<T>::insideRemove(T val, BinNode<T> *node) noexcept {
    if (node == nullptr) return node;

    auto &[value,left,right,height] = *node;

    if (val < value)
        left = insideRemove(val,left);
    else if (val > value)
        right = insideRemove(val,right);
    else {
        this->removed = true;
        int numberOfChildren = node->numberOfChildren();
        if (numberOfChildren <= 1){
            auto buff = (left != nullptr)? left: right;
            if (buff != nullptr)
                *node = *buff;
            else {
                buff = node;
                node = nullptr;
            }
            delete buff;
        }
        else {
            auto buff = this->minValNode(right);
            value = buff->val;
            right = insideRemove(buff->val,right);
        }
    }

    if (node == nullptr) return node;

    height = max(this->getHeight(left),this->getHeight(right)) + 1;

    return node;
}

/**BST Tree interface methods*/

template<class T>
BSTTree<T>::BSTTree() {this->root = nullptr;}

template<class T>
void BSTTree<T>::insert(T val) noexcept {
   this->root = insideInsert(val,this->root);
}

template<class T>
BinNode<T> *BSTTree<T>::insideInsert(T val, BinNode<T> *node) noexcept {
    return BinTree<T>::insideInsert(val,node);
}

template<class T>
bool BSTTree<T>::remove(T val) noexcept {
    this->removed = false;
    this->root = insideRemove(val, this->root);
    return this->removed;
}

template <class T>
BinNode<T> *BSTTree<T>::insideRemove(T val, BinNode<T> *node) noexcept{
    return BinTree<T>::insideRemove(val, node);
}

template<class T>
BinNode<T> *BinTree<T>::minValNode(BinNode<T> *node) noexcept {
    BinNode<T> *curr = node;

    while(curr->left != nullptr)
        curr = curr->left;

    return curr;
}

/**AVL CONSTRUCTOR*/

template <class T>
AVLTree<T>::AVLTree() {this->root = nullptr;}

/**AVL INSERT*/

template<class T>
void AVLTree<T>::insert(T val) noexcept {
    this->root = insideInsert(val, this->root);
}

template<class T>
BinNode<T> *AVLTree<T>::insideInsert(T val, BinNode<T> *node) noexcept {
    node = BinTree<T>::insideInsert(val,node);
    return correct(node,val);
}

/**AVL REMOVE*/

template<class T>
bool AVLTree<T>::remove(T val) noexcept {
    this->removed = false;
    this->root = insideRemove(val, this->root);
    return this->removed;
}

template <class T>
BinNode<T> *AVLTree<T>::insideRemove(T val, BinNode<T> *node) noexcept{
    node = BinTree<T>::insideRemove(val, node);
    return correct(node,val);
}

/**AVL BALANCING*/

template<class T>
BinNode<T> * AVLTree<T>::correct(BinNode<T> *start, T value) noexcept {

    int weight = getWeight(start);

    // LeftLeft Case
    if (weight > 1 && value < start->left->val)
        return rrotate(start);

    // RightRight Case
    if (weight < -1 && value > start->right->val)
        return lrotate(start);

    // LeftRight Case
    if (weight > 1 && value > start->left->val)
    {
        start->left = lrotate(start->left);
        return rrotate(start);
    }

    // RightLeft Case
    if (weight < -1 && value < start->right->val)
    {
        start->right = rrotate(start->right);
        return lrotate(start);
    }

    return start;
}

template<class T>
constexpr int AVLTree<T>::getWeight(BinNode<T> *node) noexcept {
    if (node == nullptr) return 0;
    return this->getHeight(node->left) - this->getHeight(node->right);
}

/**AVL ROTATIONS*/

template<class T>
BinNode<T>* AVLTree<T>::lrotate(BinNode<T>* node) noexcept {

    auto oldRight = node->right;
    auto rightleft = oldRight->left;

    oldRight->left = node;
    node->right = rightleft;

    node->height = max(this->getHeight(node->left),
                        this->getHeight(node->right)) + 1;
    oldRight->height = max(this->getHeight(oldRight->left),
                         this->getHeight(oldRight->right)) + 1 ;

    return oldRight;
}

template<class T>
BinNode<T>* AVLTree<T>::rrotate(BinNode<T>* node) noexcept {
    auto oldLeft = node->left;
    auto leftright = oldLeft->right;

    oldLeft->right = node;
    node->left = leftright;

    node->height = max(this->getHeight(node->left),
                     this->getHeight(node->right)) + 1;
    oldLeft->height = max(this->getHeight(oldLeft->left),
                        this->getHeight(oldLeft->right)) + 1;

    return oldLeft;
}
