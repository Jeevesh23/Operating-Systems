#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int look(vector<int> &rq, int current_head) {
    int head = current_head, distance = 0;
    vector<int> seq;
    sort(rq.begin(), rq.end());
    auto it = lower_bound(rq.begin(), rq.end(), head);
    int midPos;
    int var = 1;
    while (var == 1) {
        if (head > *it) {
            midPos = it - rq.begin();
            var = 0;
        } else {
            --it;
            midPos = it - rq.begin();
        }
    }

    for (int i = midPos; i >= 0; i--) {
        distance += abs(rq[i] - current_head);
        current_head = rq[i];
        seq.push_back(rq[i]);
    }
    for (int i = midPos + 1; i < rq.size(); i++) {
        distance += abs(rq[i] - current_head);
        current_head = rq[i];
        seq.push_back(rq[i]);
    }
    cout << "Seek sequence is: " << head << "-->";
    for (int i = 0; i < seq.size(); i++) {
        if (i == seq.size() - 1) {
            cout << seq[i];
        } else {
            cout << seq[i] << "-->";
        }
    }

    cout << endl;

    return distance; // Return the total seek distance
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

    int seek_distance = look(requests, current_head);

    cout << "Total seek distance: " << seek_distance << endl;

    return 0;
}
