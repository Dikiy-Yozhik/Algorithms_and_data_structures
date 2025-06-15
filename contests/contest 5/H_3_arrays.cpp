#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int main() {
    int n_A, n_B, n_C;

    cin >> n_A;
    vector<int> A (n_A);
    for (int i = 0; i < n_A; i++) cin >> A[i];

    cin >> n_B;
    vector<int> B (n_B);
    for (int i = 0; i < n_B; i++) cin >> B[i];

    cin >> n_C;
    vector<int> C (n_C);
    for (int i = 0; i < n_C; i++) cin >> C[i];

    int ptr_a = 0, ptr_b = 0, ptr_c = 0;
    int current_dif = INT_MAX, best_dif = INT_MAX, best_a = 0, best_b = 0, best_c = 0;

    while (ptr_a < n_A && ptr_b < n_B && ptr_c < n_C) {
        int current_max = max({A[ptr_a], B[ptr_b], C[ptr_c]});
        int current_min = min({A[ptr_a], B[ptr_b], C[ptr_c]});
        int current_dif = current_max - current_min;

        if (current_dif < best_dif || 
            (current_dif == best_dif && 
             (ptr_a < best_a || 
              (ptr_a == best_a && ptr_b < best_b) || 
              (ptr_a == best_a && ptr_b == best_b && ptr_c < best_c)))) {
            best_dif = current_dif;
            best_a = ptr_a;
            best_b = ptr_b;
            best_c = ptr_c;
        }

        if (A[ptr_a] == current_min && ptr_a < n_A - 1) ptr_a++;

        else if (B[ptr_b] == current_min && ptr_b < n_B - 1) ptr_b++;
    
        else if (ptr_c < n_C - 1) ptr_c++;
    
        else break;
    }

    cout << "Numbers = " << A[best_a] << " " << B[best_b] << " " << C[best_c] << endl;
    cout << "Result = " << best_dif << endl;

    return 0;
}