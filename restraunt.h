#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include<unistd.h>
#include<fstream>
//#include"iofclose.c"

using namespace std;
struct Table
{
    int id;
    int sit;
    //bool istanken;
};

struct Dish
{
    int id;
    int price;
    std::string dishname;
};

struct Order
{
    int table;
    std::vector<Dish> dish;
    int pay=0;
    int id;
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
    fstream r;
    string temps;
    Table temptable;
    r.open("table.txt");
    if(!r)
    {
        printf("TABLE DON'T EXIST!\n");
        //fclose(r);
        return false;
    }
    else
    {
        for(;!r.eof();)
        {//读入顺序为编号，座位数
            getline(r,temps);
            temptable.id=atoi(temps.c_str());
            getline(r,temps);
            temptable.sit=atoi(temps.c_str());
            //getline(&temps,0,r);
            //temptable.istanken=(bool)atoi(temps);
            restraunt.table.push_back(temptable);
        }
        r.close();
        return true;
    }
}

bool initdishes(Restraunt restraunt)
{
    Dish tempdish;
    fstream fp;
    fp.open("dish.txt");
    string temps;
    if(!fp)
    {
        printf("DISHES DO NOT EXIST.");
        return false;
    }
    else
    {
        for(;!fp.eof();)
        {
            getline(fp,temps);
            tempdish.dishname=temps;
            getline(fp,temps);
            tempdish.id=atoi(temps.c_str());
            getline(fp,temps);
            tempdish.price=atoi(temps.c_str());
            restraunt.dish.push_back(tempdish);
        }
        fp.close();
    }
    return true;
}

bool initorders(Restraunt restraunt)
{
    int a;
    fstream r;
    string temps;
    Order *temporder=(Order*)malloc(sizeof(Order));//!bug
    r.open("order.txt");
    if(!r)
    {
        printf("NO ORDER EXIST!");
        //fclose(r);
        return false;
    }
    else
    {   
        Order *orderlisthead=(Order*)malloc(sizeof(Order));
        for(int c=0;!r.eof();c++)
        {
            getline(r,temps);
            (*temporder).table=atoi(temps.c_str());
            int numstart=0;
            char* numstring;
            getline(r,temps);
            for(int i=0,p=0;i<temps.length();i++)
            {
                if(temps.c_str()[i]==' ')
                {
                    for(int j=numstart,k=0;j<i;j++,k++)
                    {
                        numstring[k]=temps.c_str()[j];
                    }
                    numstart=i+1;
                    (*temporder).dish[p++].id=atoi(numstring);
                }
                for(int i=0;i<temporder->dish.size();i++)
                {
                    a=temporder->dish.size();
                    for(int j=0;j<restraunt.dish.size();j++)
                    {
                        if(temporder->dish[i].id==restraunt.dish[j].id)
                        {
                            temporder->dish[i]=restraunt.dish[j];
                            temporder->pay=temporder->pay+restraunt.dish[j].price;
                        }
                    }
                }
                temporder->id=c;
                pushto(*temporder,orderlisthead);
            }
            orderlisthead=restraunt.order->next;
        }
    }
    return true;
}

Restraunt initrestraunt()
{
    FILE *r;
    Restraunt rest;//restraunt
    Table temptable;
    char *temps;//tempstring
    r=fopen("restraunt.txt","r+");
    if(r==NULL)
    {
        printf("RESTRAUNT DON'T EXIST!\n");
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
        printf("NO TABLE!PLEASE CHECK YOUR FILE\n");
        close=true;
    }
    if(!initdishes(rest))
    {
        printf("NO DISH,PLEASE CHECK YOUR FILE.\n");
        close=true;
    }
    if(close)
    {
        printf("不好意思，今天本餐馆不营业,请隔日在来\n");
        system("read");
        exit(0);
    }
    if(!initorders(rest))
    {
        printf("NO ORDER.");
        return rest;
    }
    return rest;
}


