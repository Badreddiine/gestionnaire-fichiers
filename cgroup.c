#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <sys/stat.h>
#include <unistd.h>

/*
 * Usage: cgroup [chemin_fichier] [groupe]
 */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [chemin_fichier] [groupe]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *chemin = argv[1];
    const char *nom_groupe = argv[2];

    /* Récupérer les infos du groupe */
    struct group *gr = getgrnam(nom_groupe);
    if (gr == NULL) {
        fprintf(stderr, "Groupe introuvable : %s\n", nom_groupe);
        return EXIT_FAILURE;
    }

    /* Récupérer l'UID actuel du fichier (pour ne pas le changer) */
    struct stat st;
    if (stat(chemin, &st) == -1) {
        perror("Erreur stat");
        return EXIT_FAILURE;
    }

    /* Changer le groupe sans toucher au propriétaire */
    if (chown(chemin, st.st_uid, gr->gr_gid) == -1) {
        perror("Erreur chown");
        return EXIT_FAILURE;
    }

    printf("Groupe de '%s' change en '%s' (GID=%d)\n",
           chemin, nom_groupe, gr->gr_gid);
    return EXIT_SUCCESS;
}
