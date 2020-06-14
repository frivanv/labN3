#include <iostream>
#include <string>
#include "BinaryTree.h"

using namespace std;

int interface() {
    cout << "What type of data do you want to work with?" << endl;
    cout << "Please, type '1' for integer or '2' for double" << endl;
    int type;

    do {
        cin >> type;
        cout << endl;
        if ((type != 1) && (type != 2)) {
            cout << ("You must choose 1 or 2") << endl;
        }
    } while ((type != 1) && (type != 2));

    auto *Tree1 = new BinaryTree<int>();
    auto *Tree2 = new BinaryTree<double>();

    auto *sub_tree1 = new BinaryTree<int>();
    auto *sub_tree2 = new BinaryTree<double>();

    auto *where_tree1 = new BinaryTree<int>();
    auto *where_tree2 = new BinaryTree<double>();

    if (type == 1) {
        Tree1->Enter();
        cout << endl;
    } else if (type == 2) {
        Tree2->Enter();
        cout << endl;
    }

    int choice = 0;

    cout << "Please, choose the operation:" << endl;
    cout << "1. Print Tree" << endl;
    cout << "2. Check for element" << endl;
    cout << "3. Get depth" << endl;
    cout << "4. Insert" << endl;
    cout << "5. Delete" << endl;
    cout << "6. Search" << endl;
    cout << "7. Get SubTree" << endl;
    cout << "8. Check for SubTree" << endl;
    cout << "9. Map" << endl;
    cout << "10. Where" << endl;
    cout << "11. Reduce | don't work :(" << endl;
    cout << "12. Turn tree into string | don't work :(" << endl;

    cout << endl << "Your choice:";
    cin >> choice;
    cout << endl;

    int int_el = 0;
    double double_el = 0;

    switch (choice) {
        case 1: {
            if (type == 1) {
                Tree1->Print(Tree1->root);
            } else if (type == 2) {
                Tree2->Print(Tree2->root);
            }

            break;
        }

        case 2: {
            if (type == 1) {
                cout << "Please, type your element:";
                cin >> int_el;
                cout << endl;
                if (Tree1->IsThereElement(Tree1->root, int_el)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            } else if (type == 2) {
                cout << "Please, type your element:";
                cin >> double_el;
                cout << endl;
                if (Tree2->IsThereElement(Tree2->root, double_el)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }

            break;
        }

        case 3: {
            if (type == 1) {
                cout << Tree1->Depth(Tree1->root);
            } else if (type == 2) {
                cout << Tree2->Depth(Tree2->root);
            }

            break;
        }

        case 4: {
            if (type == 1) {
                cout << "Please, type your element:";
                cin >> int_el;
                cout << endl;
                Tree1->Insert(int_el);
                Tree1->Print(Tree1->root);
            } else if (type == 2) {
                cout << "Please, type your element:";
                cin >> double_el;
                cout << endl;
                Tree2->Insert(double_el);
                Tree2->Print(Tree2->root);
            }

            break;
        }

        case 5: {
            if (type == 1) {
                cout << "Please, type your element:";
                cin >> int_el;
                cout << endl;
                Tree1->Delete(Tree1->root, int_el);
                Tree1->Print(Tree1->root);
            } else if (type == 2) {
                cout << "Please, type your element:";
                cin >> double_el;
                cout << endl;
                Tree2->Delete(Tree2->root, double_el);
                Tree2->Print(Tree2->root);
            }

            break;
        }

        case 6: {
            if (type == 1) {
                cout << "Please, type your element:";
                cin >> int_el;
                cout << endl;
                Tree1->Search(Tree1->root, int_el);
                Tree1->Print(Tree1->root);
            } else if (type == 2) {
                cout << "Please, type your element:";
                cin >> double_el;
                cout << endl;
                Tree2->Search(Tree2->root, double_el);
                Tree2->Print(Tree2->root);
            }

            break;
        }

        case 7: {
            if (type == 1) {
                cout << "Please, type your element:";
                cin >> int_el;
                cout << endl;
                sub_tree1 = Tree1->SubTree(Tree1->root, int_el);
                sub_tree1->Print(sub_tree1->root);
            } else if (type == 2) {
                cout << "Please, type your element:";
                cin >> double_el;
                cout << endl;
                sub_tree2 = Tree2->SubTree(Tree2->root, double_el);
                sub_tree2->Print(sub_tree2->root);
            }

            break;
        }

        case 8: {
            if (type == 1) {
                sub_tree1->Enter();
                if (Tree1->SearchSubTree(Tree1->root, sub_tree1)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            } else if (type == 2) {
                sub_tree2->Enter();
                if (Tree2->SearchSubTree(Tree2->root, sub_tree2)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }

            break;
        }

        case 9: {
            int ch;

            cout << " Choose the function:" << endl;
            cout << "1. half" << endl;
            cout << "2. mult" << endl;
            cin >> ch;

            if (type == 1 && ch == 1) {
                Tree1->Map(Tree1->root, int_half);
            } else if (type == 1 && ch == 2) {
                Tree1->Map(Tree1->root, int_mult);
            } else if (type == 2 && ch == 1) {
                Tree2->Map(Tree2->root, double_half);
            } else {
                Tree2->Map(Tree2->root, double_mult);
            }

            break;
        }

        case 10: {
            int ch;

            cout << " Choose the function:" << endl;
            cout << "1. more" << endl;
            cout << "2. pos" << endl;
            cin >> ch;

            if (type == 1 && ch == 1) {
                Tree1->Where(Tree1->root, int_more, where_tree1);
            } else if (type == 1 && ch == 2) {
                Tree1->Where(Tree1->root, int_pos, where_tree1);
            } else if (type == 2 && ch == 1) {
                Tree2->Where(Tree2->root, double_more, where_tree2);
            } else {
                Tree2->Where(Tree2->root, double_pos, where_tree2);
            }

            break;
        }

        default:
            cout << "ERROR. You need choose an action.";
    }

    return 0;
}

int main() {
    interface();

    //BinaryTree_Tests();
    //LinkedListSequence_Tests();
    return 0;
}
