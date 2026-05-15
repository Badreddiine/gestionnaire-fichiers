#!/bin/bash

# ============================================================
#  Script de compilation et lancement - Fedora
#  Usage : ./lancer_tout.sh
# ============================================================

ROUGE='\033[0;31m'
VERT='\033[0;32m'
JAUNE='\033[1;33m'
BLEU='\033[0;34m'
RESET='\033[0m'

ok()  { echo -e "${VERT}[OK]${RESET}  $1"; }
err() { echo -e "${ROUGE}[ERREUR]${RESET} $1"; }
info(){ echo -e "${BLEU}[INFO]${RESET} $1"; }
sep() { echo -e "${JAUNE}--------------------------------------------${RESET}"; }

# ============================================================
# 1. Vérifier que gcc est installé
# ============================================================
sep
info "Vérification de gcc..."
if ! command -v gcc &>/dev/null; then
    err "gcc non trouvé. Installation en cours..."
    sudo dnf install -y gcc
fi
ok "gcc disponible : $(gcc --version | head -1)"

# ============================================================
# 2. Compiler tous les fichiers C
# ============================================================
sep
info "Compilation des programmes..."

compiler() {
    local src=$1
    local out=$2
    if [ -f "$src" ]; then
        gcc "$src" -o "$out" 2>/dev/null && ok "Compilé : $src → $out" \
                                         || err "Échec compilation : $src"
    else
        err "Fichier introuvable : $src"
    fi
}

compiler mkdir.c   mon_mkdir
compiler rmdir.c   mon_rmdir
compiler ls.c      mon_ls
compiler fork1.c   mon_fork1
compiler fork2.c   mon_fork2

# ============================================================
# 3. Tests mkdir
# ============================================================
sep
info "Test mon_mkdir..."
if [ -f ./mon_mkdir ]; then
    ./mon_mkdir test_simple
    ./mon_mkdir -p dossier_a/sous_b/sous_c
    ok "mkdir terminé"
else
    err "mon_mkdir introuvable"
fi

# ============================================================
# 4. Test ls
# ============================================================
sep
info "Test mon_ls..."
if [ -f ./mon_ls ]; then
    echo "--- liste simple ---"
    ./mon_ls .
    echo "--- format long ---"
    ./mon_ls -lh .
    ok "ls terminé"
else
    err "mon_ls introuvable"
fi

# ============================================================
# 5. Tests rmdir
# ============================================================
sep
info "Test mon_rmdir..."
if [ -f ./mon_rmdir ]; then
    ./mon_rmdir test_simple
    ./mon_rmdir -p dossier_a/sous_b/sous_c
    ok "rmdir terminé"
else
    err "mon_rmdir introuvable"
fi

# ============================================================
# 6. Test fork1 (copies de programmes)
# ============================================================
sep
info "Test mon_fork1 — 2 copies de 'ls' et 'pwd'..."
if [ -f ./mon_fork1 ]; then
    ./mon_fork1 2 ls pwd
    ok "fork1 terminé"
else
    err "mon_fork1 introuvable"
fi

# ============================================================
# 7. Test fork2 (liste chaînée)
# ============================================================
sep
info "Test mon_fork2 — liste chaînée (entrée automatique)..."
if [ -f ./mon_fork2 ]; then
    # On envoie l'entrée automatiquement via echo
    printf "2\nls\npwd\n" | ./mon_fork2
    ok "fork2 terminé"
else
    err "mon_fork2 introuvable"
fi

# ============================================================
# Fin
# ============================================================
sep
echo -e "${VERT}Tous les tests terminés.${RESET}"
