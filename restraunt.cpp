//#include"restraunt.h"
#include"ordermanage.h"

int main()
{
    Restraunt rest=initrestraunt();
    int n;
    bool stop=false;
    while (!stop)
    {
        printf("欢迎来到 %s\n。",rest.name);
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
                printf("订单创建成功！");
            }
            else
            {
                puts("创建失败");
            }
        }
        if(n==3)
        {
            printf("");//!now
        }
    }
    
    
}