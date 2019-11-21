//153,
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<strings.h>

typedef struct weight
{
    int time,cost;
}weight;

typedef struct country
{
    char name[20];
    char desc[150];
}country;

typedef struct wish
{
    char s[20];
    int p[20];
    int c;
}wish;

typedef struct Bucket_stack
{
   int top;
   wish  w[15];
}Bucket_stack;

void generate_list(FILE *,country *,int );
void generate_graph(FILE *,FILE *,weight [][100],int );
void display_bucket(country *);
void push(wish );
int kmp_search(char *,char *);
void generate_lps(char *,int ,int *);
void process_bucket(int ,country *);
void menu();
void display_details(char *,country *,int );
int search_country(char *,country *,int );
int check(int *,int );
void plan_route(weight mat[][100],int ,char *,country *,int );
void find_path_cost(weight [][100],int ,int *,int ,int ,int ,country *);
void find_path_time(weight [][100],int ,int *,int ,int ,int ,country *);
void print_path(int ,int ,country *);

Bucket_stack  bucket;
int path[20],counter_path=0,final_path[20],final_cost,path_len,so;

int main()
{
  bucket.top=-1;
  system("color f0");
  int      V,ch,ch2,para,i;
  FILE     *fp,*fp1;
  country  list[100];
  weight   graph_mat[100][100];

  char     wish_list[200],*token,set[100];
  wish     x;
  fp=fopen("Tour_Places.txt","r");
  fscanf(fp,"%d",&V);
  generate_list(fp,list,V);
  fclose(fp);

  fp=fopen("Tour_Cost.txt","r");
  fp1=fopen("Tour_Duration.txt","r");
  generate_graph(fp,fp1,graph_mat,V);
  fclose(fp);

  do
  {
    menu();
    scanf("%d",&ch);
    switch(ch)
    {
       case 1 : printf("Enter Places you want to visit(Separated by ,): ");
                fflush(stdin);
                scanf("%[^\n]s",wish_list);
                token=strtok(wish_list,",");
                while(token)
                 {
                  strcpy(x.s,token);
                  push(x);
                  token=strtok(NULL,",");
                 }
                process_bucket(V,list);
                break;

      case 2 : if(bucket.top!=-1)
               {
                   printf("\nSearch Results: \n");
                   display_bucket(list);
               }
               label_2 :
               printf("\n1 To Check More details of Countries\n2 To Pick countries to Visit: ");
               scanf("%d",&ch2);
               switch(ch2)
               {
                  case 1 : printf("Enter Countries to Check(Separated by ,): ");
                           fflush(stdin);
                           scanf("%[^\n]s",set);
                           display_details(set,list,V);
                           goto label_2;

                  case 2 : printf("Enter Countries to Visit(Separated by ',' and starting with your current country): ");
                           fflush(stdin);
                           scanf("%[^\n]s",set);
                           printf("\n1 to Minimize Cost\n2 To Minimize Time: ");
                           scanf("%d",&para);
                           plan_route(graph_mat,para,set,list,V);
                           if(para==1)
                             printf("\n\nBest Path(%d rupees):",final_cost);
                           else
                             printf("\n\nBest Path(%d hrs):",final_cost);
                           for(i=0;i<path_len;i++)
                             printf("%s------>",list[final_path[i]].name);
                           printf("%s",list[so].name);

               }
               break;
        case 3: do
                {
                    printf("1. Add a country\n2. Edit path duration\n3. Edit path cost\n0. back\n");
                    scanf("%d",&ch2);
                    switch(ch2)
                    {
                        case 1: printf("Enter name and description of the new country\n");
                                fflush(stdin);
                                scanf("%[^\n]s",list[V++].name);
                                scanf("%[^\n]s",list[V++].desc);

                    }
                }while(ch2);
                break;
        case 4: bucket.top=-1;
                break;
        case 5: return;
        default:printf("Invalid input, please try again\n");

   }
   printf("\n");
 }while(ch);
}
void generate_list(FILE *fp,country *l,int s)
{
    int i,k,x;
    char n[20],d[150];

    for(k=0;k<s;k++)
    {
       fscanf(fp,"%d ",&i);
       fgets(n,20,fp);
       x=strlen(n);
       n[x-1]='\0';
       fgets(d,150,fp);
       x=strlen(d);
       d[x-1]='\0';
       strcpy(l[i].name,n);
       strcpy(l[i].desc,d);
    }
}
void generate_graph(FILE *fp1,FILE *fp2,weight mat[][100],int n)
{
  int u,v,w;

  while(fscanf(fp1,"%d %d %d",&u,&v,&w)!=EOF)
  {
      //if(u < n && v <n)
        mat[u][v].cost=w;
  }
  while(fscanf(fp2,"%d %d %d",&u,&v,&w)!=EOF)
  {
      mat[u][v].time=w;
  }
}
void push(wish x)
{
  bucket.w[++bucket.top]=x;
}

void display_bucket(country *l)
{
  int i,j;
  printf("\n%-25s%s\n","Place","Countries");
  for(i=0;i<=bucket.top;i++)
  {
    printf("\n%-25s",bucket.w[i].s);
    for(j=0;j<bucket.w[i].c;j++)
      printf("%s  ",l[bucket.w[i].p[j]].name);
  }
}
void process_bucket(int v,country *l)
{
   int i,j,flag=0;

  for(i=0;i<=bucket.top;i++)
   {
       bucket.w[i].c=0;
       for(j=0;j<v;j++)
       {
          flag=kmp_search(bucket.w[i].s,l[j].desc);
          if(flag==1)
          {
            bucket.w[i].p[bucket.w[i].c++]=j;
          }
       }
   }
}
int kmp_search(char *pat,char *txt)
{
  int m,n,i=0,j=0;

  n=strlen(txt);
  m=strlen(pat);

  int lps[m];

  generate_lps(pat,m,lps);

  while(i<n)
  {
    if(pat[j]==txt[i])
    {
        j++;
        i++;
        if(j == m)
        {
          return(1);
          //printf("Pattern found at index %d\n",i-m);
          j=lps[j-1];
        }
    }
    else if(i<n && pat[j] != txt[i])
    {
        if(j != 0)
            j=lps[j-1];
        else
            i+=1;
    }
  }
  return(0);
}
void generate_lps(char *p,int m,int *l)
{
  int len=0,i=1;

  l[0]=0; //no proper suffix for string of length 1
  while(i<m)
  {
    if(p[i]==p[len])
    {
        len++;
        l[i]=len;
        i++;
    }
    else
    {
        if(len!=0) // Mismatched char is prefixed by things that would be in prefix of previously matched block so skip and try
        {
          len=l[len-1];
        }
        else // New char
        {
          l[i]=len;
          i++;
        }
    }

  }
}
void menu()
{
  printf("/***********************/");
  printf("\n1 Add items to Bucket List\n2 To Plan Route\n3 Edit Route Database\n4 Flush Bucket list\n5 EXIT : ");
}
void display_details(char *s,country *l,int v)
{
   int idx;
   char *token;

   token=strtok(s,",");

   while(token)
   {
      idx=search_country(token,l,v);
      if(idx!=-1)
        printf("\n%-15s%s",l[idx].name,l[idx].desc);
      token=strtok(NULL,",");
   }
   printf("\n");

}
int search_country(char *t,country *l,int v)
{
  int i;

  for(i=0;i<v;i++)
  {
      if(!strcmp(t,l[i].name))
      {
          return(i);
      }
  }
  return(-1);
}
void plan_route(weight mat[][100],int para,char *s,country *l,int v)
{
    int target[v],idx,i;
    char *token;

    for(i=0;i<v;i++)
        target[i]=1;

    so=search_country(strtok(s,","),l,v);
    path[0]=so;
    token=strtok(NULL,",");
    while(token)
    {
        idx=search_country(token,l,v);
        if(idx!=-1)
            target[idx]=0;
        token=strtok(NULL,",");
    }

    if(para==1)
    find_path_cost(mat,v,target,so,1,0,l);
    else if(para==2)
    find_path_time(mat,v,target,so,1,0,l);
}
void find_path_cost(weight mat[][100],int n,int *v,int s,int j,int cost,country *l)
{
   int i,c=cost,k=j;

   for(i=0;i<n;i++)
    {
        if(mat[s][i].cost != 0 && v[i]==0)
        {
            v[i]=1;
            path[j++]=i;
            c+=mat[s][i].cost;
            if(check(v,n))  // checks if all target vertices are covered
            {
                c+=mat[i][so].cost;  //Add the cost of returning to source from last vertex and print path
                print_path(c,j,l);
            }
            else
                find_path_cost(mat,n,v,i,j,c,l);

            v[i]=0;
            c=cost;
            j=k;
        }
    }
}
void find_path_time(weight mat[][100],int n,int *v,int s,int j,int cost,country *l)
{
   int i,c=cost,k=j;

   for(i=0;i<n;i++)
    {
        if(mat[s][i].time != 0 && v[i]==0)
        {
            v[i]=1;
            path[j++]=i;
            c+=mat[s][i].time;
            if(check(v,n))  // checks if all target vertices are covered
            {
                c+=mat[i][so].time;  //Add the time of returning to source from last vertex and print path
                print_path(c,j,l);
            }
            else
                find_path_time(mat,n,v,i,j,c,l);

            v[i]=0;
            c=cost;
            j=k;
        }
    }
}
int check(int *v,int n)
{

  int i;
  for(i=0;i<n;i++)
        if(v[i]==0)
          return(0);
  return(1);
}
void print_path(int c,int n,country *l)
{
    int i;
    counter_path++;
    if(counter_path==1 || c<final_cost)
     {
        for(i=0;i<n;i++)
         final_path[i]=path[i];
         final_cost=c;
         path_len=n;
     }
    printf("\nPossible Path(%d):",c);
    for(i=0;i<n;i++)
        printf("%s------>",l[path[i]].name);
    printf("%s",l[so].name);
}
