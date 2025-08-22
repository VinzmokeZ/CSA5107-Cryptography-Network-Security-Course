
/*
Program 24: Given public key (e, n) find private key d by factoring n.
Sample Input (press Enter for defaults): e=31 n=3599
Sample Output:
n = 3599 = 37 * 97
phi = 3456
d = 223
*/
#include <stdio.h>
#include <math.h>

typedef long long ll;

ll egcd(ll a, ll b, ll *x, ll *y){
    if(b==0){ *x=1; *y=0; return a; }
    ll x1,y1; ll g = egcd(b, a%b, &x1, &y1);
    *x = y1; *y = x1 - (a/b)*y1; return g;
}

ll modinv(ll a, ll m){
    ll x,y; ll g = egcd(a,m,&x,&y);
    if(g!=1) return -1;
    x%=m; if(x<0) x+=m;
    return x;
}

int main(){
    ll e,n;
    char buf[64];
    printf("Enter e (or blank for 31): ");
    if(!fgets(buf,sizeof(buf),stdin)) return 0;
    if(sscanf(buf,"%lld",&e)!=1) e=31;
    printf("Enter n (or blank for 3599): ");
    if(!fgets(buf,sizeof(buf),stdin)) return 0;
    if(sscanf(buf,"%lld",&n)!=1) n=3599;

    ll p=0,q=0;
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){ p=i; q=n/i; break; }
    }
    if(p==0){ printf("Failed to factor n=%lld\n", n); return 0; }
    ll phi = (p-1)*(q-1);
    ll d = modinv(e, phi);
    printf("n = %lld = %lld * %lld\nphi = %lld\ne = %lld\nd = %lld\n", n,p,q,phi,e,d);
    return 0;
}
