#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED
#include<vector>
#include <fstream>
#include<string>
using namespace std;
const int afficheImage =1,composanteRouge=2, niveauxGris=3, noirEtBlanc=4, quitter=0;

class Image{
  vector<vector<int>> _TabRouge;
  vector<vector<int>> _TabVert;
  vector<vector<int>> _TabBleu;
  int _Lo; // Longueur de l'image
  int _La; // Largeur de l'image

public:
  Image(const vector<vector<int>> &red={{0,0,0,0},{0,0,255,255},{0,255,255,255},{255,255,255,255}},const vector<vector<int>> &green={{0,0,255,255},{0,255,255,255},{0,255,255,0},{255,255,0,0}},
        const vector<vector<int>> &blue={{255,255,0,0},{255,0,0,0},{0,0,0,0},{0,0,0,0}});
  Image(const string nom);

  void affiche()const;

/* Donne la valeur de chaque couleur pour un pixel donné */
  vector<int> valeurPixel(int i, int j)const;

  /*  Créer une nouvelle image à partir de l’image cible qui a la même composante Rouge et les autres composantes à zéro*/
  void composanteRouge();

/* prend en paramètre trois entiers représentant le code RVB d’une couleur et qui retourne vrai si il existe un pixel de cette couleur dans l’image cible*/
 bool detection(const int& R, const int& V, const int& B);

/* Créer une nouvelle image à partir de l’image cible dont chaque pixel est gris */
  void niveauxGris();

/* Créer une nouvelle image à partir de l’image cible dont chaque pixel est ou noir, ou blanc */
  void noirEtBlanc(int seuil);

  void save(ofstream &, const string&);

  int getLa()const;

  int getLo()const;

//supprime nb colonnes de pixel de l’image en bas
  void rognerB(int nb);

//supprime nb colonnes de pixel de l’image à droite
  void rognerD(int nb);

//supprime nb lignes de pixel de l’image en haut
  void rognerH(int nb);

//supprime nb colonnes de pixel de l’image à gauche
  void rognerG(int nb);

//retourna un vecteur d’entiers représentant l’histogramme de l’image en niveau de gris
  vector<int> histogrammeGris();

//diminue le luminosité de l’image
  void luminosityDown();

//augmente la luminosité de l’image
  void luminosityUp();

// augmente le contraste de l’image
  void contrasteUp();

// diminue le contraste de l’image
  void contrasteDown();

// effectue une symétrie d'axe horizontal sur l'image
  void retournementV();

// Blanchi les couleur proche de la couleur rentré en paramètre de la forme (R,V,B)
  void blanchirCouleur(int, int, int);

};
void affiche1D(const vector<int> &);

void loadPicture(const string &picture, vector<vector<int>> &red,
                                        vector<vector<int>> &green,
                                        vector <vector<int>> &blue);

string saisirNomFichier();

#endif // IMAGE_H_INCLUDED
