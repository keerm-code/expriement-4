#include"restraunt.h"

void addorder(Restraunt rest)
{
    Order *norder=(Order*)malloc(sizeof(Order));
    printf("请输入订单号：");
    int n;
    scanf("%d",&n);
    printf("\n请以“编号 编号”的格式在一行内输入菜品编号：\n");
    char* temps=NULL,*numstring=NULL;
    int numstart=0;
    getline(&temps,0,stdin);
    for(int i=0;temps[i]!='\0';i++)
    {
        numstring=NULL;
        if(temps[i]==' ')
        {
            for(int j=numstart,k=0;j<i;j++,k++)
            {
                numstring[k]=temps[i];
            }
            numstart=i+1;
            norder->dish[i].id=atoi(numstring);//!now
        }
    }
}

void deletelastorder(Order *haed)
{
    pushout(haed);
}

bool deletethisorder(int id,Order *head)
{
    Order tempo=*head->next;
    while (tempo.next!=NULL)
    {
        if(tempo.next->id==id)
        {
            tempo.next=tempo.next->next;
            free(&tempo.next);
            printf("删除订单信息成功。\n");
            system("read");
            return true;
        }
        else
        {
            tempo=*tempo.next;
        }
    }
    printf("删除失败，似乎没有该订单号。\n");
    system("read");
    return false;
}

void seeorders(Restraunt rest)
{
    printf("订单内容如下");
    while (rest.order->next!=NULL)
    {
        printf("订单编号：%d\t",rest.order->id);
        printf("订单桌号：%d\t",rest.order->table);
        printf("餐款：%d\n",rest.order->pay);
        printf("订单内容：\n");
        for(int i=0;i<rest.order->dish.size();i++)
        {
            printf("%d  %s\n",rest.order->dish[i].id,rest.order->dish[i].dishname);
        }
    }
    printf("请按任意键退出。");
    system("read");
}

void seedishes(Restraunt rest)
{
    printf("本店提供的菜肴如下:\n");
    for(int i=0;i<rest.dish.size();i++)
    {
        printf("%d\t%s\t%d\n",rest.dish[i].id,rest.dish[i].dishname,rest.dish[i].price);
    }
    printf("请按任意键返回");
    system("read");
}

void newdish(Dish cai,Restraunt rest)
{
    printf("请依次输入餐品编号，名称与价格,以回车为间隔\n");
    scanf("%d %s %d",&cai.id,cai.dishname,&cai.price);
    rest.dish.push_back(cai);
    printf("添加完毕，输入任意键返回");
    system("read");
}