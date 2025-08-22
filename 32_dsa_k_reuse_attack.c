
/*
Program 32: DSA k-reuse vulnerability demo.
If two signatures (r,s1) and (r,s2) on messages H1,H2 use same k, attacker recovers k and private x.
We demo with small toy parameters.
*/
#include <stdio.h>
#include <stdint.h>

long long modexp(long long a,long long e,long long m){
    long long r=1% m; a%=m;
    while(e){ if(e&1) r=(r*a)%m; a=(a*a)%m; e>>=1; } return r;
}

long long egcd(long long a,long long b,long long *x,long long *y){
    if(b==0){ *x=1; *y=0; return a; }
    long long x1,y1; long long g = egcd(b,a%b,&x1,&y1);
    *x = y1; *y = x1 - (a/b)*y1; return g;
}
long long modinv(long long a,long long m){
    long long x,y; long long g = egcd(a,m,&x,&y);
    if(g!=1) return -1;
    x%=m; if(x<0) x+=m; return x;
}

int main(){
    // Toy parameters (small): q prime
    long long q = 1019;
    long long p = 2*q + 1;
    long long g = 2;
    long long x = 123; // private
    long long k = 77;  // nonce reused
    long long H1 = 111, H2 = 222;

    long long r = modexp(g, k, p) % q;
    long long kinv = modinv(k, q);
    long long s1 = (kinv * (H1 + x * r)) % q;
    long long s2 = (kinv * (H2 + x * r)) % q;

    printf("Public: p=%lld q=%lld g=%lld\n", p,q,g);
    printf("Signatures share r=%lld\n", r);
    printf("s1=%lld s2=%lld H1=%lld H2=%lld\n", s1,s2,H1,H2);

    // Attack: recover k
    long long diff_s = (s1 - s2) % q; if(diff_s<0) diff_s+=q;
    long long diff_H = (H1 - H2) % q; if(diff_H<0) diff_H+=q;
    long long inv_diff_s = modinv(diff_s, q);
    if(inv_diff_s == -1){ printf("Cannot invert s1-s2 mod q\n"); return 0; }
    long long k_rec = (diff_H * inv_diff_s) % q;
    // recover x: x = (s1*k - H1) * r^{-1} mod q
    long long r_inv = modinv(r, q);
    long long x_rec = (((s1 * k_rec) % q - H1) % q + q) % q;
    x_rec = (x_rec * r_inv) % q;
    printf("Recovered k=%lld x=%lld (original x=%lld)\n", k_rec, x, x_rec);
    return 0;
}
