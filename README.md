# Gestionnaire de Fichiers Unix

Un ensemble d'utilitaires en ligne de commande pour gérer les fichiers sous Unix/Linux.

## Commandes disponibles

| Commande   | Description                              |
|------------|------------------------------------------|
| `attr`     | Affiche les attributs d'un fichier       |
| `cdroit`   | Modifie les permissions d'un fichier     |
| `cgroup`   | Change le groupe d'un fichier            |
| `cowner`   | Change le propriétaire d'un fichier      |
| `suprimer` | Supprime un fichier                      |

## Compilation

```bash
make
```

## Utilisation

```bash
attr [nom_fichier]
cdroit [chemin_fichier] [U/G/O] [R/W/X]
cgroup [chemin_fichier] [groupe]
cowner [chemin_fichier] [utilisateur]
suprimer [chemin_fichier]
```
## ls
Compiler
gcc ls.c -o mon_ls
Exemples
./mon_ls
./mon_ls /etc
./mon_ls -l
./mon_ls -la
./mon_ls -lh /var/log
./mon_ls -alh .
gcc mkdir.c -o mon_mkdir
gcc rmdir.c -o mon_rmdir
2. Tester mkdir
bash# Créer un dossier simple
./mon_mkdir test

# Créer des dossiers imbriqués avec -p
./mon_mkdir -p a/b/c
3. Tester rmdir
bash# Supprimer un dossier vide
./mon_rmdir test

# Supprimer des dossiers imbriqués avec -p (feuille → racine)
./mon_rmdir -p a/b/c
