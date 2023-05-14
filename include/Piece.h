#ifndef _PIECE_H
#define _PIECE_H

#include "Square.h"
#include <iostream>

using namespace std;

class Echiquier;

/**
 * @brief ensemble statique répresentant les couleurs des pièces
 *
 */
enum Couleur { Blanc = 1, Noir = 0 };

/**
 * @brief Classe abstraite répresentant les pièces de l'échiquier
 *
 */
class Piece {

    //--------atributs--------
  private:
    string nom;
    Couleur couleur; //  1 pour les pièces blanches et 0 pour les pièces noires
    Square position;
    bool deplace = false;

  public:
    /*constructeur*/
    Piece();
    Piece(Couleur couleur, string nom, Square position);

    /*desctructeur*/
    ~Piece();

    /**
     * @brief récupere la couleur d'une pièce
     *
     * @return Couleur couleur de la pièce
     */
    Couleur getCouleur() const;

    /**
     * @brief affecte une couleur à une pièce
     *
     * @param couleur couleur que l'on veut y affecter
     */
    void setCouleur(Couleur couleur);

    /**
     * @brief récupere la position d'une pièce
     *
     * @return Square const position de la pièce
     */
    Square const getPosition();

    /**
     * @brief affecte une position à une pièce
     *
     * @param position position que l'on veut y affecter
     */
    void setPosition(Square const &position);

    /**
     * @brief récupere le nom d'une pièce
     *
     * @return string nom de la pièce
     */
    string to_string() const;

    /**
     * @brief récupere la valeur de la variable deplace
     *
     * @return true si la pièce a été déplacée et false si elle ne l'a pas été
     */
    bool getDeplace();

    /**
     * @brief affecte une valeur à la pièce déplace
     *
     * @param status valeur à y affecter
     */
    void setDeplace(bool status);

    /**
     * @brief permet de promouvoir un pion
     *
     * @param e echiquier à effectuer la promotion
     * @param pos position du pion dans l'échiquier
     * @return int si 1, alors on nous a demandé de quiter la partie
     */
    int promotion(Echiquier &e, Square const &pos);

    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e,
                                     Square const &destination) = 0;

    /**
     * @brief effectue le mouvement s'il est légal
     *
     * @param e echiquier à effectuer la vérification
     * @param position position où l'on veut déplacer la pièce
     */
    void mouvement(Echiquier &e, Square const &position);
};

#endif