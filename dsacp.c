#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n;

typedef struct
{
    char name[20];
    char description[1000];
}country;

typedef struct node
{
    country *nation;
    int time;
    int cost;
    struct node *next;
}list;

typedef struct bucket
{
    char item[30];
    struct bucket *next;
}bucket;

list* createCountry()
{
    country *c=(country*)malloc(sizeof(country));
    scanf("%[^\n]s",c->name);
    scanf("%[^\n]s",c->description);
    list *l=malloc(sizeof(list));
    l->nation=c;
    l->time=0;
    l->cost=0;
    l->next=NULL;
    return l;
}

bucket* newItem()
{
    bucket *i=malloc(sizeof(bucket));
    scanf("%[^\n]s",i->item);
    i->next=NULL;
    return (strcmp(i->item,"0"))?NULL:i;
}

void main()
{
    int e,s,d,t,c,i,ch;
    list *(*cl)=malloc(250*sizeof(list*));
    printf("Enter the number of countries\n");
    scanf("%d",&n);
    printf("Enter the names and and description of all the countries\n");
    for(i=0;i<n;i++)
        cl[i]=createCountry();
    printf("Enter the total o flights\n");
    scanf("%d",&e);
    printf("Enter source no.,destination no.,duration and cost of all the routes");
    for(i=0;i<e;i++)
    {
        scanf("%d%d%d%d",&s,&d,&t,&c);
        list *l=cl[s];
        while(l->next)
            l=l->next;
        list *nr=malloc(sizeof(list));
        nr->nation=cl[d]->nation;
        nr->time=t;
        nr->cost=c;
        nr->next=NULL;
        l->next=nr;
    }
    do
    {
        printf("******************Main Menu******************\n\n");
        printf("\t1. Plan world tour based on bucket list\n");
        printf("\t2. Browse Database\n");
        printf("\t3. Edit Database\n");
        printf("\t4. Exit\n\n");
        printf("*********************************************\n");
        printf("Enter your choice\n");
        scanf(" %d",&ch);
        switch(ch)
        {
            case 1: planWorldTour(cl);
                    break;
            case 2: browseDatabase(cl);
                    break;
            case 3: editDatabase(cl);
                    break;
            case 4: printf("Enter 0 to exit, any other number to cancel\n");
                    scanf("%d",&ch);
                    break;
            default:printf("Invalid input, press any key to try again\n");
                    getchar();
        }
    }while(ch);
}

void planWorldTour(list *cl[250])
{
    int i,j,k,ch;
    bucket *bl,*t=bl;
    printf("Enter the things you would like to see/do during your tour, Enter '0' when you are done\n");
    bl=newItem();
    while(t)
    {
        t->next=newItem();
        t=t->next;
    }

}

void browseDatabase(list *cl[250])
{
    int ch,i,s,d,t,c;
    char temp[20];
    do
    {
        printf("*****************Browse Menu*****************\n\n");
        printf("\t1. Display all countries\n");
        printf("\t2. Display all routes\n");
        printf("\t3. Search a country\n");
        printf("\t4. Search a route\n");
        printf("\t5. Search countries with a particular attraction\n");
        printf("\t0. Back\n\n");
        printf("*********************************************\n");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("Following are all the countries currently in the database\n");
                    for(i=0;i<n;i++)
                    {
                        if(cl[i])
                        {
                            printf("\t%s\n",cl[i]->nation->name);
                        }
                    }
                    printf("Press any key to continue\n");
                    getchar();
                    break;
            case 2: printf("Following are all the routes currently in the database\n");
                    for(i=0;i<n;i++)
                    {
                        if(cl[i])
                        {
                            for(list *l=cl[i]->next;l;l=l->next)
                                printf("%s to %s\n",cl[i]->nation->name,l->nation->name);
                        }
                    }
                    printf("Press any key to continue\n");
                    getchar();
                    break;
            case 3: printf("Enter the name of the country you want to search\n");
                    scanf("%[^\n]s",temp);
                    s=searchCountry(cl,temp);
                    if(s==-1)
                    {
                        printf("Country not found in the database\nPress any key to continue\n");
                    }
                    else
                    {
                        printf("Country found : %s\n%s\n",cl[s]->nation->name,cl[s]->nation->description);
                        printf("Press any key to continue\n");
                    }
                    getchar();
                    break;
            case 4: printf("Enter the source and destination of the route you want to search\n");
                    scanf("%[^\n]s",temp);
                    s=searchCountry(cl,temp);
                    scanf("%[^\n]s",temp);
                    if(s==-1)
                    {
                        printf("Source not found in the database\nPress any key to continue\n");
                    }
                    else
                    {
                        list *l=cl[s];
                        while(l&&strcmp(temp,l->next->nation->name))
                            l=l->next;
                        if(l)
                        {
                            printf("%s to %s:\nDuration: %d\t Cost: %d\nPress any key to continue\n",cl[s]->nation->name,l->nation->name,l->time,l->cost);
                        }
                        else
                        {
                            printf("Route not found in the database\nPress any key to continue\n");
                        }
                    }
                    getchar();
                    break;
            case 5: printf("Enter the attraction you want to search for\n");
                    scanf("%[^\n]s",temp);
                    printf("Displaying all the countries with the particular attraction\n");
                    for(i=0;i<n;i++)
                    {
                        if(cl[i]&&boymoo(cl[i]->nation->description,temp)!=-1)
                            printf("\t%s\n",cl[i]->nation->name);
                    }
                    printf("Press any key to continue\n");
                    getchar();
                    break;
            case 0: break;
            default:printf("Invalid input, press any key to try again\n");
                    getchar();
        }
    }while(ch);
}

void editDatabase(list *cl[250])
{
    int ch,i,s,d,t,c;
    char temp[1000];
    do
    {
        printf("******************Edit Menu******************\n\n");
        printf("\t1. Add a nation\n");
        printf("\t2. Delete a nation\n");
        printf("\t3. Add a route\n");
        printf("\t4. Delete a route\n");
        printf("\t5. Edit country description\n");
        printf("\t6. Edit route parameters\n");
        printf("\t0. Back\n\n");
        printf("*********************************************\n");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: printf("Enter the name and description of the new country\n");
                    cl[++n]=createCountry();
                    printf("Country successfully added to database\nPress any key to continue\n");
                    getchar();
                    break;
            case 2: printf("Enter the name of the country you want to delete\n");
                    scanf("%[^\n]s",temp);
                    i=searchCountry(cl,temp);
                    if(i!=-1)
                    {
                        printf("Are you sure to delete the country and data of all the routes to and from the nation\n");
                        printf("Enter 1 to continue and any other number to cancel\n");
                        scanf("%d",&ch);
                        if(ch==1)
                        {
                            cl[i]=NULL;
                            for(i=0;i<n;i++)
                            {
                                if(cl[i])
                                {
                                    for(list *l=cl[i];l->next;l=l->next)
                                    {
                                        if(!strcmp(l->next->nation->name,temp))
                                            l->next=l->next->next;
                                    }
                                }
                            }
                            printf("Country successfully deleted from the database\npress any key to continue\n");
                        }
                        else
                        {
                            ch=2;
                            break;
                        }
                    }
                    else
                    {
                        printf("Nation not found in the database, press any to continue\n");
                    }
                    getchar();
                    break;
            case 3: printf("Enter the source, destination, duration and cost of the route\n");
                    scanf("%[^\n]s",temp);
                    s=searchCountry(cl,temp);
                    scanf("%[^\n]s",temp);
                    d=searchCountry(cl,temp);
                    if(s==-1||d==-1)
                    {
                        printf("Source or destination not found in the database\nPress any key to continue\n");
                    }
                    else
                    {
                        scanf(" %d%d",&t,&c);
                        list *l=cl[s];
                        while(l->next)
                            l=l->next;
                        list *nr=malloc(sizeof(list));
                        nr->nation=cl[d]->nation;
                        nr->time=t;
                        nr->cost=c;
                        nr->next=NULL;
                        l->next=nr;
                        printf("Route successfully added to database\nPress any key to continue\n");
                    }
                    getchar();
                    break;
            case 4: printf("Enter the source and destination of the route you want to delete\n");
                    scanf("%[^\n]s",temp);
                    s=searchCountry(cl,temp);
                    scanf("%[^\n]s",temp);
                    if(s==-1)
                    {
                        printf("Source not found in the database\nPress any key to continue\n");
                    }
                    else
                    {
                        list *l=cl[s];
                        while(l&&strcmp(temp,l->next->nation->name))
                            l=l->next;
                        if(l)
                        {
                            l->next=l->next->next;
                            printf("Database updated\nPress any key to continue\n");
                        }
                        else
                        {
                            printf("Route not found in the database\nPress any key to continue\n");
                        }
                    }
                    getchar();
                    break;
            case 5: printf("Enter the name of the country whose description you want to edit\n");
                    scanf("%[^\n]s,temp");
                    s=searchCountry(cl,temp);
                    if(s==-1)
                    {
                        printf("Country not found in the database\nPress enter to continue\n");
                    }
                    else
                    {
                        printf("Enter the new description of the country\n");
                        scanf("%[^\n]s,temp");
                        *(cl[s]->nation->description)=*temp;
                        printf("Database updated\nPress any key to continue\n");
                    }
                    getchar();
                    break;
            case 6: printf("Enter the source and destination of the route whose parameters you want to edit\n");
                    scanf("%[^\n]s",temp);
                    s=searchCountry(cl,temp);
                    scanf("%[^\n]s",temp);
                    if(s==-1)
                    {
                        printf("Source not found in the database\nPress any key to continue\n");
                    }
                    else
                    {
                        list *l=cl[s];
                        while(l&&strcmp(temp,l->nation->name))
                            l=l->next;
                        if(l)
                        {
                            printf("Enter the duration and cost of travel\n");
                            scanf(" %d%d",&t,&c);
                            l->time=t;
                            l->cost=c;
                            printf("Database updated\nPress any key to continue\n");
                        }
                        else
                        {
                            printf("Route not found in the database\nPress any key to continue\n");
                        }
                    }
                    getchar();
                    break;
            case 0: break;
            default:printf("Invalid input, press any key to try again\n");
                    getchar();
        }
    }while(ch);
}

int searchCountry(list *cl[250],char c[20])
{
    for(int i=0;i<n;i++)
        if(cl[i]&&!strcmp(c,cl[i]->nation->name))
            return i;
    return -1;
}

