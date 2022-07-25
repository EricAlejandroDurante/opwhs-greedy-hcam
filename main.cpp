#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include <sstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib> 
#include <string> 
#include <cstdio>
#include<fstream>

using namespace std;

//Creamos la estructura de atracciones
struct Nodos{
    float x;
    float y;
    float si;
};

//Creamos la estructura de hoteles
struct Hoteles{
    float x;
    float y;
    float si;
};

typedef struct Cercanos{
    int N;
    float distance;
    bool operator<(const Cercanos& a) const{
        return distance < a.distance;
    }
}Cercanos;

typedef struct Cercanos_hoteles{
    int N;
    float distance;
    float distance_trip;
    bool operator<(const Cercanos_hoteles& a) const{
        return distance < a.distance;
    }
}Cercanos_hoteles;

float euclidiane(float x, float y, float x0, float y0){
    return pow(pow(y0-y, 2) + pow(x0-x, 2) , 0.5);
}

vector<Cercanos> buscar_cercanos_desde_hotel(Nodos nodos[], int index, int N, Nodos Hotel[]){
    vector<Cercanos> mas_cercanos;
    for(int i=0; i<N-2; i++){
        Cercanos C;
        C.N = i;
        C.distance = euclidiane(nodos[i].x, nodos[i].y, Hotel[index].x, Hotel[index].y);
        mas_cercanos.push_back(C);
    }
    std::sort(mas_cercanos.begin(), mas_cercanos.end());
    return mas_cercanos;
}

vector<Cercanos> buscar_cercanos(Nodos nodos[], int index, int N){
    vector<Cercanos> mas_cercanos;
    for(int i=0; i<N-2; i++){
        if(index==i){
            continue;
        }else{
            Cercanos C;
            C.N = i;
            C.distance = euclidiane(nodos[i].x, nodos[i].y, nodos[index].x, nodos[index].y);
            mas_cercanos.push_back(C);
        }
    }
    std::sort(mas_cercanos.begin(), mas_cercanos.end());   
    return mas_cercanos;
}

vector<Cercanos_hoteles> buscar_hoteles(Nodos hoteles[], int index, int H){
    vector<Cercanos_hoteles> mas_cercanos;
    float distancia_trip;
    for(int i=0; i<H+1; i++){
        if(index==i){
            continue;
        }else{
            Cercanos_hoteles C;
            C.N = i;
            distancia_trip = euclidiane(hoteles[i].x, hoteles[i].y, hoteles[index].x, hoteles[index].y);
            C.distance_trip = distancia_trip;
            C.distance = distancia_trip + euclidiane(hoteles[i].x, hoteles[i].y, hoteles[H+1].x, hoteles[H+1].y);
            mas_cercanos.push_back(C);
        }
    }
    std::sort(mas_cercanos.begin(), mas_cercanos.end());   
    return mas_cercanos;
}

void mostrar_solucion(vector<vector<Nodos>> solucion_final){
    int score_final = 0;
    cout<<"Solucion final\n"<<endl;
    int i = 1;
    for(const auto &iteme : solucion_final){
        float probando = 0;
        cout<<"Trip "<<i<<": "<<"[";
        for(const auto &ite : iteme){
            cout<<"("<<ite.x<<", "<<ite.y<<"), ";
            probando += ite.si;
        }
        i++;
        cout<<"]"<<endl;
        //cout<<"Score: "<<probando<<endl;
        score_final += probando;
    }
    cout<<"Total: "<<score_final<<endl; 
}

int main(int argc, char** argv){
    //Ver tiempo de ejecucion
    unsigned t0, t1;
    t0=clock();

    //Solucion final
    vector<vector<Nodos>> solucion_final;

    int N,H,D;
    float x,y,si,total_tour;
    string linea;
    std::ifstream input(argv[1]);

    //Linea 1, Nodos + hoteles, Hoteles, Trips
    input>>N>>H>>D;
    //Tiempo de cada trip
    float tiempo_trips[D]; 
    getline(input, linea); //Linea 2 total de tours
    input>>total_tour;
    getline(input, linea); //Linea 3 salto en blanco(?
    getline(input, linea); //Linea de trips

    //Agregando los tiempos de cada trip en el arreglo trips
    stringstream stream(linea);
    int ni = 0;
    while(1){
        stream>>tiempo_trips[ni];
        if(!stream){
            break;
        }
        ni++;
    }

    //Agregamos la cantidad de hoteles al struct hoteles
    getline(input, linea);
    Nodos hoteles_s[H+2];
    for(int i=0; i<H+1; i++){
        input>>x>>y>>si;
        if(i==1){
            hoteles_s[H+1].x = x;
            hoteles_s[H+1].y = y;
            hoteles_s[H+1].si = 0;
            input>>x>>y>>si;
        }
        hoteles_s[i].x = x;
        hoteles_s[i].y = y;
        hoteles_s[i].si = 0;
    }

    //Agregamos las atracciones al struc nodos
    getline(input, linea);
    Nodos nodos[N-2];
    for(int i=0; i<N-2; i++){
        input>>x>>y>>si;
        nodos[i].x = x;
        nodos[i].y = y;
        nodos[i].si = si;
    }



    //Nodos visitados
    vector<int> nodos_visitados;
    //Hoteles ya visitados
    vector<int> hoteles_visitados;
    //Distancias de cada trip
    vector<float> distancias_del_trip;
    
    Nodos hoteles[D+1];
    int hotel_donde_estoy = 0;
    hoteles_visitados.push_back(0);
    hoteles[0] = hoteles_s[0];

    //Vamos a armar los hoteles de cada trip
    for(int i=0; i<D-1; i++){
        vector<Cercanos_hoteles> C = buscar_hoteles(hoteles_s, hotel_donde_estoy, H);
        for(const auto &item : C){
            if(std::find(hoteles_visitados.begin(), hoteles_visitados.end(), item.N) != hoteles_visitados.end()){
                continue;
            }
            if(item.distance_trip<=tiempo_trips[i]){
                hoteles[i+1] = hoteles_s[item.N];
                hotel_donde_estoy = item.N;
                hoteles_visitados.push_back(item.N);
                break;
            }
        }
        
    }
    hoteles[D] = hoteles_s[H+1];
    
    //Algortimo greedy
    for(int i=0; i<D;i++){
        vector<Nodos> trips;
        float distancia_trip = 0;
        float distancia_hotel_final = 0;
        int posicion_nodo_donde_estoy = 0;
        float ultima_distancia_aceptada = 0;
        float score_total = 0;
        Nodos nodo_donde_estoy;
        //Hago una lista de los mas cercanos
        vector<Cercanos> C = buscar_cercanos_desde_hotel(nodos, i, N, hoteles);
        //Recorro cada lista viendo al mas cercano
        for(const auto &item : C){
            if(std::find(nodos_visitados.begin(), nodos_visitados.end(), item.N) != nodos_visitados.end()){
                if(C.back().N==item.N){
                    break;
                }
                continue;
            }
            distancia_hotel_final = euclidiane(hoteles[i+1].x, hoteles[i+1].y, nodos[item.N].x, nodos[item.N].y);
            //Si cumple lo escojo altiro y guardo donde estoy
            distancia_trip = distancia_hotel_final + item.distance;
            if(distancia_trip<=tiempo_trips[i]){
                trips.push_back(hoteles[i]);
                trips.push_back(nodos[item.N]);
                nodos_visitados.push_back(item.N);
                nodo_donde_estoy = nodos[item.N];
                posicion_nodo_donde_estoy = item.N;
                score_total += nodos[item.N].si;
                break;                
            }else{
                distancia_trip = 0;
            }
            
        }
        if(distancia_trip==0){
            trips.push_back(hoteles[i]);
            trips.push_back(hoteles[i+1]);
            solucion_final.push_back(trips);
            distancia_trip = euclidiane(hoteles[i+1].x, hoteles[i+1].y, hoteles[i].x, hoteles[i].y);
            distancias_del_trip.push_back(distancia_trip);
            continue;
        }else{
            distancia_trip -= distancia_hotel_final;
        }

        //Voy a buscar los mas cercanos del nodo donde estoy
        bool state = true;
        while(state){
            vector<Cercanos> C = buscar_cercanos(nodos, posicion_nodo_donde_estoy, N);
            for(const auto &iteme : C){
                //Si la atraccion elegida existe va a la siguiente
                if(std::find(nodos_visitados.begin(), nodos_visitados.end(), iteme.N) != nodos_visitados.end()){
                    if(C.back().N==iteme.N){
                        distancia_trip += ultima_distancia_aceptada;
                        trips.push_back(hoteles[i+1]);
                        solucion_final.push_back(trips);
                        distancias_del_trip.push_back(distancia_trip);
                        state = false;
                    }
                    continue;
                }else{
                    distancia_trip += iteme.distance;
                    distancia_hotel_final = euclidiane(hoteles[i+1].x, hoteles[i+1].y, nodos[iteme.N].x, nodos[iteme.N].y);
                    distancia_trip += distancia_hotel_final;
                    
                    if(distancia_trip<=tiempo_trips[i]){
                        trips.push_back(nodos[iteme.N]);
                        nodos_visitados.push_back(iteme.N);
                        nodo_donde_estoy = nodos[iteme.N];
                        posicion_nodo_donde_estoy = iteme.N;
                        distancia_trip -= distancia_hotel_final;
                        ultima_distancia_aceptada = distancia_hotel_final;
                        score_total += nodos[iteme.N].si;
                        break;  
                    }else if(C.back().N==iteme.N){
                        distancia_trip -= distancia_hotel_final;
                        distancia_trip -= iteme.distance;
                        distancia_trip += ultima_distancia_aceptada;
                        trips.push_back(hoteles[i+1]);
                        solucion_final.push_back(trips);
                        distancias_del_trip.push_back(distancia_trip);
                        state = false;
                    }else{
                        distancia_trip -= distancia_hotel_final;
                        distancia_trip -= iteme.distance;
                        continue;

                    }
                }
                            
            }
        }


    }

    /**/
    //Hill climbing "normal"
    int posicion_del_trip = 0;
    int posicion_visitados = 0;
    std::stringstream ss(argv[2]);
    int cant_iteraciones;
    ss>>cant_iteraciones;
    bool pasar_a_la_siguiente_iteracion=false;

    for(auto &iteme : solucion_final){
        int iteraciones = cant_iteraciones;
        //Cuantas iteraciones queremos para cada solucion del trip
        while(iteraciones>0){

            //Recorreremos cada nodo para ver la solucion
            for(int j=0; j<N-2; j++){
                
                //Vemos si el nodo que elegimos esta en la solucion o no
                if(std::find(nodos_visitados.begin(), nodos_visitados.end(), j) != nodos_visitados.end()){
                    continue;
                }

                //Si no esta visitado, vemos si hace alguna mejora
                for(int i=1; i<iteme.size()-1;i++){

                    //"Sacamos" el nodo donde estamos del trip
                    float distancia_a_restar = euclidiane(iteme[i-1].x, iteme[i-1].y, iteme[i].x, iteme[i].y) + euclidiane(iteme[i].x, iteme[i].y, iteme[i+1].x, iteme[i+1].y);
                    float distancia_temporal_deltrip = distancias_del_trip[posicion_del_trip];
                    distancia_temporal_deltrip -= distancia_a_restar;

                    //Vemos si el nodo tiene mas score
                    if(nodos[j].si>iteme[i].si){
                        float distancia_a_sumar = euclidiane(iteme[i-1].x, iteme[i-1].y, nodos[j].x, nodos[j].y) + euclidiane(nodos[j].x, nodos[j].y, iteme[i+1].x, iteme[i+1].y);
                        distancia_temporal_deltrip += distancia_a_sumar;

                        //Si tiene menos del tiempo cumple todo y nos sirve por lo que elegimos y pasamos
                        //A la siguiente iteracion
                        if(distancia_temporal_deltrip<=tiempo_trips[posicion_del_trip]){
                            nodos_visitados[posicion_visitados+i-1] = j;
                            distancias_del_trip[posicion_del_trip] = distancia_temporal_deltrip;
                            iteme[i] = nodos[j];
                            distancias_del_trip[posicion_del_trip] -= distancia_a_restar;
                            distancias_del_trip[posicion_del_trip] += distancia_a_sumar;
                            pasar_a_la_siguiente_iteracion = true; 
                            break;
                        }
                    }
                }

                if(pasar_a_la_siguiente_iteracion){
                    pasar_a_la_siguiente_iteracion=false;
                    break;
                }
            }
            iteraciones--;
        }
        pasar_a_la_siguiente_iteracion=false;
        posicion_visitados += iteme.size()-2;

        posicion_del_trip++;
    }

    //mostrar solucion final
    mostrar_solucion(solucion_final);
    
    t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<<time<<endl;
    return 0;
}