#include <iostream>
#include <vector>
#include <fstream>
#include "menuNew.h"
using namespace std;
ofstream output;

void choixMenu(Image &image){

    int choix;
    do{
        cout << "1 Pour creer une image, 2 pour charger une image"<<endl;
        cin>>choix;
    }while(choix<1 ||choix >2);
    if (choix==1){
    } else {
        string NomFichier =saisirNomFichier();
        Image i(NomFichier);
        image=i;
    }
    do{
        cout << "1. Afficher l'image" << endl;
        cout << "2. Utiliser composante rouge" << endl;
        cout << "3. Utiliser blanchirCouleur" << endl; // Pour l'ajout d'une fonctionnalité j'ai du la rajouter à l'affichage du menu
        cout << "0. Sauvegarder et Quitter" << endl;
        cout << "-1. Quitter" << endl;
        cout << "Saisir votre choix" << endl;
        cin >> choix;
        system("cls");
        switch (choix){
        case 1:
            image.affiche();
            cout<<endl;
            break;
        case 2:
            image.composanteRouge();
            cout<<endl;
            break;
        case 3:
            {
            int r, v, b;
            cout << "Veuillez saisir 3 entiers représentant une couleur" <<endl;
            cout << "Rouge: ";
            cin >> r;
            cout << "\nVert: ";
            cin >>v;
            cout << "\nBleu: ";
            cin >>b;
            image.blanchirCouleur(r, v, b);
            break;
            }
        case 0:
            {
            string NomFichier =saisirNomFichier();
            image.save(output, NomFichier);
            break;
            }
        case -1:
            break;
        default:
            cout << "Choisir les bonnes valeurs !!!!!"<<endl;
            break;
        }
  }while(choix!=0 && choix!=-1);
}
