#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int scan(vector<int> &rq, int current_head, int limit) {
    int head = current_head, distance = 0;
    vector<int> seq;
    sort(rq.begin(), rq.end());
    auto it = lower_bound(rq.begin(), rq.end(), head);
    int midPos;
    int var = 1;
    while (var == 1) {
        if (head < *it) {
            midPos = it - rq.begin();
            var = 0;
        } else {
            ++it; 
            midPos = it - rq.begin();
        }
    }

    for (int i = midPos; i < rq.size(); i++) {
        distance += abs(rq[i] - current_head);
        if (i == rq.size() - 1) {
            distance += abs(rq[rq.size() - 1] - limit) + limit;
            current_head = 0;
            seq.push_back(rq[i]);
            seq.push_back(limit);
            seq.push_back(0);
        } else {
            current_head = rq[i];
            seq.push_back(rq[i]);
        }
    }
    for (int i = 0; i < midPos; i++) {
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
    int limit;

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

    cout << "Enter the limit of the memory: ";
    cin >> limit;

    int seek_distance = scan(requests, current_head, limit);

    cout << "Total seek distance: " << seek_distance << endl;

    return 0;
}