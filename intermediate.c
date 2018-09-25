#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define db 1
#define dd 4
#define dq 8
#define resd 4
#define resb 1
#define resw 2
#define resq 8
char *checkoprand(char *op,int c);
int len,cntdd,cntdb,addr=0;
FILE *fp ;
FILE *fp2;

int flag=0;
int i,j,n1,n2,bufflen1,bufflen2,addr;
char buffer1[80],buffer2[80], t1[40], t2[40], t3[40], section[20],tempt1[10];
char oprand1[50][50],oprand2[50][50],temp[10],op1[20],op2[20];
char regtable[][10]={"eax","ecx","edx","ebx","esp","edp","esi","edi"};

typedef struct optab
{
  char opname[10];
  int line;
}optab;


typedef struct littab
{
  int line;
  char litname[10];
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


char fname[20];

  symtab table[80];
  optab optab1[80];
  littab littab1[80];

int
main (int argc, char *argv[])
{

  strcpy (fname, argv[1]);
  fp= fopen (fname, "r");
  fp2=fopen("assemble.i","w+");
  int lc = 1;
  while (fgets (buffer1, 80, fp))
    {
      n1=sscanf(buffer1,"%s%s%s",t1,t2,t3);
      if(strcmp(t1,"section")==0)
      {
        if(strcmp(t2,".data")==0)
        {
          fprintf(fp2,"%d\t%s\t%s\n",lc,t1,t2);
          strcpy(section,t2);
          while(fgets(buffer1,80,fp))
          {
            lc++;
            n1=sscanf(buffer1,"%s%s%s",t1,t2,t3);
            if((n1>2 ||n1==2) && (strcmp(t2,"dd")==0)||(strcmp(t1,"dd")==0))
            {
              cntdd=0;
              if(n1==2 && strcmp(t1,"dd")==0)
              {
                strcpy(t3,t2);
                strcpy(t2,t1);
                strcpy(t1,"");
              }
              len=strlen(t3);
              for(i=0;i<=len;i++)
              {
               if(t3[i]==',')
               cntdd++;
               if(t3[i]!=',' && i==len)
               cntdd++;
              }
              strcpy(table[lc].symname,t1);
              strcpy(table[lc].type,"dd");
              strcpy(table[lc].section,section);
              strcpy(table[lc].defundef,"d");
              strcpy(table[lc].sym_or_lab,"s");
              table[lc].tot_char=cntdd;
              strcpy(table[lc].data,t3);
              table[lc].size=dd;
              table[lc].lineno=lc;
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
              table[lc].address=addr;
              addr=addr+dd*cntdd;
            }//end of dd

              if((n1>2 ||n1==2) && (strcmp(t2,"dq")==0)||(strcmp(t1,"dq")==0))
              {
                cntdd=0;
               if(n1==2 && strcmp(t1,"dq")==0)
               {
                strcpy(t3,t2);
                strcpy(t2,t1);
                strcpy(t1,"");
               }
               len=strlen(t3);
               for(i=0;i<=len;i++)
                {
                  if(t3[i]==',')
                    cntdd++;
                  if(t3[i]!=',' && i==len)
                    cntdd++;
                }
              strcpy(table[lc].symname,t1);
              strcpy(table[lc].type,"dq");
              strcpy(table[lc].section,section);
              strcpy(table[lc].defundef,"d");
              strcpy(table[lc].sym_or_lab,"s");
              strcpy(table[lc].data,t3);
              table[lc].lineno=lc;
              table[lc].tot_char=cntdd;
              table[lc].size=dq;
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
              table[lc].address=addr;
              addr=addr+dq*cntdd;
            } //end of dq
 
            if(n1>2 && strcmp(t2,"db")==0)
              {
                i=0;j=0;len=0;cntdb=0;
                len=strlen(t1)+1+strlen(t2)+1;
                for(i=len,j=0;buffer1[i]!='\0';i++,j++)
                {
                  t3[j]=buffer1[i];
                }
                len=strlen(t3);
//                printf("%s",t3);
                cntdb=0;
                for(i=0;i<len;i++)
                {
                  if(t3[i]=='"')
                  cntdb++;
                  if(t3[i]==',')
                  cntdb++;
                  if(t3[i]==',' && t3[i+1]=='1' && (t3[i+2]=='0'||t3[i+2]=='3'))
                  cntdb++;
                }
              table[lc].lineno=lc;
                strcpy(t3,"");
                strcpy(buffer1,"");
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
              }//end of db
              if(strcmp(t1,"section")==0)
              {
                break;
              }
         }//end of while in data
        }//end of data section

        if(strcmp(t2,".bss")==0)
        {
          strcpy(section,t2);
          fprintf(fp2,"%d\t%s\t%s\n",lc,t1,t2);

          while(fgets(buffer1,80,fp))
          {
            lc++;
            n1=sscanf(buffer1,"%s%s%s",t1,t2,t3);
            if (n1 == 3 && strcmp (t2, "resd") == 0)	//for labels
          	{
	            strcpy(table[lc].symname,t1);
	            table[lc].tot_char=1;
          	  strcpy(table[lc].type,t2);
	            table[lc].size=resd;
	            strcpy(table[lc].defundef,"d");
	            strcpy(table[lc].sym_or_lab,"s");
	            strcpy(table[lc].section,section);
              strcpy(table[lc].data,t3);
              table[lc].lineno=lc;
              strcpy(t3,"");
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
          	}//end of resd

            if (n1 == 3 && strcmp (t2, "resb") == 0)	//for labels
          	{
	            strcpy(table[lc].symname,t1);
	            table[lc].tot_char=1;
          	  strcpy(table[lc].type,t2);
	            table[lc].size=resb;
	            strcpy(table[lc].defundef,"d");
	            strcpy(table[lc].sym_or_lab,"s");
	            strcpy(table[lc].section,section);
              strcpy(table[lc].data,t3);
              table[lc].lineno=lc;
              strcpy(t3,"");
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
          	}//end of resb

            if (n1 == 3 && strcmp (t2, "resq") == 0)	//for labels
          	{
	            strcpy(table[lc].symname,t1);
	            table[lc].tot_char=1;
          	  strcpy(table[lc].type,t2);
	            table[lc].size=resq;
	            strcpy(table[lc].defundef,"d");
	            strcpy(table[lc].sym_or_lab,"s");
	            strcpy(table[lc].section,section);
              strcpy(table[lc].data,t3);
              table[lc].lineno=lc;
              strcpy(t3,"");
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);

          	}//end of resd

            if (n1 == 3 && strcmp (t2, "resw") == 0)	//for labels
          	{
	            strcpy(table[lc].symname,t1);
	            table[lc].tot_char=1;
          	  strcpy(table[lc].type,t2);
	            table[lc].size=resw;
	            strcpy(table[lc].defundef,"d");
	            strcpy(table[lc].sym_or_lab,"s");
	            strcpy(table[lc].section,section);
              strcpy(table[lc].data,t3);
              table[lc].lineno=lc;
              strcpy(t3,"");
              fprintf(fp2,"%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);

          	}//end of resw

              if(strcmp(t1,"section")==0)
              {
                break;
              }

          }//end of while in bss
        }//end of bss section

        if(strcmp(t2,".text")==0)
        {
          strcpy(section,t2);
          fprintf(fp2,"%d\t%s\t%s\n",lc,t1,t2);
          while(fgets(buffer1,80,fp))
          {
            lc++;
            n1=sscanf(buffer1,"%s%s",t1,t2);
            len=strlen(t1);
            strcpy(tempt1,t1);
            if(t1[len-1]==':')//validation of labels
              {
                table[lc].lineno=lc;
                strcpy(optab1[lc].opname,tempt1);
                strcpy(table[lc].symname,strtok(t1,":"));
	              strcpy(table[lc].defundef,"d");
	              strcpy(table[lc].sym_or_lab,"l");
	              strcpy(table[lc].section,section);
                optab1[lc].line=lc;
                fprintf(fp2,"%d\t%s\n",lc,optab1[lc].opname);
              }
              else if(strcmp(t1,"global")==0)
              {
                fprintf(fp2,"%d\t%s\t%s\n",lc,t1,t2);
              }
            else
              {
                strcpy(optab1[lc].opname,t1);
                char *temp[2];
                optab1[lc].line=lc;
                char *p=strtok(t2,",");
                strcpy(oprand1[lc],p);
		            while(p!=NULL)  //for separate out oprand1 and oprand2
                  {
                      strcpy(oprand2[lc],p);
		                  p=strtok(NULL,"\n");
                  }//end while of separate oprand
                if(strcmp(t1,"jmp")==0||strcmp(t1,"jmp")==0)
                  {
                  for(i=0;i<=lc;i++)
                  {
                    flag=0;
                    if(strcmp(table[i].symname,oprand1[lc])==0)
                    { 
       	              strcpy(table[i].defundef,"v");
      	              strcpy(table[i].sym_or_lab,"l");
                      flag=1;
                      break;
                    }
                  }
                    if(flag==0)//if label is use before declaring
                    {
                      table[lc].lineno=lc;
                      strcpy(optab1[lc].opname,oprand1[lc]);
                      strcpy(table[lc].symname,oprand1[lc]);
	                    strcpy(table[lc].defundef,"u");
	                    strcpy(table[lc].sym_or_lab,"l");
	                    strcpy(table[lc].section,section);
                      optab1[lc].line=lc;
                      fprintf(fp2,"%d\t%s\n",lc,table[lc].symname);
                    }
                }//end if of jump validation
                fprintf(fp2,"%d\t%s\t%s\t%s\n",optab1[lc].line,optab1[lc].opname,checkoprand(oprand1[lc],lc),checkoprand(oprand2[lc],lc));
              
              }   
          }//end of while in text
        }//end of text section
      }
}
for(i=1;i<=lc;i++)
printf("%d\t%s\t%s\t%d\t%d\t%s\t%s\t%d\t%s\t%s\n",table[i].lineno,table[i].symname,table[i].type,table[i].size, table[i].tot_char,table[i].defundef,table[i].sym_or_lab,table[i].address, table[i].section,table[i].data);
printf("opcode\n");
for(i=1;i<lc;i++)
printf("%d %s\n",optab1[i].line,optab1[i].opname);

    fclose(fp);
    fclose(fp2);
}


char *checkoprand(char * op,int lc)
{
  char *ret1=(char*)malloc(sizeof(char)+20);
  char *ret2=(char*)malloc(sizeof(char)+20);
  int i=0;
  for(i=0;i<lc;i++)
  {
    if(strcmp(table[i].symname,op)==0)
    {
      sprintf(ret1,"sym%d",table[i].lineno);
      return ret1;       
    }
    if(strcmp(regtable[i],op)==0)
    {
     sprintf(ret2,"reg%d",i);
     return ret2;       
    }
  }
  return "";
}
