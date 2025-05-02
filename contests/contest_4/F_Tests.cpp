#include <iostream>
#include <vector>

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

ll gcd(ll a, ll b) {
    while (b != 0) {
        ll temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void test_miller_rabin(ll n, bool& is_prime, ll& bad, ll& count1, ll& count2) {
    bad = 0;
    count1 = 0;
    count2 = 0;
    
    if (n <= 1) {
        is_prime = false;
        return;
    }
    if (n == 2 || n == 3) {
        is_prime = true;
        count1 = n - 1;
        return;
    }
    if (n % 2 == 0) {
        is_prime = false;
        bad = n - 3;
        count1 = 1;  
        count2 = 1;  
        return;
    }

    ll d = n - 1;
    ll s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (ll a = 1; a < n; a++) {
        if (a == 1) {
            count1++;
            continue;
        }
        
        if (gcd(a, n) > 1) {
            bad++;
            continue;
        }

        ll x = modpow(a, d, n);
        
        if (x == 1) {
            count1++;
            continue;
        }
        
        bool is_witness = (x == n - 1);
        for (ll r = 1; r < s && !is_witness; r++) {
            x = modpow(x, 2, n);
            if (x == n - 1) {
                is_witness = true;
            }
        }

        if (is_witness) {
            count2++;
        } else {
            bad++;
        }
    }

    is_prime = (bad == 0);
}

void test_ferma(ll n, bool& is_prime, ll& bad, ll& good) {
    bad = 0;
    good = 0;
    if (n <= 1) {
        is_prime = false;
        return;
    }
    if (n <= 3) {
        is_prime = true;
        good = n - 1;
        return;
    }
    if (n % 2 == 0) {
        is_prime = false;
        for (ll a = 1; a < n; ++a) {
            if (a == 1) {
                good++;
            } else {
                bad++;
            }
        }
        return;
    }

    for (ll a = 1; a < n; ++a) {
        if (gcd(a, n) != 1) {
            bad++;
        } else {
            if (modpow(a, n - 1, n) == 1) {
                good++;
            } else {
                bad++;
            }
        }
    }
    is_prime = (bad == 0);
}

int main() {
    ll n;
    std::cin >> n;

    bool fermat, miller;
    ll bad_f, good_f;
    ll bad_m, count1_m, count2_m;

    test_ferma(n, fermat, bad_f, good_f);
    test_miller_rabin(n, miller, bad_m, count1_m, count2_m);

    std::cout << "Miller-Rabin test: " << (miller ? "True" : "False") << " " << bad_m << " " << count1_m << " " << count2_m << "\n";
    std::cout << "Fermat test: " << (fermat ? "True" : "False") << " " << bad_f << " " << good_f << "\n";

    return 0;
}
