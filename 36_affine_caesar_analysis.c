
/*
Program 36: Affine Caesar analysis and encrypt/decrypt
- C = (a*p + b) mod 26; a must be coprime with 26.
- b may be any 0..25.
Program prints allowed a values and demonstrates encryption/decryption.
*/
#include <stdio.h>
#include <ctype.h>

int gcd(int a,int b){ while(b){ int t=a%b; a=b; b=t; } return a; }
int modinv(int a){
    a%=26; for(int i=1;i<26;i++) if((a*i)%26==1) return i; return -1;
}

void affine(const char *in, char *out, int a, int b, int enc){
    int inv = modinv(a);
    for(int i=0; in[i]; ++i){
        char c=in[i];
        if(isalpha((unsigned char)c)){
            char base = isupper((unsigned char)c)?'A':'a';
            int x = c - base;
            int y = enc ? (a*x + b)%26 : (inv*(x - b + 26)%26);
            out[i] = (char)(y + base);
        } else out[i]=c;
    }
    out[strlen(in)]=0;
}

int main(){
    printf("Allowed 'a' values coprime with 26:\n");
    for(int a=1;a<26;a++) if(gcd(a,26)==1) printf("%d ", a); printf("\n");
    printf("b may be any 0..25 (no restriction).\n\n");

    char pt[] = "HELLO";
    int a=5,b=8;
    char ct[128], rec[128];
    affine(pt, ct, a, b, 1);
    affine(ct, rec, a, b, 0);
    printf("Example: PT=%s a=%d b=%d\nCipher=%s\nDecrypted=%s\n", pt,a,b,ct,rec);
    return 0;
}
