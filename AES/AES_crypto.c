#include "AES_crypto.h"
#include "table.h"

void Subbytes(byte* address)
{
	int i = 0;
	for (i; i < 16; i++)
		address[i] = SBox[address[i]];
}

void invSubbytes(byte* address)
{
	int i = 0;
	for (i; i < 16; i++)
		address[i] = inv_sbox[address[i]];
}

void Shiftrows(byte* address)
{
	byte Shift[16] = { 0, };
	int i = 0;
	for (i; i < 16; i++)
	{
		Shift[i] = address[i];
	}
	i = 0;
	for (i; i < 16; i++)
	{

		if (i % 4 == 1)
			address[i] = Shift[(i + 4) % 16];
		if (i % 4 == 2)
			address[i] = Shift[(i + 8) % 16];
		if (i % 4 == 3)
			address[i] = Shift[(i + 12) % 16];
	}
}

void invShiftrows(byte* address)
{
	byte Shift[16] = { 0, };
	int i = 0;
	for (i; i < 16; i++)
		Shift[i] = address[i];
	i = 0;
	for (i; i < 16; i++)
	{
		if (i % 4 == 1)
			address[i] = Shift[(i + 12) % 16];
		if (i % 4 == 2)
			address[i] = Shift[(i + 8) % 16];
		if (i % 4 == 3)
			address[i] = Shift[(i + 4) % 16];
	}
}

void Mixcolumns(byte* address)
{
	byte address_[16] = { 0, };
	int j = 0;
	for (j; j < 16; j++)
	{
		address_[j] = address[j];
	}
	byte mix[16] = { 0, };

	int k = 0;
	for (k; k < 16; k++)
	{
		if (((address[k]) >> 7) == 1)
			mix[k] = 0x1b;
		else
			mix[k] = 0x00;
		//printf("%02x", mix[k]);
	}

	int i = 0;
	for (i; i < 16; i++)
	{
		if (i % 4 == 0)
			address[i] = ((address_[i]) << 1) ^ ((address_[i + 1]) << 1) ^ (address_[i + 1]) ^ (address_[i + 2]) ^ (address_[i + 3]) ^ (mix[i]) ^ (mix[i + 1]);
		if (i % 4 == 1)
			address[i] = (address_[i - 1]) ^ ((address_[i]) << 1) ^ ((address_[i + 1]) << 1) ^ (address_[i + 1]) ^ (address_[i + 2]) ^ (mix[i]) ^ (mix[i + 1]);
		if (i % 4 == 2)
			address[i] = (address_[i - 2]) ^ (address_[i - 1]) ^ ((address_[i]) << 1) ^ ((address_[i + 1]) << 1) ^ (address_[i + 1]) ^ (mix[i]) ^ (mix[i + 1]);
		if (i % 4 == 3)
			address[i] = ((address_[i - 3]) << 1) ^ (address_[i - 3]) ^ (address_[i - 2]) ^ (address_[i - 1]) ^ ((address_[i]) << 1) ^ (mix[i - 3]) ^ (mix[i]);
	}
}

void invMixcolumns(byte* address)
{
	byte state[16] = { 0, };
	int i = 0;
	for (i; i < 16; i++)
	{
		state[i] = address[i];
	}
	byte mix_2[16] = { 0, }; //  <<1의 경우
	byte mix_4[16] = { 0, }; //  <<2의 경우
	byte mix_8[16] = { 0, }; //  <<3의 경우
	i = 0;
	for (i; i < 16; i++)
	{
		if (((state[i]) >> 5) == 7)
		{
			mix_2[i] = 0x1b;
			mix_4[i] = 0x2d;
			mix_8[i] = 0x41;
		}
		if (((state[i]) >> 5) == 6)
		{
			mix_2[i] = 0x1b;
			mix_4[i] = 0x2d;
			mix_8[i] = 0x5a;
		}
		if (((state[i]) >> 5) == 5)
		{
			mix_2[i] = 0x1b;
			mix_4[i] = 0x36;
			mix_8[i] = 0x77;
		}
		if (((state[i]) >> 5) == 4)
		{
			mix_2[i] = 0x1b;
			mix_4[i] = 0x36;
			mix_8[i] = 0x6c;
		}
		if (((state[i]) >> 5) == 3)
		{
			mix_2[i] = 0;
			mix_4[i] = 0x1b;
			mix_8[i] = 0x2d;
		}
		if (((state[i]) >> 5) == 2)
		{
			mix_2[i] = 0;
			mix_4[i] = 0x1b;
			mix_8[i] = 0x36;
		}
		if (((state[i]) >> 5) == 1)
		{
			mix_2[i] = 0;
			mix_4[i] = 0;
			mix_8[i] = 0x1b;
		}
		if (((state[i]) >> 5) == 0)
		{
			mix_2[i] = 0;
			mix_4[i] = 0;
			mix_8[i] = 0;
		}
	}

	i = 0;
	for (i; i < 16; i++)
	{
		if (i % 4 == 0)
			address[i] = (state[i] << 3) ^ mix_8[i] ^ (state[i] << 2) ^ mix_4[i] ^ (state[i] << 1) ^ mix_2[i] ^ (state[i + 1] << 3) ^ mix_8[i + 1] ^ (state[i + 1] << 1) ^ mix_2[i + 1] ^ state[i + 1] ^ (state[i + 2] << 3) ^ mix_8[i + 2] ^ (state[i + 2] << 2) ^ mix_4[i + 2] ^ state[i + 2] ^ (state[i + 3] << 3) ^ mix_8[i + 3] ^ state[i + 3];
		if (i % 4 == 1)
			address[i] = (state[i - 1] << 3) ^ mix_8[i - 1] ^ state[i - 1] ^ (state[i] << 3) ^ mix_8[i] ^ (state[i] << 2) ^ mix_4[i] ^ (state[i] << 1) ^ mix_2[i] ^ (state[i + 1] << 3) ^ mix_8[i + 1] ^ (state[i + 1] << 1) ^ mix_2[i + 1] ^ state[i + 1] ^ (state[i + 2] << 3) ^ mix_8[i + 2] ^ (state[i + 2] << 2) ^ mix_4[i + 2] ^ state[i + 2];
		if (i % 4 == 2)
			address[i] = (state[i - 2] << 3) ^ mix_8[i - 2] ^ (state[i - 2] << 2) ^ mix_4[i - 2] ^ state[i - 2] ^ (state[i - 1] << 3) ^ mix_8[i - 1] ^ state[i - 1] ^ (state[i] << 3) ^ mix_8[i] ^ (state[i] << 2) ^ mix_4[i] ^ (state[i] << 1) ^ mix_2[i] ^ (state[i + 1] << 3) ^ mix_8[i + 1] ^ (state[i + 1] << 1) ^ mix_2[i + 1] ^ state[i + 1];
		if (i % 4 == 3)
			address[i] = (state[i - 3] << 3) ^ mix_8[i - 3] ^ (state[i - 3] << 1) ^ mix_2[i - 3] ^ state[i - 3] ^ (state[i - 2] << 3) ^ mix_8[i - 2] ^ (state[i - 2] << 2) ^ mix_4[i - 2] ^ state[i - 2] ^ (state[i - 1] << 3) ^ mix_8[i - 1] ^ state[i - 1] ^ (state[i] << 3) ^ mix_8[i] ^ (state[i] << 2) ^ mix_4[i] ^ (state[i] << 1) ^ mix_2[i];
	}

}

void Addroundkey(byte* address, byte* word, int* a)
{
	int i = 0;
	for (i; i < 16; i++)
	{
		address[i] = address[i] ^ word[i + (*a)];
	}
}


void Keyschedule(byte* address, byte* word)
{
	byte constant[10] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36 };
	int i = 0;
	for (i; i < 16; i++)
	{
		word[i] = address[i];
	}
	for (i; i < 176; i++)
	{

		if (i % 16 == 0)
			word[i] = SBox[word[i - 3]] ^ constant[(i - 16) / 16] ^ word[i - 16];
		if ((i % 16) == 1 || (i % 16) == 2)
			word[i] = SBox[word[i - 3]] ^ word[i - 16];
		if (i % 16 == 3)
			word[i] = SBox[word[i - 7]] ^ word[i - 16];
		if ((i % 16) > 3)
			word[i] = word[i - 4] ^ word[i - 16];

	}
}

void Cipher(byte* state, byte* key, byte* word, byte* out)
{
	Keyschedule(key, word);
	int i = 0;
	int x = 0;
	Addroundkey(state, word, &x);
	i = 0;
	x = 16;
	for (i; i < 9; i++)
	{
		Subbytes(state);
		Shiftrows(state);
		Mixcolumns(state);
		Addroundkey(state, word, &x);
		x = x + 16;

	}
	//for문을 다 돌면 x는 160이 됨
	Subbytes(state);
	Shiftrows(state);
	Addroundkey(state, word, &x);
	i = 0;
	for (i; i < 16; i++)
	{
		out[i] = state[i];
		printf("%02x ", out[i]);
	}

}

void Decipher(byte* state, byte* key, byte* word, byte* out)
{
	Keyschedule(key, word);
	int i = 0;
	int x = 160; //1차원 배열 키 스케줄 때문에
	Addroundkey(state, word, &x);
	i = 0;
	for (i; i < 9; i++)
	{
		x = x - 16;//word 낮춰줘야함
		invShiftrows(state);
		invSubbytes(state);
		Addroundkey(state, word, &x);
		invMixcolumns(state);
	}
	x = x - 16;
	invShiftrows(state);
	invSubbytes(state);
	Addroundkey(state, word, &x);
	i = 0;
	for (i; i < 16; i++)
	{
		out[i] = state[i];
		printf("%02x ", out[i]);
	}
}