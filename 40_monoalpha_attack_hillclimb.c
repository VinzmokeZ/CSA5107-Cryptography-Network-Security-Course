
/*
Program 40: Monoalphabetic solver using simple hill-climbing with bigram scoring.
Starts from frequency mapping, then randomly swaps and keeps improvements.
This is a lightweight heuristic (not guaranteed) but often improves results.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

const char *english_order = "ETAOINSHRDLUCMWFGYPBVKJXQZ";
const char *common_bigrams[] = {"TH","HE","IN","ER","AN","RE","ED","ON","ES","ST","EN","AT","TE","OR","TI","HI"};
#define NBIGRAMS (sizeof(common_bigrams)/sizeof(common_bigrams[0]))

int score_text(const char *txt){
    int score=0;
    for(int i=0; txt[i+1]; ++i){
        char a=toupper((unsigned char)txt[i]), b=toupper((unsigned char)txt[i+1]);
        if(a<'A'||a>'Z'||b<'A'||b>'Z') continue;
        char big[3] = {a,b,0};
        for(int j=0;j<NBIGRAMS;j++) if(strcmp(big, common_bigrams[j])==0) score+=3;
        if(a==' '||b==' ') score+=1;
    }
    return score;
}

void decode_with_map(const char *ct, char *out, const char map[26]){
    for(int i=0; ct[i]; ++i){
        char c=ct[i];
        if(isalpha((unsigned char)c)){
            int idx = toupper((unsigned char)c)-'A';
            char m = map[idx];
            out[i] = islower((unsigned char)c)? tolower(m) : m;
        } else out[i]=c;
    }
    out[strlen(ct)]=0;
}

int main(){
    srand((unsigned)time(NULL));
    char ct[8192];
    printf("Enter ciphertext (single line):\n");
    if(!fgets(ct,sizeof(ct),stdin)) return 0;

    int freq[26]={0};
    for(int i=0; ct[i]; ++i) if(isalpha((unsigned char)ct[i])) freq[toupper((unsigned char)ct[i])-'A']++;

    // initial mapping by frequency
    int idx[26]; for(int i=0;i<26;i++) idx[i]=i;
    for(int i=0;i<26;i++) for(int j=i+1;j<26;j++) if(freq[idx[j]]>freq[idx[i]]){ int t=idx[i]; idx[i]=idx[j]; idx[j]=t; }
    char map[26];
    for(int i=0;i<26;i++) map[idx[i]] = english_order[i];

    char best_map[26]; memcpy(best_map,map,26);
    char best_dec[8192]; decode_with_map(ct,best_dec,best_map);
    int best_score = score_text(best_dec);

    // hill-climb: random swaps
    for(int iter=0; iter<5000; iter++){
        // propose swap of two plaintext letters (i,j are ciphertext indices to swap mapping values)
        int a = rand()%26, b = rand()%26; if(a==b) continue;
        // swap mapping values for ciphertext letters a and b
        char tmp = map[a]; map[a]=map[b]; map[b]=tmp;
        char dec[8192]; decode_with_map(ct,dec,map);
        int s = score_text(dec);
        if(s > best_score){
            best_score = s;
            memcpy(best_map,map,26);
            strcpy(best_dec,dec);
        } else {
            // revert swap
            tmp = map[a]; map[a]=map[b]; map[b]=tmp;
        }
    }

    printf("Best score=%d\nDecoded candidate:\n%s\n", best_score, best_dec);
    return 0;
}
