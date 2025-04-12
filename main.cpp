#include "my_btree_funcs.h"

int main() {
    BTree *temp;
    int n, data;
    int case_number;
    while (case_number != 0) {
        cout << "(1) Make tree\n(2) Print tree pre/in/post/wideorder\n(3) Min/max number\n(4) Delete number\n(5) Search number\n(6) Print png\n";
        cin >> case_number;
        switch (case_number) {
            case 1:
                cout << "Enter number of numbers:\n";
                cin >> n;
                for (int i = 0; i < n; i++) {
                cin >> data;
                broot = btree_insert(broot, data);
                }
                break;
            case 2:
                cout << "in: ";
                btree_inorder(broot);
                cout << endl;
                cout << "pre: ";
                btree_preorder(broot);
                cout << endl;
                cout << "post: ";
                btree_postorder(broot);
                cout << endl;
                cout << "wide: ";
                btree_wideorder(broot);
                cout << endl;
                break;
            case 3:
                cout << "min: ";
                find_min(broot);
                cout << "max: ";
                find_max(broot);
                break;
            case 4:
                cout << "Enter number to delete:\n";
                cin >> data;
                broot = btree_delete(broot, data);
                break;
            case 5:
                print_tree_graph(broot, "tree.dot");
                break;
            case 6:

                break;
            default:
                cout << "Failed!\n";
                break;
        }
    }
    btree_destroy(broot);
    return 0;
}




