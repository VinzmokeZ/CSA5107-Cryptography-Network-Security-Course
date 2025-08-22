| No. | File Name                            | Description                                     |
| --- | ------------------------------------ | ----------------------------------------------- |
| 01  | 01\_substitution\_cipher.c           | Monoalphabetic substitution (simple mapping).   |
| 02  | 02\_transposition\_cipher.c          | Columnar transposition cipher.                  |
| 03  | 03\_shift\_cipher.c                  | Caesar cipher (shift letters by key).           |
| 04  | 04\_affine\_cipher.c                 | Affine cipher using `ax+b mod 26`.              |
| 05  | 05\_vigenere\_cipher.c               | Vigenère cipher (repeated keyword).             |
| 06  | 06\_playfair\_cipher.c               | Playfair cipher (5×5 matrix digraphs).          |
| 07  | 07\_hill\_cipher.c                   | Hill cipher (2×2 matrix multiplication mod 26). |
| 08  | 08\_rsa\_basic.c                     | RSA keygen, encryption, decryption demo.        |
| 09  | 09\_diffie\_hellman.c                | Diffie–Hellman key exchange.                    |
| 10  | 10\_des\_keygen.c                    | DES key schedule generation.                    |
| 11  | 11\_des\_encrypt.c                   | DES single-block encryption.                    |
| 12  | 12\_des\_decrypt.c                   | DES single-block decryption.                    |
| 13  | 13\_triple\_des.c                    | Triple-DES demo (EDE).                          |
| 14  | 14\_aes\_encrypt.c                   | AES-128 encryption demo.                        |
| 15  | 15\_aes\_decrypt.c                   | AES-128 decryption demo.                        |
| 16  | 16\_hash\_md5.c                      | MD5 hash function demo.                         |
| 17  | 17\_hash\_sha1.c                     | SHA-1 hash demo.                                |
| 18  | 18\_hash\_sha256.c                   | SHA-256 hash demo.                              |
| 19  | 19\_des\_vs\_3des.c                  | Compare DES vs 3DES (speed/security).           |
| 20  | 20\_cbc\_error\_propagation.c        | Demonstrates error propagation in CBC mode.     |
| 21  | 21\_bit\_padding.c                   | Implements 10\* padding scheme.                 |
| 22  | 22\_sdes\_cbc.c                      | Simplified DES (S-DES) in CBC mode.             |
| 23  | 23\_sdes\_ctr.c                      | Simplified DES (S-DES) in CTR mode.             |
| 24  | 24\_rsa\_find\_private.c             | Recover RSA private key d by factoring n.       |
| 25  | 25\_rsa\_gcd\_factor.c               | Factor n using gcd with plaintext.              |
| 26  | 26\_rsa\_n\_leak.c                   | Why leaking (d,n) breaks RSA security.          |
| 27  | 27\_rsa\_perletter\_dictionary.c     | Dictionary attack on per-letter RSA.            |
| 28  | 28\_wrong\_diffie\_variant.c         | Shows why `x^a mod q` is insecure in DH.        |
| 29  | 29\_sha3\_capacity.c                 | SHA-3 capacity lane property demo.              |
| 30  | 30\_cbc\_mac\_trick.c                | CBC-MAC ambiguity attack example.               |
| 31  | 31\_cmac\_subkeys.c                  | CMAC subkey generation demo.                    |
| 32  | 32\_dsa\_k\_reuse\_attack.c          | DSA attack when k is reused (recover x).        |
| 33  | 33\_des.c                            | Full DES cipher implementation.                 |
| 34  | 34\_ctr\_affine256.c                 | CTR mode with affine-256 toy cipher.            |
| 35  | 35\_one\_time\_pad\_vigenere.c       | One-time pad (numeric Vigenère style).          |
| 36  | 36\_affine\_caesar\_analysis.c       | Affine Caesar cipher restrictions + demo.       |
| 37  | 37\_monoalpha\_attack\_simple.c      | Frequency analysis attack (monoalphabetic).     |
| 38  | 38\_hill\_known\_plaintext\_attack.c | Known-plaintext attack on 2×2 Hill cipher.      |
| 39  | 39\_monoalpha\_attack\_bigrams.c     | Bigram scoring monoalphabetic attack.           |
| 40  | 40\_monoalpha\_attack\_hillclimb.c   | Hill-climbing monoalphabetic attack.            |
