#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void afficher_permissions(mode_t mode) {
    printf("Permissions : ");
    printf((S_ISDIR(mode))  ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [nom_fichier]\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        perror("Erreur stat");
        return EXIT_FAILURE;
    }

    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);

    printf("=== Attributs de : %s ===\n", argv[1]);
    printf("Type        : ");
    if      (S_ISREG(st.st_mode))  printf("Fichier regulier\n");
    else if (S_ISDIR(st.st_mode))  printf("Repertoire\n");
    else if (S_ISLNK(st.st_mode))  printf("Lien symbolique\n");
    else if (S_ISCHR(st.st_mode))  printf("Peripherique caractere\n");
    else if (S_ISBLK(st.st_mode))  printf("Peripherique bloc\n");
    else if (S_ISFIFO(st.st_mode)) printf("FIFO/Pipe\n");
    else                            printf("Inconnu\n");

    afficher_permissions(st.st_mode);
    printf("Proprietaire: %s (UID=%d)\n", pw ? pw->pw_name : "inconnu", st.st_uid);
    printf("Groupe      : %s (GID=%d)\n", gr ? gr->gr_name : "inconnu", st.st_gid);
    printf("Taille      : %lld octets\n", (long long)st.st_size);
    printf("Inode       : %llu\n", (unsigned long long)st.st_ino);
    printf("Liens durs  : %lu\n", (unsigned long)st.st_nlink);

    char buf[64];
    struct tm *tm_info;

    tm_info = localtime(&st.st_atime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Dernier acces       : %s\n", buf);

    tm_info = localtime(&st.st_mtime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Derniere modification: %s\n", buf);

    tm_info = localtime(&st.st_ctime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Dernier changement  : %s\n", buf);

    return EXIT_SUCCESS;
}
