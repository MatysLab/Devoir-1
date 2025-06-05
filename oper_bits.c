/*****************************************************/
//  �t� 2025 inf-147
//  pour un usage coh�rent dans le devoir

/*****************************************************/
/*****************************************************/
/*		CONSTANTE					*/
/*****************************************************/

/*  symbole du nombre de bits dans un entier positif
	sur notre plateforme de travail
 */
#define NB_BITS	 (sizeof(unsigned int) * 8)

 /* l'intervalle d'ordre acceptable ira de 0 �  NB_BITS-1 */

 /*****************************************************/
/*********************************************************/
// LES fonctions offertes
// sans MACROS  ni tests unitaires que vous devrez d�velopper

/*********************************************************/
/*****************************************************/
/*		DECLARATIONS DES FONCTIONS	OFFERTES			*/
/*****************************************************/

/*****************************************************/
/*
 get_bit donne la valeur du  bit d'ordre sp�cifi�.
 PARAMETRES : nombre , un entier non sign�
              ordre , sp�cifie le bit voulu dans nombre.
 RETOUR : 0 ou 1

 SPECIFICATIONS :
 Si ordre n'est pas dans l'intervalle [0 ,NB_BITS-1]
 retour automatique de  0
 */

unsigned int get_bit(unsigned int nombre, unsigned int ordre);
/**********************************************************/

/**********************************************************/
/*
 set_bit donne la valeur du nombre avec le bit d'ordre sp�cifi� mis � 1
 PARAMETRES : nombre , un entier quelconque
              ordre , sp�cifie le bit mis � 1 dans nombre.
 RETOUR : la valeur obtenue du param�tre avec ce bit � 1

 SPECIFICATIONS :
 Si ordre n'est pas dans l'intervalle [0 ,NB_BITS-1]
 la	fonction retourne la valeur re�ue
 */

unsigned int set_bit(unsigned int nombre, unsigned int ordre);
/**********************************************************/

/**********************************************************/
/*
 clear_bit donne la valeur du nombre  avec le bit d'ordre sp�cifi� mis � 0
 PARAMETRES : nombre , un entier quelconque
              ordre , sp�cifie le bit mis � 0 dans nombre
 RETOUR : la valeur obtenue du param�tre avec ce bit � 0

 SPECIFICATIONS :
 Si ordre n'est pas dans l'intervalle [0 ,NB_BITS-1]
 la fonction retourne la valeur re�ue
 */

unsigned int clear_bit(unsigned int nombre, unsigned int ordre);
/**********************************************************/

/**********************************************************/
/*
 flip_bit donne la valeur du nombre re�u  avec le bit invers�
 d'ordre sp�cifi�
 Entr�e : nombre : un entier positif
 ordre : sp�cifie le bit  � inverser dans nombre.
 RETOUR : la valeur obtenue du param�tre avec ce bit invers�
 SPECIFICATIONS :
 Si ordre n'est pas dans l'intervalle [0 ,NB_BITS-1]
 la fonction retourne la valeur re�ue
 */

unsigned int flip_bit(unsigned int nombre, unsigned int ordre);
/*****************************************************/
// C'EST FINI
/*****************************************************/


/*tester-les bien */


/*****************************************************/
/*		DEFINITIONS DES FONCTIONS	OFFERTES			*/
/*****************************************************/

/*****************************************************/
unsigned int get_bit(unsigned int nombre, unsigned int ordre) {

	/* Strat�gie : tester  ordre valide 
	   si correct, un bitwise and  entre nombre et
	   un train de bit n'ayant qu'un 1  plac� au bon ordre
	    et retour du test == ou non � 0
	   sinon retour de 0.*/

	if  (ordre < NB_BITS) {
		return  (nombre & (1 << ordre)) != 0;
	}
	return 0;
}
/*****************************************************/

/*****************************************************/
unsigned int set_bit(unsigned int nombre, unsigned int ordre) {

	/* Strat�gie : tester ordre valide
	   si correct retour d'un bitwise or entre nombre et  
	       un train de bit n'ayant qu'un 1 plac� au bon ordre
	   sinon retour de la valeur recue .*/

	if (ordre < NB_BITS) {
		return  nombre | (1 << ordre);
	}
	return nombre;

}
/*****************************************************/

/*****************************************************/
unsigned int clear_bit(unsigned int nombre, unsigned int ordre) {

	/* Strat�gie :  tester ordre valide
	   si correct retour d'un bitwise and entre nombre et le complement 
	    d'un train de bits n'ayant qu'un 0 plac� au bon ordre
	   sinon retour de la valeur recue.*/

	if (ordre < NB_BITS) {
		return nombre & ~(1 << ordre);
	}
	return nombre;
}
/*****************************************************/

/*****************************************************/
unsigned int flip_bit(unsigned int nombre, unsigned int ordre) {

	/* Strat�gie : Tester ordre valide
	   si correct,  
	      si ce bit ordre est � 1
			return du clear_bit 
		sinon retour du set_bit
	     
	   sinon retour de la valeur recue .*/

	if (ordre < NB_BITS) {
		if (get_bit(nombre, ordre)) { return clear_bit(nombre, ordre); }
		else { return set_bit(nombre, ordre); }

	}
	return nombre;
}

/*****************************************************/



/*****************************************************/
// C'EST FINI
/*****************************************************/
