
/*
Program 28: Diffie-Hellman key agreement (mod prime q)
Shows correct shared key with g^ab mod q.
*/
#include <stdio.h>

long long modexp(long long a,long long e,long long m){ long long r=1%m; while(e){ if(e&1) r=(r*a)%m; a=(a*a)%m; e>>=1;} return r; }

int main(){
    long long q=7919, g=10, a=1234, b=4321;
    long long A = modexp(g,a,q);
    long long B = modexp(g,b,q);
    long long s1 = modexp(B,a,q);
    long long s2 = modexp(A,b,q);
    printf("A=%lld B=%lld\nShared s1=%lld s2=%lld\n", A,B,s1,s2);
    return 0;
}
