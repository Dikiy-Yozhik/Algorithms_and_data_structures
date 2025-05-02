#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

std::vector<bool> sieve(ll start, ll end) 
{
    std::vector<bool> sieve(end + 1, true);
    
    sieve[0] = false;
    sieve[1] = false;

    ll count = 0;

    for (ll i = 2; i * i <= end; ++i) {
        std::vector<ll> no_primes;
        if (sieve[i]) {
            for (ll j = i * i; j <= end; j += i) {
                if(sieve[j]){
                    sieve[j] = false;
                    if (j >= start)
                        no_primes.push_back(j);
                }
            }
            count++;
        }
        if (!no_primes.empty()) {
            std::cout << "Iteration : " << count << "\n";
            for (ll num : no_primes)
                std::cout << num << " ";
            std::cout << "\n";
        }
    }
    return sieve;
}

int main () {
    ll s, f;
    std::cin >> s >> f;

    std::cout << "Start and finish: " << s << " " << f << "\n";

    bool flag = true;

    std::vector<bool> res = sieve(s, f);

    std::cout << "Primes :\n";
    for (ll i = 2; i <= f; i++) {
        if (res[i] && i >= s) {
            std::cout << i <<" ";
            flag = false;
        }
    }

    if (flag)
        std::cout << "No primes";

    return 0;
}
