template<class T>
class Node {
public:
    T item;
    Node *left;
    Node *right;

    explicit Node(T elem) {
        this->item = elem;
        this->left = 0;
        this->right = 0;
    }
};