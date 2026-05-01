# TP-SOCKETS

Travaux Pratiques sur la programmation réseau avec les sockets en C (TCP & UDP).

---

## Structure du projet

```
TP_SOCKET_2/
├── C_S_TCP/
│   ├── client.c
│   ├── client
│   ├── serveur.c
│   ├── serveur
│   └── fictel
├── C_S_TCP_Proc/
│   ├── client.c
│   ├── client
│   ├── serveur.c
│   ├── serveur
│   └── fictel
├── C_S_UDP/
│   ├── client.c
│   ├── client
│   ├── serveur.c
│   ├── serveur
│   └── fictel
└── TPs-2526- SOCKET.docx
```

---

## Le fichier `fictel`

Chaque dossier contient son propre fichier `fictel`. Le serveur l'utilise pour retrouver le numéro associé à un nom :

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
## Recompiler (optionnel)
 
Si tu modifies les sources :
 
```bash
gcc serveur.c -o serveur
gcc client.c -o client
```


## Utilisation

### Étape 1 — Terminal 1 : lancer le serveur

```bash
cd C_S_TCP        # ou C_S_TCP_Proc ou C_S_UDP
./serveur
```

Le serveur se met en attente de connexions.

### Étape 2 — Terminal 2 : lancer le client

```bash
cd C_S_TCP        # même dossier que le serveur
./client localhost [nom]
```

> Remplace `[nom]` par un nom présent dans `fictel`.

**Exemples :**

```bash
./client localhost rachid
# → 0001

./client localhost alami
# → 6768

./client localhost bouchra
# → 6929
```

---


## Notes

- Le fichier `fictel` doit rester dans le même dossier que `./serveur`.
- Lance toujours le serveur **avant** le client.
- Pour tester sur un autre PC du réseau local, remplace `localhost` par l'adresse IP du serveur.
