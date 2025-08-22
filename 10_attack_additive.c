
/*
Program 15/39: Frequency attack on Additive (Caesar) cipher
Prints top K candidate plaintexts by assuming most frequent cipher letter maps to 'E'
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void caesar(const char *in, char *out, int k){
    int i; for(i=0; in[i]; ++i){
        char c=in[i];
        if(isalpha((unsigned char)c)){
            char b = (c>='A'&&c<='Z')?'A':'a';
            out[i] = (char)((((c - b) - k + 26) % 26) + b);
        } else out[i]=c;
    } out[i]=0;
}

int main(){
    char text[4096]; int freq[26]={0};
    printf("Enter ciphertext: "); fgets(text,sizeof(text),stdin);
    for(int i=0;text[i];++i) if(isalpha((unsigned char)text[i])) freq[toupper((unsigned char)text[i])-'A']++;
    int maxL=0,maxF=-1;
    for(int i=0;i<26;i++) if(freq[i]>maxF){maxF=freq[i];maxL=i;}
    int assumeE=4; // 'E'
    int k = (maxL - assumeE + 26)%26; // shift used in encryption
    printf("Best guess (E assumption): shift=%d\n", k);
    char out[4096];
    for(int try=0; try<10; ++try){
        int kk = (k + try)%26;
        caesar(text,out,kk);
        printf("[%2d] %s", kk, out);
    }
    return 0;
}
