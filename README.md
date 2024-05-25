# Analyseur d'adresses IP

Ce programme en C permet d'analyser une adresse IPv4 avec un masque en notation CIDR. Il extrait l'adresse IP, valide le masque CIDR, décompose l'adresse IPv4 en octets, détermine la classe de l'adresse IP, identifie si elle est publique ou privée, détermine le type d'adresse IP (localhost, broadcast, multicast, etc.), et calcule l'adresse réseau et l'adresse hôte.

## Prérequis

- Un compilateur C (par exemple, GCC pour Linux)
- Sur Windows, la bibliothèque ws2_32 est nécessaire pour utiliser les fonctions de gestion des sockets.

## Utilisation

Compilez le programme en utilisant la commande suivante :

'''sh
gcc main.c fonctionIP.c -o main.exe
'''


ou avec le Makefile :

'''sh
make
'''


Exécutez le programme en saisissant l'adresse IPv4 avec un masque CIDR lorsqu'il est demandé. Par exemple :

'''sh
Entrez une adresse IPv4 avec un masque en notation CIDR (par exemple, 192.168.1.1/24): 192.168.1.1/24
'''


## Fonctionnalités

- **Validation de l'adresse IPv4 et du masque CIDR** : La fonction `isValidIPv4` vérifie si une chaîne donnée est une adresse IPv4 valide.
- **Extraction de l'adresse IP** : La fonction `extractIPAddress` extrait l'adresse IP à partir d'une chaîne de caractères contenant une adresse IPv4 avec un masque CIDR.
- **Validation et conversion du masque CIDR** : La fonction `validateCIDRMask` valide et convertit le masque CIDR en un entier.
- **Décomposition de l'adresse IPv4** : La fonction `decomposeIPv4` décompose une adresse IPv4 en octets et stocke les valeurs dans une structure.
- **Détermination de la classe de l'adresse IP** : La fonction `analyseClass` détermine la classe de l'adresse IP (A, B, C, etc.).
- **Identification de l'adresse IP comme publique ou privée** : La fonction `isPrivateIP` identifie si une adresse IP est publique ou privée en vérifiant si elle se trouve dans l'une des plages d'adresses privées.
- **Détermination du type d'adresse IP** : La fonction `getIPAddressType` détermine le type d'adresse IP (localhost, broadcast, multicast, etc.).
- **Calcul de l'adresse réseau et de l'adresse hôte** : La fonction `calculateNetworkAndHost` calcule l'adresse réseau et l'adresse hôte à partir de l'adresse IP et du masque CIDR.

## Auteur

Ce programme a été écrit par Arthur Colson et Maxime Lacoste
