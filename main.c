#include <stdio.h>
#include <stdlib.h>
#include "AutomataFunctions.h"

int main()
{
    graph Automata;
	FILE* fichier=NULL;
	int i=0;
	char input[TAILLE_MAX_DU_INPUT];
	fichier=fopen("graphe.txt","r");
	if (fichier==NULL)
	{
		exit(0);
    }
	Automata.startingNodes=findStart(fichier,&Automata.startSize);
	Automata.endingNodes=findEnd(fichier,&Automata.endSize);
	Automata.linksNumber=numberOfLinks(fichier);
	Automata.Links = lectureDeGraphe(fichier,Automata.linksNumber);
	for(i=0;i<TAILLE_MAX_DU_INPUT;i++)
        input[i]=0;
	scanf("%s",&input);
	i=0;
	while ((traverseCheck(Automata,input,0,*(Automata.startingNodes+i))==0)&&(i<Automata.startSize))
        i++;
    if(i>=Automata.startSize)
        printf("l'automate ne peut pas pas lire ce mot");
    else
        printf("lecture reussie");
    return 0;
}
