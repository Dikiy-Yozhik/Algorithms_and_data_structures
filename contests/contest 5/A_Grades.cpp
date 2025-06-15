#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, var;
    cin >> n;
    vector<int> marks (n);
    vector<int> dp (n, 1);
    vector<int> prev (n, -1);

    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    for (int i = 0; i < n; i++) {
        int best_j = -1, max_dp = 0;
        for (int j = 0; j < i; j++) {
            if (marks[j] <= marks[i]) {
                if (dp[j] > max_dp || (dp[j] == max_dp && j > best_j)) {
                    max_dp = dp[j];
                    best_j = j;
                }
            }
        }
        
        if (best_j != -1) {
            dp[i] = max_dp + 1;
            prev[i] = best_j;
        }
    }

    int max_len = 0, last_idx = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] >= max_len) {
            max_len = dp[i];
            last_idx = i;
        }
    }

    vector<int> answer;
    while (last_idx != -1) {
        answer.push_back(marks[last_idx]);
        last_idx = prev[last_idx];
    }
    reverse(answer.begin(), answer.end());

    cout << "Best length = " << max_len << endl;
    cout << "Best combo is:  ";
    for (int i = 0; i < answer.size(); ++i) {
        if (i != 0) cout << " ";
        cout << answer[i];
    }

    return 0;
}