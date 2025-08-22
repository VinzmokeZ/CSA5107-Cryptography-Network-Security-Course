
/*
Program 3: Playfair Cipher (5x5, I/J merged)
- Builds key table from keyword
- Encrypts digrams with standard Playfair rules
Sample:
Keyword: CIPHER
Plain: MUST SEE YOU
Output (example run):
Cipher: QZLZ XHKO QZ ...
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void build_table(const char *key, char table[5][5]){
    int used[26]={0}, r=0,c=0; // merge I/J -> treat J as I
    for(int i=0; key[i]; ++i){
        char k=toupper((unsigned char)key[i]);
        if(k<'A'||k>'Z') continue;
        if(k=='J') k='I';
        if(!used[k-'A']){
            used[k-'A']=1;
            table[r][c]=k; if(++c==5){c=0; ++r;}
        }
    }
    for(char ch='A'; ch<='Z'; ++ch){
        char k=ch; if(k=='J') continue; // skip J
        if(!used[k-'A']){
            used[k-'A']=1;
            table[r][c]=k; if(++c==5){c=0; ++r;}
            if(r==5) break;
        }
    }
}

void find_pos(char table[5][5], char ch, int *r, int *c){
    if(ch=='J') ch='I';
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) if(table[i][j]==ch){*r=i;*c=j;return;}
}

int main(){
    char key[256], text[1024], out[2048]={0};
    printf("Keyword: "); fgets(key,sizeof(key),stdin);
    printf("Plaintext: "); fgets(text,sizeof(text),stdin);

    char table[5][5]; build_table(key, table);

    // preprocess: letters only, uppercase, I/J merge, insert X between doubles, pad X
    char prep[2048]={0}; int n=0;
    for(int i=0;text[i];++i){
        char c = toupper((unsigned char)text[i]);
        if(c<'A'||c>'Z') continue;
        if(c=='J') c='I';
        prep[n++]=c;
    }
    // make digrams
    char dig[4096]={0}; int m=0;
    for(int i=0;i<n;){
        char a=prep[i++], b='X';
        if(i<n) b=prep[i];
        if(a==b){ b='X'; } else { i++; }
        dig[m++]=a; dig[m++]=b;
    }
    if(m%2){ dig[m++]='X'; }
    // encrypt
    for(int i=0;i<m;i+=2){
        char a=dig[i], b=dig[i+1]; int r1,c1,r2,c2;
        find_pos(table,a,&r1,&c1);
        find_pos(table,b,&r2,&c2);
        if(r1==r2){ // same row
            out[i]=(char)table[r1][(c1+1)%5];
            out[i+1]=(char)table[r2][(c2+1)%5];
        } else if(c1==c2){ // same col
            out[i]=(char)table[(r1+1)%5][c1];
            out[i+1]=(char)table[(r2+1)%5][c2];
        } else { // rectangle
            out[i]=(char)table[r1][c2];
            out[i+1]=(char)table[r2][c1];
        }
    }
    out[m]=0;
    printf("Cipher: ");
    for(int i=0;i<m;i++){ putchar(out[i]); if(i%2==1) putchar(' '); }
    putchar('\n');
    return 0;
}
