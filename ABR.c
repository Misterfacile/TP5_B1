#include <stdio.h>
#include <stdlib.h>

#include "ABR.h"
noeud *nouvNoeud(char c){
	noeud *p = NULL;
	static int numero; //var rémanente auto initialisée à 0
	p = (noeud*)malloc(sizeof(noeud));
	if (p==NULL){
		printf("Prob d'allocation dynamique du noeud\n");
		exit(1);
	}
	p->pere = NULL;
	p->etiquette = c;
	p->num = ++numero;
	p->filsG = NULL;
	p->filsD = NULL;
	return p;
}



void arbre_binaire(int *tab,int ordre, noeud *n,int ind){
	// Argument ind permet de conserver l'emplacement où on se trouve dans le tableau
	if(n == NULL){ // Initialisation de la racine
		n = nouvNoeud(tab[0]);
		ind++;
		// On génère ensuite ses fils
		arbre_binaire(tab,ordre,n,ind);
		int esp = (ordre)*2;
		// On affiche ensuite l'arbre binaire
		for(int i = 1; i<ordre; i++){
			espace(esp); // Espace pour faire l'arbre
			printf("(%d)\n",n->etiquette);
			espace(esp);
			printf("/\n");
			esp = esp -2;
			n = n->filsG;
		}
		espace(esp-1);
		printf("(%d)\n",n->etiquette);
		espace(esp);
		return;

	}else{
		noeud *suiv = NULL;
		suiv = nouvNoeud(tab[ind]);
		suiv->pere = n;
		n->filsG = suiv;
		ind++;
		if(ind < ordre){
			arbre_binaire(tab,ordre,suiv,ind);
		}else{
			return;
		}
	}
}

void arbre_binaire_D(int *tab,int ordre, noeud *n,int ind){
	// Argument ind permet de conserver l'emplacement où on se trouve dans le tableau
	if(n == NULL){ // Initialisation de la racine
		n = nouvNoeud(tab[0]);
		ind++;
		// On génère ensuite ses fils
		arbre_binaire_D(tab,ordre,n,ind);
		int esp = 0;
		// On affiche ensuite l'arbre binaire
		for(int i = 1; i<ordre; i++){
			espace(esp);
			printf("(%d)\n",n->etiquette);
			espace(esp+2);
			printf("\x5c\n");
			esp = esp +3;
			n = n->filsD;
		}
		espace(esp-1);
		printf("(%d)\n",n->etiquette);
		espace(esp);
		return;

	}else{
		noeud *suiv = NULL;
		suiv = nouvNoeud(tab[ind]);
		suiv->pere = n;
		n->filsD = suiv;
		ind++;
		if(ind < ordre){
			arbre_binaire_D(tab,ordre,suiv,ind);
		}else{
			return;
		}
	}
}

void arbre_recherche(int *tab,int ordre, noeud *n,int ind){
	// Initialisation de la racine
	if(n == NULL){
		n = nouvNoeud(tab[0]);
		ind++;
		arbre_recherche(tab,ordre,n,ind);
		return;
	// Génère les autres feuilles de l'arbre en les rangeant selon un arbre de recherche
	}else if(ind < ordre){

		noeud *suiv = NULL;
		suiv = nouvNoeud(tab[ind]);
		// Si le père actuelle est inférieur alors le noeud suiv devient alors son nouveau père
		if(n->etiquette < tab[ind]){
			n->pere = suiv;
			suiv->filsG = n;
			ind++;
			arbre_recherche(tab,ordre,suiv,ind);
			n = suiv;

		// Sinon il devient son fils G
		}else if(n->etiquette > tab[ind]){
			if(n->filsG == NULL){
				n->filsG = suiv;
				suiv->pere = n;
				ind++;
				arbre_recherche(tab,ordre,n,ind);
			}else{
				noeud *temp = NULL;
				temp = n->filsG;
				int fin = 0;
				do{
					if(temp->etiquette < suiv->etiquette){
						temp->pere->filsG = suiv;
						suiv->pere = temp->pere;

						suiv->filsG = temp;
						temp->pere = suiv;
						fin = 1;
					}else if(temp->filsG==NULL){
						temp->filsG = suiv;
						fin = 1;
					}else{
						temp = temp->filsG;
					}
				}while(!fin);
				ind++;
				arbre_recherche(tab,ordre,n,ind);
			}
		}

		// Dès que tout le tableau est parcouru, on affiche alors l'arbre
		if(ind == ordre){
			int esp = (ordre)*2;
			// On affiche ensuite l'arbre binaire
			for(int i = 1; i<ordre; i++){
				espace(esp); // Espace pour faire l'arbre
				printf("(%d)\n",n->etiquette);
				espace(esp);
				printf("/\n");
				esp = esp -2;
				n = n->filsG;
			}
			espace(esp-1);
			printf("(%d)\n",n->etiquette);
			espace(esp);
		}
		return;
	}else{
		return;
	}
}

int *tabtrie(int *tab,int ordre){
	// On trie d'abord le tableau en parcourant celui-ci et commençant d'abord par trouver le maximum
	int *tabtrie;
	tabtrie = (int*)malloc(ordre*sizeof(int));
	int max = 0;
	int ind = ordre-1;

	int nonzero = 0;

	int indice = 0;
	do{
		// On cherche le maximum dans le tableau d'origine
		for(int i = 0 ; i<ordre ; i++){
			if(tab[i]>max){
				max = tab[i];
				indice = i;
				// On met 1 à nonzero pour dire qu'on trouvé un sommet qui n'a un sommet égal au max origine c'est-à-dire 0
				nonzero = 1;
			}
		}
		/* Puis on l'ajoute dans le tableau trié dans l'ordre décroissant et où on mettra la valeur 0 dans le tableau d'origine pour dire que cette valeur
		 est déjà dans le tableau trié */
		if(nonzero){
			tabtrie[ind] = max;
			tab[indice] = 0;
			max = 0;
			ind--;
		//Si tout le tableau est parcouru mais qu'il reste un sommet 0 alors on sait que qu'il manque encore un sommet grâce à ind
		}else{
			tabtrie[0] = 0;
			ind --;
		}

	}while(ind >=0);
	/*
	for(int i = 0; i<ordre; i++){
		printf("%d ",tabtrie[i]);
	}
	*/
	return tabtrie;

}
void espace(int espace){
	for(int j = 0; j<espace-1 ; j++){
		printf(" ");
	}
}

int ABR_equilibre(int *tab,int ordre, noeud *n, int profondeur){
	// On trie d'abord le tableau en parcourant celui-ci et commençant d'abord par trouver le maximum
	noeud *suiv = NULL;
	// On détermine la profondeur de l'arbre avant de l'afficher avec l'argument "profondeur"
	int prof1 = profondeur;
	int prof2 = profondeur;
	int tab1[ordre/2+1];


	if(n == NULL){ // création de la racine
		n = nouvNoeud(tab[ordre/2]);
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}

		// fais la branche gauche de l'arbre depuis la racine
		prof1++;
		prof1 = ABR_equilibre(tab1,ordre/2,n,prof1);

		int j = 0;
		for(int i = ordre/2+1; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;

		}

		// Fais la partie droite depuis la racine
		prof2++;
		prof2 = ABR_equilibre(tab1,j,n,prof2);

		if(prof1>prof2){
			affichage_arbre(n,0,prof1);
			return prof1;
		}else{
			affichage_arbre(n,0,prof2);
			return prof2;
		}

		printf("\nEND");

	}else if((ordre) > 2 ){

		suiv = nouvNoeud(tab[ordre/2]);
		suiv->pere = n;
		if(n->etiquette > suiv->etiquette){
			n->filsG = suiv;
		}else{
			n->filsD = suiv;
		}
		// On sépare le tableau en 2
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}
		// fais la branche gauche de l'arbre
		prof1++;
		prof1 = ABR_equilibre(tab1,ordre/2,suiv,prof1);
		int j = 0;
		for(int i = ordre/2+1; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;
		}
		// fais la branche droite de l'arbre
		prof2++;
		prof2 = ABR_equilibre(tab1,j,suiv,prof2);
		if(prof1 > prof2){
			return prof1;
		}else{
			return prof2;
		}




	}else if(ordre == 2){
		prof1 = prof1+2;
		if(tab[1] > n->etiquette){
			suiv = nouvNoeud(tab[1]);
			n->filsD = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;


		}else if(tab[1] < n->etiquette){

			suiv = nouvNoeud(tab[1]);
			n->filsG = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;
		}
		return prof1;
	}else{
		suiv = nouvNoeud(tab[0]);
		suiv->pere = n;

		if(tab[0] > n->etiquette){

			n->filsD = suiv;

		}else{
			suiv = nouvNoeud(tab[0]);
			n->filsG = suiv;
		}
		return prof1++;

	}

}
int arbre_binaire_v1(int *tab,int ordre, noeud *n, int profondeur){
	// On trie d'abord le tableau en parcourant celui-ci et commençant d'abord par trouver le maximum
	noeud *suiv = NULL;
	// On détermine la profondeur de l'arbre avant de l'afficher avec l'argument "profondeur"
	int prof1 = profondeur;
	int prof2 = profondeur;
	int tab1[ordre/2+1];


	if(n == NULL){ // création de la racine
		n = nouvNoeud(tab[ordre/2]);
		suiv = nouvNoeud(tab[ordre/2+1]);
		suiv->pere = n;
		n->filsG = suiv;
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}

		// fais la branche gauche de l'arbre depuis la racine
		prof1 = prof1+2;
		prof1 = arbre_binaire_v1(tab1,ordre/2,suiv,prof1);

		int j = 0;
		for(int i = ordre/2+2; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;

		}

		// Fais la partie droite depuis la racine
		prof2 = prof2 + 2;
		prof2 = arbre_binaire_v1(tab1,j,suiv,prof2);
		if(prof1>prof2){
			affichage_arbre(n,0,prof1);
			return prof1;
		}else{
			affichage_arbre(n,0,prof2);
			return prof2;
		}
		return profondeur;

	}else if((ordre) > 2 ){

		suiv = nouvNoeud(tab[ordre/2]);
		suiv->pere = n;
		if(n->etiquette > suiv->etiquette){
			n->filsG = suiv;
		}else{
			n->filsD = suiv;
		}
		// On sépare le tableau en 2
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}
		// fais la branche gauche de l'arbre
		prof1++;
		prof1 = arbre_binaire_v1(tab1,ordre/2,suiv,prof1);
		int j = 0;
		for(int i = ordre/2+1; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;
		}
		// fais la branche droite de l'arbre
		prof2++;
		prof2 = arbre_binaire_v1(tab1,j,suiv,prof2);
		if(prof1 > prof2){
			return prof1;
		}else{
			return prof2;
		}


	}else if(ordre == 2){
		prof1 = prof1+2;
		if(tab[1] > n->etiquette){
			suiv = nouvNoeud(tab[1]);
			n->filsD = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;


		}else if(tab[1] < n->etiquette){

			suiv = nouvNoeud(tab[1]);
			n->filsG = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;
		}
		return prof1;
	}else{
		suiv = nouvNoeud(tab[0]);
		suiv->pere = n;

		if(tab[0] > n->etiquette){

			n->filsD = suiv;

		}else{
			suiv = nouvNoeud(tab[0]);
			n->filsG = suiv;
		}
		return prof1++;

	}

}

int arbre_binaire_v2(int *tab,int ordre, noeud *n, int profondeur){
	// On trie d'abord le tableau en parcourant celui-ci et commençant d'abord par trouver le maximum
	noeud *suiv = NULL;
	// On détermine la profondeur de l'arbre avant de l'afficher avec l'argument "profondeur"
	int prof1 = profondeur;
	int prof2 = profondeur;
	int tab1[ordre/2+1];


	if(n == NULL){ // création de la racine
		n = nouvNoeud(tab[ordre/2]);
		suiv = nouvNoeud(tab[ordre/2+1]);
		suiv->pere = n;
		n->filsD = suiv;
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}

		// fais la branche gauche de l'arbre depuis la racine
		prof1 = prof1+2;
		prof1 = arbre_binaire_v2(tab1,ordre/2,suiv,prof1);

		int j = 0;
		for(int i = ordre/2+2; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;

		}

		// Fais la partie droite depuis la racine
		prof2 = prof2 + 2;
		prof2 = arbre_binaire_v2(tab1,j,suiv,prof2);
		if(prof1>prof2){
			affichage_arbre(n,0,prof1);
			return prof1;
		}else{
			affichage_arbre(n,0,prof2);
			return prof2;
		}
		return profondeur;

	}else if((ordre) > 2 ){

		suiv = nouvNoeud(tab[ordre/2]);
		suiv->pere = n;
		if(n->etiquette > suiv->etiquette){
			n->filsG = suiv;
		}else{
			n->filsD = suiv;
		}
		// On sépare le tableau en 2
		for(int i = 0; i< ordre/2 ; i++){
			tab1[i] = tab[i];
		}
		// fais la branche gauche de l'arbre
		prof1++;
		prof1 = arbre_binaire_v2(tab1,ordre/2,suiv,prof1);
		int j = 0;
		for(int i = ordre/2+1; i< ordre ; i++){
			tab1[j] = tab[i];
			j++;
		}
		// fais la branche droite de l'arbre
		prof2++;
		prof2 = arbre_binaire_v2(tab1,j,suiv,prof2);
		if(prof1 > prof2){
			return prof1;
		}else{
			return prof2;
		}


	}else if(ordre == 2){
		prof1 = prof1+2;
		if(tab[1] > n->etiquette){
			suiv = nouvNoeud(tab[1]);
			n->filsD = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;


		}else if(tab[1] < n->etiquette){

			suiv = nouvNoeud(tab[1]);
			n->filsG = suiv;
			suiv->pere = n;

			noeud *temp = NULL;
			temp = nouvNoeud(tab[0]);

			suiv->filsG = temp;
			temp->pere = suiv;
		}
		return prof1;
	}else{
		suiv = nouvNoeud(tab[0]);
		suiv->pere = n;

		if(tab[0] > n->etiquette){

			n->filsD = suiv;

		}else{
			suiv = nouvNoeud(tab[0]);
			n->filsG = suiv;
		}
		return prof1++;

	}

}
/*Affichage de l'arbre en vertical et ".." signifie que le noeud ne possède pas de fils ( gauche ou droite )
 *
 */
void  affichage_arbre(noeud *n, int current_level, int max_level)
{
  int i;

  if (n) {
    affichage_arbre(n->filsD, current_level + 1, max_level);
    for (i = 0; i < current_level; i++) {
      printf("    ");
    }
    printf("%d\n", n->etiquette);
    affichage_arbre(n->filsG, current_level + 1, max_level);
  } else {
    if (current_level < max_level) {
      affichage_arbre(NULL, current_level + 1, max_level);
      for (i = 0; i < current_level; i++) {
        printf("    ");
      }
      printf("..\n");
      affichage_arbre(NULL, current_level + 1, max_level);
    }
  }
}


