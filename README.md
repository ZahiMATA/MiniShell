# Minishell

> Shell Unix simplifié — Projet École 42

---

## 🎯 Objectif

Reproduire le fonctionnement de base d’un shell Unix afin de comprendre
le cycle d’exécution des commandes, la gestion des processus et les mécanismes
internes d’un système Linux.

---

## 🧠 Ce que fait le programme

Minishell permet :
- d’exécuter des commandes système
- de gérer les pipes et redirections
- d’interpréter l’entrée utilisateur
- de gérer l’environnement et les signaux

---

## ⚙️ Fonctionnalités

- Exécution de commandes (`ls`, `cat`, `echo`, etc.)
- Pipes (`|`)
- Redirections (`>`, `>>`, `<`, `<<`)
- Variables d’environnement
- Builtins :
  - `cd`
  - `echo`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Gestion des signaux (`Ctrl+C`, `Ctrl+\`)

---

## 🛠️ Notions techniques abordées

- Processus (`fork`, `execve`, `wait`)
- Communication inter-processus (pipes)
- Signaux Unix
- Parsing de commandes
- Gestion mémoire et erreurs en C
- Interaction avec le système d’exploitation

---

## 🖥️ Exemple

```bash
$ echo "hello world" | grep hello > output.txt
$ cat output.txt
hello world
🚀 Apports du projet

Ce projet m’a permis de :

comprendre le fonctionnement interne d’un shell

mieux appréhender les processus et les flux système

développer une logique proche des environnements de production

renforcer ma capacité à diagnostiquer des comportements système

📌 Contexte

Projet réalisé dans le cadre du cursus de l’École 42
Formation orientée autonomie, rigueur et compréhension des systèmes.

🔍 Pourquoi ce projet est pertinent

Minishell est directement lié aux métiers de :

l’administration systèmes

l’infrastructure IT

la production

la sécurité et l’analyse d’incidents

Il démontre une compréhension concrète du fonctionnement d’un système Unix.
