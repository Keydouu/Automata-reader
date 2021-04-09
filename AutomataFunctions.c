#include <stdio.h>
#include <stdlib.h>
#include "AutomataFunctions.h"

int lectureDeNombre (FILE* fichier, int firstNumber)
{
	char B=0;
	firstNumber-=48;
	B=fgetc(fichier);
	while(('0'<=B)&&(B<='9'))
	{
		firstNumber = firstNumber * 10 + B -48;
		B=fgetc(fichier);
	}
	return firstNumber;
}

int* findStart(FILE* fichier, int* startSize)
{
    char B=50;
    int i=1,j=0,k=0;
    int* start=0;
    while(B!=';')
    {
        B=fgetc(fichier);
        if (B==',')
        i++;
    }
    *startSize = i;
    start=(int*)malloc(sizeof(int)*i);
    if(start==0)
    {
        printf("ERROR MALLOC 3");
        exit(0);
    }
    rewind(fichier);
    while(j<i)
    {
    start[j]=0;
    while((B<'0')||(B>'9'))
    {
        B=fgetc(fichier);
    }
    start[j]=lectureDeNombre (fichier,B);
    j++;
    }
    return (start);
}

int* findEnd(FILE* fichier,int* endSize)
{
    char B=50;
    int i=1,j=0;
    int* end=0;
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
    end=(int*)malloc(sizeof(int)*i);
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
    end[j]=0;
    while((B<'0')||(B>'9'))
    {
        B=fgetc(fichier);
    }
    end[j]=lectureDeNombre (fichier,B);
    j++;
    }
    return (end);
}
int numberOfLinks(FILE* fichier)
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
    return (i);
}
link* lectureDeGraphe(FILE* fichier,int Size)
{
    char B=50;
    int j=0,k=0;
    link* linkTable =0;
    linkTable=(link*)malloc(sizeof(link)*Size);
    if(linkTable==0)
    {
        printf("ERROR MALLOC 1");
        exit(0);
    }
    while(B!='A')
    {
        B=fgetc(fichier);
    }
    while(j<Size)
    {
        while((B!='(')&&(B!=EOF))
        {
            B=fgetc(fichier);
            if((47<B)&&(B<58)&&(k==0))
                {
                	(linkTable+j)->startNode=lectureDeNombre (fichier,B);
                	k++;
                }
            else if((47<B)&&(B<58)&&(k==1))
                {
                	(linkTable+j)->endNode=lectureDeNombre (fichier,B);
                	k--;
                }

        }
        B=fgetc(fichier);
        (linkTable+j)->weight=B;
        j++;
    }
    return linkTable;
}
int traverseCheck (graph g, char* input, int posInput, int Node)//bool
{
	int i=0;
	int result = 0;//bool
	if ((input[posInput]==0)||(posInput==100))
	{
		while((i<g.endSize)&&(Node!=*(g.endingNodes+i)))
			i++;
		if (i==g.endSize)
			result = 0;
		else
			result = 1;
	}
	else
	{
		while ((result==0)&&(i<g.linksNumber))
		{
			if((g.Links+i)->startNode == Node)
			{
				if( (g.Links+i)->weight == input[posInput])
					{
                        result=traverseCheck (g,input,(posInput+1),(g.Links+i)->endNode);
					}
			}
			i++;
		}
	}
	return result;
}
