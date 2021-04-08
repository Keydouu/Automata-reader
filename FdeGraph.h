#ifndef fonctiondegraph
#define fonctiondegraph
char* findStart(FILE* fichier, int* startSize);
char* findEnd(FILE* fichier,int* endSize);
int tailleDeGraph(FILE* fichier);
char* lectureDeGraphe(FILE* fichier,int i);
#endif // fonctiondegraph
