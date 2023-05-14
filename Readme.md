# Mini-Projet Echiquier (Programmation Objet - C++)


Dans le cadre de ma première année du cycle ingénieur en Informatique et Réseaux à Télécom Physique Strasbourg, j'ai réalisé un projet de programmation orientée objet en C++. Ce projet avait pour but de mettre en pratique certaines notions de la programmation orientée objet, à savoir: 
- Héritage
- Polymorphisme
- Méthodes virtuelles 

# Organisation des dossiers

*   `html/` -> contient la documentation en format htlm générée automatiquement par le Doxygen.
*   `include/` -> contient les fichiers d'en-tête(`.h`).
*   `obj/` -> contient les objets (`.o`) générés par le makefile.
*   `src/` -> contient les méthodes des classes définies dans les fichiers d'en-tête, ainsi que le `main`.
*   `tests/` -> contient les tests.  

# Compilation et exécution du programme

Pour compiler le programme, utilisez la commande suivante:

```bash
    make
```

Pour supprimer les fichiers générées par la compilation, utilisez la commande suivante:

```bash
    make clean
```

Une fois que le programme a été compilé, vous pouvez l'exécuter à l'aide de la commande suivante:

`./echecs` 

ou bien : 

```bash
make projet
```

# Niveau d'exigence du programme
 
J'ai essayé d'atteindre le niveau maximum d'exigence de ce projet, cependant certaines fonctionnalités qui ne sont pas pleinement fonctionnelles.

Les fonctionnalités suivantes sont pleinement fonctionnelles:

- Niveau 1 : Fonctionnalité - Base (Saisie, Affichage, Prise, Pions et Obstacles);
- Niveau 2 : Fonctionnalité - Détection de l'échec;
- Niveau 3 : Fonctionnalité - Roque et Promotion;

Les fonctionnalités suivantes ne sont pas pleinement fonctionnelles:

- Niveau 4 : Fonctionnalité - Mat et Mat.

La fonctionnalité suivante n'est pas fonctionnelle du tout:

- Niveau 2 : Fonctionnalité Prise en passant

* Remarques:

- Pour le mouvement du roque, je vérifie uniquement que le roi et la tour impliquée n'ont jamais bougé. 

- La fonctionnalité Pat n'est pas complètement fonctionnelle car je n'ai pas implémenté la règle des 3 positions répétées sucessivement, ni celle des 50 coups joués sans prise.

- La fonctionnalité Mat n'est pas pleinement fonctionnelle car je n'effectue pas toutes les vérifications nécessaires pour savoir si le roi est bel et bien en échec et mat. J'en parlerai dans la section concernant les difficultés rencontrées.

- En ce qui concerne la fonctionnalité Prise en passant, j'ai réussi à coder dans la méthode "mouvement légal" du pion un algorithme qui vérifie si l'on peut effectuer ce mouvement, cependant je n'ai pas réussi à vérifier si un pion a avancé de deux cases, cela est peut-être du à la modélisation de mes classes. Par conséquent, j'ai dû m'abstenir de cette fonctionnalité.

## Conception du programme et difficultés rencontrées

Pour la conception de mon programme, j'ai suivi les consignes de la modélisation des classes, néanmoins pour certaines méthodes j'ai envisagé une autre conception.

J'ai créé autant de sous-classes(Pion, Tour, Fou, Cavalier, Roi, Dame) que de variantes de pièce, et toutes ces sous-classes héritent de la classe Piece.

À la fin du développement de ce projet j'ai remarqué que je m'étais un peu trompé au niveau de la modélisation de mes sous-classes, car la sous-classe répresentant la Dame pouvait bien hériter de la sous-classe Fou et ainsi que de la sous-classe Tour vu que la Dame combine les mouvements du Fou et de la Tour.

Ce programme contient aussi une classe Jeu qui permet de gérer le jeu, une classe Echiquier, cette classe possède un tableau [8]x[8] pointant vers une pièce allouée en mémoire et cela represente en effet l'échiquier.

Dans mes fonctions qui vérifient la légalité des déplacements de chaque pièce je vérifie aussi qu'une pièce ne passe pas au-dessus d'une autre, autrement, je gère les obstacles et pour le pion je gère la prise en passant, mais je n'arrivais pas à savoir si une pièce du type Pion a avancé de deux cases, j'ai décidé de m'abstenir de cette fonctionnalité.  

Concernant les difficultés rencontrées, à l'origine je n'avais pas toutes les connaissances utilisées au cours de ce projet, en conséquence les difficultés que j'ai rencontrées étaient techniques. En général, toutes les difficultés rencontrées étaient liées aux problèmes de gestion de la mémoire lors des déplacements de mes pièces.

J'ai aussi eu des difficultés pour mettre en place la fonctionnalité mat parce que je devais vérifier que toutes les pièces pouvaient se déplacer partout et que cela empêcherait l'échec du Roi, mais cela engendré des erreurs de segmentation, vu que je simulais plusieurs déplacements pour vérifier si ce mouvement empécherait l'échec et ensuite je remettais la pièce à sa position initiale, cela devient compliqué lorsqu'il y a déjà une pièce dans la position où on a mis la pièce. J'ai décidé donc de cloner mon échiquier, mais sans succès puisque je n'arrivais pas à cloner les pièces.

## Conclusion

Ce projet m'a permis de mieux comprendre les concepts de la programmation orientée objet et de les appliquer dans un contexte concret. Il m'a également permis de renforcer mes connaissances en C++ et de découvrir de nouvelles fonctionnalités de ce langage. J'ai aussi appris à utiliser l'outil de documentation Doxygen pour générer automatiquement une documentation en HTML à partir de mes commentaires de code.

### Tests qui échouent 

* Tests 1 (failed tests): Aucun

* Tests 2 (failed tests):              
- data/2-leg-chess-1.txt_(position) 
- data/2-leg-chess-1.txt_(result) 
- data/2-ill-chess-1.txt_(position) 
- data/2-ill-chess-1.txt_(result) 
- data/2-ill-move-after-chess.txt_(position) 
- data/2-ill-move-after-chess.txt_(result) 

* Tests 3 (failed tests):              
- data/3-leg-pawn-passing.txt_(position) 
- data/3-ill-qside-castling-1.txt_(position) 
- data/3-ill-qside-castling-2.txt_(position) 

* Tests 4 (failed tests):

- data/4-leg-mat-berger.txt_(result) 
- data/4-leg-mat-decouv.txt_(position) 
- data/4-leg-mat-parade.txt_(position) 
- data/4-leg-pat.txt_(result) 

* Remarques:
    - Certains tests 2 échouent à cause de ma méthode qui détecte le mat, car elle n'effectue pas toutes les vérifications pour savoir si c'est un échec et mat.
    - En ce qui concerne les tests 3, les tests concernant le roque échouent parce que je ne vérifie pas si le roi a été en échec avant ou après ce mouvement.
    - Pour les tests 4, il faudra supprimer le test 4-leg-mat-1.txt pour pouvoir exécuter tous les autres. Et certains tests 4 échouent également en raison de ma métohode qui détecte le mat.

### Auteur

Nicolas Marra - nicolasmarra12@gmail.com
