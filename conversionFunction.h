#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char *
hexconvertor (int binaryval)
{
  char *msg = (char *) malloc (sizeof (char));
  long int hexadecimalval = 0, i = 1, remainder;
  while (binaryval != 0)
    {
      remainder = binaryval % 10;
      hexadecimalval = hexadecimalval + remainder * i;
      i = i * 2;
      binaryval = binaryval / 10;
    }
  sprintf (msg, "%lX", hexadecimalval);
printf("successful end from hexconvertor\n");
  return msg;
}

char *
binaryaddition (char *bin1, char *bin2)
{

  long binary1, binary2;
  binary1 = atoi (bin1);
  binary2 = atoi (bin2);
  int i = 0, j = 0, k = 0, sum[20], remainder = 0;
  while (binary1 != 0 || binary2 != 0)
    {
      sum[i++] = (binary1 % 10 + binary2 % 10 + remainder) % 2;
      remainder = (binary1 % 10 + binary2 % 10 + remainder) / 2;
      binary1 = binary1 / 10;
      binary2 = binary2 / 10;
    }
  if (remainder != 0)
    sum[i++] = remainder;
  --i;

  char ans[i];
  for (j = i, k = 0; j >= 0; j--)
    k += sprintf (&ans[k], "%d", sum[j]);

/*   printf("\nSum of two binary numbers: %d\n",i);
	while (i >= 0)
        {
	printf("%d",sum[i]);
	i--;
	}
*/
  return hexconvertor (atoi (ans));
}
