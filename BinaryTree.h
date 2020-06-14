#include <iostream>
#include <string>
#include "LinkedListSequence.h"
#include "Node.h"

using namespace std;

template<class T>
class BinaryTree {


public:
    Node<T> *root;

    BinaryTree() { //constructor
        root = nullptr;
    }

    explicit BinaryTree(Node<T> *node) {
        this->root = node;
    }

    ~BinaryTree() { //destructor
        Delete(root, root->item);
    }

    int max(int a, int b) { //find maximum of 2
        if (a >= b) {
            return a;
        } else {
            return b;
        }
    }

    void Enter() { //enter
        cout << "Please, type size of the Tree:";
        int size;
        cin >> size;

        for (int i = 0; i < size; i++) {
            T elem;
            cout << "Element" << i << "-";
            cin >> elem;
            Insert(elem);
        }
    }

    void Print(Node<T> *node) { //print
        if (node == nullptr) {
            return;
        } else {
            Print(node->left);
            cout << node->item << "\t";
            Print(node->right);
        }
    }

    bool IsThereElement(Node<T> *node, T elem) { //check for element
        if (node == nullptr) {
            return false;
        }

        while (node != nullptr) {
            if (elem < node->item) {
                node = node->left;
            } else {
                if (elem > node->item) {
                    node = node->right;
                } else {
                    return true;
                }
            }
        }

        return false;
    }

    int Depth(Node<T> *node) { //depth
        int left_depth, right_depth;

        if (node->left == nullptr && node->right == nullptr) {
            return 0;
        } else {
            if (node->left != nullptr) {
                left_depth = Depth(node->left) + 1;
            } else {
                left_depth = 0;
            }

            if (node->right != nullptr) {
                right_depth = Depth(node->right) + 1;
            } else {
                right_depth = 0;
            }
        }

        return max(left_depth, right_depth);
    }

    void Insert(const T &elem) { //insert
        Node<T> *tree = root;
        Node<T> *ptr = nullptr;
        auto *new_node = new Node<T>(elem);

        while (tree != nullptr) {
            ptr = tree;
            if (elem < tree->item) {
                tree = tree->left;
            } else {
                tree = tree->right;
            }
        }

        if (ptr == nullptr) {
            root = new_node;
        } else {
            if (elem < ptr->item) {
                ptr->left = new_node;
            } else {
                ptr->right = new_node;
            }
        }
    }

    void Delete(Node<T> *node, T elem) { //delete
        if (node == nullptr) {
            return;
        }

        Node<T> *ptr1 = node;
        Node<T> *new_node = nullptr;
        bool check = false;

        if (ptr1->left == nullptr && ptr1->right == nullptr) {
            if (elem == ptr1->item) {
                delete ptr1;
            } else {
                return;
            }
        }

        while (ptr1 != nullptr && ptr1->item != elem) {
            if (elem <= ptr1->item) {
                check = false;
                new_node = ptr1;
                ptr1 = ptr1->left;
            } else {
                if (elem > ptr1->item) {
                    check = true;
                    new_node = ptr1;
                    ptr1 = ptr1->right;
                }
            }
        }

        if (ptr1 == nullptr) {
            return;
        } else {
            if (ptr1->right == nullptr && ptr1->left == nullptr) {
                if (check) {
                    new_node->right = nullptr;
                } else {
                    new_node->left = nullptr;
                }

                delete ptr1;
            } else {
                if (ptr1->right == nullptr && ptr1->left == nullptr) {
                    if (new_node->left == ptr1) {
                        new_node->left = ptr1->right;
                    } else {
                        new_node->right = ptr1->right;
                    }

                    delete ptr1;
                    return;
                } else {
                    if (ptr1->left != nullptr && ptr1->right != nullptr) {
                        Node<T> *ptr2 = nullptr;
                        new_node = ptr1;
                        ptr2 = ptr1;
                        check = true;
                        ptr1 = ptr1->right;
                        while (ptr1->left != nullptr) {
                            ptr2 = ptr1;
                            check = false;
                            ptr1 = ptr1->left;
                        }
                        new_node->item = ptr1->item;

                        if (ptr1->right != nullptr) {
                            if (check) {
                                ptr2->right = ptr1->right;
                            } else {
                                ptr2->left = ptr1->right;
                            }

                            delete ptr1;
                            return;
                        } else {
                            if (check) {
                                ptr2->right = nullptr;
                            } else {
                                ptr2->left = nullptr;
                            }

                            delete ptr1;
                            return;
                        }
                    }
                }
            }
        }

    }

    Node<T> *Search(Node<T> *node, T elem) { //search
        if (node == nullptr) {
            cout << "Tree is empty" << endl;
            return node;
        }

        if (elem == node->item) {
            return node;
        } else if (elem < node->item) {
            return Search(node->left, elem);
        } else {
            return Search(node->right, elem);
        }
    }

    BinaryTree<T> *SubTree(Node<T> *node, T elem) { //get subtree
        Node<T> *new_node = Search(node, elem);
        auto *new_tree = new BinaryTree<T>(new_node);

        return new_tree;
    }

    bool IsEqual(const Node<T> *node1, const Node<T> *node2) {
        if (node1 == nullptr && node2 == nullptr) {
            return true;
        }

        if (node1 == nullptr || node2 == nullptr) {
            return false;
        }

        if (node1->item != node2->item) {
            return false;
        }

        return (IsEqual(node1->left, node2->left) && IsEqual(node1->right, node2->right));
    }


    bool SearchSubTree(Node<T> *node, BinaryTree<T> *sub_tree) {
        if (sub_tree == nullptr || node == nullptr) {
            return false;
        }

        return IsEqual(sub_tree->root, SubTree(node, sub_tree->root->item)->root);
    }

    void Map(Node<T> *node, T(*func)(T)) { //map
        if (node == nullptr) {
            cout << "Tree is empty" << endl;
            return;
        }

        node->item = func(node->item);

        if (node->left != nullptr) {
            Map(node->left, func);
        }

        if (node->right != nullptr) {
            Map(node->right, func);
        }
    }

    void Where(Node<T> *node, bool (*func)(T), BinaryTree<T> *where_tree) { //where
        if (node == nullptr) {
            return;
        }

        if (func(node->item)) {
            where_tree->Insert(node->item);
        }

        if (node->left != nullptr) {
            Where(node->left, func, where_tree);
        }

        if (node->right != nullptr) {
            Where(node->right, func, where_tree);
        }
    }

    /*
    void TreeToList(Node<T> *&node, LinkedList<T> &list) { //write Tree to list
        if (this->root == nullptr) {
            return;
        }

        TreeToList(node->left, list);
        list.Prepend(node->item);
        TreeToList(node->right, list);
    }

    T Reduce(T(*func)(T, T), const T &start) { //reduce
        LinkedList<T> list = LinkedList<T>();

        if (root == nullptr) {
            return 0;
        }

        TreeToList(root, list);

        T result;
        for (int i = 0; i < list.GetLength(); i++) {
            if (i == 0) {
                result = func(list.Get(i), start);
            } else {
                result = func(list.Get(i), result);
            }
        }

        return result;
    }

    string TreeToString(Node<T> *node) { //write Tree to string
        string str;

        if (this->root == nullptr) {
            cout << "Tree is empty" << endl;
            return str;
        } else {
            LinkedListSequence<T> list = LinkedListSequence<T>();
            TreeToList(node, list);

            for (int i = 0; i < list.GetLength(); i++) {
                str += to_string(list.Get(i)) + "\t";
            }
        }

        return str;
    }
     */
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int int_half(int x) {
    return x / 2;
}

double double_half(double x) {
    return x / 2;
}

int int_mult(int x) {
    return x * 2;
}

double double_mult(double x) {
    return x * 2;
}

bool int_more(int x) {
    return x > 10;
}

bool double_more(double x) {
    return x > 10;
}

bool int_pos(int x) {
    return x >= 0;
}

bool double_pos(double x) {
    return x >= 0;
}

int int_sum(int x, int y) {
    return x + y;
}

double double_sum(double x, double y) {
    return x + y;
}

int int_multipl(int x, int y) {
    return x * y;
}

double double_multipl(double x, double y) {
    return x * y;
}

int BinaryTree_Tests() { //tests
    auto *tree = new BinaryTree<int>();
    auto *sub_tree = new BinaryTree<int>();
    auto *map_tree = new BinaryTree<int>();
    auto *where_tree = new BinaryTree<int>();
    auto *new_tree = new BinaryTree<int>();
    auto *new_where_tree = new BinaryTree<int>();
    auto *reduce_tree = new BinaryTree<int>();

    tree->Insert(12);
    tree->Insert(11);
    tree->Insert(13);
    tree->Insert(9);
    tree->Insert(10);
    tree->Insert(15);
    tree->Insert(14);

    if (tree->IsThereElement(tree->root, 15) && !tree->IsThereElement(tree->root, 3)) {
        cout << "IsThereElement succeed" << endl;
    } else {
        cout << "IsThereElement failed" << endl;
    }

    if (tree->Depth(tree->root) == 3) {
        cout << "Depth succeed" << endl;
    } else {
        cout << "Depth failed" << endl;
    }

    tree->Insert(7);
    if (tree->Search(tree->root, 7) != nullptr) {
        cout << "Insert succeed" << endl;
    } else {
        cout << "Insert failed" << endl;
    }

    tree->Delete(tree->root, 7);
    if (!tree->IsThereElement(tree->root, 7)) {
        cout << "Delete succeed" << endl;
    } else {
        cout << "Delete failed" << endl;
    }

    if (tree->Search(tree->root, 15) != nullptr) {
        cout << "Search succeed" << endl;
    } else {
        cout << "Search failed" << endl;
    }

    sub_tree = tree->SubTree(tree->root, 13);
    if (sub_tree->IsThereElement(tree->root, 13) && sub_tree->IsThereElement(tree->root, 14) &&
        sub_tree->IsThereElement(tree->root, 15)) {
        cout << "SubTree succeed" << endl;
    } else {
        cout << "SubTree failed" << endl;
    }

    //unworking!
    if (tree->SearchSubTree(tree->root, sub_tree)) {
        cout << "SearchSubTree succeed" << endl;
    } else {
        cout << "SearchSubTree failed" << endl;
    }

    map_tree->Insert(12);
    map_tree->Insert(13);
    map_tree->Insert(15);
    map_tree->Map(map_tree->root, int_mult);
    if (map_tree->IsThereElement(map_tree->root, 24) && map_tree->IsThereElement(map_tree->root, 26) &&
        map_tree->IsThereElement(map_tree->root, 30)) {
        cout << "Map succeed" << endl;
    } else {
        cout << "Map failed" << endl;
    }

    where_tree->Insert(5);
    where_tree->Insert(9);
    where_tree->Insert(15);
    where_tree->Insert(17);
    where_tree->Where(where_tree->root, int_more, new_tree);
    if (!new_tree->IsThereElement(new_tree->root, 5) &&
        !new_tree->IsThereElement(new_tree->root, 9) &&
        new_tree->IsThereElement(new_tree->root, 15) &&
        new_tree->IsThereElement(new_tree->root, 17)) {
        cout << "Where succeed" << endl;
    } else {
        cout << "Where failed" << endl;
    }

    /*
    reduce_tree->Insert(5);
    reduce_tree->Insert(7);
    reduce_tree->Insert(9);
    if (reduce_tree->Reduce(int_sum, 11) == 32) {
        cout << "Reduce succeed" << endl;
    } else {
        cout << "Reduce failed" << endl;
    }
    */

    return 0;
}