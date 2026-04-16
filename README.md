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
