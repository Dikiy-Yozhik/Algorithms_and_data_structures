#include <iostream>
#include <vector>
#include <string>

using namespace std;

void rabin_karp_search(const string& text, const string& pattern, int mod,
                      vector<int>& matches, vector<int>& spurious_hits) {
    int n = text.size();
    int m = pattern.size();
    
    matches.clear();
    spurious_hits.clear();

    if (n < m || m == 0) return;

    // Precompute power for rolling hash: 26^(m-1) mod mod
    int power = 1;
    for (int i = 0; i < m - 1; ++i) {
        power = (power * 26) % mod;
    }

    // Compute hash of pattern and first window of text
    int pattern_hash = 0;
    int window_hash = 0;
    for (int i = 0; i < m; ++i) {
        pattern_hash = (pattern_hash * 26 + (pattern[i] - 'a')) % mod;
        window_hash = (window_hash * 26 + (text[i] - 'a')) % mod;
    }

    // Slide the window over the text
    for (int i = 0; i <= n - m; ++i) {
        // Check if hash values match
        if (window_hash == pattern_hash) {
            // Verify actual match
            bool is_match = true;
            for (int j = 0; j < m; ++j) {
                if (text[i + j] != pattern[j]) {
                    is_match = false;
                    break;
                }
            }
            
            if (is_match) {
                matches.push_back(i);
            } else {
                spurious_hits.push_back(i);
            }
        }

        // Compute hash for next window
        if (i < n - m) {
            window_hash = (26 * (window_hash - (text[i] - 'a') * power) + (text[i + m] - 'a'));
            window_hash %= mod;
            if (window_hash < 0) {
                window_hash += mod;
            }
        }
    }
}

int main() {
    int mod;
    string pattern, text;
    
    cin >> mod;
    cin >> pattern;
    cin >> text;

    vector<int> matches;
    vector<int> spurious_hits;
    
    rabin_karp_search(text, pattern, mod, matches, spurious_hits);

    // Output matches
    cout << "Matches: ";
    for (size_t i = 0; i < matches.size(); ++i) {
        if (i != 0) cout << " ";
        cout << matches[i];
    }
    cout << endl;

    // Output spurious hits
    cout << "Spurious hits: ";
    for (size_t i = 0; i < spurious_hits.size(); ++i) {
        if (i != 0) cout << " ";
        cout << spurious_hits[i];
    }
    cout << endl;

    return 0;
}