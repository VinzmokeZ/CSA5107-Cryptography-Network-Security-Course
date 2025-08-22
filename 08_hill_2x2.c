
/*
Program 12: Hill Cipher 2x2 (Encrypt/Decrypt uppercase, X padding)
Key:
|a b|
|c d|  with det = a*d - b*c invertible mod 26
Sample:
Text: MEETME
Key: 9 4 / 5 7
*/
#include <stdio.h>
#include <ctype.h>

int mod(int x){ x%=26; if(x<0) x+=26; return x; }
int inv26(int a){ for(int i=1;i<26;i++) if((a*i)%26==1) return i; return -1; }

int main(){
    char text[1024]; int a,b,c,d;
    printf("Enter UPPER plaintext: "); fgets(text,sizeof(text),stdin);
    printf("Enter key a b c d: "); if(scanf("%d %d %d %d",&a,&b,&c,&d)!=4){printf("Bad key\n");return 0;}
    int det = mod(a*d - b*c), id = inv26(det);
    if(id==-1){ printf("Non-invertible key.\n"); return 0; }
    // inverse matrix
    int ia = mod( d*id), ib = mod(-b*id), ic = mod(-c*id), idd= mod( a*id);

    char buf[2048]; int n=0;
    for(int i=0;text[i];++i) if(isalpha((unsigned char)text[i])) buf[n++]=toupper((unsigned char)text[i]);
    if(n%2) buf[n++]='X';
    char enc[2048]={0}, dec[2048]={0};
    for(int i=0;i<n;i+=2){
        int x=buf[i]-'A', y=buf[i+1]-'A';
        int e1 = mod(a*x + b*y), e2 = mod(c*x + d*y);
        enc[i]= (char)(e1+'A'); enc[i+1]= (char)(e2+'A');
        int p1 = mod(ia*e1 + ib*e2), p2 = mod(ic*e1 + idd*e2);
        dec[i]= (char)(p1+'A'); dec[i+1]=(char)(p2+'A');
    }
    printf("Encrypted: ");
    for(int i=0;i<n;i++){ putchar(enc[i]); if(i%2) putchar(' '); }
    printf("\nDecrypted: ");
    for(int i=0;i<n;i++){ putchar(dec[i]); if(i%2) putchar(' '); }
    printf("\n");
    return 0;
}
