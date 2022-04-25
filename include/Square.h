#ifndef _SQUARE_H
#define _SQUARE_H

#include <string>

using namespace std;

/**
 * @brief Représente case une de l'échiquier
 * 
 */
class Square{

    //--------atributs--------
    private:
    int x, y;
    
    public:
    /*constructeur*/
    Square();
    Square(int x,int y);
    Square(string position);

    /**
     * @brief permet de récuperer la ligne de la case actuelle 
     * 
     * @return int ligne
     */
    int getX() const;

    /**
     * @brief permet de récuperer la colonne de la case actuelle 
     * 
     * @return int colonne
     */
    int getY() const;

    /**
     * @brief permet de changer l'indice d'une case
     * 
     * @param x entier répresentant la ligne
     * @param y entier répresentant la colonne
     */
    void  setSquare(int x, int y);

    /**
     * @brief permet de changer l'indice d'une case
     * 
     * @param square position
     */
    void setSquare(Square const &square);

    /**
     * @brief permet de convertir en indice de tableau une coordonnées en notation algebrique
     * 
     * @param position indice de tableau
     */
    void conversion(string position);

    /**
     * @brief permet de convertir en notation algébrique l'indice d'une case
     * 
     * @param position coordonées en notation algébrique
     */
    string to_string();
};

#endif