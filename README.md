# TP-SOCKETS

Travaux Pratiques sur la programmation réseau avec les sockets en C (TCP & UDP).

---

## Structure du projet

```
TP-SOCKETS/
├── C_S_TCP/          # Client-Serveur TCP (simple)
├── C_S_TCP_Proc/     # Client-Serveur TCP avec processus (fork)
└── C_S_UDP/          # Client-Serveur UDP
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

Le serveur reste en attente de connexions.

### 2. Lancer le client

Ouvre un **deuxième terminal** et exécute :

```bash
./client localhost [nom]
```

> Remplace `[nom]` par ton prénom ou un identifiant quelconque.

**Exemple :**
```bash
./client localhost rachid
```
