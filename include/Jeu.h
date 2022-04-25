#ifndef _JEU_H
#define _JEU_H
#include "Echiquier.h"
#include <regex>


/**
 * @brief Cette classe possède un objet de classe Echiquier et assure la gestion d'un coup.
 * 
 */
class Jeu{
    //--------atributs--------
    private:

    bool fin_partie;
    Echiquier e;
    Couleur equipe;

    public:

    /*constructeur*/
    Jeu();

    /*destructeur*/
    ~Jeu();

    /**
     * @brief affiche l'échiquier pour que l'utilisateur se rende compte de la nouvelle position
     * 
     */
    void affiche();

    /**
     * @brief permet de lancer le jeu
     * 
     */
    void joue();

    /**
     * @brief retourne la valeur de la variable fin_partie, c'est en fait une fonction get
     * 
     * @return true si la variable fin_partie est true et false si elle est false 
     */
    bool fin();

    /**
     * @brief change la valeur de la variable fin_partie
     * 
     * @param status la nouvelle valeur(true ou false) pour la variable fin_partie 
     */
    void finir(bool status);

     /**
     * @brief vérifie la validité d'une commande
     * 
     * @param cmd commande à exécuter
     * @return true si la commande est correcte  et false si la commande est incorrecte 
     */
    bool saisie_correcte(string const & cmd);

     /**
     * @brief vérifie la validité d'une commande pour faire le mouvement roque
     * 
     * @param cmd commande à exécuter
     * @return true si la commande est correcte  et false si la commande est incorrecte 
     */
    bool saisie_correcte_petitroque(string const & cmd);

};


#endif