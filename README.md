#M5StickC Cyber Watch

Montre gestuelle minimaliste pour **M5StickC** et **M5StickC Plus**, au style cyber sombre, utilisant l’IMU pour afficher l’heure par mouvement du poignet.

---

## Fonctionnalités

* Affichage de l’heure par geste du poignet
* Format 24h ou 12h (AM/PM)
* Réglage de la sensibilité du geste
* Sauvegarde des paramètres en EEPROM
* Affichage de la batterie
* Commandes via Serial
* Aucun son (buzzer désactivé)
* Thème cyber sombre (noir / vert)

---

## Matériel requis

* M5StickC ou M5StickC Plus
* Câble USB

---

## Logiciel requis

* Arduino IDE
* Support ESP32 installé
* Bibliothèque officielle M5StickC

---

## Installation

1. Ouvrir Arduino IDE
2. Installer la bibliothèque M5StickC
3. Copier le fichier `.ino` dans un nouveau projet
4. Sélectionner la carte M5StickC ou M5StickC Plus
5. Compiler et téléverser

---

## Utilisation

### Geste

* Lever le poignet pour afficher l’heure

### Boutons

* Bouton A : ouvrir / fermer le menu
* Bouton B : naviguer dans le menu
* Appui long sur le bouton A : modifier ou valider

### Menu

1. Sensibilité du geste
2. Format de l’heure
3. Sauvegarder les réglages

---

## Commandes Serial

Ouvrir le moniteur série à 115200 bauds :

```
sens=1.5
12h
24h
```

---

## Sauvegarde

Les réglages sont stockés en EEPROM et conservés après redémarrage.

---

## Compatibilité

* Compatible M5StickC
* Compatible M5StickC Plus

---

## Limitations

* Pas d’heures silencieuses
* Pas de vibration
* Pas de son

---

## Licence

Projet libre pour usage personnel et éducatif.

---

## Auteur

Projet M5StickC
