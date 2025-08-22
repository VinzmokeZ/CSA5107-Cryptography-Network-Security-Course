
/*
Program 1: Caesar Cipher (Encrypt/Decrypt)
Sample Input:
HELLO WORLD
3
Sample Output:
Encrypted: KHOOR ZRUOG
Decrypted: HELLO WORLD
*/
#include <stdio.h>
#include <ctype.h>

void caesar(const char *in, char *out, int k, int enc) {
    int i; k%=26; if(!enc) k = (26 - k)%26;
    for(i=0; in[i]; ++i){
        char c = in[i];
        if(isalpha((unsigned char)c)){
            char base = (c>='A'&&c<='Z')?'A':'a';
            out[i] = (char)(((c - base + k) % 26) + base);
        } else out[i] = c;
    }
    out[i]=0;
}

int main(){
    char text[1024]; int key;
    printf("Enter text: "); fgets(text, sizeof(text), stdin);
    printf("Enter key (1-25): "); scanf("%d",&key);
    char enc[1024], dec[1024];
    caesar(text, enc, key, 1);
    caesar(enc, dec, key, 0);
    printf("Encrypted: %s", enc);
    printf("Decrypted: %s", dec);
    return 0;
}
