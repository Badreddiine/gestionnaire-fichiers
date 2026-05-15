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
    snprintf(tmp, sizeof(tmp), "%s", path); 
    for (p = tmp + 1; *p; p++) { 
        if (*p == '/') { 
            *p = '\0'; 
            mkdir(tmp, 0755); 
            *p = '/'; 
        } 
    } 
    make_dir(tmp); 
} 
 
int main(int argc, char *argv[]) { 
    int recursive = 0; 
    if (argc > 1 && strcmp(argv[1], "-p") == 0) { 
    recursive = 1; 
   make_dir_recursive(argv[2]); 
   } else if (argc > 1) { 
   make_dir(argv[1]); 
    } 
return 0; 
} 
