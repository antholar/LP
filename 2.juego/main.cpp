#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<int> separarxespacios(string x){
    string tmp = "";
    vector<int> rpta;
    for(int i = 0;i<x.length();i++){
        if(x[i] == ' '){
            rpta.push_back(atoi(tmp.c_str()));
            tmp="";
        }
        else
            tmp.push_back(x[i]);
    }
    if(tmp.length() != 0)
        rpta.push_back(atoi(tmp.c_str()));
    return rpta;
}

bool matrizCompleta(vector< vector<int> > data){
    for(int i = 0;i<data.size();i++){
        for(int j = 0;j<data[i].size();j++)
            if(data[i][j] != 0) return 0;
    }
    return 1;
}

void borrar(vector< vector<int> > & data,int caracter,int y,int x,char direc){
    if(x<0 || y>=data.size() || y<0 || x>=data[0].size()) return;
    if(data[y][x] == caracter)
        data[y][x] = 0;
    else return;
    if(direc == 'u'){
        borrar(data,caracter,y-1,x,'u');
        borrar(data,caracter,y,x-1,'l');
        borrar(data,caracter,y,x+1,'r');
    }
    if(direc == 'd'){
        borrar(data,caracter,y+1,x,'d');
        borrar(data,caracter,y,x-1,'l');
        borrar(data,caracter,y,x+1,'r');
    }
    if(direc == 'l'){
        borrar(data,caracter,y-1,x,'u');
        borrar(data,caracter,y+1,x,'d');
        borrar(data,caracter,y,x-1,'l');
    }
    if(direc == 'r'){
        borrar(data,caracter,y-1,x,'u');
        borrar(data,caracter,y+1,x,'d');
        borrar(data,caracter,y,x+1,'r');
    }
    if(direc == 'c'){
        borrar(data,caracter,y-1,x,'u');
        borrar(data,caracter,y+1,x,'d');
        borrar(data,caracter,y,x-1,'l');
        borrar(data,caracter,y,x+1,'r');
    }
}

void movimiento(vector< vector<int> > & data,int x,int y){
    vector< vector<int> > tmp;
    int elimi = 0;
    for(int i = data.size()-1;i>=0;i--)
        tmp.push_back(data[i]);
    data = tmp;
    cout << data[y][x] << endl;
    borrar(data,data[y][x],y,x,'c');
    tmp.clear();
    for(int i = data.size()-1;i>=0;i--)
        tmp.push_back(data[i]);
    data = tmp;
}

// despues de eliminar acomoda los datos, haciendolos bajar y mover a la izquierda
void ordenar(vector< vector<int> > & data){
    bool cambios = false;
    // bajar datos
    for(int i = 0;i<data.size()-1;){
        cambios = false;
        for(int j = 0;j<data[i].size();j++){
            if(data[i][j] != 0 && data[i+1][j] == 0){
                cambios = true;
                data[i+1][j] = data[i][j];
                data[i][j] = 0;
            }
        }
        if(cambios == true) i=i-1;
        else i++;
    }

    // acomodar a la izquierda
    bool recorrerIzq =true;
    for(int j = 0;j<data[0].size();){
        recorrerIzq = true;
        for(int i = 0;i<data.size();i++){
            if (data[i][j] != 0) {
                recorrerIzq = false;
                break;
            }
        }
        cout << j << " " << recorrerIzq << " " << data[0].size()-1<< endl;
        if(recorrerIzq == true && j != data[0].size()-1){
            for(int k = j+1;k<data[0].size();k++){
                for(int l = 0;l<data.size();l++){
                    data[l][k-1] = data[l][k];
                    data[l][k] = 0;
                }
            }
            j++;
        }
        else j++;
    }



}

int main()
{
    ifstream Ar("entrada.txt");
    string tmp;
    vector<int> tmp2;
    vector< vector<int> > data;
    while(!Ar.eof()){
        getline(Ar,tmp);
        tmp2 = separarxespacios(tmp);
        data.push_back(tmp2);
    }
    int x =0,y =0;
    while(!matrizCompleta(data)){

        cout << x << " " << y << endl;
        for(int i = 0;i<data.size();i++){
            cout << data.size()-1-i << " |	";
            for(int j = 0;j<data[i].size();j++)
                cout << data[i][j] << "	";
            cout << endl;
        }
        cout << "--+-----------------" << endl;
        cout << "  |	";
        for(int j = 0;j<data[0].size();j++){
            cout << j << "	";
        }
        cout << endl;
        cin >> y >> x;

        movimiento(data,x,y);
        ordenar(data);
        //system("cls");
    }

    ///////////
    for(int i = 0;i<data.size();i++){
        cout << data.size()-1-i << " |	";
        for(int j = 0;j<data[i].size();j++)
            cout << data[i][j] << "	";
        cout << endl;
    }
    cout << "--+-----------------" << endl;
    cout << "  |	";
    for(int j = 0;j<data[0].size();j++){
        cout << j << "	";
    }
    cout << endl;
    ///////////


    cout << "Terminaste el juego" << endl;
    return 0;
}
