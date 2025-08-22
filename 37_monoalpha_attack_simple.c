
/*
Programs 37 & 40: Heuristic attack on monoalphabetic substitution
Approach: Map most frequent letters in ciphertext to ETAOINSHRDLCUMWFGYPBVKJXQZ order.
Generate top-10 by rotating candidate mappings slightly.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *freq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

void decode(const char *ct, char *pt, const char map[26]){
    for(int i=0; ct[i]; ++i){
        char c=ct[i];
        if(isalpha((unsigned char)c)){
            int idx = toupper((unsigned char)c)-'A';
            char m = map[idx];
            if(islower((unsigned char)c)) m=tolower(m);
            pt[i]=m;
        } else pt[i]=c;
    }
    pt[strlen(ct)]=0;
}

int main(){
    char ct[8192]; int count[26]={0};
    printf("Enter ciphertext: "); fgets(ct,sizeof(ct),stdin);
    for(int i=0; ct[i]; ++i) if(isalpha((unsigned char)ct[i])) count[toupper((unsigned char)ct[i])-'A']++;
    // get indices sorted by freq
    int idx[26]; for(int i=0;i<26;i++) idx[i]=i;
    for(int i=0;i<26;i++) for(int j=i+1;j<26;j++) if(count[idx[j]]>count[idx[i]]){int t=idx[i];idx[i]=idx[j];idx[j]=t;}
    // build base map
    char map[26]; for(int i=0;i<26;i++) map[idx[i]] = freq[i];
    // output top 10 with small swaps among top-6
    char pt[8192];
    for(int k=0;k<10;k++){
        char m2[26]; for(int i=0;i<26;i++) m2[i]=map[i];
        if(k>0 && k<6){ // swap k-1 and k among top-6
            int a=idx[k-1], b=idx[k];
            char tmp=m2[a]; m2[a]=m2[b]; m2[b]=tmp;
        }
        decode(ct,pt,m2);
        printf("\nCandidate %d:\n%s", k+1, pt);
    }
    return 0;
}
