#include <iostream>

using namespace std;

int main() {
    int f, n;
    cout << "\nEnter the number of frames: ";
    cin >> f;
    cout << "\nEnter number of page references: ";
    cin >> n;
    int data[n], alloc[f];

    // Initialize alloc array with blank spaces
    for (int i = 0; i < f; i++)
        alloc[i] = -1; // Initialize with -1

    cout << "\nEnter Page String: ";
    for (int i = 0; i < n; i++)
        cin >> data[i];

    cout << endl;

    int ind = 0, fault = 0;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < f; j++) {
            if (alloc[j] == data[i])
                flag = 1;
        }
        if (flag != 1) {
            alloc[ind] = data[i];
            ind = (ind + 1) % f;
            fault++;
        }
        cout<<"Current State: ";
        for (int k = 0; k < f; k++) {
            if (alloc[k] != -1)
                cout << alloc[k] << "   ";
            else
                cout.width(4); // set the width of the next field
            cout.fill(' ');   // fill character for the next field
        }
        cout << endl;
    }

    cout << "\nPage Faults: " << fault;
    return 0;
}
