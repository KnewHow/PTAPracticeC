#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXN 1005
    int curtime=0;
    float curmoney=0,Totalmoney=0;
    int flag=0;
int visited[MAXN]={0};
int Time[24];
typedef struct CNode{
    char Name[25];
    int month;
    int date;
    int hours;
    int minutes;
    int tag;
    double TT;
}ct;

ct Customer[MAXN];
int cmp(const void *a,const void *b)
{
    if (strcmp((*(ct*)a).Name,(*(ct*)b).Name)!=0)return (strcmp((*(ct*)a).Name,(*(ct*)b).Name)); //字典顺序（降序）
    else if ((*(ct*)a).TT!=(*(ct*)b).TT)return ((*(ct*)a).TT-(*(ct*)b).TT); //时间升序
}

float chargeByTime(int total)
{
    int i,hours,minutes;
    float money=0;
    hours=total/60;
    minutes=total%60;
    for (i=0;i<hours;i++)money+=Time[i%24]*60;
    money+=Time[i%24]*minutes;
    return money;
}

float  Cost(ct s,ct t)
{
    return ((chargeByTime(s.TT)-chargeByTime(t.TT))/100);
}

void Put(int i)
{
    curtime=Customer[i+1].TT-Customer[i].TT;
    curmoney=Cost(Customer[i+1],Customer[i]);
    printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n",Customer[i].date,Customer[i].hours,Customer[i].minutes,
    Customer[i+1].date,Customer[i+1].hours,Customer[i+1].minutes,curtime,curmoney);
    Totalmoney+=curmoney;
}


int main()
{
    int i,j,N;

    for (i=0;i<24;i++)scanf("%d",&Time[i]);
    scanf("%d",&N);
    char na[25],on[10];
    int mo,da,h,m;
    for (i=0;i<N;i++)
    {
        scanf("%s%d%*c%d%*c%d%*c%d%*c%s",&na,&mo,&da,&h,&m,&on);
        strcpy(Customer[i].Name,na);
        Customer[i].month=mo;Customer[i].date=da;
        Customer[i].hours=h;Customer[i].minutes=m;
        Customer[i].TT=Customer[i].minutes+Customer[i].hours*60+Customer[i].date*60*24;
        if (strcmp(on,"on-line")==0){Customer[i].tag=1;}
        else if (strcmp(on,"off-line")==0){Customer[i].tag=0;}
        getchar();
    }

    qsort(Customer,N,sizeof(Customer[0]),cmp);
   // i=2;
   // printf("%s %02d:%02d:%02d:%02d",Customer[i].Name,Customer[i].month,Customer[i].date,Customer[i].hours,Customer[i].minutes);

    char curname[25];
    for (i=0;i<N;i++)
    {

        if (!visited[i] && (strcmp(Customer[i].Name,Customer[i+1].Name)==0) && Customer[i].tag==1 && Customer[i+1].tag==0)
        {
            visited[i]=visited[i+1]=0;
            if (i==N)break;
            if (flag==0)
            {
            strcpy(curname,Customer[i].Name);
            printf("%s %02d\n",Customer[i].Name,Customer[i].month);
            flag=1;
            }
            if (strcmp(curname,Customer[i].Name)==0)
            {
                Put(i);
            }
            else if (strcmp(curname,Customer[i].Name)!=0)
            {
                printf("Total amount: $%.2f\n",Totalmoney);
                Totalmoney=0;
                strcpy(curname,Customer[i].Name);
                printf("%s %02d\n",Customer[i].Name,Customer[i].month);

                Put(i);
            }
        }
    }
    printf("Total amount: $%.2f\n",Totalmoney);
}
