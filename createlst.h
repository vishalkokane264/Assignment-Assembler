#include<stdio.h>
#include<regex.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"conversionFunction.h"
#define file1 "Output/file.Symbol"
#define file2 "Output/file.Litral"
#define file3 "Output/file.Error"
#define file4 "Output/file.Interm"

#define db 1
#define dd 4
#define dq 8
#define resd 4
#define resb 1
#define resw 2
#define resq 8
int createlst(char*fname,int lc);
int separatelitrals(char *op,int c);
char *checkoprand(char *op,int c);
int len,cntdd,cntdb,addr=0;

FILE *fp,*fp2,*fp3,*fp4;

int flag=0,flag1=0;
int i,j,n1,n2,bufflen1,bufflen2,addr;
char buffer1[80],buffer2[80], t1[40], t2[40], t3[40], t4[40], section[20],tempt1[10];
char oprand1[50][50],oprand2[50][50],temp[10],op1[20],op2[20];
char regtable[][10]={"eax","ecx","edx","ebx","esp","edp","esi","edi"};
char errmsg[80];

typedef struct optab
{
  char opname[10];
  int line;
}optab;

typedef struct fileoptable
{
  int bit;
  int value;
  char opname[10];
}foptab;

typedef struct littab
{
  int line;
  char litnamehex[50];
  char litname[50];
}littab;

typedef struct errtab
{
  int line;
  char error[80];
}errtab;

typedef struct symtab
{
  int lineno;
  char symname[10];
  char type[5];
  int size;
  int tot_char;
  char defundef[1];
  char sym_or_lab[1];
  int address;
  char section[8];
  char data[80];
} symtab;

typedef struct regtab
{
  int regid;
  char reg[4];
  char bval[4];
  int bit;
} regtab;

char fname[20];

  symtab table[80];
  optab optab1[80];
  foptab foptab1[80];
  littab littab1[80];
  regtab regtab1[80];
  errtab errtab1[80];

int createlst(char*fname,int lc)
{
  FILE *fp4=fopen("Output/file.Objcode","w+");
  char p3[50],*p,*p1;
  char oprand3[50],oprand4[50],oprand5[50],oprand6[50];
  for(i=0;i<100;i++)
  {
    strcpy(oprand1[i],"\0");
    strcpy(oprand2[i],"\0");
  }

  int z=0;
  int no1=lc;
  int i,j,k;
  fp3=fopen("My_opcode","r");
  n1=0;
  while (fgets(buffer1, 80, fp3))
  {
      n1++;
      sscanf(buffer1,"%s\t%s\t%s",t1,t2,t3);
      foptab1[n1].value=atoi(t2);
      foptab1[n1].bit=atoi(t3);
      strcpy(foptab1[n1].opname,t1);
  }
  fclose(fp3);

  FILE *fp=fopen(fname,"r");
  if(fp==NULL)
  printf("empty file\n");
  else
  {
    while(fgets(buffer1,80,fp))   //while1
    {
      z++;
      n1=sscanf(buffer1,"%s%s%s%s",t1,t2,t3,t4);
      if((strcmp(t2,"section")==0)&&(strcmp(t3,".text")==0))
      {
        while(fgets(buffer1,80,fp)) //while2
        {
          z++;
          n1=sscanf(buffer1,"%s%s%s%s",t1,t2,t3,t4);
/*
        oprands
        /     \
      t3       t4
     /  \     /  \
  op3  op4*  op5  op6*
  (oprand1)  (oprand2)
*/
          if((strcmp(t3,"\0")!=0) &&(strcmp(t4,"\0")!=0))
          {
            p=strtok(t3,"#");
            strcpy(oprand3,p);//copying first oprand
            p=strtok(NULL,"\0");

            p1=strtok(t4,"#");
            strcpy(oprand5,p1);//copying second oprand
            p1=strtok(NULL,"\0");
            while(p!=NULL)  //for separate out oprand3 and oprand4
              {
                strcpy(oprand4,p);
                p=strtok(NULL,",");
              }//end while of separate oprand

            while(p1!=NULL)  //for separate out oprand5 and oprand6
              {
                strcpy(oprand6,p1);
                p1=strtok(NULL,",");
              }//end while of separate oprand

//              if(strcmp(oprand3,"reg")==0 && (strcmp(oprand5,"lit")==0|| strcmp(oprand5,"sym")==0))  //<instr>reg, imm32
//              {
                if(strcmp(t2,"mov")==0 &&(strcmp(oprand5,"lit")==0)&&(regtab1[atoi(oprand4)].regid>=0 && regtab1[atoi(oprand4)].regid<=7))//<instr>=mov 
                {
                  sprintf(p3,"%s%x\n",binaryaddition("10111000",regtab1[atoi(oprand4)].bval),atoi(littab1[atoi(oprand6)].litname));//B8+rd id
                  fprintf(fp4,"%d\t%s",z,p3);
                }

                if(strcmp(t2,"mov")==0 &&(strcmp(oprand5,"sym")==0)&&(regtab1[atoi(oprand4)].regid>=0 && regtab1[atoi(oprand4)].regid<=7))//<instr>=mov 
                {
                  sprintf(p3,"%s<%x>\n",binaryaddition("10111000",regtab1[atoi(oprand4)].bval),table[atoi(oprand6)].lineno);//B8+rd id
                  fprintf(fp4,"%d\t%s",z,p3);
                }


              if(strcmp(oprand3,"reg")==0 && strcmp(oprand5,"reg")==0)//<instr>reg,reg
              {
                i=atoi(oprand4);
                j=atoi(oprand6);
                sprintf(p3,"11%s%s",regtab1[j].bval,regtab1[i].bval);
                strcpy(p3,hexconvertor(atoi(p3)));
                k=foptab1[i].value;
                fprintf(fp4,"%d\t%d%s\n",z,k,p3);
                //call to hexconvert here...
//                printf("%s\n",p3);            
//                strcpy(p3,"\0");
              }
              if(strcmp(t1,"jmp")==0||strcmp(t1,"jz")==0)
            	{
			          fprintf(fp4,"%d\t<%d>\n",z,atoi(p3));
            	}
          }          
          strcpy(oprand3,"\0");
          strcpy(oprand4,"\0");
          strcpy(oprand5,"\0");
          strcpy(oprand6,"\0");
          strcpy(t2,"\0");
          strcpy(t3,"\0");
          strcpy(t4,"\0");  
        } //end of while2
      }
      else
      {
        strcpy(t2,"\0");
        strcpy(t3,"\0");
        strcpy(t4,"\0");
      }
    }//end of while1
  }//end of else
  fclose(fp4);
printf("successful end from createlst\n");
  return 0;
}
