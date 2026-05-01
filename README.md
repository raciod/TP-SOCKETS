# TP-SOCKETS

Travaux Pratiques sur la programmation réseau avec les sockets en C (TCP & UDP).

---

## Structure du projet

```
TP-SOCKETS/
├── C_S_TCP/          # Client-Serveur TCP (simple)
├── C_S_TCP_Proc/     # Client-Serveur TCP avec processus (fork)
├── C_S_UDP/          # Client-Serveur UDP
└── fictel            # Fichier de correspondance nom → numéro
```

---

## Le fichier `fictel`

Le serveur utilise ce fichier pour retrouver le numéro associé à un nom :

```
6768 alami
6929 bouchra
6024 najwa
6123 imane
6024 brahim
6127 mahfoud
6769 sekkaki
6024 figuigui
0001 rachid
```

---

## Compilation

Dans chaque dossier, compile avec `make` ou directement avec `gcc` :

```bash
gcc serveur.c -o serveur
gcc client.c -o client
```

---

## Utilisation

### 1. Lancer le serveur

Ouvre un **premier terminal**, navigue vers le dossier souhaité et exécute :

```bash
./serveur
```

Le serveur reste en attente de connexions et consulte `fictel` pour répondre.

### 2. Lancer le client

Ouvre un **deuxième terminal** et exécute :

```bash
./client localhost [nom]
```

> Remplace `[nom]` par un nom présent dans le fichier `fictel`.

**Exemples :**
```bash
./client localhost rachid
# → 0001

./client localhost alami
# → 6768

./client localhost bouchra
# → 6929
```

Le serveur recherche le nom dans `fictel` et renvoie le numéro correspondant.

---

## Notes

- Le fichier `fictel` doit se trouver dans le même répertoire que `./serveur`.
- Assure-toi que le serveur est bien lancé **avant** le client.
- Pour tester en réseau local, remplace `localhost` par l'adresse IP de la machine serveur.
- Si le nom n'est pas trouvé dans `fictel`, le serveur retourne une erreur ou une réponse (????).

---
