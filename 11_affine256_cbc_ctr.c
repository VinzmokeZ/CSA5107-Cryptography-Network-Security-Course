
/*
Programs 19,22,23: CBC and CTR modes using Affine cipher mod 256 as block cipher
Block cipher: E_a,b(x) = (a*x + b) mod 256, with a odd (invertible mod 256)
Demonstrates CBC encryption/decryption and CTR mode.
*/
#include <stdio.h>
#include <stdint.h>

uint8_t inv256(uint8_t a){
    // a must be odd. Brute-force inverse mod 256
    for(int i=1;i<256;i++) if(((int)a*i)%256==1) return (uint8_t)i;
    return 0;
}
uint8_t enc_byte(uint8_t x, uint8_t a, uint8_t b){ return (uint8_t)((a*x + b) & 0xFF); }
uint8_t dec_byte(uint8_t y, uint8_t a, uint8_t b){ uint8_t ia=inv256(a); return (uint8_t)((ia*(y - b)) & 0xFF); }

void cbc_encrypt(const uint8_t *pt, uint8_t *ct, int n, uint8_t iv, uint8_t a, uint8_t b){
    uint8_t prev = iv;
    for(int i=0;i<n;i++){
        uint8_t x = pt[i]^prev;
        ct[i] = enc_byte(x,a,b);
        prev = ct[i];
    }
}
void cbc_decrypt(const uint8_t *ct, uint8_t *pt, int n, uint8_t iv, uint8_t a, uint8_t b){
    uint8_t prev = iv;
    for(int i=0;i<n;i++){
        uint8_t x = dec_byte(ct[i],a,b);
        pt[i] = x ^ prev;
        prev = ct[i];
    }
}

void ctr_process(const uint8_t *in, uint8_t *out, int n, uint8_t nonce, uint8_t a, uint8_t b){
    for(int i=0;i<n;i++){
        uint8_t ks = enc_byte((uint8_t)(nonce+i),a,b);
        out[i] = in[i]^ks;
    }
}

int main(){
    uint8_t pt[6]={0x00,0x01,0x02,0x03,0x04,0x05};
    uint8_t a=5,b=77, iv=0xAA, nonce=0x00;
    uint8_t ct[6], dec[6], ctr_ct[6], ctr_dec[6];

    cbc_encrypt(pt,ct,6,iv,a,b);
    cbc_decrypt(ct,dec,6,iv,a,b);
    ctr_process(pt,ctr_ct,6,nonce,a,b);
    ctr_process(ctr_ct,ctr_dec,6,nonce,a,b);

    printf("CBC enc: "); for(int i=0;i<6;i++) printf("%02X ", ct[i]); printf("\n");
    printf("CBC dec: "); for(int i=0;i<6;i++) printf("%02X ", dec[i]); printf("\n");
    printf("CTR enc: "); for(int i=0;i<6;i++) printf("%02X ", ctr_ct[i]); printf("\n");
    printf("CTR dec: "); for(int i=0;i<6;i++) printf("%02X ", ctr_dec[i]); printf("\n");
    return 0;
}
