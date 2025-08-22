
/*
Program 26: If Bob leaks his RSA private key d, is it safe to keep n and generate a new (e,d)?
Answer: NO. Once d leaks, an attacker can compute phi(n) from e,d (since ed ≡ 1 mod phi(n)) or simply decrypt.
They can also factor n using gcd operations on ed-1. So Bob must generate a NEW modulus n (new p,q).
This program prints the explanation.
*/
#include <stdio.h>
int main(){
    printf("Unsafe: if d leaks, you must change n (generate new p,q). Replacing only e,d is not safe.\n");
    return 0;
}
