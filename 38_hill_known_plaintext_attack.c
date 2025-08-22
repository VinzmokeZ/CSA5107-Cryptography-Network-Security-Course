
/*
Program 38: Recover 2x2 Hill cipher key from two plaintext-ciphertext digram pairs.
Input: P1 P2 C1 C2 (each as two uppercase letters), solve K in C = K*P (mod 26).
*/
#include <stdio.h>
#include <ctype.h>

int mod(int x){ x%=26; if(x<0)x+=26; return x; }
int inv26(int a){ for(int i=1;i<26;i++) if((a*i)%26==1) return i; return -1; }

int main(){
    char p1a,p1b,p2a,p2b,c1a,c1b,c2a,c2b;
    printf("Enter P1 (AB) P2 (CD) C1 (EF) C2 (GH): ");
    if(scanf(" %c%c %c%c %c%c %c%c",&p1a,&p1b,&p2a,&p2b,&c1a,&c1b,&c2a,&c2b)!=8){ printf("Bad input\n"); return 0; }
    int P[4]={p1a-'A',p2a-'A',p1b-'A',p2b-'A'}; // columns P1,P2
    int C[4]={c1a-'A',c2a-'A',c1b-'A',c2b-'A'};
    int det = mod(P[0]*P[3]-P[1]*P[2]);
    int id = inv26(det); if(id==-1){ printf("No inverse; choose different pairs.\n"); return 0; }
    // P^{-1} = (1/det) * [ d -b ; -c a ]
    int Pinv[4]={ mod( P[3]*id), mod(-P[1]*id), mod(-P[2]*id), mod(P[0]*id) };
    // K = C * P^{-1}
    int K[4]={ mod(C[0]*Pinv[0]+C[1]*Pinv[2]), mod(C[0]*Pinv[1]+C[1]*Pinv[3]),
               mod(C[2]*Pinv[0]+C[3]*Pinv[2]), mod(C[2]*Pinv[1]+C[3]*Pinv[3]) };
    printf("Recovered key matrix:\n[%2d %2d]\n[%2d %2d]\n", K[0],K[1],K[2],K[3]);
    return 0;
}
