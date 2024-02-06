#include<bits/stdc++.h>

using namespace std;

void FCFS(int n, int arr[], int head) {
    int distance = 0;
    // Traverse the array and keep adding the absolute difference to the distance to get the head movements
    for (int i = 0; i < n - 1; i++) {
        distance += abs(arr[i] - arr[i + 1]);
    }
    // Add the initial head movement to the first request
    distance += abs(head - arr[0]);
    cout << "The head movements are: " << distance;
}

int main() {
    // Take the seek sequence
    int size, head;
    cout << "Enter the size of the request array: ";
    cin >> size;
    int seek[size];
    cout << "Enter the values in the request queue: ";
    for (int i = 0; i < size; i++) {
        cin >> seek[i];
    }
    cout << "Enter the address of the head: ";
    cin >> head;
    FCFS(size, seek, head);

    return 0;
}