
/*
Program 5: Affine Cipher (Encrypt/Decrypt)
C = (a*x + b) mod 26, x in 0..25; require gcd(a,26)=1
Sample:
Text: HELLO, a=5, b=8
Output:
Cipher: RCYYA
Plain : HELLO
*/
#include <stdio.h>
#include <ctype.h>

int gcd(int a,int b){ while(b){int t=a%b;a=b;b=t;} return a; }
int modinv(int a){
    a%=26; for(int i=1;i<26;i++) if((a*i)%26==1) return i; return -1;
}
void affine(const char *in, char *out, int a, int b, int enc){
    int i, inv=modinv(a);
    for(i=0; in[i]; ++i){
        char c=in[i];
        if(isalpha((unsigned char)c)){
            char base = (c>='A'&&c<='Z')?'A':'a';
            int x = c - base;
            int y = enc ? (a*x + b)%26 : ( (inv*((x - b + 26)%26)) % 26 );
            out[i]=(char)(y+base);
        } else out[i]=c;
    } out[i]=0;
}
int main(){
    char text[1024], enc[1024], dec[1024]; int a,b;
    printf("Enter text: "); fgets(text,sizeof(text),stdin);
    printf("Enter a (coprime with 26): "); scanf("%d",&a);
    printf("Enter b: "); scanf("%d",&b);
    if(gcd(a,26)!=1){ printf("Invalid a; not coprime with 26.\n"); return 0; }
    affine(text,enc,a,b,1);
    affine(enc,dec,a,b,0);
    printf("Cipher: %s", enc);
    printf("Plain : %s", dec);
    return 0;
}
