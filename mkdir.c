#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

void make_dir(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("Erreur mkdir");
        exit(1);
    }
    printf("Repertoire cree : %s\n", path);
}

void make_dir_recursive(const char *path) {
    char tmp[256];
    char *p = NULL;

    snprintf(tmp, sizeof(tmp) - 1, "%s", path);

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            /* Ignorer EEXIST : le dossier intermédiaire existe déjà */
            if (mkdir(tmp, 0755) == -1 && errno != EEXIST) {
                perror("Erreur mkdir");
                exit(1);
            }
            *p = '/';
        }
    }
    /* Créer le dossier final */
    if (mkdir(tmp, 0755) == -1 && errno != EEXIST) {
        perror("Erreur mkdir");
        exit(1);
    }
    printf("Repertoire cree : %s\n", tmp);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "-p") == 0) {
        if (argc < 3) {
            fprintf(stderr, "usage: mkdir -p <chemin>\n");
            return 1;
        }
        make_dir_recursive(argv[2]);
    } else if (argc > 1) {
        make_dir(argv[1]);
    } else {
        fprintf(stderr, "usage: mkdir [-p] <chemin>\n");
        return 1;
    }
    return 0;
}
