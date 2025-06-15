#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> values (n);
    for (int i = 0; i < n; i++) cin >> values[i];

    int right = 0, left = 0, current_sum = 0, min_length = INT_MAX, best_sum = 0, best_r = 0, best_l = 0;
    while (right < n) {
        current_sum += values[right];
        while (current_sum >= k) {
            if ((right - left + 1 < min_length) || (right - left + 1 == min_length && current_sum > best_sum)) {
                best_sum = current_sum;
                min_length = right - left + 1;
                best_l = left;
                best_r = right;
            }
            current_sum -= values[left];
            left++;
        }
        right++;
    }

    if (min_length == INT_MAX) {
        cout << "No summ" << endl;
    } 
    else {
        cout << "Length = " << min_length << endl;
        cout << "Sum = " << best_sum << endl;
        cout << "Start = " << best_l << endl;
        cout << "Finish = " << best_r << endl;
    }

    return 0;
}