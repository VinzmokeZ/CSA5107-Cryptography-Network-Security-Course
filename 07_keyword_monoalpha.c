
/*
Program 8: Keyword-based Monoalphabetic Key Generator
Given keyword, produce cipher alphabet.
Sample:
Keyword: CIPHER
Output cipher alphabet:
C I P H E R A B D F G J K L M N O Q S T U V W X Y Z
*/
#include <stdio.h>
#include <ctype.h>

int main(){
    char key[256]; int used[26]={0};
    printf("Enter keyword: "); fgets(key,sizeof(key),stdin);
    char out[26]; int n=0;
    for(int i=0; key[i]; ++i){
        char c=toupper((unsigned char)key[i]);
        if(c<'A'||c>'Z') continue;
        if(c=='J') c='I';
        if(!used[c-'A']){ used[c-'A']=1; out[n++]=c; if(n==26) break; }
    }
    for(char c='A';c<='Z' && n<26;c++){
        if(c=='J') continue;
        if(!used[c-'A']){ used[c-'A']=1; out[n++]=c; }
    }
    printf("Cipher alphabet: ");
    for(int i=0;i<26;i++){ printf("%c", out[i]); if(i<25) printf(" "); }
    printf("\n");
    return 0;
}
