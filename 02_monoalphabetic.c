
/*
Program 2: Monoalphabetic Substitution (Encrypt only)
Assumes UPPERCASE letters and 26-letter key.
Sample:
Plain: HELLO
Key  : QWERTYUIOPASDFGHJKLZXCVBNM
Output:
Cipher: ITSSG
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){
    char key[64], pt[1024], ct[1024]; int i;
    printf("Enter 26-letter UPPERCASE key: ");
    fgets(key, sizeof(key), stdin);
    if(strlen(key)<26){ printf("Invalid key.\n"); return 0; }
    printf("Enter plaintext: "); fgets(pt, sizeof(pt), stdin);
    for(i=0; pt[i]; ++i){
        char c=pt[i];
        if(isalpha((unsigned char)c)){
            int idx = toupper(c) - 'A';
            ct[i] = key[idx];
            if(islower(c)) ct[i] = tolower(ct[i]);
        } else ct[i]=c;
    }
    ct[i]=0;
    printf("Cipher: %s", ct);
    return 0;
}
