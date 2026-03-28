#include <iostream>
#include <cstdint>
#include <string>
#include <stdint.h>
#include "main.h"
using namespace std;
string text = "3243F6A8885A308D313198A2E0370734";
string key = "3243F6A8885A308D313198A2E0370734";
uint32_t words[4];
uint32_t keys[4];
uint32_t result[4];
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
// Khai bao ham 
void Xuli_keyOneLoop(uint32_t key[4]);
// Dich trai 1 byte
uint32_t rotWord(uint32_t x)
{
    return ((x << 8) | (x >> 24));
}
// XOR 2 text 32 bit
inline uint32_t XOR_32bit(uint32_t text1,uint32_t text2)
{
    return (text1 ^ text2);
}
/*Xac dinh yeu cau : Ma hoa theo AES
    + test: 3243F6A8 885A308D 313198A2 E0370734
    + Key : 2B7E1516 28AED2A6 ABF71588 09CF4F3C
    +Output:3925841D 02DC09FB ABF71588 196A0B32
*/ 
// Tach 8 ki tu trong text thanh 1 gia tri trong mang gom 4 phan tu
bool khoitao()
 {
    string text_check = text; // bien xu li text
    string key_check = key;
    if (text_check.length() != 32)
    {
        cout << "Loi : chuoi chua du 128 bit";
        return false; 
    }
    for (int i = 0; i < 4; i++)
    {
        string cut_text = text_check.substr(i*8,8); // Cat chuoi 8 ki tu trong mang text_check
        words[i] = static_cast<uint32_t>(stoul(cut_text,nullptr,16));


    }
    for (int j = 0; j < 4; j++)
    {
        string cut_key = key_check.substr(j*8,8); // Cat chuoi 8 ki tu trong mang text_check
        keys[j] = static_cast<uint32_t>(stoul(cut_key,nullptr,16));


    }
    // In ra ket qua kiem tra
    cout << "Word:";
    for (int i = 0; i < 4; i++)
    {
        cout << hex << uppercase << words[i];
        cout << hex <<  uppercase << keys[i];
        result[i] = XOR_32bit(words[i],keys[i]);

    }
    cout << "\nresult:";
    for (int i = 0; i < 4; i++)
    {
        cout << hex << uppercase << result[i];
    }
    
    cout << "\n";
    
    
    return true;
    


    
 }
 // Ham xu li khoa tung loop
void Xuli_keyOneLoop(uint32_t key[4],int i)
{
    uint32_t ImKey[4];
    for (int i = 0; i < 4; i++)
    {
        ImKey[i] = key[i];
    }
    
    uint32_t key_final = key[3];
    key_final = rotWord(key_final); // dich sang trai 1 byte
    key_final = subword(key_final); // the byte
    key_final = XOR_32bit(key_final,Rcon[i]);
    key[0] = XOR_32bit(key_final,key[0]);
    cout << hex << uppercase << key[0];
    cout << "\n";
    for (int i = 1; i < 4; i++)
    {
        key[i] = XOR_32bit(key[i-1],ImKey[i]);
    }
    
}
void in_ketqua(uint32_t x[4])
{
    cout << "\nWord: ";
    for (int i = 0; i < 4; i++)
    {
        cout << hex << uppercase << x[i];
        cout << "\n";
    }
    
}

int main()
{
    // if (!khoitao())
    // {
    //     return 0;
    // }
    uint32_t text1 = 0x2B9563B9;
    //cout << hex << uppercase << rotWord(text1);
    uint32_t text2 = 0x10000000;
    uint32_t test[4] = {0x2B7E1516,0x28AED2A6,0xABF71588,0x09CF4F3C};
    Xuli_keyOneLoop(test,1);
    in_ketqua(test);


    //cout << hex << uppercase << XOR_32bit(text1,text2);


  
}