#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>

// Blockchains

// Objectif : Ecrire les fonctions permettant de gérer une blockchain simplifiée

/* On supose que:
- une transaction est une structure composée du code du vendeur, du code de l'acheteur, et de la valeur de la transaction
- un block de la blockchain contient une unique transaction
- les blocks contiennent aussi un champ code_block dont la valeur est calculée à partir des champs code_block du block précédent et valeur de la transaction du block
- les blocks contiennent aussi un pointeur sur le bloc précédent
- pour le bloc genesis (prmeier bloc), le code_block est initialisé à 17, tous les champs de transaction sont initialisés à 0, et le pointeur precedent pointe vers NULL
*/

// Définition de la structure Transaction
typedef struct transaction {
  int vendeur;
  int acheteur;
  float valeur;
} Transaction;

// Définition de la structure Block
typedef struct block {
  int long code_block;
  Transaction *trans;
  struct block *precedent;
} Block;

// QU1
// Ecrire la fonction permettant de créer et d'initialiser une transaction, et qui renvoie un pointeur vers la nouvelle transaction
// On suppose ici que vendeur, acheteur, et valeur ne valent pas NULL

Transaction* creation_transaction (int vendeur, int acheteur, float valeur) {
  Transaction* new_trans = (Transaction*)malloc(sizeof(Transaction));
  if (new_trans == NULL) {
    printf("Erreur dans l’allocation mémoire");
    return NULL;
  }
  new_trans->vendeur = vendeur;
  new_trans->acheteur = acheteur;
  new_trans->valeur = valeur;
  return new_trans;
}

// QU2
// Ecrire la fonction permettant de créer et d'initialiser le bloc genesis d'une blockchain, et qui renvoie un pointeur vers le block nouvellement créé

Block *creation_block_zero() {
  Block* new_Block=(Block*)malloc(sizeof(Block));
  if (new_Block == NULL) {
    printf("Erreur dans l’allocation mémoire");
    return NULL;
  }
  new_Block->code_block=17;
  new_Block->trans=creation_transaction(0,0,0);
  new_Block->precedent=NULL;
  return new_Block;
}

// QU3
// Ecrire la fonction permettant de créer un nouveau code de block, calcul par f(x)=2*x*mod(8571),où x est la somme de code_block_precedent et la valeur de la transaction reçue en paramètre

long creation_code_block(long code_block_precedent, Transaction *trans) {
    return fmod(2 * (code_block_precedent + trans->valeur), 8571);
}

// QU4
// Ecrire la fonction d'ajout d'un nouvel block à une blockchain dont la transaction est reçue en paramètre, et qui renvoie un pointeur vers la bouvelle blockchain

Block *ajout_nouveau_block(Block *blockchain, Transaction *nt) {
    if (blockchain == NULL) {
        return creation_block_zero();
    }
    Block* new_Block=(Block*)malloc(sizeof(Block));
    if (new_Block == NULL) {
        printf("Erreur dans l’allocation mémoire");
        return NULL;
    }
    new_Block->code_block=creation_code_block(blockchain->code_block,nt);
    new_Block->trans=nt;
    new_Block->precedent=blockchain;
    return new_Block;
}

// QU5
// Ecrire la fonction permettant de calculer le bilan des transactions effectuées par une personne dont le code est donné en paramètre

float valeur_transactions_personne(Block *blockchain, int personne) {
    float val=blockchain->trans->valeur;
    if (blockchain->trans->vendeur==personne) {
        return val-valeur_transactions_personne(blockchain->precedent, personne);
    }
    return val+valeur_transactions_personne(blockchain->precedent, personne);
}

// QU6
// Ecrire la fonction permettant de modifier la valeur d'une transaction identifiée par le block dont elle fait partie, et qui retourne un pointeur vers la nouvelle blockchain

Block *modification_blockchain(Block *blockchain, Block *a_modifier, float val) {
    if ((blockchain == NULL) || (blockchain->precedent==NULL) || (a_modifier==NULL)) {
        return NULL;
    }
    if (blockchain==a_modifier) {
        blockchain->trans->valeur=val;
        return blockchain;
    }
    modification_blockchain(blockchain->precedent, a_modifier, val);
    blockchain->code_block=creation_code_block(blockchain->precedent->code_block, blockchain->trans);
    return blockchain;
}

// QU7
// Ecrire une fonction permettant d'afficher les transactions d'une blockchain de la plus récente à la plus ancienne

void afficher_blockchain(Block* blockchain) {
    if (blockchain==NULL) {
        return;
    }
    printf("transaction=%d,%d,%f",blockchain->trans->vendeur, blockchain->trans->acheteur, blockchain->trans->valeur);
    afficher_blockchain(blockchain->precedent);
    return;
}

// QU8
// Ecrure une fonction permettant de libérer la mémoire d'un blockchain

void liberer_memoire_blockchain(Block *blockchain) {
    if (blockchain==NULL) {
        return;
    }
    liberer_memoire_blockchain(blockchain->precedent);
    free(blockchain->precedent);
    free(blockchain);
    return;
}

// QU9
// Ecrire une fonction permettant d'effacer toutes les transactions du type "achat" d'une personne dont le code est donné en paramètre

void effacer(int acheteur, Block *courant) {
    if (courant==NULL) {
        return;
    }
    if (courant->trans->acheteur==acheteur) {
        courant->trans->valeur=0;
    }
    if (courant->precedent==NULL) {
        courant->code_block=0;
    }
    effacer(acheteur,courant->precedent);
    if (courant->trans->acheteur!=acheteur) {
        courant->code_block=creation_code_block(courant->precedent->code_block,courant->trans);
    }
    return;
}

// QU10
// Ecrire la fonction main

int main() {
    // Création du bloc genesis
    Block *blockchain = creation_block_zero();
    if (blockchain == NULL) {
        printf("Erreur lors de la création du bloc genesis.\n");
        return 1;
    }

    // Création de quelques transactions
    Transaction *t1 = creation_transaction(1, 2, 100.0);
    Transaction *t2 = creation_transaction(2, 3, 200.0);
    Transaction *t3 = creation_transaction(3, 1, 50.0);

    if (t1 == NULL || t2 == NULL || t3 == NULL) {
        printf("Erreur lors de la création des transactions.\n");
        liberer_memoire_blockchain(blockchain);
        return 1;
    }

    // Ajout des transactions à la blockchain
    blockchain = ajout_nouveau_block(blockchain, t1);
    blockchain = ajout_nouveau_block(blockchain, t2);
    blockchain = ajout_nouveau_block(blockchain, t3);

    if (blockchain == NULL) {
        printf("Erreur lors de l'ajout des blocks.\n");
        liberer_memoire_blockchain(blockchain);
        return 1;
    }

    // Affichage de la blockchain
    printf("Blockchain après ajout des transactions :\n");
    afficher_blockchain(blockchain);
    printf("\n");

    // Calcul du bilan pour une personne (par exemple, la personne 1)
    int personne = 1;
    float bilan = valeur_transactions_personne(blockchain, personne);
    printf("Bilan des transactions pour la personne %d : %.2f\n", personne, bilan);

    // Modification d'une transaction dans la blockchain
    Block *block_a_modifier = blockchain->precedent; // On modifie le deuxième block
    float nouvelle_valeur = 300.0;
    blockchain = modification_blockchain(blockchain, block_a_modifier, nouvelle_valeur);

    if (blockchain == NULL) {
        printf("Erreur lors de la modification de la blockchain.\n");
        liberer_memoire_blockchain(blockchain);
        return 1;
    }

    // Affichage de la blockchain après modification
    printf("Blockchain après modification de la transaction :\n");
    afficher_blockchain(blockchain);
    printf("\n");

    // Effacer toutes les transactions d'achat pour une personne (par exemple, la personne 2)
    int acheteur = 2;
    effacer(acheteur, blockchain);

    // Affichage de la blockchain après suppression des achats
    printf("Blockchain après suppression des achats de la personne %d :\n", acheteur);
    afficher_blockchain(blockchain);
    printf("\n");

    // Libération de la mémoire
    liberer_memoire_blockchain(blockchain);

    return 0;
}
