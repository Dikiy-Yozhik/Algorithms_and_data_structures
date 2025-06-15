#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

map<char, int> analyze_string(const string& s) {
    map<char, int> freq;  
    for (char c : s) {    
        freq[c]++;      
    }
    return freq;          
}

void generate_codes(Node* root, string code, map<char, string>& codes) {
    if (!root) return;
    if (root->ch != '\0') {
        if (code.empty()) code = "0";
        codes[root->ch] = code;
    }
    generate_codes(root->left, code + "0", codes);
    generate_codes(root->right, code + "1", codes);
}

pair<map<char, string>, string> huffman_code(const string& s) {
    if (s.empty()) return {{}, ""};

    auto freq = analyze_string(s);
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto& [ch, count] : freq) {
        pq.push(new Node(ch, count));
    }

    if (pq.size() == 1) {
        auto node = new Node('\0', 0);
        node->left = pq.top();
        pq.pop();
        pq.push(node);
    }

    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto node = new Node('\0', left->freq + right->freq);
        node->left = left;
        node->right = right;
        pq.push(node);
    }

    map<char, string> codes;
    generate_codes(pq.top(), "", codes);

    string encoded;
    for (char c : s) encoded += codes[c];

    return {codes, encoded};
}

int main() {
    string s;
    getline(cin, s);

    auto[codes, enc_s] = huffman_code(s);

    cout << codes.size() << " " << enc_s.size() << endl;

    vector<char> sort_letters;
    for (auto& [ch, code] : codes) sort_letters.push_back(ch);
    sort(sort_letters.begin(), sort_letters.end());

    for (char ch : sort_letters) {
        cout << ch << ": " << codes[ch] << endl;
    }

    cout << enc_s;

    return 0;
}
