#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "ui.h"

// void InitDummy()
// {
//     USERDATA a = {9, "hoon", "010-1111-1111"};
//     USERDATA b = {7, "kim", "010-2222-2222"};
//     USERDATA c = {11, "goon", "010-3333-3333"};
//     USERDATA d = {3, "khan", "010-4444-4444"};
//     USERDATA e = {5, "jang", "010-5555-5555"};
//     USERDATA f[5] = {a, b, c, d, e};
//     for (int i = 0; i < 5; i++)
//     {
//         USERDATA *pTmp = (USERDATA *)calloc(1, sizeof(USERDATA));
//         memcpy(pTmp, &f[i], sizeof(USERDATA));
//         AddNewNode(NULL, 0, pTmp, sizeof(USERDATA), false, i);
//     }
// }
// void TestStep1()
// {
//     Initialize();
//     InitDummy();
//     PrintList();
//     NodeSearchByNameUI();
//     PrintList();
//     ReleaseList();
//     PrintList();
// }

void main(void)
{
    Initialize();
    LordListFromFile();
    EventLoop();
    SaveNewNodeFromFile();
    ReleaseList();
    getch();
}