#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using ll = long long; 

ll mulmod(ll a, ll b, ll mod) {
    ll res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) 
            res = (res + a) % mod;
        a = (a * 2) % mod;
        b /= 2;
    }
    return res;
}

ll modpow(ll base, ll power, ll mod) {
    ll result = 1;
    base %= mod;
    while (power > 0) {
        if (power % 2 == 1) 
            result = mulmod(result, base, mod);
        base = mulmod(base, base, mod);
        power /= 2;
    }
    return result;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

ll modinv(ll a, ll m) {
    ll x, y;
    ll gcd = extended_gcd(a, m, x, y);
    if (gcd != 1) 
        return -1;  
    return (x % m + m) % m; 
}

ll find_e(ll e_start, ll phi_n) {
    ll e = e_start;
    while (e < phi_n) {
        ll x, y;
        if (extended_gcd(e, phi_n, x, y) == 1) 
            return e;
        e++;
    }
    return -1;
}

int main() {
    ll p, q, e_start;
    std::cin >> p >> q >> e_start;
    
    std::string message;
    std::cin >> std::ws;
    std::getline(std::cin, message);

    ll n = p * q;
    ll r = (p - 1) * (q - 1);

    ll e = find_e(e_start, r);
    if (e == -1) {
        return 1;
    }

    ll d = modinv(e, r);
    if (d == -1) {
        return 1;
    }

    std::cout << "Private: " << d << " " << n << "\n";
    std::cout << "Public: " << e << " " << n << "\n";

    ll combined = 0;
    for (char ch : message) {
        if (isalpha(ch) && islower(ch)) {
            combined = (combined << 8) | static_cast<unsigned char>(ch);
        }
    }

    std::cout << "Initial bytes:";
    ll temp = combined;
    std::vector<int> bytes;
    while (temp > 0) {
        bytes.push_back(temp & 0xFF);
        temp >>= 8;
    }
    for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    ll encrypted = modpow(combined, e, n);

    std::cout << "Encrypted bytes:";
    temp = encrypted;
    bytes.clear();
    while (temp > 0) {
        bytes.push_back(temp & 0xFF);
        temp >>= 8;
    }

    for (auto it = bytes.rbegin(); it != bytes.rend(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << "\n";

    return 0;
}