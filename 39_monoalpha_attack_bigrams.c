
/*
Program 39: Monoalphabetic substitution attack using bigram scoring.
- Build frequency mapping; take top N ciphertext letters (N=6) and try all permutations
  mapping them to top English letters "ETAOIN". For each candidate, score by counting
  common English bigrams in the decoded text. Print top 10 candidates.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

const char *english_order = "ETAOINSHRDLUCMWFGYPBVKJXQZ";
const char *common_bigrams[] = {"TH","HE","IN","ER","AN","RE","ED","ON","ES","ST","EN","AT","TE","OR","TI","HI"};
#define NBIGRAMS (sizeof(common_bigrams)/sizeof(common_bigrams[0]))

int cmp_desc(const void *a,const void *b){
    int ia = *(int*)a; int ib = *(int*)b; return ib - ia;
}

int score_text(const char *txt){
    int score=0;
    for(int i=0; txt[i+1]; ++i){
        char a=toupper((unsigned char)txt[i]), b=toupper((unsigned char)txt[i+1]);
        if(a<'A'||a>'Z'||b<'A'||b>'Z') continue;
        char big[3] = {a,b,0};
        for(int j=0;j<NBIGRAMS;j++) if(strcmp(big, common_bigrams[j])==0) score+=3;
        // reward vowels and spaces lightly
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

void permute_rec(int *arr,int l,int r, void (*visit)(int*,int)){
    if(l==r){ visit(arr, r+1); return; }
    for(int i=l;i<=r;i++){ int t=arr[l]; arr[l]=arr[i]; arr[i]=t; permute_rec(arr,l+1,r,visit); t=arr[l]; arr[l]=t; }
}

int main(){
    char ct[8192];
    printf("Enter ciphertext (single line):\n");
    if(!fgets(ct,sizeof(ct),stdin)) return 0;

    int freq[26]={0};
    for(int i=0; ct[i]; ++i) if(isalpha((unsigned char)ct[i])) freq[toupper((unsigned char)ct[i])-'A']++;

    // get ciphertext letters sorted by freq
    int idx[26]; for(int i=0;i<26;i++) idx[i]=i;
    for(int i=0;i<26;i++) for(int j=i+1;j<26;j++) if(freq[idx[j]]>freq[idx[i]]){ int t=idx[i]; idx[i]=idx[j]; idx[j]=t; }

    int N=6; // permute top N
    int topN[6]; for(int i=0;i<N;i++) topN[i]=idx[i];
    int perm[6]; for(int i=0;i<N;i++) perm[i]=i; // 0..N-1 permutations of english_order's top N letters

    typedef struct { int score; char text[8192]; } Cand;
    Cand best[20]; for(int i=0;i<20;i++){ best[i].score= -100000; best[i].text[0]=0; }

    // visitor will construct mapping using current permutation
    void visit_perm(int *p,int len){
        char map[26];
        // start with frequency mapping as default
        for(int i=0;i<26;i++) map[idx[i]] = english_order[i];
        // override topN mapping by permutation to english_order[0..N-1]
        for(int i=0;i<N;i++){
            map[topN[i]] = english_order[p[i]];
        }
        char dec[8192];
        decode_with_map(ct, dec, map);
        int s = score_text(dec);
        // store in best if high
        for(int k=0;k<20;k++) if(s > best[k].score){
            for(int q=19;q>k;q--) best[q]=best[q-1];
            best[k].score = s; strcpy(best[k].text, dec);
            break;
        }
    }

    // generate all permutations of 0..N-1 and call visitor
    permute_rec(perm,0,N-1, visit_perm);

    printf("Top candidates:\n");
    for(int i=0;i<10;i++){
        if(best[i].score < -5000) break;
        printf("Rank %d (score=%d):\n%s\n\n", i+1, best[i].score, best[i].text);
    }
    return 0;
}
