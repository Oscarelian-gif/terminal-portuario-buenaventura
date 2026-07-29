#ifndef DESTINOS_H
#define DESTINOS_H

typedef struct Destino Destino;

void registrarDestino();
Destino* buscarDestino(int codigo);
void mostrarDestinos();
void modificarDestino();

#endif