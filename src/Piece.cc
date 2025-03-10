#include "Piece.h"
#include "Echiquier.h"

Piece::Piece(Couleur couleur, string nom, Square position) {
    this->couleur = couleur;
    this->nom = nom;
    this->position = position;
}

Piece::~Piece() {}

Couleur Piece::getCouleur() const { return this->couleur; }

void Piece::setPosition(Square const &position) {
    this->position.setSquare(position);
}

Square const Piece::getPosition() { return this->position; }

string Piece::to_string() const { return this->nom; }

void Piece::mouvement(Echiquier &e, Square const &position) {
    /*
    if(e.getPiece(position) != NULL)
    {
        Piece * p = e.getPiece(position);
        if(p->to_string() == "\u2654" || p->to_string() == "\u265A")
        {
            e.setRoi(p->getCouleur());
        }
        delete p;
    }
    */

    // double pas

    if (e.getPiece(position) != NULL) {

        if ((e.getPiece(position)->to_string() == "\u2659" ||
             e.getPiece(position)->to_string() == "\u265F") &&
            abs(getPosition().getX() - position.getX()) == 2) {

        } else {
            // ce n'est pas un double pas
        }
    }

    // pion
    e.pose_piece(this, position);
    e.pose_piece(NULL, getPosition());
    this->setPosition(position);
    this->setDeplace(true);
}

bool Piece::getDeplace() { return this->deplace; }

void Piece::setDeplace(bool status) { this->deplace = status; }

int Piece::promotion(Echiquier &e, Square const &pos) {

    Piece *p = e.getPiece(pos);
    string nom1 = p->to_string();
    int retour = 0;
    if (p->getCouleur() == Blanc) {
        if (pos.getX() == 7 && e.getPiece(pos) != NULL) {

            int fin = 0;
            while (fin != 1) {

                string piece_promotion = "";
                cout << "En quelle pièce vous voulez promouvoir votre pion?"
                     << endl;
                cout << "{Q,R,B,K} pour respectivement promouvoir en Reine, "
                        "Tour, Fou, Cavalier. "
                     << endl;

                cin >> piece_promotion;
                if (piece_promotion == "Q") {
                    p = new Dame(Blanc, "\u2655",
                                 Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "R") {
                    p = new Tour(Blanc, "\u2656",
                                 Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "B") {
                    p = new Fou(Blanc, "\u2657",
                                Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "N") {
                    p = new Cavalier(Blanc, "\u2658",
                                     Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "/quit") {
                    retour = 1;
                    fin = 1;
                    continue;
                } else {
                    fin = 0;
                    cout << "Option invalide" << endl;
                }
            }

            e.pose_piece(p, pos);
            cout << nom1 << " promu en " << p->to_string() << endl;
        }

    } else {
        if (pos.getX() == 0 && e.getPiece(pos) != NULL) {
            int fin = 0;
            while (fin != 1) {

                string piece_promotion = "";
                cout << "En quelle pièce vous voulez promouvoir votre pion?"
                     << endl;
                cout << "{Q,R,B,K} pour respectivement promouvoir en Reine, "
                        "Tour, Fou, Cavalier. "
                     << endl;
                cin >> piece_promotion;

                if (piece_promotion == "Q") {
                    p = new Dame(Noir, "\u265B",
                                 Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "R") {
                    p = new Tour(Noir, "\u265C",
                                 Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "B") {
                    p = new Fou(Noir, "\u265D", Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "N") {
                    p = new Cavalier(Noir, "\u265E",
                                     Square(pos.getX(), pos.getY()));
                    fin = 1;
                } else if (piece_promotion == "/quit") {
                    retour = 1;
                    fin = 1;
                } else {
                    fin = 0;
                    cout << "Option invalide" << endl;
                }
            }

            e.pose_piece(p, pos);
            cout << nom1 << " promu en " << p->to_string() << endl;
        }
    }
    return retour;
}
