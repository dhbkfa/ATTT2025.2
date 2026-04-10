#include "KeyExpansion.h"
#include <iostream>

#include "../SubBytes_Code/SubBytes.h"

using namespace std;

const uint32_t Rcon[] = {
    0x00000000, // so 0 (khong dung)
    0x01000000, // j = 1
    0x02000000, // j = 2
    0x04000000, // j = 3
    0x08000000, // j = 4
    0x10000000, // j = 5
    0x20000000, // j = 6
    0x40000000, // j = 7
    0x80000000, // j = 8
    0x1B000000, // j = 9
    0x36000000  // j = 10
};

// Dich trai 1 byte
uint32_t rotWord(uint32_t x)
{
    return ((x << 8) | (x >> 24));
}

// Ham xu li khoa tung loop
void Expansion_key(uint32_t key[4],int i)
{
    uint32_t ImKey[4];
    for (int j = 0; j < 4; j++)
    {
        ImKey[j] = key[j];
    }
    
    uint32_t key_final = key[3];
    key_final = rotWord(key_final); // dich sang trai 1 byte
    key_final = subword(key_final); // the byte
    key_final = key_final ^ Rcon[i];
    key[0] = key_final ^ key[0];
    //cout << hex << uppercase << key[0];
    cout << "\n";
    for (int j = 1; j < 4; j++)
    {
        key[j] = key[j-1] ^ ImKey[j];
    }
}
