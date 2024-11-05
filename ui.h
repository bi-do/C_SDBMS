#pragma once
#include "list.h"
typedef enum INPUTTYPE
{
    EXIT,
    NEW,
    SEARCH,
    SEARCHRANGE,
    PRINT

} INPUTTYPE;
int ViewUI(void);
void EventLoop();
void PrintList(void);
void NodeSearchByNameUI();
void AddNewNodeUI();
void NodeSearchByRangeUI();
void PrintSearchByRange(NODEDATA**, int);
void PrintSrc();