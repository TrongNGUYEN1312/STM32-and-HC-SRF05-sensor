# Système de détection d'intrusion à ultrasons sur STM32 🛡️

Un système de détection d'obstacles et d'alerte d'intrusion en temps réel, construit autour d'un **microcontrôleur STM32** et d'un **capteur à ultrasons HC-SRF05**. Il suit les objets qui s'approchent, affiche leur position en direct sur un **écran TFT 128x160** et déclenche une alerte logicielle et matérielle dès qu'un objet franchit un seuil de distance critique.

<p align="center">
  <img width="740" alt="Vue d'ensemble du système" src="https://github.com/user-attachments/assets/8ed4737c-decc-4df6-a4ec-ea971ba1d950" />
</p>

## Table des matières
- [Fonctionnalités](#fonctionnalités)
- [Fonctionnement](#fonctionnement)
- [Matériel requis](#matériel-requis)
- [Câblage](#câblage)
- [Logiciels et outils](#logiciels-et-outils)
- [Structure du projet](#structure-du-projet)
- [Prise en main](#prise-en-main)
- [Licence](#licence)
- [Auteur](#auteur)

## Fonctionnalités
- **Mesure de distance en temps réel** sur une plage de travail de 0 à 10 cm.
- **Cartographie graphique en direct** sur un écran TFT 128x160, divisé en une *Zone de sécurité* et une *Zone d'intrusion*.
- **Double mécanisme d'alerte** déclenché lorsqu'un objet se trouve à une distance inférieure ou égale au seuil critique de **5 cm** :
  1. **Alerte logicielle :** le marqueur affiché sur le TFT devient noir.
  2. **Alerte matérielle :** une LED d'avertissement externe s'allume.

## Fonctionnement
1. Le STM32 envoie une impulsion de déclenchement (trigger) au HC-SRF05.
2. Le capteur émet une salve ultrasonore et renvoie une impulsion d'écho dont la largeur correspond au temps de vol.
3. Le microcontrôleur convertit la largeur de l'impulsion en distance.
4. La distance est comparée au seuil de 5 cm :

| Condition | Zone | Marqueur TFT | LED d'avertissement |
| :--- | :--- | :--- | :--- |
| `Distance > 5 cm` | Zone de sécurité | Couleur normale | ÉTEINTE |
| `Distance <= 5 cm` | Zone d'intrusion | Noir | ALLUMÉE (instantanément) |

## Matériel requis
- **Microcontrôleur :** STM32 (p. ex. STM32F103C8)
- **Capteur :** capteur de distance à ultrasons HC-SRF05
- **Écran :** TFT SPI 128x160 (p. ex. ST7735 ou compatible)
- **Autres composants :** LED, résistance de 220 Ω, fils de connexion, platine d'essai (breadboard)

## Câblage

| Composant | Broche | Broche STM32 | Remarque |
| :--- | :--- | :--- | :--- |
| **HC-SRF05** | VCC | 5V | |
| | GND | GND | |
| | TRIG | PB9 | |
| | ECHO | PB8 | |
| **TFT 128x160** | SCK / SCL | PA5 (SPI1_SCK) | |
| | SDA / MOSI | PA7 (SPI1_MOSI) | |
| | CS | PB0 | |
| | A0 / DC / RS | PB1 | |
| | RESET | PB10 | |
| | RD | VCC (3,3V / 5V) | Actif à l'état bas : à relier au niveau haut pour désactiver le mode lecture |
| **LED d'alerte** | Anode (+) | PB3 | En série avec une **résistance de 220 Ω** |
| | Cathode (-) | GND | |

<p align="center">
  <img width="882" alt="Schéma de câblage" src="https://github.com/user-attachments/assets/9dc946d2-0c8e-4f1d-be52-480518a0dea1" />
</p>

## Logiciels et outils
- C/C++ (bare-metal / bibliothèque HAL)
- STM32CubeMX
- Keil C

## Structure du projet
```text
STM32-and-HC-SRF05-sensor/
├── Core/
│   ├── Inc/                      # En-têtes (main.h, stm32f1xx_hal_conf.h, stm32f1xx_it.h)
│   └── Src/                      # Sources (main.c, stm32f1xx_hal_msp.c, stm32f1xx_it.c, system_stm32f1xx.c)
├── Drivers/
│   ├── CMSIS/                    # Fichiers du cœur ARM CMSIS
│   └── STM32F1xx_HAL_Driver/     # Bibliothèque HAL STM32
├── MDK-ARM/                      # Projet Keil µVision
│   ├── PRJ.uvprojx               # Fichier de projet Keil
│   └── startup_stm32f103xb.s     # Code de démarrage
├── myLib/                        # Pilotes personnalisés des périphériques
│   ├── HCSR05.c / HCSR05.h       # Pilote du capteur à ultrasons HC-SRF05
│   └── TFT.c / TFT.h             # Pilote de l'écran TFT
├── PRJ.ioc                       # Configuration STM32CubeMX
├── LICENSE
└── README.md
```

## Prise en main
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/TrongNGUYEN1312/STM32-and-HC-SRF05-sensor.git
   cd STM32-and-HC-SRF05-sensor
   ```
2. Câblez les composants comme indiqué dans la section [Câblage](#câblage).
3. Ouvrez `MDK-ARM/PRJ.uvprojx` dans Keil µVision (ou régénérez le projet à partir de `PRJ.ioc` avec STM32CubeMX).
4. Compilez le projet et flashez-le sur la carte à l'aide d'un programmateur **ST-Link**.
5. Déplacez un objet devant le capteur et observez le marqueur se déplacer sur l'écran. En dessous de 5 cm, le marqueur devient noir et la LED s'allume.

## Licence
Ce projet est distribué sous [licence MIT](LICENSE).

## Auteur
**Trong NGUYEN** – [GitHub](https://github.com/TrongNGUYEN1312)
