#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int remove_dir(const char *path) {
    if (rmdir(path) == -1) {
        perror("Erreur rmdir");
        return -1;
    }
    printf("Repertoire supprime : %s\n", path);
    return 0;
}

void remove_dir_recursive(char *path) {
    /* Supprime d'abord la feuille, puis remonte vers la racine */
    char *p;

    /* Supprimer d'abord le chemin complet */
    if (remove_dir(path) == -1) return;

    /* Remonter segment par segment */
    p = path + strlen(path) - 1;
    while (p > path) {
        /* Reculer jusqu'au '/' précédent */
        while (p > path && *p != '/') p--;
        if (*p == '/') {
            *p = '\0';
            if (remove_dir(path) == -1) break;
            p--;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-p") == 0) {
        if (argc < 3) {
            fprintf(stderr, "usage: rmdir -p <chemin>\n");
            return 1;
        }
        char path[256];
        strncpy(path, argv[2], sizeof(path) - 1);
        path[sizeof(path) - 1] = '\0';
        remove_dir_recursive(path);
    } else if (argc > 1) {
        remove_dir(argv[1]);
    } else {
        fprintf(stderr, "usage: rmdir [-p] <chemin>\n");
        return 1;
    }
    return 0;
}
