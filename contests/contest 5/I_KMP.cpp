#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> prefix_function(const string& text) {
    int n = text.length();
    vector<int> res (n, 0);

    for (int i = 1; i < n; i++) {
        int j = res[i-1];
        while (j > 0 && text[i] != text[j]) {
            j = res[j - 1];
        }
        if (text[i] == text[j]) j++;
        res[i] = j;
    }

    return res;
}

vector<int> kmp(const vector<int>& prefix, int length) {
    vector<int> res;
    for (int i = length+1; i < prefix.size(); i++) {
        if (prefix[i] == length) res.push_back(i - 2*length);
    }

    return res;
}

void print_prefix(const vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    string pattern, text;
    cin >> pattern >> text;

    vector<int> pattern_prefix = prefix_function(pattern);
    cout << "Prefix template: ";
    print_prefix(pattern_prefix);

    string extended = pattern + "#" + text;
    vector<int> text_prefix = prefix_function(extended);
    cout << "Prefix function: ";
    print_prefix(text_prefix);

    vector<int> occurrences = kmp(text_prefix, pattern.length());
    cout << "Matches: ";
    print_prefix(occurrences);

    return 0;
}