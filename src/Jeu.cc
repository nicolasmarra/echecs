#include "Jeu.h"

Jeu::Jeu() : e() {
    this->fin_partie = false;
    this->equipe = Noir;
}

Jeu::~Jeu() {}

bool Jeu::fin() { return this->fin_partie; }

void Jeu::finir(bool status) { this->fin_partie = status; }

void Jeu::affiche() { this->e.affiche(); }

bool Jeu::saisie_correcte(string const &cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd, mouvmtpattern);
}

bool Jeu::saisie_correcte_petitroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

bool saisie_correcte_grandroque(string const &cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd, mouvmtpattern);
}

ResultatPartie Jeu::getResultat() const { return this->resultat; }

void Jeu::setResultat(ResultatPartie resultat) { this->resultat = resultat; }

string Jeu::afficherResultatPartie() const {
    string sortie;
    switch (getResultat()) {
    case VICTOIRE_BLANCS:
        sortie = "1-0";
        break;
    case VICTOIRE_NOIRS:
        sortie = "0-1";
        break;
    case NULLE:
        sortie = "1/2-1/2";
        break;
    case PARTIE_INTERROMPUE:
        sortie = "?-?";
        break;
    default:
        sortie = "?-?";
        break;
    }

    return sortie;
}

void Jeu::joue() {
    this->e.affiche();
    Piece *p;
    Square position;
    int joueur = 1;
    string mouvement;
    while (!this->fin()) {
        while (joueur == 1) {

            cout << "Joueur 1(Blanc)" << endl << "Coup (eg. a1a8) ? ";
            cin >> mouvement;
            if (mouvement != "/quit" && mouvement != "/draw" &&
                mouvement != "/resign") {
                if (saisie_correcte(mouvement) ||
                    saisie_correcte_petitroque(mouvement) ||
                    saisie_correcte_grandroque(mouvement)) {

                    if (saisie_correcte_petitroque(mouvement) ||
                        saisie_correcte_grandroque(mouvement)) {

                        if (saisie_correcte_petitroque(mouvement)) {
                            if (e.executer_petitroque(Blanc) == true) {
                                joueur = 2;
                                e.affiche();
                            } else {
                                cout << "petit roque invalide" << endl;
                            }
                        } else {
                            if (e.executer_grandroque(Blanc) == true) {
                                joueur = 2;
                                e.affiche();
                            } else {
                                cout << "grand roque invalide" << endl;
                            }
                        }
                    } else {
                        // découper case origine et destination

                        string orig = mouvement.substr(0, 2);
                        string dest = mouvement.substr(2, 2);

                        position.conversion(orig);
                        p = e.getPiece(position);

                        if (p == NULL || p->getCouleur() == Noir) {
                            if (p == NULL)
                                cerr << "Aucune pièce dans la case d'origine"
                                     << endl;
                            else
                                cerr << "Mauvaise pièce(Mouvement illégal)"
                                     << endl;

                        } else {

                            position.conversion(dest);
                            if (p->est_mouvement_legal(e, position)) {
                                bool status = p->getDeplace();
                                p->mouvement(e, position);

                                if (e.detecter_echec(Blanc)) {
                                    cerr << "ce mouvement met le roi en échec";

                                    position.conversion(orig);
                                    p->mouvement(e, position);
                                    p->setDeplace(status);
                                } else {

                                    joueur = 2;
                                    cout << "-> déplacement de "
                                         << p->to_string() << " " << orig
                                         << dest << endl;
                                    if (p->to_string() == "\u2659") {
                                        p->promotion(e, position);
                                    }
                                }
                            } else
                                cerr << "Mouvement illégal" << endl;
                            e.affiche();
                        }

                        if (this->fin())
                            break;
                        if (e.detecter_echec(Noir)) {
                            cout << "Le Roi Noir est en échec!" << endl;
                            if (e.detecter_mat(Noir)) {
                                cout << "Echec et mat!" << endl;
                                cout << "Joueur 1(Blanc) a gagné" << endl;
                                setResultat(VICTOIRE_BLANCS);
                                finir(true);
                                break;
                            }
                        } else {
                            if (e.detecter_pat(Noir))
                                cout << "Match null";
                        }
                    } ////////////////////////
                } else {
                    cout << "Saisie incorrecte!" << endl;
                }

            } else {
                if (mouvement == "/quit")
                    setResultat(PARTIE_INTERROMPUE);
                else if (mouvement == "/draw")
                    setResultat(NULLE);
                else if (mouvement == "/resign")
                    setResultat(VICTOIRE_NOIRS);
                finir(true);
                break;
            }
        }
        if (this->fin())
            break;
        while (joueur == 2) {
            cout << "Joueur 2(Noir)" << endl << "Coup (eg. a1a8) ? ";
            cin >> mouvement;
            if (mouvement != "/quit" && mouvement != "/draw" &&
                mouvement != "/resign") {

                if (saisie_correcte(mouvement) ||
                    saisie_correcte_petitroque(mouvement) ||
                    saisie_correcte_grandroque(mouvement)) {

                    if (saisie_correcte_petitroque(mouvement) ||
                        saisie_correcte_grandroque(mouvement)) {

                        if (saisie_correcte_petitroque(mouvement)) {
                            if (e.executer_petitroque(Noir) == true) {
                                joueur = 1;
                                e.affiche();
                            } else {
                                cout << "petit roque invalide" << endl;
                            }
                        } else {
                            if (e.executer_grandroque(Noir) == true) {
                                joueur = 1;
                                e.affiche();
                            } else {
                                cout << "grand roque invalide" << endl;
                            }
                        }
                    } else {
                        // découper case origine et destination

                        string orig = mouvement.substr(0, 2);
                        string dest = mouvement.substr(2, 2);

                        position.conversion(orig);
                        p = e.getPiece(position);

                        if (p == NULL || p->getCouleur() == Blanc) {
                            if (p == NULL)
                                cerr << "Aucune pièce dans la case d'origine"
                                     << endl;
                            else
                                cerr << "Mauvaise pièce(Mouvement illégal)"
                                     << endl;
                        } else {

                            position.conversion(dest);
                            if (p->est_mouvement_legal(e, position)) {
                                bool status = p->getDeplace();
                                p->mouvement(e, position);
                                if (e.detecter_echec(Noir)) {
                                    cerr << "ce mouvement met le roi en "
                                            "échec";
                                    position.conversion(orig);
                                    p->mouvement(e, position);
                                    p->setDeplace(status);
                                } else {

                                    joueur = 1;
                                    cout << "-> déplacement de "
                                         << p->to_string() << " " << orig
                                         << dest << endl;
                                    if (p->to_string() == "\u265F") {
                                        p->promotion(e, position);
                                    }
                                }
                            } else
                                cerr << "Mouvement illégal" << endl;
                            e.affiche();
                        }
                        if (this->fin())
                            break;
                        if (e.detecter_echec(Blanc)) {
                            cout << "Le Roi Blanc est en échec!" << endl;
                            if (e.detecter_mat(Blanc)) {
                                cout << "Echec et mat!" << endl;
                                cout << "Joueur 2(Noir) a gagné" << endl;
                                setResultat(VICTOIRE_NOIRS);
                                finir(true);
                                break;
                            }

                        } else {
                            if (e.detecter_pat(Blanc))
                                cout << "Match null";
                        }
                    } ///////////////////////////////////////
                } else {
                    cout << "Saisie incorrecte!" << endl;
                }
            } else {
                if (mouvement == "/quit")
                    setResultat(PARTIE_INTERROMPUE);
                else if (mouvement == "/draw")
                    setResultat(NULLE);
                else if (mouvement == "/resign")
                    setResultat(VICTOIRE_BLANCS);

                finir(true);
                break;
            }
        }
        if (this->fin())
            break;
    }

    /*    if(e.getRoi(Blanc) != NULL && e.getRoi(Noir) != NULL){

        }else{


        if(e.getRoi(Blanc)==NULL)
        {
            cout <<"Joueur 2(Noir) a gagné"<<endl;
        }else{
            cout <<"Joueur 1(Blanc) a gagné"<<endl;
        }
        }
    */
    cout << "Fin de la partie" << endl;
    cout << e.canonical_position() << " " << afficherResultatPartie() << endl;
}
