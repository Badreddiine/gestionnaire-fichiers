#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

/* Options activées par les flags */
typedef struct {
    int all;     /* -a : fichiers cachés */
    int detail;  /* -l : format long     */
    int human;   /* -h : tailles lisibles */
} Options;

/* Formate une taille en B, K, M, G */
void fmt_taille(off_t taille, char *buf) {
    const char *unites[] = {"B", "K", "M", "G", "T"};
    double v = (double)taille;
    int i = 0;
    while (v >= 1024.0 && i < 4) { v /= 1024.0; i++; }
    if (i == 0) sprintf(buf, "%4lld%s", (long long)v, unites[i]);
    else        sprintf(buf, "%4.1f%s", v, unites[i]);
}
/* Affiche les permissions (ex: drwxr-xr-x) */
void afficher_perms(mode_t mode) {
    putchar(S_ISDIR(mode) ? 'd' : S_ISLNK(mode) ? 'l' : '-');
    putchar(mode & S_IRUSR ? 'r' : '-');
    putchar(mode & S_IWUSR ? 'w' : '-');
    putchar(mode & S_IXUSR ? 'x' : '-');
    putchar(mode & S_IRGRP ? 'r' : '-');
    putchar(mode & S_IWGRP ? 'w' : '-');
    putchar(mode & S_IXGRP ? 'x' : '-');
    putchar(mode & S_IROTH ? 'r' : '-');
    putchar(mode & S_IWOTH ? 'w' : '-');
    putchar(mode & S_IXOTH ? 'x' : '-');
}

/* Affiche une entrée en format long (-l) */
void afficher_detail(const char *chemin, const char *nom,
                     const Options *opt) {struct stat st;
    char full[4096];
    snprintf(full, sizeof(full), "%s/%s", chemin, nom);

    if (lstat(full, &st) == -1) { perror(nom); return; }

    /* Permissions + liens */
    afficher_perms(st.st_mode);
    printf(" %3lu", (unsigned long)st.st_nlink);

    /* Propriétaire et groupe */
    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);
    printf(" %-8s %-8s",
           pw ? pw->pw_name : "?",
           gr ? gr->gr_name : "?");/* Taille */
    if (opt->human) {
        char buf[16];
        fmt_taille(st.st_size, buf);
        printf(" %6s", buf);
    } else {
        printf(" %8lld", (long long)st.st_size);
    }

    /* Date de modification */
char date[20];
    strftime(date, sizeof(date), "%b %e %H:%M",
             localtime(&st.st_mtime));
    printf(" %s %s\n", date, nom);
}

/* Liste le contenu d'un dossier */
void lister(const char *chemin, const Options *opt) {
    DIR *dir = opendir(chemin);
    if (!dir) { perror(chemin); return; }

    struct dirent *e;
    while ((e = readdir(dir)) != NULL) {
        if (!opt->all && e->d_name[0] == '.')
            continue;
        if (opt->detail)
            afficher_detail(chemin, e->d_name, opt);
        else
            printf("%s\n", e->d_name);
    }
    closedir(dir);
}
int main(int argc, char *argv[]) {
    Options opt = {0, 0, 0};
    const char *chemin = ".";

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                if      (argv[i][j] == 'a') opt.all    = 1;
                else if (argv[i][j] == 'l') opt.detail = 1;
                else if (argv[i][j] == 'h') opt.human  = 1;
                else {
                    fprintf(stderr, "option inconnue: -%c\n", argv[i][j]);
                    fprintf(stderr, "usage: ls [-alh] [dossier]\n");
                    return 1;
                }
            }
        } else {
            chemin = argv[i];
        }
    }
  lister(chemin, &opt);
    return 0;
}
