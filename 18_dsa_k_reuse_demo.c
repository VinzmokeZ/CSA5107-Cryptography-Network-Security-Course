
/*
Program 32: DSA k-reuse vulnerability demo (toy parameters)
If the same k is reused for two messages, private key can be recovered.
*/
#include <stdio.h>

long long modinv(long long a,long long m){
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
    long long q=1019, p= q*2+1; // not real DSA-safe, demo only
    long long g=2, x=123; // private
    long long y=1; for(long long i=0;i<x;i++) y=(y*g)%p;
    long long k=77;
    long long H1=111, H2=222; // message hashes
    long long r = 1; for(int i=0;i<k;i++) r=(r*g)%p; r%=q;
    long long s1 = (modinv(k,q) * (H1 + x*r)) % q;
    long long s2 = (modinv(k,q) * (H2 + x*r)) % q;
    // attacker knowing (r,s1),(r,s2) recovers x:
    long long num = ( (s1 - s2) * k ) % q;
    if(num<0) num+=q;
    long long den = (H1 - H2)%q; if(den<0) den+=q;
    long long xrec = ( num * modinv(den,q) ) % q;
    printf("Original x=%lld, Recovered x=%lld\n", x, xrec);
    return 0;
}
