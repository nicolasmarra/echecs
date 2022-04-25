# Mini-Projet Echiquier (Programmation Objet - C++)


Dans le cadre de ma première année du cycle ingénieur en Informatique et Réseaux à Télécom Physique Strasbourg, je devais réaliser un projet de programmation orientée objet en C++. Ce projet avait pour but de mettre en pratique certaines notions de la programmation orientée objet, à savoir: 
- Héritage
- Polymorphisme
- Méthodes virtuelles 

# Organisation des dossiers

*   html -> contient les fichiers de la documentation en format htlm générée automatiquement par le doxygen.
*   include -> contient les headers (fichiers .h)
*   obj -> contient les objets (fichiers .o) générés par le makefile
*   src -> contient les méthodes des classes des fichiers .h, et le main
*   tests -> contient les tests  

# Exécution du programme

Pour la compilation du programme, il faut utiliser la commande suivante:

```bash
    make
```

Pour supprimer les fichiers de la compilation, il faut utiliser la commande suivante:

```bash
    make clean
```

Une fois que le programme a été compilé, nous pouvons le lancer à l'aide de la commande suivante:

`./echecs` 

ou alors: 

```bash
make projet
```

# Niveau d'exigence du programme
 
J'essayais d'attendre le niveau maximum d'exigence de ce projet, cependant il y a certaines fonctionnalités qui ne sont pas pleinement fonctionnelles.

Les fonctionnalités suivantes sont pleinement fonctionnelles:

- Fonctionnalité Base;
- Fonctionnalité Prise;
- Fonctionnalité Pions;
- Fonctionnalité Obstacle;
- Fonctionnalité Echec;
- Fonctionnalité Roque;
- Fonctionnalité Promotion;

Les fonctionnalités suivantes ne sont pas pleinement fonctionnelles:

- Fonctionnalité Pat;
- Fonctionnalité Mat;

La fonctionnalité suivante ne pas fonctionnelle du tout:

- Fonctionnalité Prise en passant

* Remarques:

Je ne suis pas complètement sûr que la fonctionnalité Roque soit pleinement fonctionnelle car que je ne vérifie pas s'il le roi a été en échec avant ce mouvement ni après ce mouvement.

La fonctionnalité Pat en soi est complètement fonctionnelle, mais je n'ai pas implémenté la règle des 3 positions répétées sucessivement, ni celle des 5O coups joués sans prise.

La fonctionnalité mat n'est pas pleinement fonctionnelle parce que je n'effectue pas tous les vérifications pour savoir si le roi est bel et bien en échec et mat, j'en parlerai dans la section concernant les difficultés rencontrées.

Et en ce qui concerne la fonctionnalité Prise en passant, j'ai réussi à coder dans la méthode mouvement légal du pion un algorithme qui vérifie s'il on peut effectuer ce mouvement, cependant je n'arrivais pas à vérifier si un pion a avancé de deux cases, cela est peut-être du à la modélisation de mes classes. En conséquence, j'ai du m'abstenir de cette fonctionnalité.

## Conception du programme et les difficultés rencontrées

Pour la conception de mon programme, j'ai suivi les consignes de la modélisation des classes, néanmoins pour certaines méthodes j'ai envisagé une autre conception.

J'ai crée autant de sous-classes(Pion, Tour, Fou, Cavalier, Roi, Dame) que de variantes de pièce, et toutes ces sous-classes héritent de classe Piece.

A la fin du développement de ce projet j'ai remarqué que je m'étais un peu trompé au niveau de la modelisation de mes sous-classes, car la sous-classe répresentant la Dame pouvait bien hériter de la sous-classe Fou et ainsi que de la sous-classe Tour vu que la Dame combine les mouvement du Fou et de la Tour.

Ce programme contient aussi une classe Jeu qui permet de gérer le jeu, une classe Echiquier, cette classe possède un tableau [8]x[8] pointant vers une pièce allouée en mémoire et cela represente en effet l'échiquier.

Dans mes fonctions qui vérifient la légalité des déplacements de chaque pièce je vérifie aussi qu'une pièce ne passe pas au-dessus d'une autre, autrement, je gère les obstacles et pour le pion je gère la prise en passant, mais je n'arrivais pas à savoir si une pièce du type Pion a avancé de deux cases, j'ai décidé de m'abstenir de cette fonctionnalité.  

Concernant les difficultés rencontrées, à l'origine je n'avais pas toutes les connaissances utilisées au cours de ce projet, en conséquence les difficultés que j'ai rencontrées étaient techniques. En général, toutes les difficultés rencontrées étaient liées aux problèmes de gestion de la mémoire lors des déplacements de mes pièces.

J'ai aussi eu difficultés pour mettre en place la fonctionnalité mat parce que je devais vérifier que toutes les pièces pouvaient se déplacer partout et que cela empêcherait l'échec du Roi, mais cela engendré des erreurs de segmentation, car je simulais plusieurs déplacements pour vérifier si ce mouvement empécherait l'échet et ensuite je remettais la pièce à sa position initiale, cela devient compliqué lorsqu'il y a déjà une pièce dans la position où on a mis la pièce. J'ai décidé donc de cloner mon échiquier, mais sans succès puisque je n'arrivais pas à cloner les pièces.

### Auteur

Nicolas Marra - nicolasmarra12@gmail.com