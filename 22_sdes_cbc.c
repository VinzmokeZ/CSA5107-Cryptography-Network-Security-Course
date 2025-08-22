
/*
Program 22: Encrypt/Decrypt in CBC mode using S-DES
Test vector mentioned:
 IV (binary): 1010 1010
 PT (binary): 0000 0001 0010 0011  (i.e., 4 bytes: 0x00 0x01 0x02 0x03)
 Key (binary): 01111 11101  (10-bit S-DES key -> here we take 0b0111111101 = 0x1FD? No, S-DES uses 10 bits.)
 For simplicity, we take key bits as 0b0111111101 (decimal 0x1FD & 0x3FF).

Note: This is a compact S-DES with standard steps: P10, LS-1/2, P8, IP, fK with S-boxes, SW, IP^-1.
*/
#include <stdio.h>
#include <stdint.h>

// Bit helpers
static inline int getb(unsigned x,int pos){ return (x>>pos)&1; }
static inline unsigned setb(unsigned x,int pos,int v){ return v? (x|(1u<<pos)) : (x&~(1u<<pos)); }

unsigned permute(unsigned x, const int *p, int n){
    unsigned y=0;
    for(int i=0;i<n;i++) y = setb(y, n-1-i, getb(x, p[i]));
    return y;
}

// S-DES tables
const int P10[10]={2,4,1,6,3,9,0,8,7,5};
const int P8[8]={5,2,6,3,7,4,9,8};
const int P4[4]={1,3,2,0};
const int IP[8]={1,5,2,0,3,7,4,6};
const int IP_1[8]={3,0,2,4,6,1,7,5};
const int EP[8]={3,0,1,2,1,2,3,0};

int S0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
int S1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}};

// left shift (circular) for 5-bit half
unsigned ls(unsigned x,int n){
    return ((x<<n)|(x>>(5-n))) & 0x1F;
}

void keygen(unsigned key10, unsigned *K1, unsigned *K2){
    unsigned p10 = permute(key10, P10, 10);
    unsigned L = (p10>>5)&0x1F, R = p10&0x1F;
    L = ls(L,1); R = ls(R,1);
    unsigned k1in = (L<<5)|R;
    *K1 = permute(k1in, P8, 10);
    L = ls(L,2); R = ls(R,2);
    unsigned k2in = (L<<5)|R;
    *K2 = permute(k2in, P8, 10);
}

unsigned fk(unsigned in8, unsigned subk){
    unsigned L=(in8>>4)&0xF, R=in8&0xF;
    unsigned exp = permute(R, EP, 8);
    unsigned x = exp ^ subk;
    int r0 = ((getb(x,7)<<1)|getb(x,4));
    int c0 = ((getb(x,6)<<1)|getb(x,5));
    int r1 = ((getb(x,3)<<1)|getb(x,0));
    int c1 = ((getb(x,2)<<1)|getb(x,1));
    int s0 = S0[r0][c0];
    int s1 = S1[r1][c1];
    unsigned s = ((s0&0x3)<<2)|(s1&0x3);
    unsigned p4 = permute(s, P4, 4);
    unsigned outL = L ^ p4;
    return ((outL&0xF)<<4) | (R&0xF);
}

unsigned sdes_enc8(unsigned b, unsigned K1, unsigned K2){
    unsigned x = permute(b, IP, 8);
    x = fk(x,K1);
    // swap halves
    x = ((x&0xF)<<4)|((x>>4)&0xF);
    x = fk(x,K2);
    x = permute(x, IP_1, 8);
    return x & 0xFF;
}

unsigned sdes_dec8(unsigned b, unsigned K1, unsigned K2){
    // decryption uses subkeys reversed
    unsigned x = permute(b, IP, 8);
    x = fk(x,K2);
    x = ((x&0xF)<<4)|((x>>4)&0xF);
    x = fk(x,K1);
    x = permute(x, IP_1, 8);
    return x & 0xFF;
}

void cbc_enc(const unsigned char *pt, unsigned char *ct, int n, unsigned char iv, unsigned K1, unsigned K2){
    unsigned char prev=iv;
    for(int i=0;i<n;i++){
        unsigned char x = pt[i]^prev;
        ct[i] = (unsigned char)sdes_enc8(x,K1,K2);
        prev = ct[i];
    }
}
void cbc_dec(const unsigned char *ct, unsigned char *pt, int n, unsigned char iv, unsigned K1, unsigned K2){
    unsigned char prev=iv;
    for(int i=0;i<n;i++){
        unsigned char x = (unsigned char)sdes_dec8(ct[i],K1,K2);
        pt[i] = x ^ prev;
        prev = ct[i];
    }
}

int main(){
    unsigned key10 = 0b0111111101; // example 10-bit key
    unsigned K1,K2; keygen(key10,&K1,&K2);
    unsigned char iv = 0b10101010;
    unsigned char pt[4] = {0x00,0x01,0x02,0x03};
    unsigned char ct[4], rec[4];
    cbc_enc(pt,ct,4,iv,K1,K2);
    cbc_dec(ct,rec,4,iv,K1,K2);
    printf("CT: "); for(int i=0;i<4;i++) printf("%02X ", ct[i]); printf("\n");
    printf("PT: "); for(int i=0;i<4;i++) printf("%02X ", rec[i]); printf("\n");
    return 0;
}
