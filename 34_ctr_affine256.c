
/*
Program 34: Counter (CTR) mode using affine byte cipher mod 256.
Block cipher: E(x) = (a*x + b) mod 256 (a must be odd to be invertible)
Demo uses default a=5,b=77, nonce=0
*/
#include <stdio.h>
#include <stdint.h>

uint8_t inv256(uint8_t a){
    for(int i=1;i<256;i++) if(((int)a*i)%256==1) return (uint8_t)i;
    return 0;
}
uint8_t enc_byte(uint8_t x, uint8_t a, uint8_t b){ return (uint8_t)((a*x + b) & 0xFF); }
uint8_t dec_byte(uint8_t y, uint8_t a, uint8_t b){ uint8_t ia=inv256(a); return (uint8_t)((ia*(y - b)) & 0xFF); }

void ctr_process(const uint8_t *in, uint8_t *out, int n, uint8_t nonce, uint8_t a, uint8_t b){
    for(int i=0;i<n;i++){
        uint8_t ks = enc_byte((uint8_t)(nonce + i), a, b);
        out[i] = in[i] ^ ks;
    }
}

int main(){
    uint8_t a=5,b=77, nonce=0x00;
    uint8_t pt[6] = {0x00,0x01,0x00,0x02,0x00,0x04};
    uint8_t ct[6], rec[6];
    ctr_process(pt, ct, 6, nonce, a, b);
    ctr_process(ct, rec, 6, nonce, a, b);
    printf("PT : "); for(int i=0;i<6;i++) printf("%02X ", pt[i]); printf("\n");
    printf("CT : "); for(int i=0;i<6;i++) printf("%02X ", ct[i]); printf("\n");
    printf("REC: "); for(int i=0;i<6;i++) printf("%02X ", rec[i]); printf("\n");
    return 0;
}
