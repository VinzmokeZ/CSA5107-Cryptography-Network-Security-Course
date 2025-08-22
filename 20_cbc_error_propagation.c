
/*
Program 20: Error Propagation in CBC Mode (byte-sized toy cipher)
Block cipher (toy, NOT secure): E(x) = x XOR 0x5A, D(x) = x XOR 0x5A
CBC Encrypt:  C[i] = E( P[i] XOR C[i-1] ), C[-1] = IV
CBC Decrypt:  P[i] = D( C[i] ) XOR C[i-1], C[-1] = IV

Demo:
- Encrypt 4 bytes.
- Flip 1 bit in C[0].
- Decrypt the corrupted ciphertext.
Observation:
- P[0] becomes garbage (all bits affected by wrong decryption input).
- P[1] is identical to original except the SINGLE flipped bit position.
- P[2], P[3], ... unaffected.

Sample Output (example):
CT: F0 A9 F3 A2
Flipped C0 bit0 -> CT': F1 A9 F3 A2
Recovered PT': 01 03 03 04   (only first two blocks affected)
*/
#include <stdio.h>
#include <stdint.h>

static inline uint8_t E(uint8_t x){ return (uint8_t)(x ^ 0x5A); }
static inline uint8_t D(uint8_t y){ return (uint8_t)(y ^ 0x5A); }

void cbc_encrypt(const uint8_t *pt, uint8_t *ct, int n, uint8_t iv){
    uint8_t prev = iv;
    for(int i=0;i<n;i++){
        uint8_t x = (uint8_t)(pt[i] ^ prev);
        ct[i] = E(x);
        prev = ct[i];
    }
}
void cbc_decrypt(const uint8_t *ct, uint8_t *pt, int n, uint8_t iv){
    uint8_t prev = iv;
    for(int i=0;i<n;i++){
        uint8_t x = D(ct[i]);
        pt[i] = (uint8_t)(x ^ prev);
        prev = ct[i];
    }
}

int main(){
    uint8_t pt[4] = {0x01,0x02,0x03,0x04};
    uint8_t iv = 0xAA;
    uint8_t ct[4], ct_err[4], rec[4];

    cbc_encrypt(pt, ct, 4, iv);

    // Show ciphertext
    printf("Original PT: "); for(int i=0;i<4;i++) printf("%02X ", pt[i]); printf("\n");
    printf("Ciphertext : "); for(int i=0;i<4;i++) printf("%02X ", ct[i]); printf("\n");

    // Flip bit 0 of C[0]
    for(int i=0;i<4;i++) ct_err[i]=ct[i];
    ct_err[0] ^= 0x01;

    // Decrypt corrupted ciphertext
    cbc_decrypt(ct_err, rec, 4, iv);

    printf("Corrupted CT: "); for(int i=0;i<4;i++) printf("%02X ", ct_err[i]); printf("\n");
    printf("Recovered PT: "); for(int i=0;i<4;i++) printf("%02X ", rec[i]); printf("\n");

    puts("\nNote: Only P[0] (garbage) and P[1] (single-bit flip) are affected; later blocks are intact.");
    return 0;
}
