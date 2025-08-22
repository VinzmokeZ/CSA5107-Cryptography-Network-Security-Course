
/*
Program 6: Break Affine given two most frequent letters in ciphertext
Assume they correspond to 'E' and 'T' (order unknown). Solve for a,b.
Input: two ciphertext letters (e.g., B and U)
*/
#include <stdio.h>
#include <ctype.h>

int modinv26(int a){ for(int x=1;x<26;x++) if((a*x)%26==1) return x; return -1; }
int mod(int x){ x%=26; if(x<0) x+=26; return x; }

int solve(int c1, int c2, int p1, int p2, int *a, int *b){
    // c = a*p + b (mod 26) -> (c1-c2) = a*(p1-p2)
    int dc = mod(c1 - c2), dp = mod(p1 - p2);
    int inv = modinv26(dp);
    if(inv==-1) return 0;
    *a = mod(dc * inv);
    *b = mod(c1 - (*a)*p1);
    return 1;
}

int main(){
    char x1,x2;
    printf("Enter two most frequent ciphertext letters (e.g., B U): ");
    if(scanf(" %c %c",&x1,&x2)!=2){ printf("Bad input\n"); return 0; }
    int c1=toupper((unsigned char)x1)-'A', c2=toupper((unsigned char)x2)-'A';
    int a,b,ok1=solve(c1,c2,'E'-'A','T'-'A',&a,&b);
    int a2,b2,ok2=solve(c1,c2,'T'-'A','E'-'A',&a2,&b2);
    if(ok1) printf("Assuming E,T -> a=%d b=%d\n",a,b);
    if(ok2) printf("Assuming T,E -> a=%d b=%d\n",a2,b2);
    if(!ok1 && !ok2) printf("No solution with E/T mapping.\n");
    return 0;
}
