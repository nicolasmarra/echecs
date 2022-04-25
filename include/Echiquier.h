#ifndef _ECHIQUIER_H
#define _ECHIQUIER_H

#include "Piece.h"
#include "Square.h"
#include "Variant.h"

/**
 * @brief Représente le stockage des pièces crées
 *
 */
class Echiquier {

    //--------atributs--------
  private:
    Piece *echiquier[8][8];
    Piece *roiBlanc;
    Piece *roiNoir;
    Piece *piecesb[8];
    Piece *piecesn[8];
    Piece *pionsb[8];
    Piece *pionsn[8];

  public:
    /*constructeur*/
    Echiquier();

    /*destructeur*/
    ~Echiquier();

    /**
     * @brief Récuperer une pièce quelconque
     * @param position position de la pièce que l'on veut récuperer
     * @return retourne un pointeur sur une Piece s'il y a une dans la case
     *correspondant à la position saisie ou NULL  si la case est vide
     **/
    Piece *getPiece(Square const &position) const;

    /**
     * @brief Récuperer une pièce du type Roi
     * @param couleur couleur du roi que l'on veut récuperer
     * @return un pointeur sur une pièce du type Roi
     **/
    Piece *getRoi(Couleur couleur);

    /**
     * @brief Affecte un pointeur NULL à une pièce du type Roi
     * @param couleur couleur du roi que l'on veut affecter le pointeur NULL
     **/
    void setRoi(Couleur couleur);

    /**
     * @brief Pose une pièce à une position donnée
     * @param p pointeur vers une pièce
     * @param position la position où on veut poser la pièce
     */
    void pose_piece(Piece *p, Square const &position);

    /**
     * @brief affiche l'échiquier
     *
     */
    void affiche() const;

    /**
     * @brief initiatilse toutes les cases de l'échiquier à NULL et alloue des
     * vecteurs piecesb,piecesn, pionsb et pionsn
     *
     */
    void alloc_mem_echiquier();

    /**
     * @brief rendre le symbole utilisé dans la notation PGN
     *
     * @param name nom de la pièce
     * @param view_pawn affichage des pions
     * @param view_color afficage des couleurs
     * @return string
     */
    string pgn_piece_name(string const name, bool view_pawn,
                          bool view_color) const;

    /**
     * @brief affiche le contenue de chaque case de l'échiquier
     *
     * @return string
     */
    string canonical_position() const;

    /**
     * @brief vérifie si une case est vide
     *
     * @param position position de la case
     * @return true si la case est vide et false si la case n'est pas vide
     */

    bool est_case_vide(Square const &position) const;

    /**
     * @brief détecte si un roi est en échec
     *
     * @param Couleur couleur du roi que l'on veut détecter s'il est en échec
     * @return true si le roi est en échec et false si le roi n'est pas en échec
     */
    bool detecter_echec(Couleur Couleur);

  /**
   * @brief détecte si c'est échec et mat
   * 
   * @param Couleur couleur du roi que l'on veut détecter son échec et mat
   * @return true si c'est échec et mat
   * @return false si ce n'est pas échec et mat
   */
    bool detecter_mat(Couleur Couleur);

  /**
   * @brief détecte si c'est pat
   * 
   * @param Couleur couleur du joueur qu'on veut détecter le pat
   * @return true si c'est pat
   * @return false si ce n'est pas pat
   */
    bool detecter_pat(Couleur Couleur);

  /**
   * @brief détecte si l'on peut empecher l'échec 
   * 
   * @param position positon de la pièce adverse qui met le roi en échec
   * @param Couleur couleur du roi qui est en échec
   * @return true si l'on peut empecher l'échec et false si l'on ne peut empecher l'échec
   */
    bool enlever_check(Square const &position, Couleur Couleur);

    bool executer_petitroque(Couleur Couleur);
    bool executer_grandroque(Couleur Couleur);
};

#endif