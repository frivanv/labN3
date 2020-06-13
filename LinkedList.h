#include <iostream>

using namespace std;

template<class T>
class LinkedList {
private:
    struct Node {
        T item;
        Node *next;
    };

    Node *head = nullptr;
    int size = 0;

public:
    LinkedList() : size(0), head(nullptr) {};

    LinkedList(const T *item, const int size) : LinkedList() {
        if ((size < 0) || (size == 0)) {
            throw length_error("Index is out of range");
        }

        Node *tail = new Node{*item, nullptr};
        head = tail;

        for (size_t i = 1; i < size; i++) {
            Node *body = new Node{*(item + i), nullptr};
            tail->next = body;
            tail = body;
        }

        this->size = size;
    }

    LinkedList(LinkedList<T> const &list) {
        Node *body{head};
        Node *List{body};

        for (size_t i = 1; i < size; i++, body = body->next) {
            List = new Node{body->item, List};
        }

        this->size = size;
    }

    ~LinkedList() {
        while (this->head != nullptr) {
            Node *body{head->next};
            delete[] head;
            this->head = body;
        }

        delete[] this->head;
    }

    T GetFirst() {
        if (size == 0) {
            throw length_error("Index is out of range");
        }

        return head->item;
    }

    T GetLast() {
        if (size == 0) {
            throw length_error("Index is out of range");
        }

        Node *body{head};

        for (size_t i = 0; i < size - 1; i++) {
            body = body->next;
        }

        return body->item;
    }

    T Get(int index) {
        if (index < 0 || index >= size) {
            throw length_error("Index is out of range");
        }

        Node *body{head};

        for (size_t i = 0; i < index; i++) {
            body = body->next;
        }

        return body->item;
    }

    int GetLength() {

        return size;
    }

    void Append(T item) {
        head = new Node{item, head};
        ++size;
    }

    void Prepend(T item) {
        if (head == nullptr) {
            head = new Node{item, head};
        } else {
            Node *body{head};

            for (size_t i = 1; i < size; i++) {
                body = body->next;
            }

            body->next = new Node{item, nullptr};
        }

        ++size;
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index >= size) {
            throw length_error("Index is out of range");
        }

        Node *body{head};

        for (size_t i = 0; i < index - 1; i++) {
            body = body->next;
        }

        Node *new_node = new Node{item, body->next};
        body->next = new_node;
        this->size += 1;
    }

    void Print() {
        for (int i = 0; i < size; i++) {
            cout << Get(i) << " ";
        }

        cout << endl;
    }

    void Enter() {
        cout << "Please, type List size:";
        int count;
        cin >> count;

        for (int i = 0; i < count; i++) {
            T value;
            cout << "Element" << i << "-";
            cin >> value;
            Prepend(value);
        }
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) {
        if (startIndex < 0 || endIndex < 0 || startIndex >= size || endIndex >= size || startIndex > endIndex) {
            throw length_error("Index is out of range");
        }

        Node *body{head};

        for (size_t i = 0; i < startIndex; i++) {
            body = body->next;
        }

        auto *new_node = new LinkedList<T>;

        for (auto i = static_cast<size_t>(startIndex); i < endIndex + 1; i++) {
            new_node->Prepend(body->item);
            body = body->next;
        }

        new_node->size = endIndex - startIndex + 1;

        return new_node;
    }

    LinkedList<T> *Concat(LinkedList<T> *list) {
        auto *new_list = new LinkedList<T>();
        Node *body1{this->head};


        for (int i = 0; i < this->size; i++) {
            new_list->Prepend(body1->item);
            body1 = body1->next;
        }

        Node *body2{list->head};

        for (int i = this->size; i < (list->size + this->size); i++) {
            new_list->Prepend(body2->item);
            body2 = body2->next;
        }

        new_list->size = this->size + list->size;

        return new_list;
    }

    T &operator[](int index) {
        if (index < 0 || index >= size) {
            throw length_error("Index is out of range");
        }

        Node *body{head};

        for (size_t i = 0; i < index; i++) body = body->next;

        return body->item;
    }

};

int LinkedList_Tests() {
    int *a{new int[4]{2, 4, 6, 8}};
    int *b{new int[5]{1, 3, 7, 9, 11}};

    LinkedList<int> list1{a, 4};
    LinkedList<int> list2{b, 5};

    if (list1.GetFirst() == 2) {
        cout << "GetFirst succeed" << endl;
    } else {
        cout << "GetFirst failed" << endl;
    }

    if (list1.GetLast() == 8) {
        cout << "GetLast succeed" << endl;
    } else {
        cout << "GetLast failed" << endl;
    }

    if (list1.Get(2) == 6) {
        cout << "Get succeed" << endl;
    } else {
        cout << "Get failed" << endl;
    }

    if (list1.GetLength() == 4) {
        cout << "GetLength succeed" << endl;
    } else {
        cout << "GetLength failed" << endl;
    }

    list1.Append(0);
    if (list1[0] == 0) {
        cout << "Append succeed" << endl;
    } else {
        cout << "Append failed" << endl;
    }

    list2.Prepend(10);
    if (list2[5] == 10) {
        cout << "Prepend succeed" << endl;
    } else {
        cout << "Prepend failed" << endl;
    }

    list2.InsertAt(5, 2);
    if (list2[2] == 5) {
        cout << "InsertAt succeed" << endl;
    } else {
        cout << "InsertAt failed" << endl;
    }

    LinkedList<int> *new_list = list2.GetSubList(1, 4);
    if (new_list->Get(0) == 2 && new_list->Get(1) == 4 && new_list->Get(2) == 6 && new_list->Get(3) == 8) {
        cout << "GetSubList succeed" << endl;
    } else {
        cout << "GetSubList failed" << endl;
    }

    LinkedList<int> *new_list2 = list1.Concat(&list2);
    if (new_list2->Get(0) == 0 && new_list2->Get(1) == 2 && new_list2->Get(2) == 4
        && new_list2->Get(3) == 6 && new_list2->Get(4) == 8 && new_list2->Get(5) == 10
        && new_list2->Get(6) == 1 && new_list2->Get(7) == 3 && new_list2->Get(8) == 5
        && new_list2->Get(9) == 7 && new_list2->Get(10) == 9 && new_list2->Get(11) == 11) {
        cout << "Concat succeed" << endl;
    } else {
        cout << "Concat failed" << endl;
    }

    if (list1[1] == 2 && list1[3] == 6) {
        cout << "Operator [] succeed" << endl;
    } else {
        cout << "Operator [] failed" << endl;
    }

    delete[] a;
    delete[] b;

    return 0;
}