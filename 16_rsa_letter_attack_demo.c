
/*
Program 27: Insecure per-letter RSA demo
Encrypts letters 0..25; shows pattern repetition -> vulnerable to dictionary attack.
*/
#include <stdio.h>
#include <math.h>

long long modexp(long long a,long long e,long long m){ long long r=1%m; while(e){ if(e&1) r=(r*a)%m; a=(a*a)%m; e>>=1;} return r; }

int main(){
    long long n=3233, e=17; // classic RSA example (61*53)
    char msg[]="HELLOHELLO";
    printf("Cipher blocks: ");
    for(int i=0; msg[i]; ++i){
        int x = (msg[i]-'A')%26;
        long long c = modexp(x,e,n);
        printf("%lld ", c);
    }
    printf("\nNote repeating patterns for repeating letters.\n");
    return 0;
}
