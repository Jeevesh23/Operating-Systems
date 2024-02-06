#include<iostream>
#include<string.h>

using namespace std;

int faults = 0;

int return_index(int *arr, int n, int search);
int ifpresent(int n, int *arr, int value, int start);
int last_page(int n, int *arr, int *frames, int curr, int fn);

int main() {
    int n, ch, page_no, flag, j = 0, replace_index, nop, frames_empty, lp, lp_index;
    cout << "\nEnter the number of frames: ";
    cin >> n;
    frames_empty = n;
    int frames[n], replace[n], y = 0;
    char c[1];
    for (int i = 0; i < n; i++) {
        replace[i] = frames[i] = -1; // Initialize with -1
    }
    cout << "\nEnter number of page references: ";
    cin >> nop;
    int pages[nop];
    cout << "\nEnter Page String: ";
    for (int i = 0; i < nop; i++) {
        cin >> pages[i];
    }
    cout << endl;

    for (int y = 0; y < nop; y++) {
        page_no = pages[y];
        for (int i = 0; i < n; i++) {
            if (frames[i] != page_no) {
                flag = 1;
            } else {
                flag = 0;
                break;
            }
        }
        if (flag == 1) {
            if (frames_empty > 0) {
                frames[n - frames_empty] = page_no;
            } else {
                lp = last_page(nop, pages, frames, y, n);
                if (lp != -1) {
                    lp_index = return_index(frames, n, lp);
                } else {
                    lp_index = 0;
                }
                frames[lp_index] = page_no;
            }
            frames_empty--;
            faults++;
        } else {
        }
        cout<<"Current State: ";
        for (int i = 0; i < n; i++) {
            if (frames[i] != -1)
                cout << frames[i] << "   ";
            else
                cout.width(4); // set the width of the next field
            cout.fill(' ');   // fill character for the next field
        }
        cout << endl;
    }
    cout << "\nTotal Page faults = " << faults;
    return 0;
}

int return_index(int *arr, int n, int search) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == search) {
            return i;
        }
    }
    return -1;
}

int ifpresent(int n, int *arr, int value, int start) {
    for (int i = start; i < n; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

int last_page(int n, int *arr, int *frames, int curr, int fn) {
    int got[fn], k = 0;
    for (int i = 0; i < fn; i++) {
        if (!ifpresent(n, arr, frames[i], curr + 1)) {
            return frames[i];
        }
    }
    int last = -1;
    for (int i = curr + 1; i < n; i++) {
        for (int j = 0; j < fn; j++) {
            if (arr[i] == frames[j] && !ifpresent(k, got, arr[i], 0)) {
                last = arr[i];
                got[k++] = last;
            }
        }
    }
    return got[--k];
}



#include<iostream>
#include<string.h>

using namespace std;

int faults = 0; // Counter for page faults

// Function to return the index of a value in an array
int return_index(int *arr, int n, int search);

// Function to check if a value is present in an array starting from a given index
int ifpresent(int n, int *arr, int value, int start);

// Function to find the last occurrence of a page in the page reference string
int last_page(int n, int *arr, int *frames, int curr, int fn);

int main() {
    int n, ch, page_no, flag, j = 0, replace_index, nop, frames_empty, lp, lp_index;
    cout << "\nEnter the number of frames: ";
    cin >> n; // Number of frames in the page table
    frames_empty = n;
    int frames[n], replace[n], y = 0;
    char c[1];
    for (int i = 0; i < n; i++) {
        replace[i] = frames[i] = -1; // Initialize frames and replace arrays with -1
    }
    cout << "\nEnter number of page references: ";
    cin >> nop; // Number of page references
    int pages[nop];
    cout << "\nEnter Page String: ";
    for (int i = 0; i < nop; i++) {
        cin >> pages[i]; // Input the page reference string
    }
    cout << endl;

    for (int y = 0; y < nop; y++) {
        page_no = pages[y]; // Get the current page reference
        for (int i = 0; i < n; i++) {
            if (frames[i] != page_no) {
                flag = 1; // Set flag to 1 if the page is not in the frames
            } else {
                flag = 0;
                break; // If the page is in frames, set flag to 0 and break the loop
            }
        }
        if (flag == 1) {
            if (frames_empty > 0) {
                frames[n - frames_empty] = page_no; // If frames are not full, add the page to frames
            } else {
                lp = last_page(nop, pages, frames, y, n); // Find the last page for replacement
                if (lp != -1) {
                    lp_index = return_index(frames, n, lp); // Get the index of the last page in frames
                } else {
                    lp_index = 0;
                }
                frames[lp_index] = page_no; // Replace the last page in frames with the current page
            }
            frames_empty--; // Decrement the frames_empty counter
            faults++; // Increment the page fault counter
        } else {
            // No action needed if the page is already in frames
        }
        cout << "Current State: ";
        for (int i = 0; i < n; i++) {
            if (frames[i] != -1)
                cout << frames[i] << "   ";
            else
                cout.width(4); // set the width of the next field
            cout.fill(' ');   // fill character for the next field
        }
        cout << endl;
    }
    cout << "\nTotal Page faults = " << faults; // Output the total number of page faults
    return 0;
}

// Function to return the index of a value in an array
int return_index(int *arr, int n, int search) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == search) {
            return i;
        }
    }
    return -1; // Return -1 if the value is not found in the array
}

// Function to check if a value is present in an array starting from a given index
int ifpresent(int n, int *arr, int value, int start) {
    for (int i = start; i < n; i++) {
        if (arr[i] == value) {
            return 1; // Return 1 if the value is present in the array
        }
    }
    return 0; // Return 0 if the value is not present in the array
}

// Function to find the last occurrence of a page in the page reference string
int last_page(int n, int *arr, int *frames, int curr, int fn) {
    int got[fn], k = 0;
    for (int i = 0; i < fn; i++) {
        if (!ifpresent(n, arr, frames[i], curr + 1)) {
            return frames[i]; // Return the page if it is not present in the future references
        }
    }
    int last = -1;
    for (int i = curr + 1; i < n; i++) {
        for (int j = 0; j < fn; j++) {
            if (arr[i] == frames[j] && !ifpresent(k, got, arr[i], 0)) {
                last = arr[i];
                got[k++] = last; // Store the last occurrences in the 'got' array
            }
        }
    }
    return got[--k]; // Return the last page from the 'got' array
}
