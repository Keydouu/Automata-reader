#include <stdio.h>
#include <stdlib.h>
#include "AutomataFunctions.h"

graph lectureDuFichier()
{
	graph Automata;
	FILE* fichier=NULL;
	printf("Le programme va utiliser l'automate qui se trouve au fichier \"graphe.txt\"\n");
	fichier=fopen("graphe.txt","r");
	if (fichier==NULL)
	{
		exit(0);
	}
	Automata.startingNodes=findStart(fichier,&Automata.startSize);
	Automata.endingNodes=findEnd(fichier,&Automata.endSize);
	Automata.linksNumber=numberOfLinks(fichier);
	Automata.Links = lectureDeGraphe(fichier,Automata.linksNumber);
	fclose(fichier);
	return Automata;
}

void viderLeBuffer(char input)
{
	while(input!=10)
	scanf("%c",&input);
}

graph lectureManuelle()
{
	graph Automata;
	int i;
	char input=0;
	printf("Quel est le nombre des etats initiaux ?\n");
	scanf("%d",&Automata.startSize);
	Automata.startingNodes=(int*)malloc(sizeof(int)*Automata.startSize);
	for(i=0;i<Automata.startSize;i++)
	{
		printf("Entrez le numero de l'état initial numero %d\n",(i+1));
		scanf("%d",(Automata.startingNodes+i));
	}
	printf("Quel est le nombre des etats finaux ?\n");
	scanf("%d",&Automata.endSize);
	Automata.endingNodes=(int*)malloc(sizeof(int)*Automata.endSize);
	for(i=0;i<Automata.endSize;i++)
	{
		printf("Entrez le numero de l'état final numero %d\n",(i+1));
		scanf("%d",(Automata.endingNodes+i));
	}
	printf("Quel est le nombre des arcs ?\n");
	scanf("%d",&Automata.linksNumber);
	Automata.Links=(link*)malloc(sizeof(link)*Automata.linksNumber);
	for(i=0;i<Automata.linksNumber;i++)
	{
		printf("Entrez l'etat de depart de l'arc numero %d\n",(i+1));
		scanf("%d",&((Automata.Links+i)->startNode));
		printf("Entrez l'etat d'arrivee l'arc numero %d\n",(i+1));
		scanf("%d",&((Automata.Links+i)->endNode));
		printf("Entrez le poid de l'arc numero %d\n",(i+1));
		viderLeBuffer(input);
		scanf("%c",&input);
		(Automata.Links+i)->weight=input;
	}
	return Automata;
}

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
	if ((input[posInput]==0)||(posInput==TAILLE_MAX_DU_INPUT))
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
