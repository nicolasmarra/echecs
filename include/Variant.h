#ifndef _VARIANT_H
#define _VARIANT_H

#include "Piece.h"
#include <string>

/**
 * @brief classe concrète répresentant les Pions de l'échiquer, cette classe
 * hérite de la classe pièce
 *
 */
class Pion : public Piece {
    //--------atributs--------
  private:
    bool double_pas = false;
    bool prise_passant = false;

  public:
    /*constructeurs*/
    Pion(Couleur couleur, string nom, Square position);
    Pion(Couleur couleur, Square position);
    Pion(Square position);

    /*destructeur*/
    ~Pion();

    /**
     * @brief récupere la valeur de la variable double_pas
     *
     * @return true si la valeur de variable est true et false si c'est false
     */
    bool getDouble_pas();

    /**
     * @brief change la valeur de la variable prise_passant
     *
     * @param status nouvelle valeur de la variable prise_passant
     */
    void setPrise_passant(bool status);

    /**
     * @brief récupere la valeur de la variable prise_passant
     *
     * @return true si la valeur de variable est true et false si c'est false
     */
    bool getPrise_passant();

    /**
     * @brief change la valeur de la variable status
     *
     * @param status nouvelle valeur de la variable status
     */
    void setDouble_pas(bool status);

    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

/**
 * @brief classe concrète répresentant les Tours de l'échiquer, cette classe
 * hérite de la classe pièce
 *
 */
class Tour : public Piece {
  public:
    /*constructeurs*/
    Tour(Couleur couleur, string nom, Square position);
    Tour(Couleur couleur, Square position);
    Tour(Square position);

    /*destructeur*/
    ~Tour();

    /**
     * @brief vérifie si le mouvement de la tour est legal
     *
     * @param e echiquier à effectuer la vérification
     * @param positon position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    bool mouvement_tour(Echiquier &e, Square const &position, Piece &p);
    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @param p pièce que l'on veut vérifier le déplacement
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

/**
 * @brief classe concrète répresentant les Cavaliers de l'échiquer, cette classe
 * hérite de la classe pièce
 *
 */
class Cavalier : public Piece {
  public:
    /*constructeurs*/
    Cavalier(Couleur couleur, string nom, Square position);
    Cavalier(Couleur Couleur, Square position);
    Cavalier(Square position);

    /*destructeur*/
    ~Cavalier();

    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

/**
 * @brief classe concrète répresentant les Fous de l'échiquer, cette classe
 * hérite de la classe pièce
 *
 */
class Fou : public Piece {
  public:
    /*constructeurs*/
    Fou(Couleur couleur, string nom, Square position);
    Fou(Couleur couleur, Square position);
    Fou(Square position);

    /*destructeur*/
    ~Fou();

    /**
     * @brief vérifie si le mouvement du fou est legal
     *
     * @param e echiquier à effectuer la vérification
     * @param positon position où l'on veut déplacer la pièce
     * @param p pièce que l'on veut vérifier le déplacement
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    bool mouvement_fou(Echiquier &e, Square const &position, Piece &p);
    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

/**
 * @brief classe concrète répresentant la Dame de l'échiquer, cette classe
 * hérite de la classe pièce
 *
 */
class Dame : public Piece {
  public:
    /*constructeurs*/
    Dame(Couleur couleur, string nom, Square position);
    Dame(Couleur couleur, Square position);
    Dame(Square position);

    /*destructeur*/
    ~Dame();

    // Changer ça

    /**
     * @brief vérifie si le mouvement de la tour est legal
     *
     * @param e echiquier à effectuer la vérification
     * @param positon position où l'on veut déplacer la pièce
     * @param p pièce que l'on veut vérifier le déplacement
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    bool mouvement_tour(Echiquier &e, Square const &position, Piece &p);

    /**
     * @brief vérifie si le mouvement du fou est legal
     *
     * @param e echiquier à effectuer la vérification
     * @param positon position où l'on veut déplacer la pièce
     * @param p pièce que l'on veut vérifier le déplacement
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    bool mouvement_fou(Echiquier &e, Square const &position, Piece &p);
    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

/**
 * @brief classe concrète répresentant le Roi de l'échiquer, cette classe hérite
 * de la classe pièce
 *
 */
class Roi : public Piece {
  public:
    /*constructeurs*/
    Roi(Couleur couleur, string nom, Square position);
    Roi(Couleur couleur, Square position);
    Roi(Square position);

    /*destructeur*/
    ~Roi();

    /**
     * @brief vérifie si un mouvement est légal, cette méthode est commune à
     * toutes les pièces
     *
     * @param e echiquier à effectuer la vérification
     * @param destination position où l'on veut déplacer la pièce
     * @return true si le mouvement est légal et false si le mouvement ne l'est
     * pas
     */
    virtual bool est_mouvement_legal(Echiquier &e, Square const &position);
};

#endif