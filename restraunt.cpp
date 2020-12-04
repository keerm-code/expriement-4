//#include"restraunt.h"
#include"ordermanage.h"

int main()
{
    FILE *fp=fopen64("key.txt","r+");
    char* s;
    getline(&s,0,fp);
    Restraunt rest=initrestraunt();
    int n;
    bool stop=false;
    while (!stop)
    {
        printf("\n欢迎来到 %s\n。",rest.name);
        printf("请输入对应数字使用对应功能。\n");
        printf("1.菜单\t2.点餐\t3.结账\t4.管理系统\n");
        printf("输入0退出本系统\n");
        scanf("%d",&n);
        if(n==1)
        {
            for(int i=0;i<rest.dish.size();i++)
            {
                printf("%d\t%s\t%d\n",rest.dish[i].id,rest.dish[i].dishname,rest.dish[i].price);
            }
            printf("请按任意键回到主界面:");
            system("read");
            continue;
        }
        if(n==2)
        {
            if(addorder(rest))
            {
                printf("订单创建成功！\n");
            }
            else
            {
                puts("创建失败\n");
            }
            system("read");
            continue;
        }
        if(n==3)
        {
            printf("请付款%d元。\n",rest.order->pay);//!no
            printf("请确认顾客是否付款,是按1，否按0\n");
            int booler;
            scanf("%d",&booler);
            if(booler==1)
            {
                printf("付款成功\n");
            }
            else
            {
                deletelastorder(rest.order);
                printf("付款失败，请重新创建订单\n");
            }
            system("read");
            continue;
        }
        if(n==4)
        {
            char* temps;
            printf("\n请输入密码:");
            getline(&temps,0,stdin);
            if(temps==s)
            {
                printf("\n密码正确");
            }
            else
            {
                printf("\n密码错误，请重试\n");
                system("read");
                continue;
            }
            printf("\n请选择要查阅或改变的项目：");
            printf("\n1.改动账户密码\t2.菜单相关\t\3.账目相关,输入其他退出");
            int m=0;
            scanf("%d",&m);
            if(m==1)
            {
                printf("\n请输入新密码:");
                getline(&temps,0,stdin);
                fclose(fp);
                fp=freopen("key.txt","w+",stdin);
                fprintf(fp,"%s",temps);
                printf("\n修改成功");
                system("read");
                continue;
            }
            if(m==2)
            {
                printf("\n请选择要进行什么操作");
                printf("\n1.显示菜单\t2.添加新菜品，其他按键：返回最上层");
                scanf("%d",&m);
                if(m==1)
                {
                    seedishes(rest);
                    //system("read");
                    continue;
                }
                if(m==2)
                {
                    newdish(rest);
                    continue;
                }
                else
                {
                    continue;
                } 
            }
            if(m==3)
            {
                printf("\n请选择要进行的账目操作\n1.账目显示\t2.删除指定账目\t3.删除最近账目\t4.计算营业额\n");
                printf("按其他按键返回到最上层");
                scanf("%d",&m);
                if(m==1)
                {
                    seeorders(rest);
                    continue;
                }
                if(m==2)
                {
                    printf("请输入要删除的订单编号");
                    scanf("%d",&m);
                    deletethisorder(m,rest.order);
                    continue;
                }
                if(m==3)
                {
                    deletelastorder(rest.order);
                    printf("删除成功\n");
                    continue;
                }
                if(m==4)
                {
                    int money=0;
                    for(;rest.order->next!=NULL;)
                    {
                        money=money+rest.order->pay;
                        printf("今日营业额为：%d元",money);
                        system("read");
                        continue;
                    }
                }
            }

        }
        else
        {
            exit(0);
        }
        
    }
    return 0;   
}