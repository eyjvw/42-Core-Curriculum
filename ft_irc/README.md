# ft_irc

*Ce projet a été créé dans le cadre du cursus 42 par sbonneau.*

## Description

`ft_irc` (exécutable `ircserv`) est un serveur IRC minimal en C++98. Il implémente l'acceptation de connexions TCP non-bloquantes, l'authentification par mot de passe (PASS), la gestion des utilisateurs (NICK/USER), et des fonctionnalités de base des salons (JOIN/INVITE/KICK/TOPIC/MODE) ainsi que l'envoi de messages (PRIVMSG).

Le serveur utilise `poll()` pour la gestion d'IO et traite les commandes/réponses via des modules `MSG`, `CMD` et `RPL`.

## Compilation

```bash
make
```

Le Makefile est configuré pour compiler en C++98 avec les flags `-Werror -Wall -Wextra -std=c++98 -g3`.

## Exécution

Usage :

```bash
./ircserv <PASSWORD> <PORT>
# Exemple :
./ircserv mySecretPass 6667
```

- `<PASSWORD>` : mot de passe requis pour l'authentification PASS
- `<PORT>` : port TCP (1-65535)

Le serveur réagit à `SIGINT` pour déclencher un arrêt propre.

## Règles Makefile

- `make` / `make all` : compiler le binaire `ircserv`
- `make clean` : supprimer les fichiers objets (`obj/`)
- `make fclean` : supprimer le binaire
- `make re` : `fclean` puis `all`

## Structure du projet

```
ft_irc/
├── Makefile                     - règle de build
├── README.md                    - ce fichier
├── headers/                     - en-têtes (.hpp/.h)
├── srcs/                        - sources C++
│   ├── main.cpp                 - point d'entrée, vérification des args
│   ├── Server.cpp               - boucle principale, accept, poll, auth
│   ├── Client.cpp               - gestion des clients
│   ├── Channel.cpp              - gestion des salons
│   ├── MSG.cpp                  - parsing/formatage des messages
│   ├── RPL.cpp                  - génération des replies (RPL/ERR)
│   ├── Package.cpp              - structure temporaire des commandes
│   ├── Ft.cpp                   - utilitaires (time, parsing, etc.)
│   ├── Errors.cpp               - codes d'erreur/constantes
│   └── cmds/                    - implémentation des commandes IRC
│       ├── CMD.cpp
│       ├── Mode.cpp
│       ├── Join.cpp
│       ├── Invite.cpp
│       ├── Kick.cpp
│       ├── Topic.cpp
│       ├── Priv.cpp
│       ├── Nick.cpp
│       └── User.cpp
```

## Commandes supportées (implémentées)

- PASS, NICK, USER : authentification et identification
- JOIN, PART (via Join), MODE : création/gestion de salons
- INVITE : invitation dans un salon
- KICK : expulsion d'un utilisateur
- TOPIC : lecture/écriture du topic d'un salon
- PRIVMSG / NOTICE (via Priv) : envoi de messages privés ou vers salons

> Remarque : la liste ci-dessus correspond aux implémentations présentes dans `srcs/cmds/`.

## Comportement important

- Le serveur attend d'abord la commande PASS, puis NICK/USER pour authentifier un client.
- Les messages entrants sont lus avec un buffer par client et traités ligne par ligne en s'appuyant sur CRLF comme séparateur.
- Les clients inactifs ou déconnectés sont nettoyés correctement et leurs descripteurs fermés.

## Dépendances / Environnement

- compilateur C++ compatible C++98 (`g++` / `clang++`)
- système POSIX (Linux recommandé)

## Tests et débogage

- Compiler avec `make` puis lancer `./ircserv <PASS> <PORT>`.
- Se connecter avec un client IRC (ex : `irssi`, `weechat`) ou `telnet`/`nc` pour tester les commandes manuellement.

## Ressources utiles

- RFC 1459 — Internet Relay Chat Protocol: https://datatracker.ietf.org/doc/html/rfc1459
- man pages: `socket(2)`, `bind(2)`, `listen(2)`, `accept(2)`, `poll(2)`, `fcntl(2)`


---

Si tu veux, je peux :
- ajouter des exemples d'échanges IRC (séquence PASS/NICK/USER/JOIN/PRIVMSG)
- détailler les codes de reply implémentés dans `srcs/RPL.cpp`
- exécuter une compilation test et afficher les erreurs éventuelles

Dis-moi ce que tu préfères que je fasse ensuite.