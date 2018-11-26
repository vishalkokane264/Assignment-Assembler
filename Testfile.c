#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    char*oprand1=(char*)malloc(sizeof(char)+30);
    char *data=(char*)malloc(sizeof(char)+30);
    strcpy(data,"dword[eax+ebx*4]");
    char *p = strtok (data, "[");
    p = strtok (NULL, "+");
    p = strtok (NULL, "*");
    p = strtok (NULL, "]");
}
