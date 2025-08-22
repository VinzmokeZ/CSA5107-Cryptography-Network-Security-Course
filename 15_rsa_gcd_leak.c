
/*
Program 25: If a plaintext block shares a factor with n, gcd reveals a factor of n.
We simulate: given n and a plaintext m with gcd(m,n)>1.
*/
#include <stdio.h>

long long gcd(long long a,long long b){ while(b){ long long t=a%b; a=b; b=t;} return a; }

int main(){
    long long n=391, m=17*5; // 391=17*23, choose m multiple of 17
    long long g = gcd(m, n);
    if(g>1) printf("GCD reveals factor: %lld (other factor %lld)\n", g, n/g);
    else printf("No factor revealed.\n");
    return 0;
}
