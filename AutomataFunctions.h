#ifndef AutomataFunctions
#define AutomataFunctions
#define TAILLE_MAX_DU_INPUT 100
typedef struct link link;
typedef struct graph graph;
struct link {
  char weight;
  int startNode;
  int endNode;
};
struct graph
{
  int* startingNodes;
  int* endingNodes;
  link* Links;
  int startSize,endSize,linksNumber;
};
int lectureDeNombre (FILE* fichier, int firstNumber);
int* findStart(FILE* fichier, int* startSize);
int* findEnd(FILE* fichier,int* endSize);
int numberOfLinks(FILE* fichier);
link* lectureDeGraphe(FILE* fichier,int Size);
int traverseCheck (graph g, char* input, int posInput, int Node);//bool
#endif
