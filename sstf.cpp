#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int sstf(vector<int> &requests, int current_head) {
    int total_seek_time = 0;
    int head = current_head;
    vector<int> seekSequence;

    while (!requests.empty()) {
        int min_seek = INT_MAX;
        int min_index = -1;

        for (int i = 0; i < requests.size(); i++) {
            int seek = abs(current_head - requests[i]);
            if (seek < min_seek) {
                min_seek = seek;
                min_index = i;
            }
        }

        seekSequence.push_back(requests[min_index]);
        total_seek_time += min_seek;
        current_head = requests[min_index];
        requests.erase(requests.begin() + min_index);
    }

    // Prints the seek sequence
    cout << "Seek sequence is: " << head << "-->";
    for (int i = 0; i < seekSequence.size(); i++) {
        cout << seekSequence[i] << "-->";
        if (i == seekSequence.size() - 1) {
            cout << seekSequence[i];
        }
    }
    cout << endl;

    return total_seek_time;
}

int main() {
    vector<int> requests;
    int request_count;
    int current_head;

    cout << "Enter the number of requests: ";
    cin >> request_count;

    cout << "Enter the requests: ";
    for (int i = 0; i < request_count; i++) {
        int request;
        cin >> request;
        requests.push_back(request);
    }

    cout << "Enter the current position of the disk head: ";
    cin >> current_head;

    int seek_time = sstf(requests, current_head);

    cout << "Total seek time: " << seek_time << endl;

    return 0;
}