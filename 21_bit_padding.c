
/*
Program 21: Bit Padding (1 followed by zeros) — always add a full block
Padding rule ("10*"):
- Append 0x80 then 0x00 bytes until message length ≡ 0 (mod block_size).
- If the message is already a multiple of block_size, append an entire block
  consisting of 0x80 followed by zeros.

Includes pad() and unpad() functions.

Sample:
Input: "HELLO" (5 bytes), block = 8
Padded length: 8
Data (hex): 48 45 4C 4C 4F 80 00 00
Unpadded: "HELLO"
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void pad_bit_10star(const uint8_t *in, int n, int block, uint8_t *out, int *outn){
    int r = n % block;
    int add = block - r;
    if(add == 0) add = block; // always add one full block
    int i=0;
    for(; i<n; ++i) out[i]=in[i];
    out[i++] = 0x80;
    for(; i<n+add; ++i) out[i]=0x00;
    *outn = n + add;
}

// returns unpadded length, or -1 on error
int unpad_bit_10star(const uint8_t *in, int n, int block){
    if(n==0 || n%block!=0) return -1;
    int i = n - 1;
    // Skip 0x00
    while(i>=0 && in[i]==0x00) i--;
    if(i<0 || in[i]!=0x80) return -1;
    return i; // number of original bytes
}

int main(){
    char msg[256];
    int block=8;
    printf("Enter ASCII message (<=255 chars): ");
    if(!fgets(msg, sizeof(msg), stdin)) return 0;
    int n = (int)strcspn(msg, "\r\n");
    msg[n]=0;

    uint8_t out[512]; int outn=0;
    pad_bit_10star((const uint8_t*)msg, n, block, out, &outn);

    printf("Padded length: %d\nData: ", outn);
    for(int i=0;i<outn;i++) printf("%02X ", out[i]);
    printf("\n");

    int unp = unpad_bit_10star(out, outn, block);
    if(unp<0){ printf("Unpad error\n"); return 0; }

    printf("Unpadded length: %d\nUnpadded text: ", unp);
    for(int i=0;i<unp;i++) putchar(out[i]);
    putchar('\n');

    return 0;
}
