#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/*
 * Usage: cdroit [chemin_fichier] [U/G/O] [R/W/X]
 * Exemple: cdroit fichier.txt U R   -> ajoute la lecture pour le proprietaire
 */

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s [chemin_fichier] [U/G/O] [R/W/X]\n", argv[0]);
        fprintf(stderr, "  U = Proprietaire, G = Groupe, O = Autres\n");
        fprintf(stderr, "  R = Lecture,      W = Ecriture, X = Execution\n");
        return EXIT_FAILURE;
    }

    const char *chemin = argv[1];
    char qui   = argv[2][0]; /* U / G / O */
    char droit = argv[3][0]; /* R / W / X */

    /* Convertir en majuscules */
    if (qui   >= 'a' && qui   <= 'z') qui   -= 32;
    if (droit >= 'a' && droit <= 'z') droit -= 32;

    /* Vérifier les arguments */
    if (qui != 'U' && qui != 'G' && qui != 'O') {
        fprintf(stderr, "Cible invalide : utilisez U (user), G (groupe) ou O (autres)\n");
        return EXIT_FAILURE;
    }
    if (droit != 'R' && droit != 'W' && droit != 'X') {
        fprintf(stderr, "Droit invalide : utilisez R (read), W (write) ou X (execute)\n");
        return EXIT_FAILURE;
    }

    /* Récupérer les permissions actuelles */
    struct stat st;
    if (stat(chemin, &st) == -1) {
        perror("Erreur stat");
        return EXIT_FAILURE;
    }

    mode_t mode = st.st_mode;

    /* Construire le bit à ajouter */
    mode_t bit = 0;
    if (qui == 'U') {
        if      (droit == 'R') bit = S_IRUSR;
        else if (droit == 'W') bit = S_IWUSR;
        else                   bit = S_IXUSR;
    } else if (qui == 'G') {
        if      (droit == 'R') bit = S_IRGRP;
        else if (droit == 'W') bit = S_IWGRP;
        else                   bit = S_IXGRP;
    } else { /* O */
        if      (droit == 'R') bit = S_IROTH;
        else if (droit == 'W') bit = S_IWOTH;
        else                   bit = S_IXOTH;
    }

    /* Basculer le bit (toggle) */
    if (mode & bit) {
        mode &= ~bit;
        printf("Permission %c%c supprimee sur %s\n", qui, droit, chemin);
    } else {
        mode |= bit;
        printf("Permission %c%c ajoutee sur %s\n", qui, droit, chemin);
    }

    if (chmod(chemin, mode) == -1) {
        perror("Erreur chmod");
        return EXIT_FAILURE;
    }

    printf("Nouvelles permissions appliquees avec succes.\n");
    return EXIT_SUCCESS;
}
