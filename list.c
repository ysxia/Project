#include "./list.h"
#include "./public.h"

//管理员操作链表
//分配空间
lottNode *makeNode()
{
    lottNode *newNode = (lottNode*)malloc(LOTTNODE_LEN);
	if(NULL == newNode)
        newNode = (lottNode*)malloc(LOTTNODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

adminNode *makeadminNode()
{
    adminNode *newNode = (adminNode*)malloc(ADMINNODE_LEN);
	if(NULL == newNode)
        newNode = (adminNode*)malloc(ADMINNODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

//获取管理员信息
int getAdminData(adminInfo *temp)
{
    system("clear");
    printf("\n\t*****************管理员注册*******************\n");
    printf("\t帐号：");
    mygets(temp->name, sizeof(temp->name));
    printf("\n\t密码: ");
    temp->pwd = myscanf();
	return 0;
}

//添加管理员信息-------管理员注册
int add_admin(adminNode *pHead, adminInfo data)
{
    if(NULL == pHead)
    {
		printf("\n\t%s:the link is empty!\n",__func__);
		return -1;
    }

    //申请新的节点并初始化数据域
    adminNode *newNode = makeadminNode();
    newNode->data = data;

    //创建链表
    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 0;
}

//获得数据域的基本信息
int getData(lottInfo *temp)
{
    system("clear");
    printf("\n\t 彩票信息录入\n");
    printf("************************************\n");
    printf("\t彩票编号：");
    temp->lottID = myscanf();
    printf("\n\t彩票类型: ");
    mygets(temp->type, sizeof(temp->type));
    printf("\n\t彩票单价：");
    temp->price = myscanf();
    //初始化已购数量为0
    temp->amount = 0;
	//初始化彩票状态为false------未开奖
	temp->state = false;
    printf("\n\t发布时间：");
    mygets(temp->startime, sizeof(temp->startime));
    printf("\n\t开奖时间：");
    mygets(temp->endtime, sizeof(temp->endtime));
	return 0;
}

//发布彩票
int add_lott(lottNode *pHead, lottInfo data)
{
    if(NULL == pHead)
    {
		printf("\n\t%s:the link is empty!\n",__func__);
		return -1;
    }

    //申请新的节点并初始化数据域
    lottNode *newNode = makeNode();
    newNode->data = data;

    //创建链表
    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 0;
}

//按ID删除彩票
int del_lott(lottNode *pHead, long lottID)
{
	if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return -1;
    }

    lottNode *pPre = pHead;
    lottNode *pCur = pHead->pNext;

    while(NULL != pCur)
    {
        if(lottID == pCur->data.lottID)
        {
            pPre->pNext = pCur->pNext;
            free(pCur);
            pCur = NULL;
            return 1;       //找到并删除,返回 1
        }
        pCur = pCur->pNext;
        pPre = pPre->pNext;
    }
    if(NULL == pCur)
        return 0;           //未找到lottID匹配信息,返回 0
    return 1;
}

//按ID查询彩票信息
lottNode *lookupUser(lottNode *pHead, long lottID)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\t%s:the link is empty!\n", __func__);
        return NULL;
    }

    lottNode *temp = pHead->pNext;
    while(NULL != temp)
    {
        if(lottID == temp->data.lottID)
            return temp;
        temp = temp->pNext;
    }
    return NULL;
}

//彩票排序-----按ID
int sort(lottNode *pHead)
{
    if(NULL == pHead)
    {
		printf("\n\t%s:the link is empty!\n",__func__);
		return -1;
    }

    lottNode *max = NULL;
    lottNode *min = NULL;
    lottInfo temp;
    for(max = pHead->pNext; max != NULL; max = max->pNext)
    {
        for(min = max->pNext; min != NULL; min = min->pNext)
        {
            if(max->data.lottID > min->data.lottID)
            {
                temp = min->data;
                min->data = max->data;
                max->data = temp;
            }
        }
    }
    return 0;
}


//保存彩票数据
void writeToFile(lottNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\tthere is not info to save!\n");
        return;
    }
    FILE *fpw = fopen("lott.dat", "w");
    if(NULL == fpw)
    {
        perror("fopen error");
        return;
    }

    lottNode *temp = pHead->pNext;
    int ret = 0;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data, LOTTINFO_LEN, 1, fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return;
}

//保存管理员数据
void writeadminFile(adminNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\tthere is not info to save!\n");
        return;
    }
    FILE *fpw = fopen("admin.dat", "w");
    if(NULL == fpw)
    {
        perror("fopen error");
        return;
    }

    adminNode *temp = pHead->pNext;
    int ret = 0;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data, ADMININFO_LEN, 1, fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return;
}

//加载管理员数据
adminNode *readadminFile()
{
    FILE *fpr = fopen("./admin.dat", "r");
    if(NULL == fpr)
    {
        perror("fopen error");
        exit(1);
    }
    adminNode *pHead = makeadminNode();
    adminNode *newNode = makeadminNode();

    while(fread(&newNode->data, ADMININFO_LEN, 1, fpr) > 0)
    {
        newNode->pNext = pHead->pNext;
        pHead->pNext = newNode;
        newNode = makeadminNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHead;
}

//加载彩票数据
lottNode *readFromFile()
{
    FILE *fpr = fopen("./lott.dat", "r");
    if(NULL == fpr)
    {
        perror("fopen error");
        exit(1);
    }
    lottNode *pHead = makeNode();
    lottNode *newNode = makeNode();

    while(fread(&newNode->data, LOTTINFO_LEN, 1, fpr) > 0)
    {
        newNode->pNext = pHead->pNext;
        pHead->pNext = newNode;
        newNode = makeNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHead;
}


//用户操作链表

//分配空间
userNode *makeUserNode()
{
    userNode *newNode = (userNode*)malloc(USERNODE_LEN);
	if(NULL == newNode)
        newNode = (userNode*)malloc(USERNODE_LEN);
    newNode->pNext = NULL;
    return newNode;
}

//获取用户信息
int getUserData(userInfo *temp)
{
    system("clear");
    printf("\n\t*****************用户注册*******************\n");
    printf("\t帐号：");
    mygets(temp->name, sizeof(temp->name));
    printf("\n\t密码: ");
    temp->passwd = myscanf();
    //余额初始化为0
    temp->balance = 0;
	return 0;
}

//添加用户----注册
int add_user(userNode *pHead, userInfo data)
{
    if(NULL == pHead)
    {
		printf("\n\t%s:the link is empty!\n",__func__);
		return -1;
    }

    //申请新的节点并初始化数据域
    userNode *newNode = makeUserNode();
    newNode->data = data;

    //创建链表
    newNode->pNext = pHead->pNext;
    pHead->pNext = newNode;
    newNode = NULL;
    return 0;
}

//保存数据
void writeFile(userNode *pHead)
{
    if(NULL == pHead || NULL == pHead->pNext)
    {
        printf("\n\tthere is not info to save!\n");
        return;
    }
    FILE *fpw = fopen("user.dat", "w");
    if(NULL == fpw)
    {
        perror("fopen error");
        return;
    }

    userNode *temp = pHead->pNext;
    int ret = 0;
    while(NULL != temp)
    {
        ret = fwrite(&temp->data, USERINFO_LEN, 1, fpw);
        if(ret < 0)
            break;
        temp = temp->pNext;
    }

    fclose(fpw);
    return;
}

//加载数据
userNode *readFile()
{
    FILE *fpr = fopen("./user.dat", "r");
    if(NULL == fpr)
    {
        perror("fopen error");
        exit(1);
    }
    userNode *pHead = makeUserNode();
    userNode *newNode = makeUserNode();

    while(fread(&newNode->data, USERINFO_LEN, 1, fpr) > 0)
    {
        newNode->pNext = pHead->pNext;
        pHead->pNext = newNode;
        newNode = makeUserNode();
    }
    free(newNode);
    newNode = NULL;
    fclose(fpr);
    return pHead;
}

//销毁用户链表
void destroyUserList(userNode *pHead)
{
    if(NULL == pHead)
    {
        printf("\n\t%s:the list is empty!\n", __func__);
        return;
    }

    userNode *p = NULL;
    while(NULL != pHead)
    {
        p = pHead;
        pHead = pHead->pNext;
        free(p);
    }
    p = NULL;
    return;
}

//销毁管理员链表
void destroyAdminList(adminNode *pHead)
{
    if(NULL == pHead)
    {
        printf("\n\t%s:the list is empty!\n", __func__);
        return;
    }

    adminNode *p = NULL;
    while(NULL != pHead)
    {
        p = pHead;
        pHead = pHead->pNext;
        free(p);
    }
    p = NULL;
    return;
}

//销毁彩票链表
void destroyLottList(lottNode *pHead)
{
    if(NULL == pHead)
    {
        printf("\n\t%s:the list is empty!\n", __func__);
        return;
    }

    lottNode *p = NULL;
    while(NULL != pHead)
    {
        p = pHead;
        pHead = pHead->pNext;
        free(p);
    }
    p = NULL;
    return;
}
















