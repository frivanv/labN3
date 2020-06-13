#include <iostream>
#include "Sequence.h"
#include "LinkedList.h"

template<class T>
class LinkedListSequence : public Sequence<T> {
protected:
    LinkedList<T> *linked_list;

public:
    LinkedListSequence() : Sequence<T>() {
        linked_list = new LinkedList<T>();
    }

    LinkedListSequence(T *item, int size) : Sequence<T>() {
        linked_list = new LinkedList<T>(item, size);
    }

    ~LinkedListSequence() override = default;

    T GetFirst() const override {
        if (linked_list->GetLength() == 0) {
            throw out_of_range("Index is out of range");
        }

        return linked_list->GetFirst();
    }

    T GetLast() const override {
        if (linked_list->GetLength() == 0) {
            throw out_of_range("Index is out of range");
        }

        return linked_list->GetLast();
    }

    T Get(int index) const override {
        if (index < 0 || index >= linked_list->GetLength()) {
            throw out_of_range("Index is out of range");
        }

        return linked_list->Get(index);
    }

    int GetLength() const override {

        return linked_list->GetLength();
    }

    void Append(T item) override {

        return linked_list->Append(item);
    }

    void Prepend(T item) override {

        return linked_list->Prepend(item);
    }

    void InsertAt(T item, int index) override {
        if (index < 0 || index >= linked_list->GetLength()) {
            throw out_of_range("Index is out of range");
        }

        return linked_list->InsertAt(item, index);
    }

    void Print() override {

        return linked_list->Print();
    }

    void Enter() override {

        return linked_list->Enter();
    }

    Sequence<T> *GetSubSequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex >= linked_list->GetLength() ||
            endIndex >= linked_list->GetLength()) {
            throw out_of_range("Index is out of range");
        }

        LinkedList<T> *sub_list = linked_list->GetSubList(startIndex, endIndex);
        Sequence<T> *sub_sequence = new LinkedListSequence<T>();

        for (int i = 0; i < sub_list->GetLength(); i++) {
            sub_sequence->Prepend(sub_list->Get(i));
        }

        return sub_sequence;
    }

    LinkedListSequence<T> *Concat(Sequence<T> *linked_list2) const override {
        auto *concat_sequence = new LinkedListSequence<T>();

        for (int i = 0; i < linked_list->GetLength(); i++) {
            concat_sequence->Prepend(linked_list->Get(i));
        }

        for (int i = 0; i < linked_list2->GetLength(); i++) {
            concat_sequence->Prepend(linked_list2->Get(i));
        }

        return concat_sequence;
    }

    T &operator[](int index) const override {

        return linked_list->operator[](index);
    }

};

int LinkedListSequence_Tests() {
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

    list2.Prepend(13);
    if (list2[5] == 13) {
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
    if (new_list->Get(0) == 3 && new_list->Get(1) == 5 && new_list->Get(2) == 7 && new_list->Get(3) == 9) {
        cout << "GetSubList succeed" << endl;
    } else {
        cout << "GetSubList failed" << endl;
    }

    LinkedList<int> *new_list2 = list1.Concat(&list2);
    if (new_list2->Get(0) == 0 && new_list2->Get(1) == 2 && new_list2->Get(2) == 4
        && new_list2->Get(3) == 6 && new_list2->Get(4) == 8 && new_list2->Get(5) == 1
        && new_list2->Get(6) == 3 && new_list2->Get(7) == 5 && new_list2->Get(8) == 7
        && new_list2->Get(9) == 9 && new_list2->Get(10) == 11 && new_list2->Get(11) == 13) {
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
