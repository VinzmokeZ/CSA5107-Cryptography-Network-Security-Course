
/*
Program 25: If one plaintext block shares a non-trivial factor with n, gcd reveals factor.
Demo: Input n and m (plaintext block as integer). Program prints gcd(m,n).
Sample:
n=391 (17*23), m=85 (5*17) => gcd = 17 -> factor found.
*/
#include <stdio.h>

long long gcd(long long a,long long b){ while(b){ long long t=a%b; a=b; b=t;} return a; }

int main(){
    long long n,m;
    printf("Enter modulus n (e.g., 391): "); if(scanf("%lld",&n)!=1) return 0;
    printf("Enter plaintext integer m (e.g., 85): "); if(scanf("%lld",&m)!=1) return 0;
    long long g = gcd(m,n);
    if(g>1 && g<n) printf("Non-trivial gcd = %lld -> factor found. Other factor = %lld\n", g, n/g);
    else if(g==n) printf("gcd equals n (m multiple of n)\n");
    else printf("gcd = %lld (no factor found)\n", g);
    return 0;
}
