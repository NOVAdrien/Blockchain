Projet de Blockchain Simplifiée

Ce projet implémente une blockchain simplifiée en langage C. La blockchain est composée de blocs contenant des transactions. Chaque bloc est lié au bloc précédent, et le code du bloc est calculé en fonction du code du bloc précédent et de la valeur de la transaction.

Structure du Projet

- Transaction : Une structure représentant une transaction entre un vendeur et un acheteur, avec une valeur associée.
- Block : Une structure représentant un bloc dans la blockchain. Chaque bloc contient une transaction, un code de bloc, et un pointeur vers le bloc précédent.
- Fonctions : Plusieurs fonctions sont implémentées pour gérer la blockchain, comme la création de transactions, l'ajout de blocs, la modification de transactions, et la libération de mémoire.

Fonctionnalités Implémentées

1. **Création d'une transaction** : `creation_transaction`
2. **Création du bloc genesis** : `creation_block_zero`
3. **Calcul du code de bloc** : `creation_code_block`
4. **Ajout d'un nouveau bloc** : `ajout_nouveau_block`
5. **Calcul du bilan des transactions pour une personne** : `valeur_transactions_personne`
6. **Modification d'une transaction dans la blockchain** : `modification_blockchain`
7. **Affichage de la blockchain** : `afficher_blockchain`
8. **Libération de la mémoire de la blockchain** : `liberer_memoire_blockchain`
9. **Suppression des transactions d'achat pour une personne** : `effacer`

Compilation et Exécution

Pour compiler et exécuter ce projet, suivez les étapes suivantes :

1. **Compilation** :
   - Ouvrez un terminal et naviguez jusqu'au dossier contenant le fichier `Blockchain.c`.
   - Compilez le programme avec la commande suivante :
     ```bash
     gcc Blockchain.c -o Blockchain -lm
     ```
     Le flag `-lm` est nécessaire pour lier la bibliothèque mathématique (`libm`) qui contient la fonction `fmod`.

2. **Exécution** :
   - Après la compilation, exécutez le programme avec la commande :
     ```bash
     ./Blockchain
     ```

Exemple de Sortie

Le programme affichera les étapes suivantes :
- Création du bloc genesis.
- Ajout de transactions à la blockchain.
- Affichage de la blockchain après chaque ajout.
- Calcul du bilan des transactions pour une personne donnée.
- Modification d'une transaction et affichage de la blockchain mise à jour.
- Suppression des transactions d'achat pour une personne et affichage final de la blockchain.

Libération de Mémoire

Le programme libère automatiquement la mémoire allouée pour la blockchain à la fin de l'exécution.
