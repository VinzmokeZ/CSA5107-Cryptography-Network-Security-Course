
/*
Program 20: Error propagation in CBC
We simulate flipping a bit in C1 and show it corrupts P1 and P2 only.
*/
#include <stdio.h>
#include <stdint.h>

uint8_t enc(uint8_t x){ return (uint8_t)(x ^ 0x5A); } // toy cipher
uint8_t dec(uint8_t y){ return (uint8_t)(y ^ 0x5A); }

void cbc_enc(const uint8_t *pt, uint8_t *ct, int n, uint8_t iv){
    uint8_t prev=iv;
    for(int i=0;i<n;i++){ uint8_t x=pt[i]^prev; ct[i]=enc(x); prev=ct[i]; }
}
void cbc_dec(const uint8_t *ct, uint8_t *pt, int n, uint8_t iv){
    uint8_t prev=iv;
    for(int i=0;i<n;i++){ uint8_t x=dec(ct[i]); pt[i]=x^prev; prev=ct[i]; }
}

int main(){
    uint8_t pt[4]={1,2,3,4}, ct[4], rec[4], iv=0xAA;
    cbc_enc(pt,ct,4,iv);
    // introduce 1-bit error in C1 (index 0)
    ct[0] ^= 0x01;
    cbc_dec(ct,rec,4,iv);
    printf("Recovered: "); for(int i=0;i<4;i++) printf("%02X ", rec[i]); printf("\n");
    return 0;
}
