#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdlib.h>
#include "list.h"
#include "ui.h"

int ViewUI(void)
{
    int a = 0;
    system("cls");
    printf_s("[1]NEW [2]SEARCH [3]SEARCH RANGE [4]PRINT [5]EXIT\n");
    scanf_s("%d%*c", &a);
    while (a == 0)
    {
        printf("잘못 된 입력입니다. 다시 입력해주세요\n");
        scanf("%*s");
        scanf_s("%d%*c", &a);
    }

    return a;
}

void EventLoop()
{
    INPUTTYPE input = 0;

    while ((INPUTTYPE)(input = ViewUI()) != 5)
    {
        switch (input)
        {
        case NEW:
            AddNewNodeUI();
            break;
        case SEARCH:
            NodeSearchByNameUI();
            break;
        case SEARCHRANGE:
            NodeSearchByRangeUI();
            break;
        case PRINT:
            PrintList();
            break;
        default:

            break;
        }
    }
    printf("프로그램을 종료합니다\n");
}

void PrintList(void)
{
    NODEDATA *pTmp = g_HeadNode.pNext;
    if (IsEmpty())
    {
        printf("목록에 데이터가 없습니다.\n");
        _getch();
        return;
    }
    while (pTmp != &g_TailNode)
    {
        PrintSrc(pTmp);
        pTmp = pTmp->pNext;
    }
    _getch();
}

void AddNewNodeUI()
{
    printf("새 정보를 입력하세요 (나이 이름 휴대전화번호 순)\n");
    USERDATA *pUser = (USERDATA *)calloc(1, sizeof(USERDATA));
    scanf_s("%d%s%s", &pUser->age, pUser->name, sizeof(pUser->name), pUser->phone, sizeof(pUser->phone));
    AddNewNode(NULL, 0, pUser, sizeof(USERDATA), true, 0);
    _getch();
}

void NodeSearchByNameUI()
{
    if (IsEmpty())
    {
        printf("항목이 비어있습니다\n");
        _getch();
        return;
    }
    char tmp[32] = {0};
    printf_s("검색 할 이름을 입력하세요\n");
    scanf_s("%s%*c", &tmp);
    NODEDATA *pTmp = NodeSearchByName(tmp);
    if (pTmp == NULL)
    {
        printf("검색한 결과가 없습니다\n");
        _getch();
        return;
    }
    printf("검색 결과 :");
    PrintSrc(pTmp);
    printf("넘기기 : 0\t편집 : 1\t삭제 : 2\n");
    int a;
    scanf_s("%d%*c", &a);
    while (a != 0)
    {
        switch (a)
        {
        case 1:
            printf("편집할 내용을 입력하세요\n");
            EditNode(pTmp);
            if (pTmp->NEW != true)
            {
                printf("파일에 편집한 내용을 저장하시겠습니까? Y / N\n");
                char ch = getchar();
                if ('y' == ch || 'Y' == ch)
                {
                    EditNodeCommit(pTmp);
                }
            }
            printf("편집 완료\n");
            _getch();
            return;
        case 2:
            DeleteNode(pTmp);
            printf("삭제 완료\n");
            _getch();
            return;
        default:
            printf("잘못된 입력입니다. 다시 입력하세요\n");
            scanf("%*s");
            scanf_s("%d", &a);
            break;
        }
    }
}

void NodeSearchByRangeUI()
{
    unsigned Min = 0;
    unsigned Max = 0;
    if (IsEmpty())
    {
        printf("항목이 비어있습니다.\n");
        _getch();
        return;
    }
    printf_s("검색할 나이의 범위를 입력하세요 (MIN MAX).\n");
    scanf_s("%d%d%*c", &Min, &Max);
    SearchIndexByRange(Min, Max);
    ("아무 키나 누르세요..");
    _getch();
}

void PrintSearchByRange(NODEDATA **pTmp, int Length)
{

    if (Length <= 0)
    {
        printf("검색 결과가 없습니다.\n");
        return;
    }

    for (int i = 0; i < Length; ++i)
    {
        PrintSrc(pTmp[i]);
    }
}

void PrintSrc(NODEDATA *pTmp)
{
    if (pTmp->pUser == NULL)
    {
        printf("[%p] %d %s %s [%p]\n", pTmp, pTmp->KeyAge, pTmp->KeyName, pTmp->NEW == true ? "NEW" : "LEGACY", pTmp->pNext);
    }
    else
        printf("[%p] %d %s %s %s [%p]\n", pTmp, pTmp->pUser->age, pTmp->pUser->name, pTmp->pUser->phone, pTmp->NEW == true ? "NEW" : "LEGACY", pTmp->pNext);
}