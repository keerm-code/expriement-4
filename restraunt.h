#include<stdio.h>
#include<stdlib.h>
#include<vector>

struct Order
{
    int table;
    int dish[];
    Order *next;
};

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
            delete tempo->next;
            tempo->next=NULL;
            break;
        }
    }
}

Restraunt initrestraunt()
{
    FILE *r;
    Restraunt rest;
    Table temptable;
    char *temps;
    r=fopen("restraunt.txt","r");
    if(r==NULL)
    {
        printf("RESTRAUNT DON'T EXIST!");
        fclose(r);
        exit(0);
        return rest;
    }
    else
    {
        getline(&rest.name,0,r);
        fclose(r);
    }
    r=fopen("table.txt","r");
    if(r==NULL)
    {
        printf("TABLE DON'T EXIST!");
        fclose(r);
        goto DISH;
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
            rest.table.push_back(temptable);
        }
        fclose(r);
    }
    DISH:Dish tempdish;
    r=fopen("dish.txt","r");
    if(r=NULL)
    {
        printf("DISHES DO NOT EXIST.");
        fclose(r);
        goto ORDER;
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
            rest.dish.push_back(tempdish);
        }
        fclose(r);
    }
    ORDER:Order temporder;
    r=fopen("order.txt","r");
    if(r==NULL)
    {
        new 
    }


}


