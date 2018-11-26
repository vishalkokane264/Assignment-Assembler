#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int a[]={1,0,1,0,1,1,0,1,1,0,0};

char str[128];
int i=0;
int index = 0;
for (i=0; i<sizeof(a)/4; i++)
   index += snprintf(&str[index], 128-index, "%d", a[i]);

printf("%s",str);
}
