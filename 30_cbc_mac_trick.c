
/*
Program 30: CBC-MAC of one-block message X gives T=MAC(K,X).
Then MAC(K, X || (X xor T)) == T again (ambiguous extension). We demo with a toy block cipher.
*/
#include <stdio.h>
#include <stdint.h>

uint32_t toyE(uint32_t x){ return x ^ 0xA5A5A5A5u; } // not secure; demo only
uint32_t cbc_mac(const uint32_t *m, int blocks, uint32_t K){
    uint32_t iv=0, c=iv;
    for(int i=0;i<blocks;i++){ uint32_t x = m[i] ^ c ^ K; c = toyE(x); }
    return c;
}
int main(){
    uint32_t X=0x11223344, K=0x01020304;
    uint32_t T = cbc_mac(&X,1,K);
    uint32_t Y[2]; Y[0]=X; Y[1]=X ^ T;
    uint32_t T2 = cbc_mac(Y,2,K);
    printf("T = %08X, T2 = %08X (equal)\n", T, T2);
    return 0;
}
