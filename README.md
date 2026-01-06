# Acquisition et Traitement de Données : Joystick Analogique avec ESP32

Ce projet porte sur la conception d'un système d'acquisition et de traitement de données pour un joystick analogique utilisant un microcontrôleur ESP32 sous l'IDE Arduino. Ce travail s'inscrit dans le cadre du cours Programmation Orientée Objet (GEI1084).

## Description du Projet
L'objectif est de transformer des signaux analogiques bruts en données numériques exploitables pour le contrôle de systèmes robotiques ou d'interfaces. Le programme gère la lecture des axes, applique des filtres logiciels (zone morte) et effectue des calculs trigonométriques pour fournir la vitesse et la direction.

## Spécifications Techniques

### Matériel
* Microcontrôleur : ESP32
* Entrée : Joystick analogique (2 axes et 1 bouton)
* Communication : Série (Vitesse de transmission : 115200 baud)

### Brochage (Pinout)
| Composant | Broche ESP32 | Fonction |
| :--- | :--- | :--- |
| VRX | GPIO 34 | Axe X (Analogique) |
| VRY | GPIO 35 | Axe Y (Analogique) |
| SW | GPIO 32 | Bouton (Digital avec résistance de tirage interne) |

---

## Algorithmes de Traitement

Le programme implémente les étapes de traitement de données suivantes :

1. **Normalisation** : Conversion des valeurs du convertisseur analogique-numérique (0-4095) vers un référentiel centré (-512 à 512).
2. **Zone Morte (Deadzone)** : Application d'un seuil de sécurité pour éliminer le bruit électronique au repos.
3. **Calcul de Vecteur** :
    * **Vitesse** : Calcul de la magnitude via le théorème de Pythagore, normalisée sur une échelle de 0 à 100%.
    * **Direction** : Utilisation de la fonction atan2 pour déterminer l'angle en degrés (0-360°).
