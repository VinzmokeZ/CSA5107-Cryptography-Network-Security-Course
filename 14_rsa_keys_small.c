
/*
Program 24: RSA small example - given e=31, n=3599, find d
We factor n by trial division, compute phi, then modular inverse.
*/
#include <stdio.h>
#include <math.h>

long long modinv(long long a, long long m){
    long long t=0, nt=1, r=m, nr=a%m;
    while(nr!=0){
        long long q=r/nr;
        long long tmp=nt; nt=t - q*nt; t=tmp;
        tmp=nr; nr=r - q*nr; r=tmp;
    }
    if(r>1) return -1;
    if(t<0) t+=m;
    return t;
}

int main(){
    long long e=31, n=3599, p=0,q=0;
    for(long long i=2; i*i<=n; ++i) if(n%i==0){ p=i; q=n/i; break; }
    if(!p){ printf("Failed to factor n.\n"); return 0; }
    long long phi=(p-1)*(q-1);
    long long d=modinv(e,phi);
    printf("n=%lld = %lld * %lld\nphi=%lld\ne=%lld\nd=%lld\n", n,p,q,phi,e,d);
    return 0;
}
