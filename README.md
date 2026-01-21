🐚 Minishell

Implémentation d’un shell Unix minimaliste en C — projet École 42.

📌 Description

Minishell est un projet dont l’objectif est de recréer un shell simplifié inspiré de bash.
Il permet de comprendre concrètement comment un interpréteur de commandes fonctionne, depuis la lecture de l’entrée utilisateur jusqu’à l’exécution des processus.

⚙️ Fonctionnalités

Exécution de commandes externes

Gestion des pipes (|)

Redirections :

entrée (<)

sortie (>, >>)

Gestion des variables d’environnement

Built-ins implémentés :

echo

cd

pwd

export

unset

env

exit

Gestion des signaux (SIGINT, SIGQUIT)

Comportement proche de bash dans les cas standards

🧠 Notions abordées

Création et gestion des processus (fork, execve, wait)

Manipulation des descripteurs de fichiers

Communication inter-processus

Parsing de commandes et gestion des erreurs

Gestion de la mémoire en C

Gestion des signaux Unix

🧩 Ce que ce projet m’a apporté

Une meilleure compréhension du fonctionnement interne d’un système Unix

Une approche plus rigoureuse de la gestion des erreurs et des ressources

Une vision concrète de la chaîne complète : entrée utilisateur → parsing → exécution

Une amélioration de la structuration du code sur un projet de taille conséquente

⚠️ Difficultés rencontrées

La gestion correcte des signaux en fonction du contexte (shell / processus enfant)

Le parsing des commandes complexes avec redirections et pipes

La gestion fine des descripteurs de fichiers pour éviter les fuites

La reproduction fidèle de certains comportements de bash

Ces points ont nécessité de nombreux tests et itérations.

🏗️ Structure du projet
minishell/
├── src/
│   ├── parsing/
│   ├── execution/
│   ├── builtins/
│   ├── signals/
│   └── utils/
├── include/
│   └── minishell.h
├── Makefile
└── README.md

▶️ Compilation et exécution
make
./minishell

🧪 Tests

Comparaison manuelle avec le comportement de bash

Vérification de la gestion mémoire avec Valgrind

Tests des cas d’erreur et des signaux

📚 Contexte

Projet réalisé dans le cadre du cursus de l’École 42.

👤 Auteur

Zahi Mata
École 42
