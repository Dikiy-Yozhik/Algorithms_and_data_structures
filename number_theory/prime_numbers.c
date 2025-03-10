#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int gcd(int a, int b)// Euclidean algorithm
{
    if (b == 0)
        return a;
    return gcd(b, a%b);
}

int lcm(int a, int b)
{
    return (a*b) / gcd(a, b);
}

bool* sieve_of_eratosthenes(int size) 
{
    bool* sieve = malloc((size+1) * sizeof(bool));
    for (int i = 0; i <= size; ++i) {
        sieve[i] = true;
    }

    sieve[0] = false;
    sieve[1] = false;

    for (int i = 2; i*i <= size; ++i) {
        if (sieve[i]) {
            for (int j = i*i; j <= size; j += i) {
                sieve[j] = false;
            }
        }
    }
    return sieve;
}

bool is_prime_naive(int x) 
{
    for (int i = 2; i < x; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}

bool is_prime_sqrt(int x) 
{
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0)
            return false;
    }
    return true;
}

int bin_pow(int base, int p) 
{
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (res * base);
        }
        base = (base * base);
        p /= 2;
    }
    return res;
}

int bin_pow_modulo(int base, int p, int mod) 
{
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        p /= 2;
    }
    return res;
}

int main() 
{
    int a, b;
    printf("gcd: \n");
    scanf("%d %d", &a, &b);
    printf("%d\n", gcd(a, b));

    printf("lcm: \n");
    scanf("%d %d", &a, &b);
    printf("%d\n", lcm(a, b));

    printf("sieve:\n");
    scanf("%d", &a);
    bool* primes = sieve_of_eratosthenes(a);
    for (int i = 2; i <= a; ++i) {
        if (primes[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    free(primes);
}