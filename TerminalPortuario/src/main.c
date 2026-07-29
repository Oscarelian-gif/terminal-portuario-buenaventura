#include <stdio.h>
#include "../include/destino.h"
#include "../include/pasajero.h"
#include "../include/viajes.h"

int main() {

    int opcion;

    do {

        printf("\n1. Registrar destino");
        printf("\n2. Registrar pasajero");
        printf("\n3. Mostrar pasajeros por destino");
        printf("\n4. Registrar viaje");
        printf("\n5. Buscar viaje");
        printf("\n6. Mostrar viajes");
        printf("\n7. Embarcar pasajero");
        printf("\n0. Salir");

        printf("\nOpcion: ");
        scanf("%d", &opcion);

        switch(opcion) {

            case 1:
                registrarDestino();
                break;

            case 2:
                registrarPasajero();
                break;

            case 3:
                mostrarPasajerosDestino();
                break;

            case 4:
                registrarViaje();
                break;

            case 5:
                buscarViajeDestino();
                break;

            case 6:
                mostrarViajesDestino();
                break;

            case 7:
                embarcarPasajero();
                break;
        }

    } while(opcion != 0);

    return 0;
}