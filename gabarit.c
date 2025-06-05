//=========================================================
// 	hs pour nos �tudiants en C
//=========================================================


/*=========================================================*/
/*
	gabarit d'un programme en premi�re semaine de C
	il semble contenir deux main
	vous savez bien qu'il est impossible que deux main
	soient tous deux actifs simultanement

	j'utilise un artifice de PR�-COMPILATION  pour qu'en fait
	le compilateur n'en voit qu'un seul
	c'est #if(condition)  tout ce qu'on veut voir ou cacher  #endif

	c'est simple, agr�able et ainsi vous pourrez travailler,
	�changer rapidement vos premi�res exp�riences 
	( plut�t qu'un fichier de code par probleme )


	Vous avez BIEN des exercices � faire cette semaine
	Vous n'allez tout  de m�me pas g�n�rer un fichier pour chacun

	N'oubliez jamais de commenter
	du code correct, bien test� mais sans indication du probl�me r�solu
	.... CA VAUT QUOI???  je r�ponds m�me pas
	je recois parfois un mail qui me montre du code
		rien en commentaires
		sans m�me me dire quel est le probleme � r�soudre
		me demandant : pourquoi �a marche pas ?
	parfois je devine et je r�ponds 
	souvent je r�ponds sans m�chancet�
		pouvez-vous r�p�ter la question :)

*/

/*=========================================================*/


/* la constante qui permet de d�sactiver certains 
	warnings achalants de Visual
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>
/*=========================================================*/

/*=========================================================*/
// d'abord un CADEAU 
/*=========================================================*/
/*
	Voici quatre fonctions offertes pour r�aliser certains 
	des exercices qui demandent une simulation num�rique et ont 
	besoin d'un g�n�rateur de nombres  pseudo-al�atoires

	Avant de savoir utiliser un bon generateur, je vous offre
	ces  fonctions qui interfacent le  vieux g�n�rateur du C 
	bien connu pour ses fonctions rand, srand et son obsolescence

	Quatre fonctions 
	randf, randi et randf_bornes civilisent le vieux rand du C pour 
	�mette dans la distribution uniforme sp�cifi�e
	srand_sys rend  plus simple l'initialisation de ce vieux generateur
	en utilisant l'horloge interne de la machine

	Mais y'a bien plus important.... la forme standard utilis�e dans 
	les quatre d�clarations de fonctions sera la forme NORMALE
	ET OBLIG�E pour TOUTES VOS FONCTIONS et pour toute la session

*/
/*=========================================================*/
// LES DECLARTIONS DE FONCTIONS (dit aussi prototypes)
/*=========================================================*/
/*  randf donne un nombre r�el dans l'intervalle ouvert(0,1)
	
	PARAMETRES :  aucun
	RETOUR : une valeur r�elle dans l'intervalle

	SPECIFICATIONS : aucune
*/
double randf(void);
/***************** VOIR_BITS ****************************/
/*
      Affiche les bits du nombre reçu à l'écran.
      PARAMETRE : nombre , un entier non signé
      RETOUR : rien
      SPECIFICATIONS :
      Les bits sont affichés du plus significatif au moins significatif

*/
void voir_bits(unsigned int nombre);
//=========================================================
/*=========================================================*/
/*  randi simule un de a N faces pour donner
    un entier positif entre 1 et le parametre recu
	PARAMETRES :  nombre , un entier positif
	RETOUR : 0  ou  une valeur entre 1 et nombre

	SPECIFICATIONS : recevant nombre <= 0 retour automatique de 0
*/
int randi(int nombre);
/*=========================================================*/
/*  randf_bornes donne un nombre r�el dans l'intervalle sp�cifi�
	PARAMETRES :  deux r�els quelconques
	RETOUR : une valeur r�elle dans l'intervalle d�fini par ses
			 deux param�tres

	SPECIFICATIONS : l'ordre des param�tres est sans importance
*/
double randf_bornes(double b1, double b2);
/*=========================================================*/

/*=========================================================*/
/*  srand_sys initialise le g�n�rateur de la valeur de 
    l'horloge interne de la machine
	PARAMETRES :  Rien
	RETOUR : Rien

	SPECIFICATIONS : DANS UNE SIMULATION NUM�RIQUE, ON NE DOIT JAMAIS
		INITIALISER PLUS D'UNE FOIS UN G�N�RATEUR
*/
void srand_sys(void);
/*=========================================================*/

/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/
// petit bonhomme bien connu en maths 
// c'est m�me un ami de  Shrek
// alors respect
#define EPSILON (0.00000001)


/*=========================================================*/

/*=========================================================*/

// avec son 1 au #if, ce main est actuellement actif
#if 0
int main(void) {

	// je me permets un entier et un r�el
	int mon_entier = 135;
	double mon_reel = 0;

	srand_sys(); // init du PRG

	//premier usage de randi suivi d'un  
	//test unitaire de la fonction
	mon_entier = randi(17);
	assert((mon_entier >0) && (mon_entier < 18));


	// maintenant  pareil  pour un r�el
	mon_reel = randf_bornes(2904.5988, 184);
	assert( mon_reel> 184);
	assert(mon_reel < 2905);


	// on termine avec le standard
	system("pause");
	return EXIT_SUCCESS; 
}
#endif
/*=========================================================*/


/*=========================================================*/
/* avec son 0 au #if, ce main reste  inactif
	c'est � vous de l'utiliser maintenant
	de faire vos solutions aux probl�mes
*/

#if 0
int main(void) {





	// on termine
	system("pause");
	return EXIT_SUCCESS;
}
#endif
/*=========================================================*/



// vous pouvez continuer � empiler vos solutions aux probl�mes




/*=========================================================*/
/*=========================================================*/
// D�finitions des quatre fonctions offertes
/*=========================================================*/
double randf(void) {
	// STRATEGIE
	// calcul du rapport de la valeur issue de rand au maximum
	// emissible + epsilon  
	return (1.0*rand()) / (RAND_MAX + EPSILON) ;
}
/*=========================================================*/
int randi(int n) {
	// STRATEGIE
	// si n <= 0 retour 0 
	// n * randf()) donne un r�el 
	// le typecast (int) va le tronquer dans [0,n[
	//  ajouter 1 va assurer �tre dans [1,n]
	return (n <= 0) ? 0 : (1 + (int)(n * randf()));
}
/*=========================================================*/
double randf_bornes(double b1, double b2) {
	// STRATEGIE
	// passer de [0,1] � l'intervalle d�sign� par les param�tres
	// maths :  une dilatation de [0,1] par le facteur(b2 - b1)
	// suivie d'une translation de b1
	return b1 + ((b2 - b1) * randf());
}
/*=========================================================*/
/*=========================================================*/

void srand_sys(void) {
	unsigned int secondes;
	// d�calage secondes (Unix timestamp)
	secondes = (unsigned int)time(NULL);
	// init du generateur
	srand(secondes);
	// qui par tradition est suivi d'un premier appel au generateur
	secondes = rand(); 
}
/*=========================================================*/
/*****************************************************/
/* voir_bits
STRATÉGIE  réutilisation
      après un saut de ligne
      on affiche INT_BIT fois le résultat obtenu
      par logiciel pour chaque position.
*/
void voir_bits(unsigned int nombre) {
	int i;
	printf("\n");
	for (i = 8 * sizeof(int) - 1; i > -1; i -= 1) {
		int val_bit;
		val_bit = ((1 << i) & nombre) ? 1 : 0;
		printf("%d", val_bit);
	}
}

/*****************************************************/
/*=========================================================*/
