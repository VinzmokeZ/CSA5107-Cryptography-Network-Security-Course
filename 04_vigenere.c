
/*
Program 4: Polyalphabetic (Vigenere) Encrypt/Decrypt
Sample:
Text: ATTACKATDAWN
Key : LEMON
Output:
Encrypted: LXFOPVEFRNHR
Decrypted: ATTACKATDAWN
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void vigenere(const char *in, const char *key, char *out, int enc){
    int n=strlen(key), j=0;
    for(int i=0; in[i]; ++i){
        char c=in[i];
        if(isalpha((unsigned char)c)){
            int shift = toupper((unsigned char)key[j%n])-'A';
            if(!enc) shift = (26-shift)%26;
            char base = isupper((unsigned char)c)?'A':'a';
            out[i]=(char)(((c-base+shift)%26)+base);
            j++;
        } else out[i]=c;
    }
    out[strlen(in)]=0;
}

int main(){
    char text[1024], key[256], enc[1024], dec[1024];
    printf("Enter text: "); fgets(text,sizeof(text),stdin);
    printf("Enter key: "); fgets(key,sizeof(key),stdin);
    // strip newline
    key[strcspn(key,"\r\n")]=0;
    vigenere(text,key,enc,1);
    vigenere(enc,key,dec,0);
    printf("Encrypted: %s", enc);
    printf("Decrypted: %s", dec);
    return 0;
}
