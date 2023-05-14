#include "Echiquier.h"
#include "Square.h"
#include "Variant.h"
#include <iostream>
#include <string>
#define NBCOL 8

using namespace std;

Echiquier::Echiquier() {

    // allocations de toutes les pièces sauf les pions
    alloc_mem_echiquier();
    roiBlanc = new Roi(Blanc, "\u2654", Square(0, 4));
    piecesb[0] = new Tour(Blanc, "\u2656", Square(0, 0));
    piecesb[1] = new Cavalier(Blanc, "\u2658", Square(0, 1));
    piecesb[2] = new Fou(Blanc, "\u2657", Square(0, 2));
    piecesb[3] = new Dame(Blanc, "\u2655", Square(0, 3));
    piecesb[4] = roiBlanc;
    piecesb[5] = new Fou(Blanc, "\u2657", Square(0, 5));
    piecesb[6] = new Cavalier(Blanc, "\u2658", Square(0, 6));
    piecesb[7] = new Tour(Blanc, "\u2656", Square(0, 7));

    roiNoir = new Roi(Noir, "\u265A", Square(7, 4));
    piecesn[0] = new Tour(Noir, "\u265C", Square(7, 0));
    piecesn[1] = new Cavalier(Noir, "\u265E", Square(7, 1));
    piecesn[2] = new Fou(Noir, "\u265D", Square(7, 2));
    piecesn[3] = new Dame(Noir, "\u265B", Square(7, 3));
    piecesn[4] = roiNoir;
    piecesn[5] = new Fou(Noir, "\u265D", Square(7, 5));
    piecesn[6] = new Cavalier(Noir, "\u265E", Square(7, 6));
    piecesn[7] = new Tour(Noir, "\u265C", Square(7, 7));

    // allocation des pions
    for (unsigned char i(0); i < NBCOL; i++) {
        pionsb[i] = new Pion(Blanc, "\u2659", Square(1, i));
        pionsn[i] = new Pion(Noir, "\u265F", Square(6, i));
    }

    // on pose les pièces dans leur respectives positions
    for (unsigned char i(0); i < NBCOL; i++) {

        pose_piece(piecesb[i], piecesb[i]->getPosition());
        pose_piece(piecesn[i], piecesn[i]->getPosition());
        pose_piece(pionsb[i], pionsb[i]->getPosition());
        pose_piece(pionsn[i], pionsn[i]->getPosition());
    }
}

Echiquier::~Echiquier() {
    /*Piece *del;
    for (unsigned char i(0); i < NBCOL; i++) {
        for (unsigned char j(0); j < NBCOL; j++) {
            if(echiquier[i][j] != nullptr)
            {
                del = echiquier[i][j];
                delete del;
                echiquier[i][j] =nullptr;
            }
            if(i==j){

                piecesb[i] = nullptr;
                piecesn[i] = nullptr;
                pionsb[i] = nullptr;
                pionsn[i] = nullptr;
            }
        }
    }
    roiBlanc = nullptr;
    roiNoir = nullptr;
    */
}

void Echiquier::affiche() const {

    string space5 = string(5, ' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    " << endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL - 1); i >= 0; i--) {
        cout << i + 1 << " "; // numérotation ligne dans affichage
        for (int j(0); j < NBCOL; j++) {
            cout << "|";
            if (echiquier[i][j]) {
                cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille
                                        // police
                cout << echiquier[i][j]->to_string();
                cout << "\u0020"
                     << " ";
            } else
                cout << space5; // 2 ascii spaces
        }
        cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
        cout << endl;
    }
}

Piece *Echiquier::getPiece(Square const &position) const {
    return echiquier[position.getX()][position.getY()];
}

void Echiquier::pose_piece(Piece *p, Square const &position) {
    echiquier[position.getX()][position.getY()] = p;
}

void Echiquier::alloc_mem_echiquier() {
    for (unsigned char i(0); i < NBCOL; i++) {
        for (unsigned char j(0); j < NBCOL; j++) {
            echiquier[i][j] = nullptr;
        }
    }
}

string Echiquier::pgn_piece_name(string const name, bool view_pawn,
                                 bool view_color) const {

    string psymb;
    if (name == "\u2656")
        psymb = "R"; // Rook W
    else if (name == "\u2658")
        psymb = "N"; // Knight W
    else if (name == "\u2657")
        psymb = "B"; // Bishop W
    else if (name == "\u2655")
        psymb = "Q"; // Queen W
    else if (name == "\u2654")
        psymb = "K"; // King W
    else if (name.rfind("\u2659", 0) == 0 && view_pawn)
        psymb = "P";        // Pawn W
    if (psymb.size() > 0) { // one of the white piece has been found
        if (view_color)
            return "w" + psymb;
        else
            return psymb;
    }
    if (name == "\u265C")
        psymb = "R"; // Rook B
    else if (name == "\u265E")
        psymb = "N"; // Knight B
    else if (name == "\u265D")
        psymb = "B"; // Bishop B
    else if (name == "\u265B")
        psymb = "Q"; // Queen B
    else if (name == "\u265A")
        psymb = "K"; // King B
    else if (name.rfind("\u265F", 0) == 0 && view_pawn)
        psymb = "P";        // Pawn B
    if (psymb.size() > 0) { // one of the black piece has been found
        if (view_color)
            return "b" + psymb;
        else
            return psymb;
    } else
        return "";
}

// cette méthode permet de vérifier si une case est vide
bool Echiquier::est_case_vide(Square const &position) const {

    if (this->getPiece(position) == NULL)
        return true;
    else
        return false;
}
string Echiquier::canonical_position() const {
    string output;
    Piece *p;
    for (size_t row(1); row <= 8; row++) {
        for (char col('a'); col <= 'h'; col++) {
            Square square(col + to_string(row));
            p = this->getPiece(square);
            if (p != NULL)
                output += pgn_piece_name(p->to_string(), true, true);
            output += ",";
        }
    }
    return output;
}

// cette méthode permet de détecter si le roi est en échec
bool Echiquier::detecter_echec(Couleur Couleur) {

    Piece *roi = getRoi(Couleur);

    // On parcourt chaque pièce de la couleur adverse et on vérifie si elle peut
    // atteindre le roi de la couleur donnée en argument.
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j] != NULL) {
                if (echiquier[i][j]->getCouleur() != Couleur) {
                    if (echiquier[i][j]->est_mouvement_legal(
                            *this, roi->getPosition())) {

                        // Si une pièce adverse peut atteindre le roi, alors le
                        // roi est en échec.
                        return true;
                    }
                }
            }
        }
    }

    // Si aucune pièce n'est atteindre le roi, alors il n'est pas en échec.
    return false;
}

// cette méthode permet de vérifier si après le mouvement d'une pièce le roi
// reste toujours en échec
bool Echiquier::enlever_check(Square const &position, Couleur Couleur) {

    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j] != NULL) {
                if (echiquier[i][j]->getCouleur() == Couleur) {
                    if (echiquier[i][j]->est_mouvement_legal(*this, position)) {

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Echiquier::detecter_mat(Couleur Couleur) {

    // on récupère la position du roi de la couleur passée en argument

    Piece *roi = getRoi(Couleur);
    Square p = roi->getPosition();
    Square p_echec;
    bool resultat = false;

    // on parcourt toutes les cases de l'échiquier

    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            Square position(i, j);

            // Pour chaque case on
            // vérifie si le roi peut s'y déplacer.
            if (roi->est_mouvement_legal(*this, position)) {
                //   Si c'est le cas, on simule
                // le déplacement du roi à cette position
                roi->mouvement(*this, position);

                // Et pour chaque pièce  de l'adversaire, on vérifie si elle
                // peut attaquer le roi à sa nouvelle position.
                bool on_echec = false;
                Piece *roi1 = getRoi(Couleur);
                for (int i1(0); i1 < NBCOL; i1++) {
                    for (int j1(0); j1 < NBCOL; j1++) {
                        if (echiquier[i1][j1] != NULL) {
                            if (echiquier[i1][j1]->getCouleur() != Couleur) {
                                if (echiquier[i1][j1]->est_mouvement_legal(
                                        *this, roi1->getPosition())) {
                                    p_echec.setSquare(i1, j1);
                                    on_echec = true;
                                    break;
                                }
                            }
                        }
                    }
                }

                if (on_echec == true) {
                    if (enlever_check(p_echec, Couleur) == true) {
                        resultat = false;
                        break;
                    } else {
                        resultat = true;
                    }
                }
                // on remet le roi à sa position initiale
                roi->mouvement(*this, p);
            }
        }
    }

    return resultat;
}

bool Echiquier::detecter_pat(Couleur Couleur) {
    for (int i(0); i < NBCOL; i++) {
        for (int j(0); j < NBCOL; j++) {
            if (echiquier[i][j] != NULL) {
                if (echiquier[i][j]->getCouleur() == Couleur) {

                    for (int x(0); x < NBCOL; x++) {
                        for (int y(0); y < NBCOL; y++) {
                            Square position(x, y);
                            if (echiquier[i][j]->est_mouvement_legal(
                                    *this, position)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Echiquier::setRoi(Couleur couleur) {
    if (couleur == Blanc)
        roiBlanc = NULL;
    else
        roiNoir = NULL;
}

Piece *Echiquier::getRoi(Couleur couleur) {
    if (couleur == Blanc)
        return roiBlanc;
    else
        return roiNoir;
}

bool Echiquier::executer_petitroque(Couleur Couleur) {
    Piece *roi = getRoi(Couleur);
    if (Couleur == Blanc) {

        if (roi->getDeplace() == false && getPiece(Square(0, 7)) != NULL) {

            if (getPiece(Square(0, 7))->getDeplace() == false) {

                if (getPiece(Square(0, 7))
                        ->est_mouvement_legal(*this, Square(0, 5)) == true) {

                    roi->mouvement(*this, Square(0, 6));
                    getPiece(Square(0, 7))->mouvement(*this, Square(0, 5));
                    return true;
                }
            }
        }

    } else {
        if (roi->getDeplace() == false && getPiece(Square(7, 7)) != NULL) {

            if (getPiece(Square(7, 7))->getDeplace() == false) {

                if (getPiece(Square(7, 7))
                        ->est_mouvement_legal(*this, Square(7, 5)) == true) {

                    roi->mouvement(*this, Square(7, 6));
                    getPiece(Square(7, 7))->mouvement(*this, Square(7, 5));
                    return true;
                }
            }
        }
    }
    return false;
}

bool Echiquier::executer_grandroque(Couleur Couleur) {
    Piece *roi = getRoi(Couleur);
    if (Couleur == Blanc) {

        if (roi->getDeplace() == false && getPiece(Square(0, 0)) != NULL) {

            if (getPiece(Square(0, 0))->getDeplace() == false) {

                if (getPiece(Square(0, 0))
                        ->est_mouvement_legal(*this, Square(0, 2)) == true) {

                    roi->mouvement(*this, Square(0, 2));
                    getPiece(Square(0, 0))->mouvement(*this, Square(0, 3));
                    return true;
                }
            }
        }

    } else {
        if (roi->getDeplace() == false && getPiece(Square(7, 0)) != NULL) {

            if (getPiece(Square(7, 0))->getDeplace() == false) {

                if (getPiece(Square(7, 0))
                        ->est_mouvement_legal(*this, Square(7, 2)) == true) {

                    roi->mouvement(*this, Square(7, 2));
                    getPiece(Square(7, 0))->mouvement(*this, Square(7, 3));
                    return true;
                }
            }
        }
    }
    return false;
}
