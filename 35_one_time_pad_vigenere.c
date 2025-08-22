
/*
Program 35: One-time pad version of Vigenere (numeric key stream)
- Accepts plaintext and a key stream (integers 0..25); encrypts by shifting each letter.
Sample:
Plain: SENDMOREMONEY
Key stream: 9 0 1 7 23 15 21 14 11 11 2 8 9
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char text[1024];
    int key[1024], klen=0;
    printf("Enter plaintext (letters): ");
    if(!fgets(text,sizeof(text),stdin)) return 0;
    int n = (int)strcspn(text, "\r\n"); text[n]=0;
    printf("Enter key stream integers 0..25 separated by spaces (end with -1):\n");
    while(1){ int v; if(scanf("%d",&v)!=1) break; if(v<0) break; key[klen++]=v%26; }

    int j=0;
    char out[1024]; strcpy(out, text);
    for(int i=0;i<n;i++){
        if(isalpha((unsigned char)text[i])){
            char base = isupper((unsigned char)text[i])?'A':'a';
            int shift = key[j%klen];
            out[i] = (char)(((text[i]-base+shift)%26)+base);
            j++;
        } else out[i]=text[i];
    }
    out[n]=0;
    printf("Ciphertext: %s\n", out);

    // Decrypt demonstration
    j=0; for(int i=0;i<n;i++){
        if(isalpha((unsigned char)out[i])){
            char base = isupper((unsigned char)out[i])?'A':'a';
            int shift = key[j%klen];
            text[i] = (char)(((out[i]-base - shift + 26)%26)+base);
            j++;
        }
    }
    printf("Decrypted back: %.s%s\n", "", text);
    return 0;
}
