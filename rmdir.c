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
    /* Supprime de la feuille vers la racine */ 
    char *p = path + strlen(path) - 1; 
    while (p > path) { 
        if (remove_dir(path) == -1) break; 
        while (p > path && *p != '/') p--; 
        if (*p == '/') *p = '\0'; 
    } 
    if (p == path) remove_dir(path); 
} 
 
int main(int argc, char *argv[]) { 
    if (argc > 1 && strcmp(argv[1], "-p") == 0) { 
        char path[256]; 
        strncpy(path, argv[2], sizeof(path)); 
        remove_dir_recursive(path); 
    } else if (argc > 1) { 
        remove_dir(argv[1]); 
    } 
    return 0; 
}
