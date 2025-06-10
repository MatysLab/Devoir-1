/*****************************************************/
//  Matys L'Abbée
//  Été 2025 INF-147
//  Manipulation de bits sur 32 générateurs
//  Contraintes : Maximum 2 contigues à 1
/*****************************************************/

#include "oper_bits.c"
#include <assert.h>
#include "gabarit.c"

/*****************************************************/
/*              CONSTANTES ET DÉFINITIONS            */
/*****************************************************/

#define TEST_MODE 0
#define main_selector 1
int N = 32;
int K = 12;

#define PERIODE_REPARATION  50
#define PROB_BRIS 0.5f
#define MAX_ITER 2000
/*****************************************************/
/*         DÉCLARATIONS DES FONCTIONS UTILISÉES      */
/*****************************************************/

/*=========================================================
  isContigue vérifie si trois bits consécutifs à 1 existent
  PARAMETRES : etats_generateur - valeur sur 32 bits
  RETOUR : 1 si trois bits consécutifs à 1 sont détectés, sinon 0
*/
int isContigue(unsigned int etats_generateur);

/*=========================================================
  get_bits_dispo retourne les positions disponibles (bits à 0) qui peuvent être mises à 1
  sans créer 3 bits à 1 consécutifs.
  PARAMETRES : etat_bits - unsigned int (32 bits)
  RETOUR : une valeur avec les positions valides à 1
*/
unsigned int get_bits_dispo(unsigned int etat_bits);

/*=========================================================
  choix_alea_bit1 retourne la position du bit à 1 choisi aléatoirement parmi les bits à 1
  PARAMETRES : etat_bits - unsigned int (32 bits)
  RETOUR : la position du bit à 1 choisi ou -1 si aucun bit à 1
*/
int choix_alea_bit1(unsigned int etat_bits);

/*=========================================================
  initGenerateur initialise le générateur avec une configuration valide
  RETOUR : la configuration initiale (unsigned int)
*/
unsigned int initGenerateur( void );

/*=========================================================
  permuter_bits permute un bit inactif (0 valide) avec un bit actif (1)
  PARAMETRES : etat_gen_ions - état actuel
  RETOUR : le nouvel état après permutation
*/
unsigned int permuter_bits( unsigned int etat_gen_ions );
/*****************************************************/

/*****************************************************/
/*
 Teste la fonction isContigue pour vérifier si elle détecte correctement
 la présence de trois bits consécutifs à 1 dans une séquence de 32 bits.
*/
void testIsContigue(void);
/*****************************************************/

/*****************************************************/
/*
 Teste la fonction get_bits_dispo pour s'assurer qu'elle retourne
 correctement les positions disponibles (bits à 0) pouvant être activées
 sans enfreindre la contrainte de contiguité (pas plus de 2 bits à 1 consécutifs).
*/
void testGet_bits_dispo(void);
/*****************************************************/

/*****************************************************/
/*
 Teste la fonction choix_alea_bit1 pour vérifier qu'elle retourne
 un index valide d'un bit à 1 aléatoirement,
 ou -1 si aucun bit n'est actif.
*/
void testChoix_alea_bit1(void);
/*****************************************************/

/*****************************************************/
/*
Verifie si meme index bit a 1 simultanne
 Retourne 1 success
 retourne 0 Fail
 */
int valider_bris( unsigned int arrBits1 , unsigned int arrBits2 );
/*****************************************************/

/*****************************************************/
/*
Test la fonction Valider_bris
 */
void testValider_bris( void );
/*****************************************************/

/*****************************************************/
/*
Verifie que K bit sont inferieure a N
 */
int valider_etatK (unsigned int etat_gen_ions);
/*****************************************************/

/*****************************************************/
/*
Test la fonction de verification de K bit dans Etats gen ion
 */
void testvalider_etatK( void );
/*****************************************************/

/*****************************************************/
/*
 */
unsigned int get_bits_dispo2 ( unsigned int etat_bits, unsigned int bris_ions );
/*****************************************************/
int controler_bris ( unsigned int * etat_bits, unsigned int * bris_gen );
int permuter_bit ( unsigned int * etat_bits, unsigned int bris_gen );

int reparation_bris_gen ( unsigned int * bris_gen);

/*****************************************************/
/*      FONCTIONS DE TRAITEMENT DES BITS             */
/*****************************************************/

/*****************************************************/
int isContigue(unsigned int etats_generateur)
{
    // Si un des generateurs est contigus, return index
    for (unsigned int index = 0, count = 0; index < 32; ++index)
    {
        if (get_bit(etats_generateur, index))
            ++count;
        else
            count = 0;

        if (count == 3)
            return 1;
    }
    // Si aucun generateurs est contigus, return -1
    return 0;
}
/*****************************************************/

/*****************************************************/
unsigned int get_bits_dispo(unsigned int etat_bits)
{
    unsigned int bits_possibles = 0;

    if (etat_bits == 0)
        return 0xFFFFFFFF;
    else if (etat_bits == 0xFFFFFFFF)
        return 0;

    for (int i = 0; i < N; ++i)
    {
        if (!get_bit(etat_bits, i) && !isContigue(etat_bits + (1 << i)))
        {
            bits_possibles = set_bit(bits_possibles, i);
        }
    }

    return bits_possibles;
}
/*****************************************************/

/*****************************************************/
int choix_alea_bit1(unsigned int etat_bits)
{
    if (!etat_bits)
        return -1;

    unsigned int index = 0;
    do
    {
        index = randi(N) - 1;
    } while (!get_bit(etat_bits, index));

    return index;
}
/*****************************************************/

/*****************************************************/
unsigned int initGenerateur( void )
{
    unsigned int config_initiale = 0;
    unsigned int bits_dispo = get_bits_dispo ( config_initiale );
    unsigned int ordre = 0;

    int k_count = 0;

    while ( bits_dispo && k_count != K)
    {
        ordre = choix_alea_bit1( bits_dispo );
        assert ( ordre >= 0 && ordre < N );
        config_initiale += (1 << ordre);

        ++k_count;

        bits_dispo = get_bits_dispo ( config_initiale );
    }
    assert ( !isContigue ( config_initiale ) );

    return config_initiale;
}
/*****************************************************/

/*****************************************************/
unsigned int permuter_bits( unsigned int etat_gen_ions )
{
    //Choisir un bit disponible 0
    int posInactive = choix_alea_bit1( get_bits_dispo ( etat_gen_ions ) );
    assert( posInactive >= 0);
    //Choisir un bit aleatoire 1
    int posActive = choix_alea_bit1 ( etat_gen_ions );
    assert( posInactive >= 0);
    //Permuter les bits
    etat_gen_ions = flip_bit( etat_gen_ions, posInactive);
    etat_gen_ions = flip_bit( etat_gen_ions, posActive);

    return etat_gen_ions;
}
/*****************************************************/

/*****************************************************/
int valider_bris( unsigned int arrBits1 , unsigned int arrBits2 )
{
    return arrBits1 & arrBits2 ? 0 : 1;
}
/*****************************************************/

/*****************************************************/
int valider_etatK (unsigned int etat_gen_ions)
{
    int k_count = 0;
    for ( int i = 0; i < 32; ++i)
    {
        if ( get_bit(etat_gen_ions, i) )
        {
            ++k_count;
            if ( i > N )
                return 0;
        }
    }
    return k_count == K && k_count < N ? 1 : 0;
}
/*****************************************************/

/*****************************************************/
unsigned int get_bits_dispo2 ( unsigned int etat_bits, unsigned int bris_ions )
{
    unsigned int bits_possibles = 0;
    unsigned int bit_unavaible = etat_bits | bris_ions;

    if (bit_unavaible == 0)
        return 0xFFFFFFFF;
    else if (bit_unavaible == 0xFFFFFFFF)
        return 0;

    for (int i = 0; i < N; ++i)
    {
        if (!get_bit(bit_unavaible, i) && !isContigue(bit_unavaible + (1 << i)))
        {
            bits_possibles = set_bit(bits_possibles, i);
        }
    }

    return bits_possibles;
}
/*****************************************************/
int controler_bris ( unsigned int * etat_bits, unsigned int * bris_gen )
{
    
    for ( int i = 0; i < N; i++)
    {
        if ( get_bit(*etat_bits, i) && !get_bit(*bris_gen, i) && randf() < PROB_BRIS ){
            *etat_bits = clear_bit( *etat_bits, i );
            *bris_gen = set_bit(*bris_gen, i );

            int index = choix_alea_bit1( get_bits_dispo2( *etat_bits, *bris_gen ) );

            if ( index != -1 )
                *etat_bits = set_bit( *etat_bits, index );
            else
                return 0;
        }
    }
    return 1;
}

int reparation_bris_gen(unsigned int *bris_gen)
{
    if (bris_gen == NULL)
            return -1;

    int nb_bris = 0;

    for (int i = 0; i < 32; ++i)
    {
        nb_bris += get_bit(*bris_gen, i) ? 1 : 0;
    }

    *bris_gen = 0;

    //Retourne le nombre de bits repare
    return nb_bris;
}

/*****************************************************/

int permuter_bit ( unsigned int * etat_bits, unsigned int bris_gen )
{
    unsigned int  index_bit1 = choix_alea_bit1( *etat_bits );
    unsigned int index_bit0 = choix_alea_bit1( get_bits_dispo2( *etat_bits, bris_gen ) );

    if ( index_bit1 != -1 && index_bit0 != -1 )
    {
        *etat_bits = clear_bit( *etat_bits, index_bit1 );
        *etat_bits = set_bit( *etat_bits, index_bit0);
        return 1;
    }else
        return 0;
}

/*****************************************************/
/*              FONCTIONS DE TEST                    */
/*****************************************************/

/*****************************************************/
void testIsContigue(void)
{
    // Test si aucun contigues
    assert(isContigue(0b1101100110001000110010011010110) == 0);

    // Test si un contigues
    assert(isContigue(0b1101100110001000110010011110110) == 1);
}
/*****************************************************/

/*****************************************************/
void testchoix_alea_bit1(void)
{
    assert(choix_alea_bit1(0) == -1);
    assert(choix_alea_bit1(0x1) == 0);
}
/*****************************************************/

/*****************************************************/
void testGet_bits_dispo(void)
{
    unsigned int disposition = 9;
    assert( get_bits_dispo( disposition ) == ~disposition);
}
/*****************************************************/

/*****************************************************/
void testValider_bris( void )
{
    assert(valider_bris(0x01, 0x01) == 0);
    assert(valider_bris(0x01, 0x02) == 1);
}
/*****************************************************/

/*****************************************************/
void testvalider_etatK( void )
{
    K = 15;
    assert( valider_etatK(0b111111111111111) );
    K = 20;
    assert( valider_etatK(0b11011011011011011011011011011) );
    assert( valider_etatK(0b1101101101101101101101101101101) == 0);
}
/*****************************************************/

/*****************************************************/
/*              MAIN POUR TESTS UNITAIRES            */
/*****************************************************/
#if TEST_MODE == 1
int main(void)
{
    srand_sys();
    testIsContigue();
    testchoix_alea_bit1();
    testGet_bits_dispo();
    testValider_bris();
    testvalider_etatK();
    testControler_bris();
    return 0;
}
#endif
/*****************************************************/

/*****************************************************/
/*                 MAIN PRINCIPAL                    */
/*****************************************************/
#if TEST_MODE == 0 && main_selector == 0
int main(void)
{
    // Demarage du systeme aleatoire
    srand_sys();

    // verification des entrees N et K
    assert( ( 18 <= N && N <= 32 ) );
    assert( ( ( 0.28 * N ) <= K ) );
    assert(( K <= ( 0.48 * N ) ) );

    // Initialisation du generateur (Randomizer)
    unsigned int etats_gen_ions = initGenerateur();
    unsigned int bris_gen_ions = 0;
    int nb_passages = 0;
    int nbr_loops = 1000;

    voir_bits(etats_gen_ions);

    // Boucle principale de simulation
    for (int i = 0; i < nbr_loops; ++i)
    {
        nb_passages++;
        etats_gen_ions = permuter_bits(etats_gen_ions);

        if (!controler_bris(&etats_gen_ions, &bris_gen_ions))
            break;
        if (!valider_bris(etats_gen_ions, bris_gen_ions))
            break;
        if (!valider_etatK(etats_gen_ions))
            break;

        if (i % PERIODE_REPARATION == 0 && bris_gen_ions > 0)
        {
            if (reparation_bris_gen(&bris_gen_ions) <= 0)
                break;
        }
    }
    // Affichage de bits
    voir_bits(etats_gen_ions);
    // Affichage du nombre de passages
    printf("Nombre de passages effectues : %d\n", nb_passages);

    return 0;
}
#endif
/*****************************************************/

#if TEST_MODE == 0 && main_selector == 1
#include <limits.h>
#define MAX_REPETITION 1000

int main(void)
{
    srand_sys();
    assert((18 <= N && N <= 32));
    assert(((0.28 * N) <= K));
    assert((K <= (0.48 * N)));

    int resultats[MAX_REPETITION];
    int nb_repetitions = 0;
    int min_passages = INT_MAX;
    int max_passages = 0;
    long somme_passages = 0;

    for (nb_repetitions = 0; nb_repetitions < MAX_REPETITION; ++nb_repetitions)
    {
        unsigned int etats_gen_ions = initGenerateur();
        unsigned int bris_gen_ions = 0;
        int nb_passages = 0;
        int success = 1;

        for (int i = 0; i < MAX_ITER; ++i)
        {
            nb_passages++;

            if (!controler_bris(&etats_gen_ions, &bris_gen_ions)) { success = 0; break; }
            if (permuter_bit(&etats_gen_ions, bris_gen_ions) == 0) { success = 0; break; }
            if (!valider_bris(etats_gen_ions, bris_gen_ions)) { success = 0; break; }
            if (!valider_etatK(etats_gen_ions)) { success = 0; break; }
            if (i % PERIODE_REPARATION == 0 && bris_gen_ions > 0)
                if (reparation_bris_gen(&bris_gen_ions) <= 0) { success = 0; break; }

            if ((i > 0) && (i % (MAX_ITER / 10) == 0)) {
                printf("[Sim %d] Passage %d\n", nb_repetitions+1, nb_passages);
                printf("  etats_gen_ions: %u\n", etats_gen_ions);
                printf("  bris_gen_ions: %u\n", bris_gen_ions);
            }
        }
        resultats[nb_repetitions] = nb_passages;
        somme_passages += nb_passages;
        if (nb_passages < min_passages) min_passages = nb_passages;
        if (nb_passages > max_passages) max_passages = nb_passages;
        if ((nb_repetitions+1) % (MAX_REPETITION/10) == 0) {
            printf("---\nSimulation %d/%d\n", nb_repetitions+1, MAX_REPETITION);
            printf("Constantes: N=%d, K=%d, PROB_BRIS=%.2f, PERIODE_REPARATION=%d, MAX_ITER=%d\n", N, K, PROB_BRIS, PERIODE_REPARATION, MAX_ITER);
            printf("  Dernier etats_gen_ions: %u\n", etats_gen_ions);
            printf("  Dernier bris_gen_ions: %u\n", bris_gen_ions);
            printf("  Dernier nb_passages: %d\n", nb_passages);
        }
    }
    printf("=========================\n");
    printf("Constantes: N=%d, K=%d, PROB_BRIS=%.2f, PERIODE_REPARATION=%d, MAX_ITER=%d\n", N, K, PROB_BRIS, PERIODE_REPARATION, MAX_ITER);
    printf("Statistiques sur %d simulations :\n", MAX_REPETITION);
    printf("  Moyenne : %.2f\n", (double)somme_passages / MAX_REPETITION);
    printf("  Minimum : %d\n", min_passages);
    printf("  Maximum : %d\n", max_passages);
    printf("=========================\n");

    return 0;
}
#endif
/*****************************************************/

/*****************************************************/
// FIN DU FICHIER
/*****************************************************/