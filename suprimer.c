#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * Usage: suprimer [chemin_fichier]
 */

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [chemin_fichier]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *chemin = argv[1];

    /* Confirmation avant suppression */
    printf("Confirmer la suppression de '%s' ? [o/N] : ", chemin);
    int c = getchar();
    if (c != 'o' && c != 'O') {
        printf("Suppression annulee.\n");
        return EXIT_SUCCESS;
    }

    if (unlink(chemin) == -1) {
        perror("Erreur suppression");
        return EXIT_FAILURE;
    }

    printf("Fichier '%s' supprime avec succes.\n", chemin);
    return EXIT_SUCCESS;
}
