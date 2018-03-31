#ifndef _ADMIN_H_
#define _ADMIN_H_

#include"./list.h"

int AdminRegister(adminNode *pHead);
int adminlogin(adminNode *pHead);
int addFunc(lottNode *pHead);
int delFunc(lottNode *pHead);
int checkFunc(lottNode *pHead);
void showAllLott(lottNode *pHead);
int openFunc(lottNode *pHead);
int adminFunc();

#endif
