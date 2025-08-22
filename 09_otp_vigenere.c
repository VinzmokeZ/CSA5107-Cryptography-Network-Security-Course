
/*
Program 14/35: One-time pad as numeric Vigenere (0-25 shifts)
Sample:
Plain: SEND MORE MONEY
Key  : 9 0 1 7 23 15 21 14 11 11 2 8 9
*/
#include <stdio.h>
#include <ctype.h>

int main(){
    char text[1024]; int key[1024], klen=0;
    printf("Enter plaintext: "); fgets(text,sizeof(text),stdin);
    printf("Enter key stream as integers 0-25 (end with -1): ");
    while(1){ int v; if(scanf("%d",&v)!=1) break; if(v<0) break; key[klen++]=v%26; }
    int j=0; 
    for(int i=0;text[i];++i){
        char c=text[i];
        if(isalpha((unsigned char)c)){
            int base = (c>='A'&&c<='Z')?'A':'a';
            int shift= key[j%klen];
            char out = (char)(((c-base+shift)%26)+base);
            text[i]=out; j++;
        }
    }
    printf("Ciphertext: %s", text);
    return 0;
}
