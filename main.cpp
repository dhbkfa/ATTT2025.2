#include <iostream>
#include <cstdint>
#include <string>
#include <stdint.h>
#include <iomanip>
#include <sstream>
#include "main.h"
using namespace std;
/*Xac dinh yeu cau : Ma hoa theo AES
    + test: 3243F6A8 885A308D 313198A2 E0370734
    + Key : 2B7E1516 28AED2A6 ABF71588 09CF4F3C
    +Output:3925841D 02DC09FB ABF71588 196A0B32
*/ 
string text = "3243F6A8885A308D313198A2E0370734";
string key = "2B7E151628AED2A6ABF7158809CF4F3C";
uint32_t words[4];
uint32_t keys[4];
uint32_t results[4];
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
// XOR 2 text 32 bit
inline uint32_t XOR_32bit(uint32_t text1,uint32_t text2)
{
    return (text1 ^ text2);
}
void XOR_text(uint32_t text1[4],uint32_t text2[4],uint32_t result[4])
{
    for (int i = 0; i < 4; i++)
    {
        result[i] = XOR_32bit(text1[i],text2[i]);
    }
    
    
    
}

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
    XOR_text(words,keys,results);
    return true;
    


    
 }
 // Ham xu li khoa tung loop
void AddRoundKey(uint32_t key[4],int i)
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
    //cout << hex << uppercase << key[0];
    cout << "\n";
    for (int i = 1; i < 4; i++)
    {
        key[i] = XOR_32bit(key[i-1],ImKey[i]);
    }
    
}
void in_ketqua(uint32_t x[4],const string& text)
{
    cout << text << "\n";
    for (int i = 0; i < 4; i++)
    {
        cout << "0x" << hex << uppercase << setfill('0') << setw(8)<< x[i];
        cout << "\n";
    }
    
}

int main()
{




    string infor_text;
    string infor_key;
    cout << "\nNhap thong tin ban can ma hoa(y/c:128bit) : ";
    cin >> infor_text ;
    cout << "\nDat khoa (y/c:128bit): ";
    cin >> infor_key;
    text = infor_text;
    key  = infor_key;
    if (!khoitao())
    {
        cout << "\nDau vao khong hop le!";
        return 0;
    }
    in_ketqua(results,"hien thi ket qua khoi tao : ");
    // Thuat toan ma hoa AES
    for (int i = 1; i < 10; i++)
    {
        cout << "\nBuoc thu: " << i;
        cout << "\n";
        subBytes(results);
        in_ketqua(results,"Ket qua subBytes: ");
        shiftRows(results);
        in_ketqua(results,"Ket qua shiftRows: ");
        mixColumns(results);
        in_ketqua(results,"Ket qua mixColumns: ");
        AddRoundKey(keys,i);
        in_ketqua(keys,"Ket qua AddRoundkey: ");
        XOR_text(results,keys,results);
        in_ketqua(results,"Ket qua lan tiep theo :");



    }
    // Buoc thu 10
    cout << "\nBuoc 10 \n";
    subBytes(results);
    in_ketqua(results,"Ket qua subBytes: ");
    shiftRows(results);
    in_ketqua(results,"Ket qua shiftRows: ");
    AddRoundKey(keys,10);
    in_ketqua(keys,"Ket qua AddRoundkey: ");
    XOR_text(results,keys,results);
    // Hien thi ket qua ma hoa
    cout << "\n Thong tin : " << text;
    cout << "\n Khoa      : " << key;
    stringstream ss;
    for (int i = 0; i < 4; i++)
    {
        ss << hex << uppercase << setfill('0') << setw(8) << results[i];
    }
    cout << "\ncipher    : " << ss.str();

    // uint32_t text1 = 0x2B9563B9;
    // //cout << hex << uppercase << rotWord(text1);
    // uint32_t text2 = 0x10000000;
    // uint32_t test[4] = {0x2B7E1516,0x28AED2A6,0xABF71588,0x09CF4F3C};
    // AddRoundKey(test,1);
    // in_ketqua(test);


    //cout << hex << uppercase << XOR_32bit(text1,text2);



  
}