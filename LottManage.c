#include "./user.h"
#include "./interfaceUI.h"
#include "./public.h"
#include "./list.h"
#include "./admin.h"

int mainMenu();

//管理员登录界面
int adminLoginMenu(adminNode *pHead)
{
    adminloginUI(pHead);
    int choice = myscanf();
    switch(choice)
    {
        case 1:             //管理员注册
        {
            system("clear");
            AdminRegister(pHead);
            break;
        }
        case 2:             //管理员登录
        {
            system("clear");
            adminlogin(pHead);
            break;
        }
        case 0:
        {
            mainMenu();
            break;
        }
         default:
        {
            printf("\n\t输入有误,请重新输入：\n");
            adminLoginMenu(pHead);
            break;
        }
    }
	return 1;
}

//用户登录界面
int loginMenu(userNode *pHead)
{
    userloginUI(pHead);
    int choice = myscanf();
    switch(choice)
    {
        case 1:             //用户注册
        {
            system("clear");
			Register(pHead);
            break;
        }
        case 2:             //用户登录
        {
            system("clear");
            login(pHead);
            break;
        }
        case 0:
        {
            mainMenu();
            break;
        }
         default:
        {
            printf("\n\t输入有误,请重新输入：\n");
            loginMenu(pHead);
            break;
        }
    }
	return 1;
}

//开始界面
int mainMenu()
{
    adminNode *pHead1 = readadminFile();
    userNode *pHead2 = readFile();
    system("clear");
    mainUI();
    int choice = myscanf();
    switch(choice)
    {
        case 1:                 //管理员登录
        {
            system("clear");
            adminLoginMenu(pHead1);
            break;
        }
        case 2:                 //用户登录
        {
            system("clear");
            loginMenu(pHead2);
            break;
        }
        case 0:
        {
            printf("\n\t即将退出...\n");
            sleep(2);
            break;
        }
         default:
        {
            printf("\n\t输入有误!\n");
            sleep(1);
            mainMenu();
            break;
        }
    }
    return 0;
}

int main(void)
{
    userNode *pHead1 = readFile();
    adminNode *pHead2 = readadminFile();
    lottNode *pHead3 = readFromFile();
    mainMenu();
    destroyUserList(pHead1);
    destroyAdminList(pHead2);
    destroyLottList(pHead3);
    return 0;
}