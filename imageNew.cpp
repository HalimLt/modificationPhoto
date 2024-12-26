#include <iostream>
#include <vector>
#include <fstream>
#include "imageNew.h"
using namespace std;

Image::Image(const vector<vector<int>> &TabRouge,const vector<vector<int>> &TabVert,const vector<vector<int>> &TabBleu) {
  if (TabRouge.size() != TabVert.size() || TabVert.size() != TabBleu.size()|| TabBleu.size()!=TabRouge.size())throw(0);
  _TabRouge = TabRouge;
  _TabVert = TabVert;
  _TabBleu = TabBleu;
  _Lo = TabRouge.size();
  _La = TabRouge[0].size();
}
Image::Image(const string nom){
    vector<vector<int>> rouge;
    vector<vector<int>> vert;
    vector<vector<int>> bleu;
    loadPicture(nom, rouge, vert, bleu);
    _La=rouge[0].size();
    _Lo=rouge.size();
    (*this) = Image(rouge, vert, bleu);
}

void Image::affiche()const {
  for (int i = 0; i < _Lo; i++) {
    for (int j = 0; j < _La; j++) {
      cout <<"{" <<_TabRouge[i][j] << ", " << _TabVert[i][j] << ", " << _TabBleu[i][j] << "} ";
    }
    cout<<endl;
  }
}

vector<int> Image::valeurPixel(int i, int j) const {
  if (i < 0 || i >= _Lo || j < 0 || j >= _La) {
    throw(0);
  }
  return {_TabRouge[i][j], _TabVert[i][j], _TabBleu[i][j]};
}
void affiche1D(const vector<int> &v) {
  cout<<"{";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i];
    if (i != v.size() - 1) {
    cout<<", ";
    }
  }
  cout<<"}"<<endl;
}


void Image::composanteRouge(){
  for (int i = 0; i < _Lo; i++) {
    for (int j = 0; j < _La; j++) {
    _TabVert[i][j]=0;
    _TabBleu[i][j]=0;
    }
  }
}

bool Image::detection(const int& R, const int& V, const int& B){
  int i, j;
  i=0;
  j=0;
  bool Trouve = false;
  while (!(Trouve) && i<_Lo && j<_La){
    if (valeurPixel(i,j)[0] == R && valeurPixel(i,j)[1] == V && valeurPixel(i,j)[2] == B){
      Trouve = true;
    }
    else{
      i++;
      j++;
    }
  }
  return Trouve;
}

void Image::niveauxGris(){
    int moyRVB, i,j;
    for (i=0;i<_Lo;i++){
        for (j=0;j<_La;j++){
            moyRVB = (_TabRouge[i][j]+_TabVert[i][j]+_TabBleu[i][j])/3;
            _TabRouge[i][j]=moyRVB;
            _TabVert[i][j]=moyRVB;
            _TabBleu[i][j]=moyRVB;
        }
  }
}

void Image::noirEtBlanc(const int seuil){
  int i,j;
  for (i=0;i<_Lo;i++){
    for (j=0;j<_La;j++){
      if((_TabRouge[i][j]+_TabVert[i][j]+_TabBleu[i][j])/3 >seuil){
        _TabRouge[i][j]=255;
        _TabVert[i][j]=255;
        _TabBleu[i][j]=255;
      }
      else{
        _TabRouge[i][j]=0;
        _TabVert[i][j]=0;
        _TabBleu[i][j]=0;
      }
    }
  }
}

string saisirNomFichier(){
  cout << "Saisir le nom du fichier" << endl;
  string nomFichier;
  cin >> nomFichier;
  return nomFichier+".ppm"  ;
}

void Image::save(ofstream &o, const string &NomFichier){
    o.open(NomFichier);
    o << "P3" << endl;
    o<<"# Created by Thomas ESCOBAR and Halim Luquet"<<endl;
    o<< _La<<" "<<_Lo<<endl;
    o<<"255"<<endl;
    for (int i = 0; i < _Lo; i++) {
        for (int j = 0; j < _La; j++) {
            o <<_TabRouge[i][j] <<" "<< _TabVert[i][j] <<" "<< _TabBleu[i][j];
            o<<endl;
        }
    }
    o.close();

}

int Image::getLa()const{
    return _La;
}
int Image::getLo()const{
    return _Lo;
}

void loadPicture(const string &picture, vector<vector<int>> &red,
                                        vector<vector<int>> &green,
                                        vector <vector<int>> &blue)
{
    // Declaration des variables
    string line; // pour recuperer les lignes du fichier image au format .ppm, qui est code en ASCII.
    string format; //pour recuperer le format de l'image : celui-ci doit être de la forme P3
    string name; // au cas où l'utilisateur se trompe dans le nom de l'image a charger, on redemande le nom.
    int taille;
    vector <int> mypixels; // pour recuperer les donnees du fichier de maniere lineaire. On repartira ensuite ces donnees dans les tableaux correspondants
    ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les donnees de l'image.
    int hauteur; // pour bien verifier que l'image est carree, et de taille respectant les conditions fixees par l'enonce
    // Initialisation des variables
    name = picture;
    // Permet d'ouvrir le fichier portant le nom picture
    // ouverture du fichier portant le nom picture
    entree.open(name);
    // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on redemande un nom de fichier valide
    while (!entree){
        //cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        entree.open(name); // relance
    }
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    // on finit de lire la ligne (caractere d'espacement)
    getline(entree, line);
    // Lecture du commentaire
    getline(entree, line);
    //lecture des dimensions
    entree >> taille >> hauteur;
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // On verifie que l'image a une taille qui verifie bien les conditions requises par l'enonce.
    // Si cela n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
    while (format != "P3"){
        if (format != "P3"){
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
  entree.close();
        // On va redemander un nom de fichier valide.
        do{
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            entree.open(name); // relance
        }while(!entree);
         // Lecture du nombre definissant le format (ici P3)
         entree >> format;
         getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
        // Lecture du commentaire
        getline(entree, line);
        //lecture des dimensions
        entree >> taille >> hauteur; // relance
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    }
    //Lecture de la valeur max
    getline(entree, line);
    //Lecture des donnees et ecriture dans les tableaux :
    // Pour plus de simplicite, on stocke d'abord toutes les donnees dans mypixels
    // dans l'ordre de lecture puis ensuite on les repartira dans les differents tableaux.
    //Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
    // Il faudra donc repartir les valeurs R correspondant a la composante rouge de l'image
    // dans le tableau red, de même pour G et B.
    int pix;
    mypixels.resize(3*taille*hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3*taille*hauteur; i++){
      entree >> pix;
      mypixels[i]=pix;
    }
    // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les donnees sont stockees de la maniere suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant a la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus a 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus a 1 mod 3, ...
     // les valeurs d'une ligne
    int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for (int i = 0; i < hauteur; i++){
      vector <int> ligneR(taille);
      vector <int> ligneB(taille);  // les lignes ont toutes la même taille
      vector <int> ligneG(taille);
      for (int j = 0; j < taille; j++){
            val =  mypixels[3*j + 3*taille*i];
            ligneR[j]=val;
            val = mypixels[3*j + 1 + 3*taille*i];
            ligneG[j]=val;
            val = mypixels[3*j + 2 + 3*taille*i];
            ligneB[j]=val;
        }
        red[i]=ligneR;
        green[i]=ligneG;
        blue[i]=ligneB;
    }
    // Informations a l'utilisateur pour dire que tout s'est bien passe
    cout << " L'image " << name << " a bien ete chargee dans les tableaux ." << endl;
     entree.close();
 }

void Image::rognerB(int nb){
  int i;
  for (i=0;i<nb;i++){
    _TabRouge.pop_back();
    _TabVert.pop_back();
    _TabBleu.pop_back();
    _Lo--;
  }

}
void Image::rognerD(int nb){
  int i, j;
  for (i=0;i<nb;i++){
    for (j=0;j<_Lo;j++){
      _TabRouge[j].pop_back();
      _TabVert[j].pop_back();
      _TabBleu[j].pop_back();
    }
     _La--;
  }
}

void Image::rognerH(int nb){
  int i;
  for(i=0;i<nb;i++){
    _TabRouge.erase(_TabRouge.begin());
    _TabVert.erase(_TabVert.begin());
    _TabBleu.erase(_TabBleu.begin());
    _Lo--;
  }
}

void Image::rognerG(int nb){
  int i,j, b;
// Copie les pixels qui ne doivent pas être rogner au début des vecteurs
  for(b=0;b<nb;b++){
    for (i=0;i<_Lo;i++){
      for(j=0;j<_La-nb;j++){
        _TabRouge[i][j]=_TabRouge[i][j+nb];
        _TabVert[i][j]=_TabVert[i][j+nb];
        _TabBleu[i][j]=_TabBleu[i][j+nb];
      }
    }

  }
  rognerD(nb);
}

vector<int> Image::histogrammeGris(){
  int i,j;
  vector<vector<int>> _TabNewRouge = _TabRouge;
  vector<vector<int>> _TabNewVert =_TabVert;
  vector<vector<int>> _TabNewBleu = _TabBleu;
  Image imageD(_TabNewRouge, _TabNewVert, _TabNewBleu);

  vector<int> histGris(256,0);
  imageD.niveauxGris();
  imageD.affiche();
  for (i=0; i<_Lo; i++) {
    for (j=0; j<_La; j++) {
      histGris[imageD._TabRouge[i][j]]=histGris[imageD._TabRouge[i][j]]+1;
    }
  }
  return histGris;
}


void Image::luminosityDown(){
  int i,j;
  float coeff;
  // Saisie du facteur de diminution
  cout << "Par quel facteur souhaitez-vous diminuer la luminosité ?\n Donnez un nombre situé entre 0 et 1 non compris: ";
  cin >> coeff;
  while(coeff<0 || coeff>1){
    cout << "Le nombre saisie est incorrect\n Entre 0 et 1 : ";
    cin >> coeff;
  }
// multiplie chaque taux par le coefficient
  for (i=0; i<_Lo; i++) {
    for (j=0; j<_La; j++) {
      _TabRouge[i][j]*=coeff;
      _TabVert[i][j]*=coeff;
      _TabBleu[i][j]*=coeff;
    }
  }
}


void Image::luminosityUp(){
  int i,j;
  float coeff;
  cout << "Par quel facteur voulez-vous augmenter la luminosité ?\n Donnez un nombre supérieur à 1: ";
  cin >> coeff;
// Demande une nouvelle saisie tant qu'elle est inférieur à 1
  while(coeff<1){
    cout << "Le nombre saisie est incorrect\n Donnez un nombre supérieur à 1: ";
    cin >> coeff;
  }

// multiplie chaque taux par le coefficient en vérifiant que cela ne dépasse pas 255
  for (i=0; i<_Lo; i++) {
    for (j=0; j<_La; j++) {
      if (_TabRouge[i][j]*coeff>255)_TabRouge[i][j]=255;
      else _TabRouge[i][j]*=coeff;

      if (_TabVert[i][j]*coeff>255) _TabVert[i][j]=255;
      else _TabVert[i][j]*=coeff;

      if (_TabBleu[i][j]*coeff>255) _TabBleu[i][j]=255;
      else _TabBleu[i][j]*=coeff;
      }
    }
}

void Image::contrasteUp(){
  int i,j;
  float coeff;

  cout << "Par quel facteur voulez-vous augmenter le contraste ?\n Donnez un nombre supérieur à 1: ";
  cin >> coeff;
// Demande une nouvelle saisie tant qu'elle est inférieur à 1
  while(coeff<1){
    cout << "Le nombre saisie est incorrect\n Donnez un nombre supérieur à 1: ";
    cin >> coeff;
  }
    for (i=0; i<_Lo; i++) {
      for (j=0; j<_La; j++) {

        if (128+coeff*(_TabRouge[i][j]-128)<0) _TabRouge[i][j]=0;
        else if (128+coeff*(_TabRouge[i][j]-128)>255) _TabRouge[i][j]=255;
        else _TabRouge[i][j]=128+coeff*(_TabRouge[i][j]-128);

        if (128+coeff*(_TabVert[i][j]-128)<0) _TabVert[i][j]=0;
        else if (128+coeff*(_TabVert[i][j]-128)>255) _TabVert[i][j]=255;
        else _TabVert[i][j]=128+coeff*(_TabVert[i][j]-128);

        if (128+coeff*(_TabBleu[i][j]-128)<0) _TabBleu[i][j]=0;
        else if (128+coeff*(_TabBleu[i][j]-128)>255) _TabBleu[i][j]=255;
        else _TabBleu[i][j]=128+coeff*(_TabBleu[i][j]-128);
      }
    }
}

void Image::contrasteDown(){
  int i,j;
  float coeff;

  cout << "Par quel facteur voulez-vous augmenter le contraste ?\n Donnez un nombre inférieur à 1: ";
  cin >> coeff;
// Demande une nouvelle saisie tant qu'elle est supérieur à 1
  while(coeff>1){
    cout << "Le nombre saisie est incorrect\n Donnez un nombre inférieur à 1: ";
    cin >> coeff;
  }
  for (i=0; i<_Lo; i++) {
    for (j=0; j<_La; j++) {

      if (128+coeff*(_TabRouge[i][j]-128)<0) _TabRouge[i][j]=0;
      else if (128+coeff*(_TabRouge[i][j]-128)>255) _TabRouge[i][j]=255;
      else _TabRouge[i][j]=128+coeff*(_TabRouge[i][j]-128);

      if (128+coeff*(_TabVert[i][j]-128)<0) _TabVert[i][j]=0;
      else if (128+coeff*(_TabVert[i][j]-128)>255) _TabVert[i][j]=255;
      else _TabVert[i][j]=128+coeff*(_TabVert[i][j]-128);

      if (128+coeff*(_TabBleu[i][j]-128)<0) _TabBleu[i][j]=0;
      else if (128+coeff*(_TabBleu[i][j]-128)>255) _TabBleu[i][j]=255;
      else _TabBleu[i][j]=128+coeff*(_TabBleu[i][j]-128);
      }
    }
}

void Image::retournementV(){
  int i,j;
  vector<vector<int>> _TabNewRouge;
  vector<vector<int>> _TabNewVert;
  vector<vector<int>> _TabNewBleu;
  for (i=_Lo-1;i>=0;i--){
    _TabNewRouge.push_back(_TabRouge[i]);
    _TabNewVert.push_back(_TabVert[i]);
    _TabNewBleu.push_back(_TabBleu[i]);
  }
  Image imageD(_TabNewRouge, _TabNewVert, _TabNewBleu);
  (*this)=imageD;
}

void Image::blanchirCouleur(int r, int v, int b) {
    int i, j;
    bool proche;
    for (i = 0; i < _Lo; i++) {
        for (j = 0; j < _La; j++) {
            // Calcul de la distance euclidienne entre la couleur cible et la couleur du pixel
            double distance = (_TabRouge[i][j] - r) * (_TabRouge[i][j] - r) +
                                   (_TabVert[i][j] - v) * (_TabVert[i][j] - v) +
                                   (_TabBleu[i][j] - b) * (_TabBleu[i][j] - b);
            // Vérifier si la distance est inférieure ou égale au seuil de similitude
            proche = (distance / (r * r + v * v + b * b)) <= 0.01;
            if (proche) {
                _TabRouge[i][j] = 255;
                _TabVert[i][j] = 255;
                _TabBleu[i][j] = 255;
            }
        }
    }
}




