
/*
Program 19: CBC mode with a cipher stronger than DES (3DES) and choice Q&A.
This file prints the reasoning:
- For SECURITY: choose 3DES over DES (larger effective key, not vulnerable to brute-force like DES).
- For PERFORMANCE: DES is faster than 3DES, but insecure in 2025; AES is recommended for both security and performance.
We also reference separate demo files:
  - 11_affine256_cbc_ctr.c shows CBC/CTR mechanics with a toy invertible cipher.
  - For a production setup, use a crypto library (e.g., OpenSSL) for 3DES/AES.
*/
#include <stdio.h>
int main(){
    printf("Security choice: 3DES (over DES).\n");
    printf("Performance choice: DES is faster but insecure; prefer AES for both security and speed.\n");
    printf("See 11_affine256_cbc_ctr.c for CBC mechanics demo.\n");
    return 0;
}
