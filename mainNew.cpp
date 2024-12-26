#include <iostream>
#include "imageNew.h"
#include <fstream>
#include"menuNew.h"
#include<vector>
using namespace std;
int main() {

    vector<vector<int>> red={{0,0,0,0},{0,0,255,255},{0,255,255,255},{255,255,255,255}};
    vector<vector<int>> green={{0,0,255,255},{0,255,255,255},{0,255,255,0},{255,255,0,0}};
    vector<vector<int>> blue={{255,255,0,0},{255,0,0,0},{0,0,0,0},{0,0,0,0}};
    bool encore =true;
    char str;
    while (encore){
        Image image;
        choixMenu(image);
        cout << "Voulez vous recommencer ? (o/n)"<<endl;
        cin >> str;
        if (str =='o'||str=='O'){
            encore=true;
        } else {
            cout <<"Bonne journee ! :)"<<endl;
            encore=false;
        }
    }

return 0;
}




