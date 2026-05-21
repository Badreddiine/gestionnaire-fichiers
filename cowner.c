#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Usage: cowner [chemin_fichier] [utilisateur]
 */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [chemin_fichier] [utilisateur]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *chemin = argv[1];
    const char *nom_user = argv[2];

    /* Récupérer les infos de l'utilisateur */
    struct passwd *pw = getpwnam(nom_user);
    if (pw == NULL) {
        fprintf(stderr, "Utilisateur introuvable : %s\n", nom_user);
        return EXIT_FAILURE;
    }

    /* Récupérer le GID actuel du fichier (pour ne pas le changer) */
    struct stat st;
    if (stat(chemin, &st) == -1) {
        perror("Erreur stat");
        return EXIT_FAILURE;
    }

    /* Changer le propriétaire sans toucher au groupe */
    if (chown(chemin, pw->pw_uid, st.st_gid) == -1) {
        perror("Erreur chown");
        return EXIT_FAILURE;
    }

    printf("Proprietaire de '%s' change en '%s' (UID=%d)\n",
           chemin, nom_user, pw->pw_uid);
    return EXIT_SUCCESS;
}
