#include "AES_crypto.h"

int main()
{
	byte plaintext[16] = { 0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34 };
	byte ciphertext[16] = { 0x39,0x25,0x84,0x1d,0x02,0xdc,0x09,0xfb,0xdc,0x11,0x85,0x97,0x19,0x6a,0x0b,0x32 };
	byte word[176] = { 0, };
	byte key[16] = { 0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c };
	byte out[16] = { 0, };
	int i = 0;
	printf("평문:");
	for (i; i < 16; i++)
	{
		printf("%02x ", plaintext[i]);
	}
	printf("\n키:");
	i = 0;
	for (i; i < 16; i++)
	{
		printf("%02x ", key[i]);
	}
	printf("\n--->>>암호화");
	printf("\n암호문:");
	Cipher(plaintext, key, word, out);
	printf("\n키:");
	i = 0;
	for (i; i < 16; i++)
	{
		printf("%02x ", key[i]);
	}
	printf("\n--->>>복호화");
	printf("\n");
	printf("평문:");
	Decipher(ciphertext, key, word, out);
}