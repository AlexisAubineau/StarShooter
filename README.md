
# Star Shooter Made By Patrcik and Alexis

Projet créé à partir de la SFML 2.5.1, le but de ce projet étais de créer une architecture forte capable de servir de base sur d'autres projets perso et d'évaluer nos compétences acquises en C++ .

L’exécutable du projet est disponible à l'adesse suivante :
[Lien release Github](https://github.com/AlexisAubineau/Project-Shooter/releases/tag/1.0.0)

Les sources du projet sont disponible à l'adresse suivante :
[Lien repo Github](https://github.com/AlexisAubineau/Project-Shooter)

## SDK SFML 2.5.1 : 
Suite au téléchargement des sources du projet vous devriez pouvoir lancer un build de debug ou build une release si vous avez un problème regarder bien dans les propriétés du projets si les chemins ci-dessous sont correcte :

 - Propriété de config -> C/C++ -> Général -> Autres répertoires include : SFML-2.5.1/include
 - Propriété de config -> Editeur de lien -> Général -> Répertoires de bibliothèques supplémentaires : SFML-2.5.1/lib

## Controle du jeu : 

**Control In-Game**

 - Move Up : Z
 - Move Down : S
 - Move Left : Q
 - Move Right : D
 - Shoot: ESPACE

**Control Editor**
- Activer les collisions sur une tile : C
- Move Up : Z
- Move Down : S
- Move Left : Q
- Move Right : D
- Changer le type de tile: UP KEY / DOWN KEY

## Travail réalisé par l'équipe :

Pour ce projet nous avons constitué une équipe de 2 personnes:

 - Patrick
 - Alexis

### Travail réalisé par Patrick :


### Travail réalisé par Alexis :

 - Player
 - Death Player Systems
 - Tile System
 - Engine
 - Editor
 - Menu (Pause / MainMenu / Settings)
 - Component ( Movement / Input / Hitbox / Animation)
 - Gui
 - Graphics

## Difficultés rencontré :

 #### Patrick :
 
  - Le moteur:
    * Création des differents outils: GameObject, GameObjectManager
- Normal Enemy:
    * Du mal a leur donner un patern et leur faire tirer des projectiles
    * Gestion des projectiles enemis
- Enemy Wave Spawner:
    * Gros mal a spawn des mobs en vagues, 
    * Gerer les collisions des mobs par rapports aux balles
    
 #### Alexis :
 
- Gestion des collisions plus complexe qu'attendu.
- Gestion des tiles implémentation et gestion de celle-ci qui m'ont pris beaucoup plus de temps que prévu car je pensé que ce serais moins complexe.
- La création d'une "Library" pour la gui qui a pu me facilité du temps de travail mais m'en à pris beaucoup d'un autre côté.
- La création d'un analyser de pixel pour créer une hitbox autour du personnage que j'ai finalement abandonné car pas eu le temps
- Tentative de création d'un screen ration pour faire un menu settings avec possibilité de changer de résolution
