//backup from Sept29
#include<regex.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "conversionFunction.h"
#include "createlst.h"

char *
checkoprand (char *op, int lc)
{
  char *ret1 = (char *) malloc (sizeof (char) + 20);
  char *ret2 = (char *) malloc (sizeof (char) + 20);
  int i;
  if (strcmp (op, "\0") == 0)
    return "";

  for (i = 0; i < lc; i++)
    {
      if (strcmp (table[i].symname, op) == 0)
	{
	  sprintf (ret1, "sym#%d", table[i].lineno);
	  return ret1;
	}

      if (strcmp (regtab1[i].reg, op) == 0)
	{
	  sprintf (ret2, "reg#%d", regtab1[i].regid);
	  return ret2;
	}

    }

//checking condition for dword is remaining
  if(strcmp(op,"dword[]")==0)
  {
  //write code here;
  }

  if (isdigit (atoi (op)) == 0)
    {
      strcpy (littab1[lc].litname, op);
      littab1[lc].line = lc;
      sprintf (ret2, "lit#%d", littab1[lc].line);
      return ret2;
    }

}

int
separatelitrals (char *str, int lc)
{
  int i;
  littab1[lc].line = lc;
  char *p = strtok (str, ",");
  strcpy (littab1[i].litname, p);
  while (p != NULL)		//for separate out oprand1 and oprand2
    {
      i++;
      strcpy (littab1[i].litname, p);
      p = strtok (NULL, ",");
      fprintf (fp2, "%s ", littab1[i].litname);
    }				//end while of separate oprand
  fprintf (fp2, "\n");
}

int
main (int argc, char *argv[])
{
  char *data = (char *) malloc (sizeof (char) + 20);

  strcpy (fname, argv[1]);
  fp = fopen (fname, "r");
  if (fp == NULL)
    {
      printf ("<%s> File opening error\n", argv[1]);
      exit (0);
    }

  fp3 = fopen ("My_register", "r");
  if (fp3 == NULL)
    {
      printf ("<My_register> File opening error\n");
      exit (0);
    }
  while (fgets (buffer1, 80, fp3) != NULL)
    {
      sscanf (buffer1, "%s%s%s%s", t1, t2, t3, t4);
      n2 = atoi (t1);
      regtab1[n1].regid = n2;
      strcpy (regtab1[n1].reg, t2);
      strcpy (regtab1[n1].bval, t3);
      n2 = atoi (t4);
      regtab1[n1].bit = n2;
      n1++;
    }
  fclose (fp3);

  fp4 = fopen (file1, "w+");	//for printing symbol table
  n1 = 0;
  n1 = 0;
  fp2 = fopen (file4, "w+");	//intermediate file
  fp3 = fopen (file3, "w+");	//error table file
  int lc = 1;
  while (fgets (buffer1, 80, fp))
    {
      n1 = sscanf (buffer1, "%s%s%s", t1, t2, t3);
      if (strcmp (t1, "section") == 0)
	{
	  if (strcmp (t2, ".data") == 0)
	    {
	      flag1 += 1;
	      fprintf (fp2, "%d\t%s\t%s\n", lc, t1, t2);
	      strcpy (section, t2);
	      optab1[lc].line = lc;
	      table[lc].lineno = lc;
	      while (fgets (buffer1, 80, fp))
		{
		  lc++;
		  n1 = sscanf (buffer1, "%s%s%s", t1, t2, t3);
		  if ((n1 > 2 || n1 == 2) && (strcmp (t2, "dd") == 0)
		      || (strcmp (t1, "dd") == 0))
		    {
		      cntdd = 0;
		      if (n1 == 2 && strcmp (t1, "dd") == 0)
			{
			  strcpy (t3, t2);
			  strcpy (t2, t1);
			  strcpy (t1, "");
			}
		      len = strlen (t3);
		      for (i = 0; i <= len; i++)
			{
			  if (t3[i] == ',')
			    cntdd++;
			  if (t3[i] != ',' && i == len)
			    cntdd++;
			}
		      strcpy (table[lc].symname, t1);
		      strcpy (table[lc].type, "dd");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      table[lc].tot_char = cntdd;
		      strcpy (table[lc].data, t3);
		      table[lc].size = dd;
		      table[lc].lineno = lc;
		      sprintf (data, "%d\t%s\t%s\t", lc, table[lc].symname,
			       table[lc].type);
		      fprintf (fp2, "%s", data);
		      strcpy (data, "\0");
//              printf("%d\t%s\t%s\t",lc,table[lc].symname,table[lc].type);
		      separatelitrals (t3, lc);
		      table[lc].address = addr;
		      addr = addr + (dd * cntdd);
		    }		//end of dd

		  if ((n1 > 2 || n1 == 2) && (strcmp (t2, "dq") == 0)
		      || (strcmp (t1, "dq") == 0))
		    {
		      cntdd = 0;
		      if (n1 == 2 && strcmp (t1, "dq") == 0)
			{
			  strcpy (t3, t2);
			  strcpy (t2, t1);
			  strcpy (t1, "");
			}
		      len = strlen (t3);
		      for (i = 0; i <= len; i++)
			{
			  if (t3[i] == ',')
			    cntdd++;
			  if (t3[i] != ',' && i == len)
			    cntdd++;
			}
		      strcpy (table[lc].symname, t1);
		      strcpy (table[lc].type, "dq");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].data, t3);
		      table[lc].lineno = lc;
		      table[lc].tot_char = cntdd;
		      table[lc].size = dq;
		      sprintf (data, "%d\t%s\t%s\t", lc, table[lc].symname,
			       table[lc].type);
		      fprintf (fp2, "%s", data);
		      separatelitrals (t3, lc);
		      table[lc].address = addr;
		      addr = addr + (dq * cntdd);
		    }		//end of dq

		  if (n1 > 2 && strcmp (t2, "db") == 0)
		    {
		      i = 0;
		      j = 0;
		      len = 0;
		      cntdb = 0;
		      len = strlen (t1) + 1 + strlen (t2) + 2;
		      for (i = len, j = 0; buffer1[i] != '\0'; i++, j++)
			{
			  t3[j] = buffer1[i];
			}
		      len = strlen (t3);
		      cntdb = 0;
		      for (i = 0; i < len; i++)
			{
			  if (t3[i] == '"')
			    cntdb++;
			  if (t3[i] == ',')
			    cntdb++;
			  if (t3[i] == ',' && t3[i + 1] == '1'
			      && (t3[i + 2] == '0' || t3[i + 2] == '3'))
			    cntdb++;
			}
		      cntdb = len - cntdb;
		      table[lc].lineno = lc;
		      strcpy (table[lc].symname, t1);
		      strcpy (table[lc].type, "db");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].data, t3);
		      table[lc].tot_char = cntdb;
		      table[lc].size = db;
		      for (i = 0; i < 80; i++)	//for emptying t3
			{
			  t3[i] = '\0';
			  buffer1[i] = '\0';
			}
		      fprintf (fp2, "%d\t%s\t%s\t%s", lc, table[lc].symname,
			       table[lc].type, table[lc].data);
//              printf("%d\t%s\t%s\t%s\n",lc,table[lc].symname,table[lc].type,table[lc].data);
//              separatelitrals(t3,lc);
		      table[lc].address = addr;
		      addr = addr + (db * cntdb);
		    }		//end of db

		  if (strcmp (t1, "section") == 0)
		    {
		      table[lc].lineno = lc;
		      break;
		    }
		  if ((strcmp (t2, "dd") != 0) && (strcmp (t2, "db") != 0)
		      && (strcmp (t2, "dq") != 0) && (strcmp (t2, "dw") != 0))
		    {
		      errtab1[lc].line = lc;
		      sprintf (errmsg, "line %d:Invalid opcode\n", lc);
		      printf ("%s", errmsg);
		      strcpy (errtab1[lc].error, errmsg);
		      fprintf (fp3, "line %d:Invalid opcode\n", lc);
		    }
		}		//end of while in data
	    }			//end of data section

	  if (strcmp (t2, ".bss") == 0)
	    {
	      addr = 0;
	      flag1 += 1;
	      strcpy (section, t2);
	      fprintf (fp2, "%d\t%s\t%s\n", lc, t1, t2);

	      while (fgets (buffer1, 80, fp))
		{
		  lc++;
		  n1 = sscanf (buffer1, "%s%s%s", t1, t2, t3);
		  if (n1 == 3 && strcmp (t2, "resd") == 0)	//for labels
		    {
		      strcpy (table[lc].symname, t1);
		      table[lc].tot_char = atoi (t3);
		      strcpy (table[lc].type, t2);
		      table[lc].size = resd;
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].data, t3);
		      table[lc].lineno = lc;
		      table[lc].address = addr;
		      addr += (resd * atoi (t3));
		      strcpy (t3, "");
		      fprintf (fp2, "%d\t%s\t%s\t%s\n", lc, table[lc].symname,
			       table[lc].type, table[lc].data);
		    }		//end of resd

		  if (n1 == 3 && strcmp (t2, "resb") == 0)	//for labels
		    {
		      int temp;
		      strcpy (table[lc].symname, t1);
		      table[lc].tot_char = atoi (t3);
		      strcpy (table[lc].type, t2);
		      table[lc].size = resb;
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].data, t3);
		      table[lc].lineno = lc;
		      table[lc].address = addr;
		      addr += (resb * atoi (t3));
		      strcpy (t3, "");
		      fprintf (fp2, "%d\t%s\t%s\t%s\n", lc, table[lc].symname,
			       table[lc].type, table[lc].data);
		    }		//end of resb

		  if (n1 == 3 && strcmp (t2, "resq") == 0)	//for labels
		    {
		      int temp;
		      strcpy (table[lc].symname, t1);
		      table[lc].tot_char = atoi (t3);
		      strcpy (table[lc].type, t2);
		      table[lc].size = resq;
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].data, t3);
		      table[lc].lineno = lc;
		      table[lc].address = addr;
		      addr += (resd * atoi (t3));
		      fprintf (fp2, "%d\t%s\t%s\t%s\n", lc, table[lc].symname,
			       table[lc].type, table[lc].data);
		      strcpy (t3, "");
		    }		//end of resd

		  if (n1 == 3 && strcmp (t2, "resw") == 0)	//for labels
		    {
		      strcpy (table[lc].symname, t1);
		      table[lc].tot_char = atoi (t3);
		      strcpy (table[lc].type, t2);
		      table[lc].size = resw;
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "s");
		      strcpy (table[lc].section, section);
		      strcpy (table[lc].data, t3);
		      table[lc].lineno = lc;
		      table[lc].address = addr;
		      addr = addr + (resw * atoi (t3));
		      strcpy (t3, "");
		      fprintf (fp2, "%d\t%s\t%s\t%s\n", lc, table[lc].symname,
			       table[lc].type, table[lc].data);

		    }		//end of resw

		  if (strcmp (t1, "section") == 0)
		    {
		      table[lc].lineno = lc;
		      break;
		    }
		  if ((strcmp (t2, "resd") != 0) && (strcmp (t2, "resq") != 0)
		      && (strcmp (t2, "resw") != 0)
		      && (strcmp (t2, "resb") != 0))
		    {
		      fprintf (fp3, "line %d:Invalid opcode\n", lc);
		      sprintf (errmsg, "line %d:Invalid opcode\n", lc);
		      printf ("%s", errmsg);
		      errtab1[lc].line = lc;
		      strcpy (errtab1[lc].error, errmsg);
		    }

		}		//end of while in bss
	    }			//end of bss section


	  if (strcmp (t2, ".text") == 0)
	    {
	      flag1 += 1;
	      strcpy (section, t2);
	      fprintf (fp2, "%d\t%s\t%s\n", lc, t1, t2);
	      while (fgets (buffer1, 80, fp))
		{
		  lc++;
		  table[lc].lineno = lc;
		  n1 = sscanf (buffer1, "%s%s", t1, t2);
		  len = strlen (t1);
		  strcpy (tempt1, t1);
		  if (t1[len - 1] == ':')	//validation of labels
		    {
		      /*if(strcmp(strtok(t1,":"),"section")==0||strcmp(strtok(t1,":"),"global")==0)
		         {
		         sprintf(errmsg,"Line%d:Invalid label\n",lc);
		         errtab1[lc].line=lc;
		         strcpy(errtab1[lc].error,errmsg);
		         }
		       */

		      table[lc].lineno = lc;
		      strcpy (optab1[lc].opname, tempt1);
		      strcpy (table[lc].symname, strtok (t1, ":"));
		      strcpy (table[lc].defundef, "d");
		      strcpy (table[lc].sym_or_lab, "l");
		      strcpy (table[lc].section, section);
		      optab1[lc].line = lc;
		      fprintf (fp2, "%d\t%s\n", lc, optab1[lc].opname);
		    }
		  else if (strcmp (t1, "global") == 0)
		    {
		      fprintf (fp2, "%d\t%s\t%s\n", lc, t1, t2);
		    }
		  else if (strcmp (t1, "extern") == 0)
		    {
		      fprintf (fp2, "%d\t%s\t%s\n", lc, t1, t2);
		    }

		  else
		    {
		      strcpy (optab1[lc].opname, t1);
		      char *temp[2];
		      optab1[lc].line = lc;
		      if (strcmp (t1, "jmp") == 0 || strcmp (t1, "jz") == 0)
			{
			  for (i = 0; i <= lc; i++)
			    {
			      flag = 0;
			      if (strcmp (table[i].symname, oprand1[lc]) == 0)
				{
				  strcpy (table[i].defundef, "v");
				  strcpy (table[i].sym_or_lab, "l");
				  flag = 1;
				  break;
				}
			    }
			  if (flag == 0)	//if label is use before declaring
			    {
			      table[lc].lineno = lc;
			      strcpy (optab1[lc].opname, oprand1[lc]);
			      strcpy (table[lc].symname, oprand1[lc]);
			      strcpy (table[lc].defundef, "u");
			      strcpy (table[lc].sym_or_lab, "l");
			      strcpy (table[lc].section, section);
			      optab1[lc].line = lc;
			      fprintf (fp2, "%d\t<%d>\n", lc,
				       table[lc].lineno);
			      break;
			    }
			}	//end if of jump validation


		      char *p = strtok (t2, ",");
		      strcpy (oprand1[lc], p);
		      p = strtok (NULL, "\0");
		      while (p != NULL)	//for separate out oprand1 and oprand2
					{
					  strcpy (oprand2[lc], p);
			  		p = strtok (NULL, "\n");
					}	//end while of separate oprand
          
					printf("%d\t%s\t%s\n",lc,oprand1[lc],oprand2[lc]);
		      fprintf (fp2, "%d\t%s\t%s\t%s\n", lc, optab1[lc].opname,
   	      checkoprand (oprand1[lc], lc),
			    checkoprand (oprand2[lc], lc));
		      optab1[lc].line = lc;
		    }
		}		//end of while in text

	    }			//end of text section
	}
      if (flag1 != 3)		//for checking all section are present or not
	{
	  fprintf (fp3, "section missing\n");
	  sprintf (errmsg, "section missing\n");
	  printf ("%s", errmsg);
	  errtab1[lc].line = lc;
	  strcpy (errtab1[lc].error, errmsg);
	}

    }

  fprintf (fp4,
	   "lineno\tsymname\ttype\tsize\ttot_chr\tdef\tsorl\taddress\tsection\tdata\n");
  for (i = 1; i <= lc; i++)
    {
      fprintf (fp4, "%d\t%s\t%s\t%d\t%d\t%s\t%s\t%d\t%s\t%s\n",
	       table[i].lineno, table[i].symname, table[i].type,
	       table[i].size, table[i].tot_char, table[i].defundef,
	       table[i].sym_or_lab, table[i].address, table[i].section,
	       table[i].data);
    }
  fclose (fp4);
  fp4 = fopen (file3, "w+");	//for error table
  fprintf (fp4, "lineno\tError\n");
  for (i = 1; i <= lc; i++)
    {
      fprintf (fp4, "%d\t%s\n", errtab1[i].line, errtab1[i].error);
    }
  fclose (fp4);
  fp4 = fopen (file2, "w+");
//printf("opcode\n");
  for (i = 0; i <= lc; i++)
    {
      if (littab1[i].line != 0)
	fprintf (fp4, "%d\t%s\t%s\n", littab1[i].line, littab1[i].litnamehex,
		 littab1[i].litname);
    }
  fclose (fp4);
  flag = 1;
  for (i = 1; i < lc; i++)
    {
      if (strcmp (errtab1[i].error, "\0") != 0)
	{
	  flag = 0;
	  break;
	}
    }
  if (flag == 0)
    {
      remove (file4);		//if errors then remove intermediate file
    }

  fclose (fp);
  fclose (fp2);
  fclose (fp3);

  if (flag == 1)
    {
      char *op = file4;
      createlst (op, lc);
    }
  printf ("successful end from assembler.c\n");
}
