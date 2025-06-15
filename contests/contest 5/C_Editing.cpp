#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int levenshtein(const string& pattern, const string& word) {
    int m = pattern.length();
    int n = word.length();

    vector<vector<int>> dp (m+1, vector<int> (n+1, 0));

    for (int i = 0; i <= m; i++) 
        dp[i][0] = i;
    for (int j = 0; j <= n; j++) 
        dp[0][j] = j;
    
    for (int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if (pattern[i-1] == word[j-1])
                dp[i][j] = dp[i-1][j-1];
            else {
                dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            }
        }
    }

    return dp[m][n];
}

int main() {
    string pattern;
    int n;

    getline(cin, pattern);
    cin >> n;
    cin.ignore();

    vector<string> words (n);
    for (int i = 0; i < n; i++) {
        getline(cin, words[i]);
    }

    vector<int> cost (n, 0);
    for (int i = 0; i < n; i++) {
        cost[i] = levenshtein(pattern, words[i]);
    }

    int min = *min_element(cost.begin(), cost.end());
    vector<string> answer;
    for (int i = 0; i < n; i++) {
        if (cost[i] == min) {
            answer.push_back(words[i]);
        }
    }

    cout << "Most similar words = " << answer.size() << endl;
    cout << "Minimal operations needed = " << min << endl;
    for (const string &s : answer) {
        cout << s << endl;
    }

    return 0;
}