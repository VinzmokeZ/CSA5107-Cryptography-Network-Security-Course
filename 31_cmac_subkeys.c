
/*
Program 31: CMAC subkey generation notes
- For 64-bit block ciphers, Rb = 0x1B.
- For 128-bit block ciphers (AES), Rb = 0x87.
Left shift L to get K1; if MSB(L) was 1 before shift, XOR Rb; K2 is derived same from K1.
We demonstrate on a dummy 128-bit L.
*/
#include <stdio.h>
#include <stdint.h>

void leftshift_128(const uint8_t *in, uint8_t *out){
    uint8_t carry=0;
    for(int i=15;i>=0;i--){
        uint8_t ncarry = (in[i]>>7)&1;
        out[i] = (uint8_t)((in[i]<<1) | carry);
        carry = ncarry;
    }
}

void xor128(uint8_t *x, const uint8_t *y){
    for(int i=0;i<16;i++) x[i]^=y[i];
}

int main(){
    uint8_t L[16]={0}; L[15]=0x6B; // example
    uint8_t K1[16], K2[16];
    leftshift_128(L,K1);
    if((L[0]>>7)&1){ uint8_t Rb[16]={0}; Rb[15]=0x87; xor128(K1,Rb); }
    for(int i=0;i<16;i++) K2[i]=K1[i];
    leftshift_128(K2,K2);
    if((K1[0]>>7)&1){ uint8_t Rb[16]={0}; Rb[15]=0x87; xor128(K2,Rb); }
    printf("K1: "); for(int i=0;i<16;i++) printf("%02X", K1[i]); printf("\n");
    printf("K2: "); for(int i=0;i<16;i++) printf("%02X", K2[i]); printf("\n");
    return 0;
}
