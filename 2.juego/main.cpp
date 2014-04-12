#include <iostream>
#include <vector>
#include <fstream>
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

bool find(vector<pair<int,int> > x, pair<int,int> a ){
    for(int i = 0;i<x.size() ;i++)
        if(x[i].first == a.first && x[i].second == a.second)
            return 1;
    return 0;
}

void ingresarValoresNuevos(vector<pair<int,int> > & ingresa,vector<pair<int,int> > x){
    for(int i = 0;i<x.size();i++)
        ingresa.push_back(x[i]);
}



class datos{
    public:
        vector< vector<int> > data;

        datos(){
            data.clear();
        }

        void cargar(){
            ifstream Ar("entrada.txt");
            string tmp;
            vector<int> tmp2;
            vector< vector<int> > tmp3;
            while(!Ar.eof()){
                getline(Ar,tmp);
                tmp2 = separarxespacios(tmp);
                tmp3.push_back(tmp2);
            }
            for(int i = tmp3.size()-1;i>=0;i--)
                data.push_back(tmp3[i]);
        }

        void print(){
            for(int i = data.size()-1;i>=0;i--){
                cout << i << " |    ";
                for(int j = 0;j<data[i].size();j++)
                    cout << data[i][j] <<  "    ";
                cout << endl;
            }
            cout << "--+-----------------" << endl;
            cout << "  |    ";
            for(int j = 0;j<data[0].size();j++){
                cout << j << "  ";
            }
            cout << endl;

            /*for(int i = data.size()-1;i>=0;i--){
                for(int j = 0;j<data[i].size();j++)
                    cout << data[i][j] << " ";
                cout << endl;
            }*/
        }

        bool matrizCompleta(){
            for(int i = 0;i<data.size();i++){
                for(int j = 0;j<data[i].size();j++)
                    if(data[i][j] != 0) return 0;
            }
            return 1;
        }

        vector<pair<int,int> > contarVecinos(int x,int y){
            int caracter = data[x][y];
            vector<pair<int,int> > visitados;
            vector<pair<int,int> > cola;
            pair<int,int> tmp;
            pair<int,int> tmp2;
            tmp.first = x;
            tmp.second = y;
            cola.push_back(tmp);
            while(cola.size() > 0){
                tmp = cola[0];
                cola.erase (cola.begin());
                if(!find(visitados,tmp)){
                    if(tmp.first+1<data.size()) //abajo
                        if(data[tmp.first+1][tmp.second] == caracter) {
                            tmp2=tmp;
                            tmp2.first+=1;
                            cola.push_back(tmp2);
                        }
                    if(tmp.first-1>=0) //arriba
                        if(data[tmp.first-1][tmp.second] == caracter) {
                            tmp2=tmp;
                            tmp2.first-=1;
                            cola.push_back(tmp2);
                        }
                    if(tmp.second+1<data[0].size()) //izquierda
                        if(data[tmp.first][tmp.second+1] == caracter) {
                            tmp2=tmp;
                            tmp2.second+=1;
                            cola.push_back(tmp2);
                        }
                    if(tmp.second-1>=0) //derecha
                        if(data[tmp.first][tmp.second-1] == caracter) {
                            tmp2=tmp;
                            tmp2.second-=1;
                            cola.push_back(tmp2);
                        }
                    visitados.push_back(tmp);

                }
            }
            return visitados;
        }

        void borrar(int caracter,int x,int y,char direc){
            if(x<0 || x>=data.size() || y<0 || y>=data[0].size())
                return;
            if(data[x][y] == caracter)
                data[x][y] = 0;
            else return;
            if(direc == 'u'){
                borrar(caracter,x-1,y,'u');
                borrar(caracter,x,y-1,'l');
                borrar(caracter,x,y+1,'r');
            }
            if(direc == 'd'){
                borrar(caracter,x+1,y,'d');
                borrar(caracter,x,y-1,'l');
                borrar(caracter,x,y+1,'r');

            }
            if(direc == 'l'){
                borrar(caracter,x-1,y,'u');
                borrar(caracter,x+1,y,'d');
                borrar(caracter,x,y-1,'l');
            }
            if(direc == 'r'){
                borrar(caracter,x-1,y,'u');
                borrar(caracter,x+1,y,'d');
                borrar(caracter,x,y+1,'r');
            }
            if(direc == 'c'){
                borrar(caracter,x-1,y,'u');
                borrar(caracter,x+1,y,'d');
                borrar(caracter,x,y-1,'l');
                borrar(caracter,x,y+1,'r');
            }
        }

        void movimiento(int x,int y){
            borrar(data[x][y],x,y,'c');
            ordenar();
        }

        void ordenar(){
            bool cambios = false;
            //bajar
            for(int i = 0;i<data.size()-1;i++){
                for(int j = 0;j<data[i].size();j++){
                    if(data[i][j] == 0){
                        data[i][j] = data[i+1][j];
                        data[i+1][j] = 0;
                    }
                }
            }

            // acomodar a la izquierda
            bool recorrerIzq =true;
            for(int j = 0;j<data[0].size();){
                recorrerIzq = true;
                for(int i = 0;i<data.size();i++)
                    if (data[i][j] != 0) {
                        recorrerIzq = false;
                        break;
                    }
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
};

class nodo{
    public:
        datos t;
        vector<nodo *> son;
        vector<pair<int,int> > visitados;
        vector<pair<int,int> > camino;
        vector<datos> camino2;


        nodo(){
            son.clear();
            visitados.clear();
        }

        void cargar(){
            t.cargar();
        }

        void copiarDatos(nodo * x){
            t.data = x->t.data;
            camino = x->camino;
            camino2= x->camino2;
        }

        int obtenerPos(int x,int y){
            return t.data[x][y];
        }

        void borrarPos(int x,int y){
            if(t.contarVecinos(x,y).size()>1)
                t.movimiento(x,y);
        }
};

class tree{
    public:
        nodo * proot;

        tree(){
            proot = 0;
        }

        void start(){
            proot = new nodo(); //proot es la raiz entonces carga el nodo principal que vendria a ser la matriz del archivo sin cambios
            proot->cargar();

            vector<nodo *> cola;
            cola.push_back(proot); // se pone a la matriz inicial en la cola para poder sacar a sus hijos
            nodo * actual;
            nodo * tmp1;
            int filas = proot->t.data.size();
            int colum = proot->t.data[0].size();
            pair<int,int> tmp2;

            vector<pair<int,int> > rpta;
            vector<datos> rpta2;
            int contardorxxx = 0;
            bool parenMaquinas = 0;
            while(cola.size()>0){
                actual = cola[0];
                cola.erase(cola.begin());

                for(int i = 0;i<filas;i++){
                    for(int j = 0;j<colum;j++){
                        tmp2.first = i;
                        tmp2.second = j;
                        tmp1 = 0;
                        //bool find(vector<pair<int,int> > x, pair<int,int> a ){
                        if(find (actual->visitados,tmp2) == false && actual->obtenerPos(i,j) != 0){
                            ingresarValoresNuevos(actual->visitados,actual->t.contarVecinos(tmp2.first,tmp2.second));
                            if(actual->t.contarVecinos(i,j).size()>1){
                                tmp1 = new nodo();
                                tmp1->copiarDatos(actual);
                                tmp1->camino2.push_back(actual->t);
                                tmp1->camino.push_back(tmp2);
                                tmp1->borrarPos(i,j);
                                actual->son.push_back(tmp1);
                                cola.push_back(tmp1);
                            }

                            //funcion de validacion de respuesta
                            if(tmp1!= 0)
                            if(tmp1->t.matrizCompleta()){
                                rpta = tmp1->camino;
                                rpta2 =tmp1->camino2;
                                parenMaquinas = 1;
                                break;
                            }

                        }
                    }
                }

                if(parenMaquinas == 1)
                    break;
            }
            if(rpta.size() == 0)
                cout << "no hay una repuesta :s" << endl;
            else{
                proot->t.print();
                cout << endl << "la solucion para la matriz de entrada es la siguiente" << endl;
                for(int i = 0;i<rpta.size();i++){
                    rpta2[i].print();
                    cout << rpta[i].first << " - " << rpta[i].second << endl;
                    cout << endl << endl;
                }
                cout << "matriz resuelta" << endl;
            }
        }

};

int main()
{
    tree a;
    a.start();
    return 0;
}
