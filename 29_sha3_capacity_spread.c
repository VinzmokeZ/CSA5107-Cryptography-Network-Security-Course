
/*
Program 29: SHA-3 option with block size 1024 bits.
Keccak-f[1600] has 1600-bit state = 25 lanes * 64 bits. With rate r=1024, capacity c=576 -> 9 capacity lanes.
If we ignore permutation (as instructed) and only XOR message block into rate lanes, the original capacity lanes
remain zero forever. Therefore they will NEVER all become nonzero.
This program prints that conclusion.
*/
#include <stdio.h>
int main(){
    printf("Ignoring permutation, capacity lanes (9 lanes) start as zero and stay zero.\n");
    printf("=> Time until all have at least one nonzero bit: NEVER (infinite).\n");
    return 0;
}
