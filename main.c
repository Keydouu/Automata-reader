#include <stdio.h>
#include <stdlib.h>
#include "FdeGraph.h"
int main()
{
    int taille,i=0,j=0,k=0,l,startSize,endSize,nPos=0,getOut=0;
    FILE* fichier=NULL;
    char motEntre[100],uniquePosAct;
    char *graph, *end, *start, *posAct;
    int *exitDoor;
    while(i<100)
    {
        motEntre[i]=0;
        i++;
    }
    i=0;
    fichier=fopen("graphe.txt","r");
    if (fichier==NULL)
    {
        exit(0);
    }
    start=findStart(fichier,&startSize);
    printf("start = %s",start);
    end=findEnd(fichier,&endSize);
    printf("startsize = %d while endSize = %d\n",startSize,endSize);
    taille=tailleDeGraph(fichier);
    graph=lectureDeGraphe(fichier,taille);
    fclose(fichier);
    i=taille/3;
    posAct=(char*)malloc(sizeof(char)*i);
    i=0;
    while((i*3)<taille)//initialisation de la position actuelle selon la position de depart
    {
        if(j<startSize)
        {
            posAct[j]=start[j];
            nPos++;
        }
        else
        {posAct[i]=-1;}
        i++;
        j++;
    }
    i=0;
    j=0;
    printf("aaaa aaaaa aaaa\n");
    exitDoor=(int*)malloc(sizeof(int)*taille/3);
    while(3*i<taille)// chaque PosAct correspond à 1 exitDoor
    {exitDoor[i]=0;i++;}
    i=0;
    while(i<taille)
    {
        printf("%c ",*graph);
        graph++;
        i++;
    }
    graph-=i;
    i=0;
    printf("\nVeuillez entrer le mot\n");
    scanf("%s",motEntre);
    while((motEntre[i]!=0)&&(getOut==0))//pour chaque lettre entrée
    {
        printf("\n\n%c nPos %d:",motEntre[i],nPos);
        l=nPos;
        getOut=1;
        while(k<nPos)//pour chaque etat actuel
        {
            uniquePosAct=posAct[k];
            printf("\nuniquePosAct = %c",uniquePosAct);
            while(j<taille) //pour chaque case du graph
            {
                if(graph[j]==uniquePosAct)//si l'etat lu correspond à l'etat actuel
                {
                    if(graph[j+2]==motEntre[i])
                    {
                        if(exitDoor[k]==0)
                        {printf("\nstate %c ",posAct[k]);posAct[k]=graph[j+1];exitDoor[k]=1;printf("became %c",posAct[k]);}
                        else
                        {posAct[l]=graph[j+1];exitDoor[l]=1;printf(" and %c",posAct[l]);l++;}
                    }
                }
                j+=3;
            } //fin de lecture de graphe pour 1 position actuelle
            if(exitDoor[k]==0)
                {posAct[k]=-1;}
            else if (getOut)
                getOut=0;
            j=0;
            k++;
            printf("\nl= %d",l);
        }//fin de verification pour chaque position actuelle
        k=0;
        nPos=0;
        if(getOut==0)
        {
            while(k<=l)
            {

                if(exitDoor[k]==0)//case empty
                {
                    j++;
                }
                else
                {
                    exitDoor[k]=0;
                    if (j!=0) // remove empty case in the middle of the table
                    {
                        posAct[k-j]=posAct[k];
                        posAct[k]=-1;
                    }
                    nPos++;
                }
                k++;
            }
            k=0;
            j=0;
        }
        i++;
    } //fin de lecture, passer à afficher le resultat de lecture
    i=0;
    //system("clear");
    printf("\n\n%c nPos %d:",motEntre[i],nPos);
    if(getOut==1)
        printf("\nError");
    else
    {
        while((i<nPos)&&(getOut==0))
        {
            while((j<endSize)&&(getOut==0))
            {
                if(posAct[i]==end[j])
                    getOut=1;
                j++;
            }
        i++;
        }
        if(getOut==1)
            printf("\nprefect");
        else
            printf("\nunfinished");
    }
    free(graph);
    free(end);
    return 0;
}
