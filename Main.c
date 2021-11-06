#include <stdio.h>
#include <stdlib.h>

#include "ABR.h"

void chargerArbreBinaire(){
	printf("Tapez la taille de l'arbre : ");
	int taille;
	scanf("%d",&taille);
	int tab[taille];
	for(int i = 0; i< taille ; i++){
		tab[i] = i;
	}
	noeud *n = NULL;
	printf("Possibilité arbre de taille %d :\n",taille);
	arbre_binaire_D(tab,taille,n,0);

	n = NULL;
	printf("\n-----\n");

	arbre_binaire(tab,taille,n,0);
	n = NULL;
	printf("\n-----\n");
	printf("Arbre binaire équilibré : \n");
	int test = ABR_equilibre(tab,taille,n,0);

	if(taille > 2){
		n = NULL;
		printf("----\n");
		int test1 = arbre_binaire_v1(tab,taille,n,0);

		n = NULL;
		printf("----\n");
		int test2 = arbre_binaire_v2(tab,taille,n,0);
	}
}

int main(){
	chargerArbreBinaire();
}

