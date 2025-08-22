
/*
Programs 21/34: Bit-padding demo (1 followed by zeros to block-size)
Shows always adding a padding block even if exact multiple.
*/
#include <stdio.h>
#include <string.h>

void pad(const unsigned char *in, int n, int block, unsigned char *out, int *outn){
    int r = n % block;
    int need = block - r;
    if(need==0) need = block; // always add one block
    int i;
    for(i=0;i<n;i++) out[i]=in[i];
    out[n]=0x80; // 1000 0000
    for(i=n+1;i<n+need;i++) out[i]=0x00;
    *outn = n + need;
}
int main(){
    unsigned char m[] = "HELLO";
    unsigned char out[128]; int outn;
    pad(m, (int)strlen((char*)m), 8, out, &outn);
    printf("Padded length: %d\nData: ", outn);
    for(int i=0;i<outn;i++) printf("%02X ", out[i]);
    printf("\n");
    return 0;
}
