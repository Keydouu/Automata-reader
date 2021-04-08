#include <stdio.h>
#include <stdlib.h>
#include "FdeGraph.h"

char* findStart(FILE* fichier, int* startSize)
{
    char B=50;
    int i=1,j=0;
    char* start=0;
    while(B!=';')
    {
        B=fgetc(fichier);
        if (B==',')
        i++;
    }
    *startSize = i;
    start=(char*)malloc(sizeof(char)*i);
    if(start==0)
    {
        printf("ERROR MALLOC 3");
        exit(0);
    }
    rewind(fichier);
    while(j<i)
    {
    while((B<'0')||(B>'9'))
    {
        B=fgetc(fichier);
    }
    start[j]=B;
    B=fgetc(fichier);
    printf("S : %c\n",start[j]);
    j++;
    }
    return (start);
}

char* findEnd(FILE* fichier,int* endSize)
{
    char B=50;
    int i=1,j=0;
    char* end=0;
    while(B!='E')
    {
        B=fgetc(fichier);
    }
    while(B!=';')
    {
        B=fgetc(fichier);
        if (B==',')
        i++;
    }
    *endSize = i;
    end=(char*)malloc(sizeof(char)*i);
    if(end==0)
    {
        printf("ERROR MALLOC 2");
        exit(0);
    }
    rewind(fichier);
    while(B!='E')
    {
        B=fgetc(fichier);
    }
    while(j<i)
    {
    while((B<'0')||(B>'9'))
    {
        B=fgetc(fichier);
    }
    end[j]=B;
    B=fgetc(fichier);
    printf("E : %c\n",end[j]);
    j++;
    }
    return (end);
}
int tailleDeGraph(FILE* fichier)
{
    char B=50;
    int i=0;
    while(B!=EOF)
    {
        B=fgetc(fichier);
        if (B==')')
            i++;
    }
    rewind(fichier);
    printf("T = %d\n",i);
    return (i*3);
}

char* lectureDeGraphe(FILE* fichier,int i)
{
    char B=50;
    int j=0,k=0;
    char* graph=0;
    graph=(char*)malloc(sizeof(char)*i);
    if(graph==0)
    {
        printf("ERROR MALLOC 1");
        exit(0);
    }
    while(B!='A')
    {
        B=fgetc(fichier);
    }
    while(j<i)
    {
        while((B!='(')&&(B!=EOF))
        {
            B=fgetc(fichier);
            if((47<B)&&(B<58)&&(k==0))
                {*(graph+j)=B;k++;}
            if((47<B)&&(B<58)&&(k==2))
                {*(graph+j+1)=B;k=0;}
            if(k==1)
                k++;
        }
        B=fgetc(fichier);
        *(graph+j+2)=B;
        fseek(fichier,4, SEEK_CUR);
        j=j+3;
    }
    return graph;
}

