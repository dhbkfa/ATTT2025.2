#include "../main.h"
using namespace std;
using namespace std;

void shiftRows(uint32_t w[4]) {

    uint32_t IM_w[4];
    for (int i = 0; i < 4; i++)
    {
        IM_w[i] = w[i];
    }
    
    w[0] = (IM_w[0] & 0xFF000000) | (IM_w[1] & 0x00FF0000) | (IM_w[2] & 0x0000FF00) | (IM_w[3] & 0x000000FF);
    w[1] = (IM_w[1] & 0xFF000000) | (IM_w[2] & 0x00FF0000) | (IM_w[3] & 0x0000FF00) | (IM_w[0] & 0x000000FF);
    w[2] = (IM_w[2] & 0xFF000000) | (IM_w[3] & 0x00FF0000) | (IM_w[0] & 0x0000FF00) | (IM_w[1] & 0x000000FF);
    w[3] = (IM_w[3] & 0xFF000000) | (IM_w[0] & 0x00FF0000) | (IM_w[1] & 0x0000FF00) | (IM_w[2] & 0x000000FF);

}

void invShiftRows(uint32_t w[4]) {
    uint32_t IM_w[4];
    for (int i = 0; i < 4; i++)
    {
        IM_w[i] = w[i];
    }
    w[0] =  (IM_w[0] & 0xFF000000) | (IM_w[3] & 0x00FF0000) | (IM_w[2] & 0x0000FF00) | (IM_w[1] & 0x000000FF);
    w[1] =  (IM_w[1] & 0xFF000000) | (IM_w[0] & 0x00FF0000) | (IM_w[3] & 0x0000FF00) | (IM_w[2] & 0x000000FF);
    w[2] =  (IM_w[2] & 0xFF000000) | (IM_w[1] & 0x00FF0000) | (IM_w[0] & 0x0000FF00) | (IM_w[3] & 0x000000FF);
    w[3] =  (IM_w[3] & 0xFF000000) | (IM_w[2] & 0x00FF0000) | (IM_w[1] & 0x0000FF00) | (IM_w[0] & 0x000000FF);
}
