#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{char name[200][500];}CVS;
void tokenize(char *string,CVS *list,int order,int *size)
{
  int i=0;
  for(char *address=strtok(string,";");address;address=strtok(NULL,";"))
  {
    strcpy(list[i++].name[order],address);
  }
  *size=i;
}
int compare(char *str1,char *str2)
{
  for(char c1,c2;*str1 && *str2;str1++,str2++)
  {
    c1=tolower(*str1);
    c2=tolower(*str2);
    if(c1<c2){return -1;} 
    else if(c1>c2){return 1;}
  }
  return *str1 ? 1:(*str2 ? -1:0);
}
void sort_csv_columns(char *FILE,char *OUT)
{
  CVS *list=calloc(100,sizeof(CVS));
  int *size=calloc(1,4),i=0;
  char string[strlen(FILE)+1],NAME[200][5000];
  strcpy(string,FILE);
  for(char *address=strtok(string,"\n");address;address=strtok(NULL,"\n"),i++)
  {
    strcpy(NAME[i],address);
  }
  for(int j=0;j<i;j++)
  {
    tokenize(NAME[j],list,j,size);
  }
  int array[*size],t;
  for(int j=0;j<*size;array[j]=j,j++);
  for(int j=0;j<*size;j++)
  {
    for(int k=j+1;k<*size;k++)
    {
      if(compare(list[array[j]].name[0],list[array[k]].name[0])==1)
      {
        t=array[j];
        array[j]=array[k];
        array[k]=t;
      }
    }
  }
  *OUT='\0';
  for(int k=0;k<i;k++)
  {
    for(int j=0;j<*size;j++)
    {
      strcat(OUT,list[array[j]].name[k]);
      strcat(OUT,";");
    }
    OUT[strlen(OUT)-1]='\0';
    strcat(OUT,"\n");
  }
  OUT[strlen(OUT)-1]='\0';
}
