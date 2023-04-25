#include "Variant.h"
#include "Echiquier.h"

using namespace std;

Pion::Pion(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Pion::Pion(Couleur couleur, Square position)
    : Piece(couleur, "\u2659", position) {}

Pion::Pion(Square position) : Piece(Noir, "\u265F", position) {}

Pion::~Pion() {}

bool Pion::est_mouvement_legal(Echiquier &e, Square const &position) {

    setDouble_pas(false);
    setPrise_passant(false);

    if (e.getPiece(position) != NULL)
        if ((e.getPiece(position)->getCouleur()) == getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de la même couleur

    Square pos = getPosition();
    Square pos1 = pos;

    int compare = abs(pos.getX() - position.getX());

    if (compare != 2 && compare != 1)
        return false; // on vérifie si le mouvement est légal

    if (pos.getY() == position.getY()) // le pion ne bouge en diagonale vers
                                       // l'avant que lors d'une prise
    {
        if (e.getPiece(position) != NULL)
            return false; // on verifie que la case de destination est occupée

        if (getCouleur() == Blanc) {
            if (compare == 2) {

                // setDouble_pas(false);

                pos1.setSquare(pos.getX() + 1, pos.getY());
                if (pos.getX() != 1 || e.getPiece(pos1) != NULL)
                    return false;

                if (getPosition().getY() == position.getY() &&
                    e.getPiece(position) == nullptr) {
                    // Si le pion avance de deux cases et n'est pas en train de
                    // prendre une pièce, il peut être pris en passant par un
                    // pion adverse
                    setDouble_pas(true);
                }
                // Les pions blancs commencent à la ligne 2, alors
                // ils ne peuvent avancer que de
                // deux cases depuis leur position d'origine
                // L'autre comparaison verifie s'il y a une pièce entre la case
                // actuelle et la case que le pion veut occupée.
            }
            return (pos.getX() < position.getX());
        } else {

            if (compare == 2) {

                // setDouble_pas(false);

                pos1.setSquare(pos.getX() - 1, pos.getY());
                if (pos.getX() != 6 || e.getPiece(pos1) != NULL)
                    return false; // Les pions noirs commencent à la ligne 7,
                                  // alors ils ne peuvent avancer que de
                                  // deux cases depuis leur position d'origine
                // L'autre comparaison verifie s'il y a une pièce entre la case
                // actuelle et la case que le pion veut occupée.

                if (getPosition().getY() == position.getY() &&
                    e.getPiece(position) == nullptr) {
                    // Si le pion avance de deux cases et n'est pas en train de
                    // prendre une pièce, il peut être pris en passant par un
                    // pion adverse
                    setDouble_pas(true);
                }
            }
            return (pos.getX() > position.getX());
        }

    } else {
        int compare_x = abs(pos.getX() - position.getX());
        int compare_y = abs(pos.getY() - position.getY());

        if (compare_x != 1 || compare_y != 1)
            return false;

        if (e.getPiece(position) != NULL)

            return true;
    }

    // Prise en passant
    if (getCouleur() == Blanc && pos.getX() == 4) {

        if (position.getY() == pos.getY() - 1 ||
            position.getY() == pos.getY() + 1) {

            pos1.setSquare(position.getX() - 1, position.getY());
            if (e.getPiece(pos1) != NULL)
                if (e.getPiece(pos1)->getCouleur() != Blanc) {
                    if (dynamic_cast<Pion *>(e.getPiece(pos1))
                            ->getDouble_pas()) {

                        setPrise_passant(true);
                        return true;
                    }
                }
        }

    } else if (getCouleur() == Noir && pos.getX() == 3) {
        if (position.getY() == pos.getY() - 1 ||
            position.getY() == pos.getY() + 1) {

            pos1.setSquare(position.getX() - 1, position.getY());
            if (e.getPiece(pos1) != NULL)
                if (e.getPiece(pos1)->getCouleur() != Noir) {
                    if (dynamic_cast<Pion *>(e.getPiece(pos1))
                            ->getDouble_pas()) {
                        setPrise_passant(true);
                        return true;
                    }
                }
        }
    }
    //
    return false;
}

void Pion::setDouble_pas(bool status) { this->double_pas = status; }

bool Pion::getDouble_pas() { return this->double_pas; }

void Pion::setPrise_passant(bool status) { this->prise_passant = status; }

bool Pion::getPrise_passant() { return this->prise_passant; }

Tour::Tour(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Tour::Tour(Couleur couleur, Square position)
    : Piece(couleur, "\u2656", position) {}

Tour::Tour(Square position) : Piece(Noir, "\u265C", position) {}

Tour::~Tour() {}

bool Tour::mouvement_tour(Echiquier &e, Square const &position, Piece &p) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == p.getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur

    Square pos = getPosition();
    Square pos1 = pos;

    if (pos.getX() == position.getX()) // mouvement horizontal
    {
        int compare = abs(pos.getY() - position.getY());
        if (pos.getY() > position.getY()) // on vérifie si la tour bouge vers la
                                          // droite ou vers la gauche
        {
            // deplacement vers la gauche
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(position.getX(), pos.getY() - i);
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
            return true;
        } else {
            // deplacement vers la droite
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(position.getX(), pos.getY() + i);
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
            return true;
        }
    }

    if (pos.getY() == position.getY()) // mouvement horizontal
    {
        int compare = abs(pos.getX() - position.getX());
        if (pos.getX() > position.getX()) {
            // deplacement vers le haut

            for (int i = 1; i < compare; i++) {
                pos1.setSquare(pos.getX() - i, position.getY());
                if (e.getPiece(pos1) != NULL)
                    return false;
            }

        } else {
            // deplacement vers le bas
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(pos.getX() + i, position.getY());
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
        }

        return true;
    }

    return false;
}

bool Tour::est_mouvement_legal(Echiquier &e, Square const &position) {
    return mouvement_tour(e, position, *this);
}

Cavalier::Cavalier(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Cavalier::Cavalier(Couleur couleur, Square position)
    : Piece(couleur, "\u2658", position) {}

Cavalier::Cavalier(Square position) : Piece(Noir, "\u265E", position) {}

Cavalier::~Cavalier() {}

bool Cavalier::est_mouvement_legal(Echiquier &e, Square const &position) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == getCouleur())
            return false;
    // mouvement illégal car la case est occupée par une pièce de même couleur

    int comparex = abs(getPosition().getX() - position.getX());
    int comparey = abs(getPosition().getY() - position.getY());

    // Se le min entre comparex et  comparey est égal à 1 et le max égal à 2,
    // donc le mouvement est légal vu que le cavalier se déplace en L

    if (min(comparex, comparey) == 1 && max(comparex, comparey) == 2)
        return true;

    return false;
}

Fou::Fou(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Fou::Fou(Couleur couleur, Square position)
    : Piece(couleur, "\u2657", position) {}

Fou::Fou(Square position) : Piece(Noir, "\u265D", position) {}

Fou::~Fou() {}

bool Fou::mouvement_fou(Echiquier &e, Square const &position, Piece &p) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == p.getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur

    Square pos = getPosition();
    Square pos1 = pos;

    if ((pos.getX() - pos.getY() != (position.getX() - position.getY()) &&
         (pos.getX() + pos.getY()) != (position.getX() + position.getY()))) {
        return false;
    }

    int compare = abs(pos.getX() - position.getX());

    if (pos.getX() > position.getX() &&
        pos.getY() <
            position
                .getY()) // deplacement en diagonale vers la droite supérieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() - i, pos.getY() + i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }

    if (pos.getX() > position.getX() &&
        pos.getY() >
            position
                .getY()) // deplacement en diagonale vers la gauche supérieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() - i, pos.getY() - i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }

        return true;
    }

    if (pos.getX() < position.getX() &&
        pos.getY() <
            position
                .getY()) // deplacement en diagonale vers la droite inférieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() + i, pos.getY() + i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }

    if (pos.getX() < position.getX() &&
        pos.getY() >
            position
                .getY()) // deplacement en diagonale vers la gauche inférieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() + i, pos.getY() - i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }
    return false;
}

bool Fou::est_mouvement_legal(Echiquier &e, Square const &position) {
    return mouvement_fou(e, position, *this);
}

Dame::Dame(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Dame::Dame(Couleur couleur, Square position)
    : Piece(couleur, "\u2655", position) {}

Dame::Dame(Square position) : Piece(Noir, "\u265B", position) {}

Dame::~Dame() {}

bool Dame::mouvement_tour(Echiquier &e, Square const &position, Piece &p) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == p.getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur

    Square pos = getPosition();
    Square pos1 = pos;

    if (pos.getX() == position.getX()) // mouvement horizontal
    {
        int compare = abs(pos.getY() - position.getY());
        if (pos.getY() > position.getY()) // on vérifie si la tour bouge vers la
                                          // droite ou vers la gauche
        {
            // deplacement vers la gauche
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(position.getX(), pos.getY() - i);
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
            return true;
        } else {
            // deplacement vers la droite
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(position.getX(), pos.getY() + i);
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
            return true;
        }
    }

    if (pos.getY() == position.getY()) // mouvement horizontal
    {
        int compare = abs(pos.getX() - position.getX());
        if (pos.getX() > position.getX()) {
            // deplacement vers haut

            for (int i = 1; i < compare; i++) {
                pos1.setSquare(pos.getX() - i, position.getY());
                if (e.getPiece(pos1) != NULL)
                    return false;
            }

        } else {
            // deplacement vers bas
            for (int i = 1; i < compare; i++) {
                pos1.setSquare(pos.getX() + i, position.getY());
                if (e.getPiece(pos1) != NULL)
                    return false;
            }
        }

        return true;
    }

    return false;
}

bool Dame::mouvement_fou(Echiquier &e, Square const &position, Piece &p) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == p.getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur

    Square pos = getPosition();
    Square pos1 = pos;

    if ((pos.getX() - pos.getY() != (position.getX() - position.getY()) &&
         (pos.getX() + pos.getY()) != (position.getX() + position.getY()))) {
        return false;
    }

    int compare = abs(pos.getX() - position.getX());

    if (pos.getX() > position.getX() &&
        pos.getY() <
            position
                .getY()) // deplacement en diagonale vers la droite supérieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() - i, pos.getY() + i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }

    if (pos.getX() > position.getX() &&
        pos.getY() >
            position
                .getY()) // deplacement en diagonale vers la gauche supérieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() - i, pos.getY() - i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }

        return true;
    }

    if (pos.getX() < position.getX() &&
        pos.getY() <
            position
                .getY()) // deplacement en diagonale vers la droite inférieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() + i, pos.getY() + i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }

    if (pos.getX() < position.getX() &&
        pos.getY() >
            position
                .getY()) // deplacement en diagonale vers la gauche inférieure
    {
        for (int i = 1; i < compare; i++) {
            pos1.setSquare(pos.getX() + i, pos.getY() - i);
            if (e.getPiece(pos1) != NULL) {

                return false;
            }
        }
        return true;
    }
    return false;
}

bool Dame::est_mouvement_legal(Echiquier &e, Square const &position) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur

    bool verifie_horizontal = mouvement_tour(e, position, *this);
    bool verifie_vertical = mouvement_fou(e, position, *this);

    // La dame combine le déplacement de la tour et celui du fou

    if (!verifie_horizontal && !verifie_vertical)
        return false;

    return true;
}

Roi::Roi(Couleur couleur, string nom, Square position)
    : Piece(couleur, nom, position) {}

Roi::Roi(Couleur couleur, Square position)
    : Piece(couleur, "\u2654", position) {}

Roi::Roi(Square position) : Piece(Noir, "\u265A", position) {}

Roi::~Roi() {}

bool Roi::est_mouvement_legal(Echiquier &e, Square const &position) {
    if (e.getPiece(position) != NULL)
        if (e.getPiece(position)->getCouleur() == getCouleur())
            return false; // mouvement illégal car la case est occupée par une
                          // pièce de même couleur
    int compare_x = abs(getPosition().getX() - position.getX());
    int compare_y = abs(getPosition().getY() - position.getY());

    if (compare_x > 1 || compare_y > 1)
        return false;
    if (e.getPiece(position) != NULL) {
        if (e.getPiece(position)->to_string() == "\u265A" ||
            e.getPiece(position)->to_string() == "\u2654") {
            cout << "Un Roi ne peut prendre un autre Roi" << endl;
            return false;
        }
    }
    return true;
}
