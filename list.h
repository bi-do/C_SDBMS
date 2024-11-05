#pragma once
#include <stdbool.h>
// 구조체 선언
typedef struct USERDATA
{
    int age;
    char name[32];
    char phone[32];
} USERDATA;

typedef struct NODEDATA
{
    bool NEW;
    USERDATA *pUser;
    struct NODEDATA *pNext;
    struct NODEDATA *pPrev;
    void * KeyName;
    int KeyAge;
    unsigned int offset; 

} NODEDATA;

// 전역 변수 선언
extern NODEDATA g_HeadNode;
extern NODEDATA g_TailNode;
extern NODEDATA **g_IndexListByage;

// 초기화
void Initialize();
bool IsEmpty();
void ReleaseList(void);

// 편집
void AddNewNode(const char *keyName, const int KeyAge, USERDATA *pUser, int SizeData, bool New, unsigned int Offset);
void EditNode(NODEDATA *);
void DeleteNode(NODEDATA *);
void UpdateIndexAllByAge();

// 검색
NODEDATA *NodeSearchByName(char *);
void SearchIndexByRange(int Min, int Max);

// 파일 I/O
void LordListFromFile();
void SaveNewNodeFromFile();
void EditNodeCommit(NODEDATA *pNode);