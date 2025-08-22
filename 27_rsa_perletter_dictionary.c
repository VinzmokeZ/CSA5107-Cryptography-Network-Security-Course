
/*
Program 27: Demonstrate insecurity of encrypting letters (0..25) separately under RSA.
Attacker can build dictionary of ciphertexts for all 26 possible plaintext letters using public (e,n).
Then map ciphertext blocks back to letters without private key.
Sample default uses small RSA: n=3233 e=17 (p=61 q=53)
*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long long modexp(long long a,long long e,long long m){
    long long res=1% m;
    a%=m;
    while(e){
        if(e&1) res = (res*a)%m;
        a=(a*a)%m; e>>=1;
    }
    return res;
}

int main(){
    long long n,e;
    char buf[128];
    printf("Enter public e (blank for 17): ");
    if(!fgets(buf,sizeof(buf),stdin)) return 0;
    if(sscanf(buf,"%lld",&e)!=1) e=17;
    printf("Enter modulus n (blank for 3233): ");
    if(!fgets(buf,sizeof(buf),stdin)) return 0;
    if(sscanf(buf,"%lld",&n)!=1) n=3233;

    long long dict[26];
    for(int i=0;i<26;i++) dict[i] = modexp(i,e,n);

    printf("Dictionary (cipher -> plain):\n");
    for(int i=0;i<26;i++) printf("%3lld -> %c\n", dict[i], 'A'+i);

    printf("\nNow enter ciphertext integers separated by space (end with non-number):\n");
    while(1){
        long long c;
        if(scanf("%lld",&c)!=1) break;
        int found=-1;
        for(int i=0;i<26;i++) if(dict[i]==c){ found=i; break; }
        if(found>=0) printf("%c", 'A'+found);
        else printf("?");
    }
    printf("\n");
    return 0;
}
