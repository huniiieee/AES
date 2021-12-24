#ifndef _AES_CRYPTO_H_
#define _AES_CRYPTO_H_
#include "type.h"

void Subbytes(byte* address);

void invSubbytes(byte* address);

void Shiftrows(byte* address);

void invShiftrows(byte* address);

void Mixcolumns(byte* address);

void invMixcolumns(byte* address);

void Addroundkey(byte* address, byte* word, int* a);

void Cipher(byte* state, byte* key, byte* word, byte* out);

void Decipher(byte* state, byte* key, byte* word, byte* out);



#endif
