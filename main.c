#include <stdio.h>
#include <stdlib.h>
#include "AutomataFunctions.h"

int main()
{
	graph Automata;
	int i=0;
	char input[TAILLE_MAX_DU_INPUT],yesOrNo=0;
	while((yesOrNo!='y')&&(yesOrNo!='Y')&&(yesOrNo!='n')&&(yesOrNo!='N'))
	{
		printf("Voulez vous entrer manuellement l'automate ? [Y/N]\n");
		scanf("%c",&yesOrNo);
		viderLeBuffer(yesOrNo);
		system("clear");
	}
	if((yesOrNo=='Y')||(yesOrNo=='y'))
		Automata=lectureManuelle();
	else
		Automata=lectureDuFichier();
	for(i=0;i<TAILLE_MAX_DU_INPUT;i++)
	input[i]=0;
	printf("Veuillez entrer le mot à lire\n");
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
