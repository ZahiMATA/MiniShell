nishell — Shell Unix simplifié (École 42)
🎯 Objectif du projet

Développer un shell Unix simplifié en C, permettant de comprendre en profondeur le fonctionnement d’un système Linux : processus, exécution de commandes, redirections, pipes et signaux.

Ce projet vise à reproduire le comportement de base d’un shell (bash), sans utiliser de bibliothèques externes complexes.

🧠 Compétences techniques mises en œuvre

Gestion des processus (fork, execve, wait)

Communication inter-processus via pipes

Gestion des redirections (>, >>, <, <<)

Manipulation des signaux (SIGINT, SIGQUIT)

Gestion de l’environnement système (variables d’environnement)

Parsing et interprétation de commandes utilisateur

Gestion des erreurs et des cas limites

Programmation bas niveau en C (rigueur mémoire et logique)

⚙️ Fonctionnalités principales

Exécution de commandes simples (ls, echo, pwd, etc.)

Gestion des pipes (cmd1 | cmd2)

Redirections d’entrée et de sortie

Variables d’environnement ($PATH, $HOME, etc.)

Commandes intégrées (builtins) :

cd

echo

pwd

export

unset

env

exit

Gestion correcte des signaux pendant l’exécution des commandes

🖥️ Pourquoi ce projet est important

Minishell permet de comprendre ce qui se passe réellement sous le capot lorsqu’une commande est exécutée sur un système Linux.

Il apporte une vision concrète de :

la gestion des processus

la communication entre programmes

la manière dont un système d’exploitation orchestre l’exécution des tâches

Ces notions sont directement utiles pour :

l’administration systèmes

la production IT

la compréhension des logs et incidents système

les environnements SOC et sécurité

🧪 Exemple d’utilisation
$ echo "hello world" | grep hello > output.txt
$ cat output.txt
hello world

🚀 Ce que j’ai appris grâce à ce projet

Lire et comprendre des logs et erreurs système

Diagnostiquer des comportements anormaux liés aux processus

Appliquer une logique rigoureuse proche des environnements de production

Développer une forte autonomie et une méthodologie de résolution de problèmes

📌 Contexte

Projet réalisé dans le cadre du cursus de l’École 42, formation basée sur l’autonomie, la pratique et la compréhension approfondie des systèmes.

⭐ Note pour les recruteurs

Ce projet met en avant ma compréhension des systèmes Unix/Linux, des processus et de la logique bas niveau, compétences essentielles pour des rôles en administration systèmes, infrastructure, production IT ou sécurité.
