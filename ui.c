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
        printf("�߸� �� �Է��Դϴ�. �ٽ� �Է����ּ���\n");
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
    printf("���α׷��� �����մϴ�\n");
}

void PrintList(void)
{
    NODEDATA *pTmp = g_HeadNode.pNext;
    if (IsEmpty())
    {
        printf("��Ͽ� �����Ͱ� �����ϴ�.\n");
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
    printf("�� ������ �Է��ϼ��� (���� �̸� �޴���ȭ��ȣ ��)\n");
    USERDATA *pUser = (USERDATA *)calloc(1, sizeof(USERDATA));
    scanf_s("%d%s%s", &pUser->age, pUser->name, sizeof(pUser->name), pUser->phone, sizeof(pUser->phone));
    AddNewNode(NULL, 0, pUser, sizeof(USERDATA), true, 0);
    _getch();
}

void NodeSearchByNameUI()
{
    if (IsEmpty())
    {
        printf("�׸��� ����ֽ��ϴ�\n");
        _getch();
        return;
    }
    char tmp[32] = {0};
    printf_s("�˻� �� �̸��� �Է��ϼ���\n");
    scanf_s("%s%*c", &tmp);
    NODEDATA *pTmp = NodeSearchByName(tmp);
    if (pTmp == NULL)
    {
        printf("�˻��� ����� �����ϴ�\n");
        _getch();
        return;
    }
    printf("�˻� ��� :");
    PrintSrc(pTmp);
    printf("�ѱ�� : 0\t���� : 1\t���� : 2\n");
    int a;
    scanf_s("%d%*c", &a);
    while (a != 0)
    {
        switch (a)
        {
        case 1:
            printf("������ ������ �Է��ϼ���\n");
            EditNode(pTmp);
            if (pTmp->NEW != true)
            {
                printf("���Ͽ� ������ ������ �����Ͻðڽ��ϱ�? Y / N\n");
                char ch = getchar();
                if ('y' == ch || 'Y' == ch)
                {
                    EditNodeCommit(pTmp);
                }
            }
            printf("���� �Ϸ�\n");
            _getch();
            return;
        case 2:
            DeleteNode(pTmp);
            printf("���� �Ϸ�\n");
            _getch();
            return;
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���\n");
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
        printf("�׸��� ����ֽ��ϴ�.\n");
        _getch();
        return;
    }
    printf_s("�˻��� ������ ������ �Է��ϼ��� (MIN MAX).\n");
    scanf_s("%d%d%*c", &Min, &Max);
    SearchIndexByRange(Min, Max);
    ("�ƹ� Ű�� ��������..");
    _getch();
}

void PrintSearchByRange(NODEDATA **pTmp, int Length)
{

    if (Length <= 0)
    {
        printf("�˻� ����� �����ϴ�.\n");
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