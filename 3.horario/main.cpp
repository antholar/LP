#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

// analisa un string y devuelve dividido el string apartir de los espacios
vector<string> getData(string a){
    string x = "";
    vector<string> rpta;
    for(int i = 0;i<a.length();i++){
        if(a[i] != ' ')
            x.push_back(a[i]);
        else{
            rpta.push_back(x);
            x = "";
        }
    }
    rpta.push_back(x);
    return rpta;
}

class tiempoF{
public:
    string dia; // dia del horario libre
    string nombre; // nombre de la persona del horario
    float inicio; // inicio del horario libre
    float fin; // fin del horario libre
    vector<string> reunion; // personas que pueden asistir en este horario

    tiempoF(){
        dia = "";
        nombre = "";
        inicio = 0;
        fin = 0;
        reunion.clear();
    }

    void operator=(tiempoF x){
        dia = x.dia;
        nombre = x.nombre;
        inicio = x.inicio;
        fin = x.fin;
        reunion = x.reunion;
    }

    // constructor que recibe el nombre de la persona el dia y la hora en formato 16:03-17:50 y lo convierte a flotante teniendo el formato 16.03 17.5
    tiempoF(string nombre_,string dia_,string x){
        reunion.push_back(nombre_);

        inicio = 0;
        fin = 0;
        nombre = nombre_;

        dia = dia_;
        bool h = 0;
        bool s = 0;
        string tmp;
        for(int i = 0 ;i<x.length();i++){
            if(x[i] == ':'){
                x[i] = '.';
            }
            if(x[i] == '-'){
                inicio = atof(tmp.c_str());
                tmp = "";
            }
            else
                tmp.push_back(x[i]);
        }
        fin = atof(tmp.c_str());
    }

    void print(){
        cout << dia << "	"<< inicio << "  " << fin << endl;
    }

    // comprueba si en este horario la persona x ya se encuentra en asistencia
    bool buscarReunion(string x){
        for(int i = 0;i<reunion.size();i++)
            if(reunion[i] == x) return true;
        return false;
    }

};

// convierte un string hora a un flotante
float analisarHora(string x){
    float sale;
    string tmp = "";
    bool xx = 0;
    for(int i = 0;i<x.length();i++){
        if(x[i] == ':'){
            x[i] = '.';
        }
        tmp.push_back(x[i]);
    }
    sale = atof(tmp.c_str());
    return sale;
}

// convierte un float en el formato de la hora
string convertirHora(float x){
    stringstream ss (stringstream::in | stringstream::out);
    ss << x;
    string test = ss.str();
    if(test.length() == 2){
        test.push_back(':');
        test.push_back('0');
        test.push_back('0');
    }
    else{
        for(int i = 0;i<test.length();i++)
            if(test[i]=='.'){
                test[i] = ':';
                if(i == 1) test.insert(test.begin(),'0');

            }
        if(test.length() == 4)test.push_back('0');
    }
    return test;
}

// calcula las posibilidades en las cuales se puede llevar la reunion
void calcularReunion(vector<string> x,vector<tiempoF> data){
    float tiempoReunion = analisarHora(x[0]);
    vector<tiempoF> posibilidad;
    for(int i = 1;i<x.size();i++)
        for(int j = 0;j<data.size();j++)
            if(x[i] == data[j].nombre)
                posibilidad.push_back(data[j]);

    // calendario guarda primero los dias y luego en ese dia los horarios disponibles de todas las personas
    // si en un horario pueden hacer la reunion dos personas, modifica el calendario a la hora que pueden asistir los dos y guardamos tambien
    // el nombre de la persona que puede asistir. 
    map<string, vector<tiempoF *> > calendario;
    bool cruce = false;
    tiempoF * tmp1;
    tiempoF * tmp2;
    for(int i = 0;i<posibilidad.size();i++){
        cruce = false;
        tmp1 = &posibilidad[i];
        
        // analisis de los cruces
        for(int j = 0;j<calendario[posibilidad[i].dia ].size();j++){
            if(!calendario[posibilidad[i].dia][j]->buscarReunion(posibilidad[i].nombre)){
                tmp2 = calendario[posibilidad[i].dia][j];

                if(tmp1->inicio <= tmp2->inicio && tmp2->inicio < tmp1->fin){
                    cruce = true;
                    tmp2->reunion.push_back(tmp1->nombre);
                    if(tmp1->fin < tmp2->fin){
                        tmp2->fin = tmp1->fin;
                    }
                }
                else{
                    if(tmp2->inicio <= tmp1->inicio && tmp1->inicio<tmp2->fin){
                        cruce = true;
                        tmp2->reunion.push_back(tmp1->nombre);
                        tmp2->inicio = tmp1->inicio;
                        if(tmp2->fin < tmp1->fin){
                            tmp2->fin = tmp2->fin;
                        }
                        else tmp2->fin = tmp1->fin;
                    }
                }

            }
        }
        // ingreso de un horario nuevo en el calendario
        if(cruce == false)
            calendario[posibilidad[i].dia].push_back(&posibilidad[i]);
    }

    // se limpia el calendario y se guardan solo los horarios en los que las personas pueden estar 
    calendario.clear();
    for(int i = 0;i<posibilidad.size();i++)
        if(posibilidad[i].reunion.size() == 2 && posibilidad[i].fin - posibilidad[i].inicio >= tiempoReunion )
            calendario[posibilidad[i].dia].push_back(&posibilidad[i]);

    for (std::map<string, vector<tiempoF *> >::iterator it=calendario.begin(); it!=calendario.end(); it++){
        cout << it->first << "  ";
        for(int i = 0;i<it->second.size();i++)
            cout << convertirHora(it->second[i]->inicio)<<"-"<<convertirHora(it->second[i]->fin) << "  ";
        cout << endl;
    }


    //cout << posibilidad.size() << endl;
}

int main()
{
    // entrada de datos
    string reunion = "00:45 a b";
    vector<string> horarios;
    horarios.push_back("a");
    horarios.push_back("b");

    // Cargar data de archivos
    vector<tiempoF> data;
    string tmp;
    vector<string> tmp1;
    for(int i = 0;i<horarios.size();i++){
        ifstream Ar(horarios[i].c_str());
        while(!Ar.eof()){
            getline(Ar,tmp,'\n');
            tmp1 = getData(tmp);
            for(int j = 1;j<tmp1.size();j++)
                data.push_back(tiempoF(horarios[i],tmp1[0],tmp1[j]));
        }
    }

    // analisis de la entrada
    vector<string> entrada_ = getData(reunion);
    calcularReunion(entrada_,data);

    return 0;
}
