#include <iostream>
#include <cstdint>
#include <string>
using namespace std;
string text = "3243F6A8885A308D313198A2E0370734";
string key = "3243F6A8885A308D313198A2E0370734";
uint32_t words[4];
uint32_t keys[4];
uint32_t result[4];
// Khai bao ham 
uint32_t Substitute_bytes(uint32_t x)
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
int main()
{
    // if (!khoitao())
    // {
    //     return 0;
    // }
    uint32_t text1 = 0x2B9563B9;
    cout << hex << uppercase << Substitute_bytes(text1);
    uint32_t text2 = 0x10000000;

    //cout << hex << uppercase << XOR_32bit(text1,text2);


  
}