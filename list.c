#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "ui.h"

NODEDATA g_HeadNode = {0};
NODEDATA g_TailNode = {0};
static unsigned int g_NodeCount = 0;

NODEDATA **g_IndexListByage = NULL;

void Initialize(void)
{
    g_HeadNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeadNode;
}

bool IsEmpty(void)
{
    if (g_HeadNode.pNext == &g_TailNode)
    {
        return 1;
    }
    return 0;
}

void AddNewNode(const char *keyName, const int KeyAge, USERDATA *pUser, int SizeData, bool New, unsigned int Offset)
{
    NODEDATA *pNode = (NODEDATA *)calloc(1, sizeof(NODEDATA));

    pNode->pUser = pUser;
    pNode->pNext = &g_TailNode;
    pNode->pPrev = g_TailNode.pPrev;

    if (New == true)
    {
        pNode->NEW = true;
    }
    else
    {
        pNode->offset = Offset;
    }
    if (pUser == NULL)
    {
        pNode->KeyName = malloc(strlen(keyName) + 1);
        memcpy(pNode->KeyName, keyName, sizeof(strlen(keyName) + 1));
        pNode->KeyAge = KeyAge;
    }
    else
    {
        pNode->KeyName = malloc(strlen(pUser->name) + 1);
        memcpy(pNode->KeyName, pUser->name, sizeof(strlen(pUser->name) + 1));
        pNode->KeyAge = pUser->age;
    }

    g_TailNode.pPrev = pNode;
    pNode->pPrev->pNext = pNode;
    g_NodeCount++;
}

void ReleaseList(void)
{
    NODEDATA *pTmp = g_HeadNode.pNext;
    NODEDATA *pDelete;
    while (pTmp != &g_TailNode)
    {
        printf("삭제 : ");
        PrintSrc(pTmp);
        pDelete = pTmp;
        pTmp = pTmp->pNext;
        free(pDelete->pUser);
        free(pDelete);
    }
    g_HeadNode.pNext = &g_TailNode;
    g_TailNode.pPrev = &g_HeadNode;

    if (g_IndexListByage != NULL)
    {
        free(g_IndexListByage);
        g_IndexListByage = NULL;
    }
}

NODEDATA *NodeSearchByName(char *tmp)
{
    NODEDATA *pTmp = g_HeadNode.pNext;
    while (pTmp != &g_TailNode)
    {
        if ((strcmp(tmp, pTmp->KeyName)) == 0)
            break;
        pTmp = pTmp->pNext;
    }
    if (pTmp == &g_TailNode)
    {
        return NULL;
    }
    if (pTmp->pUser == NULL)
    {
        FILE *fp = NULL;
        USERDATA *pUser = (USERDATA*)malloc(sizeof(USERDATA));
        fopen_s(&fp, "ListData.dat", "rb");
        fseek(fp, sizeof(USERDATA)* pTmp->offset, SEEK_SET);
        fread(pUser, sizeof(USERDATA), 1, fp);
        pTmp->pUser = pUser;
        fclose(fp);
    }
    return pTmp;
}

void EditNode(NODEDATA *pNode)
{
    int age;
    char name[32];
    char phone[32];
    scanf_s("%d%s%s%*c", &age, name, sizeof(name), phone, sizeof(phone));
    pNode->pUser->age = age;
    strcpy_s(pNode->pUser->name, sizeof(pNode->pUser->name), name);
    strcpy_s(pNode->pUser->phone, sizeof(pNode->pUser->phone), phone);
}

void EditNodeCommit(NODEDATA *pNode)
{
    FILE *fp = NULL;
    fopen_s(&fp, "ListData.dat", "rb+");
    fseek(fp, sizeof(USERDATA) * pNode->offset, SEEK_SET);
    fwrite(pNode->pUser, sizeof(USERDATA), 1, fp);
    fclose(fp);
}

void DeleteNode(NODEDATA *pNode)
{
    pNode->pPrev->pNext = pNode->pNext;
    pNode->pNext->pPrev = pNode->pPrev;
    free(pNode->pUser);
    free(pNode);
    g_NodeCount--;
}

void UpdateIndexAllByAge()
{
    if (g_IndexListByage != NULL)
    {
        free(g_IndexListByage);
        g_IndexListByage = NULL;
    }

    g_IndexListByage = (NODEDATA **)calloc(1, sizeof(NODEDATA) * g_NodeCount);
    NODEDATA *pTmp = g_HeadNode.pNext;

    for (int i = 0; i < g_NodeCount; i++)
    {
        g_IndexListByage[i] = pTmp;
        pTmp = pTmp->pNext;
    }

    for (int i = 0; i < g_NodeCount; i++)
    {
        for (int j = i + 1; j < g_NodeCount; j++)
        {
            if (g_IndexListByage[i]->KeyAge > g_IndexListByage[j]->KeyAge)
            {
                pTmp = g_IndexListByage[i];
                g_IndexListByage[i] = g_IndexListByage[j];
                g_IndexListByage[j] = pTmp;
            }
        }
    }
    printf("인덱스 정렬 완료\n");
}

void SearchIndexByRange(int Min, int Max)
{
    int Minindex = 0, Maxindex = 0;
    UpdateIndexAllByAge();
    if (Min > Max)
    {
        int tmp = Min;
        Min = Max;
        Max = tmp;
    }
    for (int i = 0; i < g_NodeCount; i++)
    {
        if (g_IndexListByage[i]->KeyAge >= Min && Max >= g_IndexListByage[i]->KeyAge)
        {
            Minindex = i;
            break;
        }
    }
    for (int j = Minindex; j < g_NodeCount; j++)
    {
        if (g_IndexListByage[j]->KeyAge > Max)
        {
            Maxindex = j - 1;
            break;
        }
    }
    int Length = Maxindex - (Minindex - 1);

    NODEDATA **pTmp = (NODEDATA **)malloc(sizeof(NODEDATA) * Length);
    memcpy(pTmp, g_IndexListByage + Minindex, sizeof(NODEDATA) * Length);
    free(g_IndexListByage);
    g_IndexListByage = NULL;

    PrintSearchByRange(pTmp, Length);
    free(pTmp);

    return;
}

void LordListFromFile()
{
    ReleaseList();
    FILE *fp = NULL;
    fopen_s(&fp, "ListData.dat", "rb");
    USERDATA a = {0};
    unsigned int offset = 0;
    while (fread(&a, sizeof(USERDATA), 1, fp) > 0)
    {
        AddNewNode(a.name, a.age, NULL, sizeof(USERDATA), false, offset);
        memset(&a, 0, sizeof(USERDATA));
        ++offset;
    }
    fclose(fp);
    return;
}

void SaveNewNodeFromFile()
{
    FILE *fp = NULL;
    fopen_s(&fp, "ListData.dat", "ab+");
    if (fp == NULL)
    {
        printf("파일 열기에 실패했습니다.");
        return;
    }
    NODEDATA *pTmp = g_HeadNode.pNext;
    while (pTmp != &g_TailNode)
    {
        if (pTmp->NEW == true)
        {
            if (fwrite(pTmp->pUser, sizeof(USERDATA), 1, fp) != 1)
            {
                printf("파일 쓰기에 실패했습니다.\n");
                continue;
            }
            printf("잘 저장됐습니다.");
        }
        pTmp = pTmp->pNext;
    }
    fclose(fp);
}