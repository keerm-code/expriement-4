#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<unistd.h>

struct Table
{
    int id;
    int sit;
    bool istanken;
};

struct Dish
{
    int id;
    int price;
    char *dishname;
};

struct Order
{
    int table;
    std::vector<Dish> dish;
    int pay=0;
    Order *next;
};
struct Restraunt
{
    char *name;
    std::vector<Dish> dish;
    std::vector<Table> table;
    Order *order;
};

Order init()
{
    Order *list;
    list=(Order*)malloc(sizeof(Order));
    list->next=NULL;
    return *list;
}

void pushto(Order neworder,Order *head)
{
    Order *tempo=head;
    while (1)
    {
        if(tempo->next!=NULL)
        {
            tempo=tempo->next;
        }
        else
        {
            neworder.next=NULL;
            *((*tempo).next)=neworder;
            break;
        }
    }
}

void pushout(Order *head)
{
    Order *tempo=head;
    while (1)
    {
        if(tempo->next!=NULL)
        {
            tempo=tempo->next;
        }
        else
        {
            free(tempo->next);
            tempo->next=NULL;
            break;
        }
    }
}

bool inittables(Restraunt restraunt)
{
    FILE* r;
    char* temps;
    Table temptable;
    r=fopen("table.txt","r");
    if(r==NULL)
    {
        printf("TABLE DON'T EXIST!");
        //fclose(r);
        return false;
    }
    else
    {
        for(;getline(&temps,0,r)!=EOF;)
        {//读入顺序为编号，座位数，是否被占用
            temptable.id=atoi(temps);
            getline(&temps,0,r);
            temptable.sit=atoi(temps);
            getline(&temps,0,r);
            temptable.istanken=(bool)atoi(temps);
            restraunt.table.push_back(temptable);
        }
        fclose(r);
        return true;
    }
}

bool initdishes(Restraunt restraunt)
{
    Dish tempdish;
    FILE* r;
    char* temps;
    r=fopen("dish.txt","r");
    if(r=NULL)
    {
        printf("DISHES DO NOT EXIST.");
        //fclose(r);
        return false;
    }
    else
    {
        for(;getline(&temps,0,r)!=EOF;)
        {
            tempdish.dishname=temps;
            getline(&temps,0,r);
            tempdish.id=atoi(temps);
            getline(&temps,0,r);
            tempdish.price=atoi(temps);
            restraunt.dish.push_back(tempdish);
        }
        fclose(r);
    }
    return true;
}

bool initorders(Restraunt restraunt)
{
    FILE *r;
    char* temps;
    ORDER:Order *temporder=(Order*)malloc(sizeof(Order));
    r=fopen("order.txt","r");
    if(r==NULL)
    {
        printf("NO ORDER EXIST!");
        //fclose(r);
        return false;
    }
    else
    {   
        Order *orderlisthead=(Order*)malloc(sizeof(Order));
        for(;getline(&temps,0,r)!=EOF;)
        {
            (*temporder).table=atoi(temps);
            int numstart=0;
            char* numstring=NULL;
            for(int i=0,p=0;temps[i]!='/0';i++)
            {
                if(temps[i]==' ')
                {
                    for(int j=numstart,k=0;j<i;j++,k++)
                    {
                        numstring[k]=temps[j];
                    }
                    (*temporder).dish[p++].id=atoi(numstring);
                }
                for(int i=0;i<(*temporder).dish.size();i++)
                {
                    for(int j=0;j<restraunt.dish.size();j++)
                    {
                        if(temporder->dish[i].id==restraunt.dish[j].id)
                        {
                            temporder->dish[i]=restraunt.dish[j];
                            temporder->pay=temporder->pay+restraunt.dish[j].price;
                        }
                    }
                }
                pushto(*temporder,orderlisthead);
            }
            restraunt.order->next=orderlisthead;
        }
    }
}

Restraunt initrestraunt()
{
    FILE *r;
    Restraunt rest;//restraunt
    Table temptable;
    char *temps;//tempstring
    r=fopen("restraunt.txt","r");
    if(r==NULL)
    {
        printf("RESTRAUNT DON'T EXIST!");
        system("read");
        //fclose(r);
        exit(0);
    }
    else
    {
        getline(&rest.name,0,r);
        fclose(r);
    }
    bool close=false;
    if(!inittables(rest))
    {
        printf("NO TABLE!\nPLEASE CHECK YOUR FILE.");
        close=true;
    }
    if(!initdishes(rest))
    {
        printf("NO DISH,PLEASE CHECK YOUR FILE.");
        close=true;
    }
    if(close)
    {
        printf("不好意思，今天本餐馆不营业,请隔日在来");
        system("pause");
        exit(0);
    }
    if(!initorders(rest))
    {
        printf("NO ORDER.");
        return rest;
    }
}


