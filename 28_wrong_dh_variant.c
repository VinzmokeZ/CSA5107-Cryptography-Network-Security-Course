
/*
Program 28: What if participants send x^a (mod q) instead of a^x?
This breaks the Diffie-Hellman structure; the shared key cannot be computed symmetrically as g^(ab).
We print a short explanation and give a safe method (classic DH).
*/
#include <stdio.h>
int main(){
    printf("Sending x^a mod q instead of g^x leaks structure and doesn't yield a shared g^(ab).\n");
    printf("Use standard DH: choose secret a,b; exchange A=g^a mod q, B=g^b mod q; shared = B^a = A^b = g^(ab).\n");
    printf("Eve cannot derive the key without solving discrete log.\n");
    return 0;
}
