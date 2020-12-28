# Projet Monde Virtuel Yann ROUBEAU

## Vidéo de démonstration : https://www.youtube.com/watch?v=aRyXIpHTCYo&feature=youtu.be

## Jeu

Le jeu se joue en "top person", vue du dessus, déplacement au clique souris

## Joueur

Le joueur cherche des objets

Il possède une arme

Les tirs de l'armes ont x% de chances de toucher la cible

## Drone

Patrouille dans la salle et cherche le joueur

Lorsqu'un des deux éléments principaux du drone est détruit un nouveau drone apparait à une extrémité de la salle après X temps

### Projecteur

Le drone possède un projecteur rouge qui émets une forte lumière, le joueur doit l'éviter

Quand le projecteur est détruit le drone ne peut plus identifier le joueur

Quand le projecteur détecte une cible le drone appel le robot et lui fourni les coordonnées de détection (Cf: Robot)

### Œil

œil permet au drone de se déplacer dans la salle

Lorsque œil du drone est détruit il ne peut plus se déplacer mais peut encore détecter le joueur en tournant en rond

## Robot

Le robot attends dans un coin de la salle tant que le drone ne lui fournis pas de cible

Le robot de possède pas œil donc sa vision est très réduite

Lorsqu'une les coordonnées d'une cible lui sont envoyées il s'y approche de manière a faire rentrer la cible dans son champs de vision

Lorsque la cible rentre dans son champs de vision il lui tire dessus

Lorsqu'un des deux éléments principaux du robot est détruit un nouveau robot apparait à une extrémité de la salle après X temps

### Arme

Le robot possède une arme très précise, mortelle pour le joueur

Lorsque l'arme est détruite le robot ne peut plus tirer

### Roue

La roue permet au robot de se déplacer

Lorsque la roue est détruite le robot ne peut plus se déplacer mais peut encore tirer de manière hasardeuse

## Salle

La salle est remplie d'objets massif pour permettre au joueur de se cacher

Le joueur doit trouver des objets de manière à pouvoir quitter la salle

Le but du jeu est de trouver les objets le plus vite possible sans mourir

Des munitions vont apparaitre sur la carte de manière aléatoire

Les munitions seront très rare donc le tir doit être une solution de dernier recours

