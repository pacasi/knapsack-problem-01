#include <iostream>   // cout, cin
#include <string>
#include <chrono>
#include <cassert>
#include "mochila.h"

#define REPS 100

extern uint32_t peso_limite, cant_pedidos;

/*
 * Lee una cantidad fija de entradas e imprime una columna con el tiempo que tardó cada algoritmo.
 * Donde "tiempo" es el promedio de 100 corridas de la misma entrada.
 * Se pueden agregar, sacar, modificar o ignorar columnas de acuerdo al experimento.
 */

int main(int argc, char** argv) {
  uint32_t cant_entradas;
  cin >> cant_entradas;
 
  cout << "n,W,fb,bt,mitm,pd" << endl;

  for (uint32_t j = 0; j < cant_entradas; ++j) {
    cin >> cant_pedidos >> peso_limite;

    uint32_t peso, beneficio;
    vector<pair<uint32_t, uint32_t>> pedidos(cant_pedidos);
    
    for (uint32_t i = 0; i < cant_pedidos; ++i) {
      cin >> peso >> beneficio;
      pedidos[i] = make_pair(peso, beneficio);
    }

    double tiempo_fb = 0.0, tiempo_bt = 0.0, tiempo_pd = 0.0, tiempo_mitm = 0.0;
    chrono::steady_clock::time_point tiempo_inicio, tiempo_fin;

    uint32_t max = fuerza_bruta(pedidos);
    assert(max == backtracking(pedidos));
    assert(max == programacion_dinamica(pedidos));
    assert(max == meet_in_the_middle(pedidos));

    for (uint32_t num_entrada = 0; num_entrada < REPS; ++num_entrada) {
      tiempo_inicio = chrono::steady_clock::now();
      fuerza_bruta(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_fb = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      backtracking(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_bt = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      programacion_dinamica(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_pd = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      tiempo_inicio = chrono::steady_clock::now();
      meet_in_the_middle(pedidos);
      tiempo_fin = chrono::steady_clock::now(); 
      tiempo_mitm = chrono::duration<double, milli>(tiempo_fin - tiempo_inicio).count();

      cout << cant_pedidos << "," << peso_limite << "," << tiempo_fb << ","
           << tiempo_bt << "," << tiempo_mitm << "," << tiempo_pd << endl;
    }

    // cout << j << "," << cant_pedidos << "," << peso_limite << "," << tiempo_fb/REPS << ","
    //      << tiempo_bt/REPS << "," << tiempo_mitm/REPS << "," << tiempo_pd/REPS << endl;
  }
  return 0;
}
