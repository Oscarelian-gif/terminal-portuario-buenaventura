#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pasajero{
    int documento;
    int tipoDoc;
    int estado;

    struct Pasajero *sig;
}Pasajero;

typedef enum{
    ROJO,
    NEGRO
}Color;

typedef struct Viaje{
    int codigoViaje;
    int capacidad;

    Color color;

    struct Viaje *izq;
    struct Viaje *der;
    struct Viaje *padre;
}Viaje;

typedef struct Destino{
    int codigo;
    char nombre[50];
    char empresa[50];

    Pasajero *frente;
    Pasajero *final;

    Viaje *raizViajes;

    struct Destino *sig;
}Destino;

typedef struct Embarcado{

    int documento;
    int tipoDoc;

    char destino[50];

    struct Embarcado *sig;

}Embarcado;

Destino *listaDestinos = NULL;
int totalEmbarcados = 0;
Embarcado *listaEmbarcados = NULL;
Destino* buscarDestino(int codigo){

    Destino *aux = listaDestinos;

    while(aux != NULL){

        if(aux->codigo == codigo){
            return aux;
        }

        aux = aux->sig;
    }

    return NULL;
}



void registrarDestino(){

    Destino *nuevo =
        (Destino*)malloc(sizeof(Destino));

    printf("Codigo destino: ");
    scanf("%d",&nuevo->codigo);

    if(buscarDestino(nuevo->codigo)!=NULL){
        printf("Ya existe ese destino\n");
        free(nuevo);
        return;
    }

    printf("Nombre destino: ");
    scanf(" %[^\n]",nuevo->nombre);

    printf("Empresa: ");
    scanf(" %[^\n]",nuevo->empresa);

    nuevo->frente = NULL;
    nuevo->final = NULL;
    nuevo->raizViajes = NULL;

    nuevo->sig = listaDestinos;
    listaDestinos = nuevo;

    printf("Destino registrado correctamente\n");
}

int pasajeroExiste(int documento){

    Destino *d = listaDestinos;

    while(d != NULL){

        Pasajero *p = d->frente;

        while(p != NULL){

            if(p->documento == documento){
                return 1;
            }

            p = p->sig;
        }

        d = d->sig;
    }

    return 0;
}

void registrarPasajero(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    Pasajero *nuevo =
        (Pasajero*)malloc(sizeof(Pasajero));

    printf("Documento: ");
    scanf("%d",&nuevo->documento);

    if(pasajeroExiste(nuevo->documento)){
        printf("ERROR: pasajero ya registrado\n");
        free(nuevo);
        return;
    }

    printf("Tipo documento\n");
    printf("1. Cedula\n");
    printf("2. Pasaporte\n");
    printf("3. Tarjeta Identidad\n");
    printf("Seleccione: ");
    scanf("%d",&nuevo->tipoDoc);

    if(nuevo->tipoDoc < 1 || nuevo->tipoDoc > 3){

        printf("Tipo documento invalido\n");
        free(nuevo);
        return;
    }

    nuevo->estado = 0;
    nuevo->sig = NULL;

    if(dest->frente == NULL){

        dest->frente = nuevo;
        dest->final = nuevo;
    }
    else{

        dest->final->sig = nuevo;
        dest->final = nuevo;
    }

    printf("Pasajero registrado correctamente\n");
}

void mostrarPasajerosDestino(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    if(dest->frente == NULL){
        printf("No hay pasajeros en espera\n");
        return;
    }

    Pasajero *aux = dest->frente;

    printf("\nPASAJEROS DE %s\n",dest->nombre);

    while(aux != NULL){

        printf("\nDocumento: %d",aux->documento);

        if(aux->tipoDoc == 1)
            printf("\nTipo: Cedula");

        if(aux->tipoDoc == 2)
            printf("\nTipo: Pasaporte");

        if(aux->tipoDoc == 3)
            printf("\nTipo: Tarjeta Identidad");

        printf("\nEstado: En espera\n");
        printf("--------------------\n");

        aux = aux->sig;
    }
}

int contarPasajeros(Destino *dest){

    int contador = 0;

    Pasajero *aux = dest->frente;

    while(aux != NULL){

        contador++;
        aux = aux->sig;
    }

    return contador;
}

void consultarCantidadPasajeros(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    printf("Pasajeros en espera: %d\n",
           contarPasajeros(dest));
}


void mostrarDestinos(){

    Destino *aux = listaDestinos;

    if(aux == NULL){
        printf("No hay destinos registrados\n");
        return;
    }

    while(aux != NULL){

        printf("\n----------------");
        printf("\nCodigo: %d",aux->codigo);
        printf("\nNombre: %s",aux->nombre);
        printf("\nEmpresa: %s",aux->empresa);

        aux = aux->sig;
    }

    printf("\n");
}

void registrarDestino();
void mostrarDestinos();
void registrarPasajero();
void mostrarPasajerosDestino();
void consultarCantidadPasajeros();
void consultarPrimerPasajero();

Viaje* buscarViaje(Viaje *raiz, int codigo);

void insertarRB(Viaje **raiz,
                int codigo,
                int capacidad);


void consultarPrimerPasajero(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    if(dest->frente == NULL){
        printf("La cola esta vacia\n");
        return;
    }

    printf("\nPRIMER PASAJERO");
    printf("\nDocumento: %d",
           dest->frente->documento);

    printf("\nTipo documento: %d",
           dest->frente->tipoDoc);

    printf("\n");
}


void embarcarPasajero(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    if(dest->frente == NULL){
        printf("No hay pasajeros en espera\n");
        return;
    }

    Pasajero *temp = dest->frente;

    printf("\nPasajero embarcado:");
    printf("\nDocumento: %d\n",
            temp->documento);

    dest->frente = dest->frente->sig;

    if(dest->frente == NULL){
        dest->final = NULL;
    }

    totalEmbarcados++;
Embarcado *nuevo =
(Embarcado*)malloc(sizeof(Embarcado));

nuevo->documento = temp->documento;
nuevo->tipoDoc = temp->tipoDoc;

strcpy(nuevo->destino,
       dest->nombre);

nuevo->sig = listaEmbarcados;
listaEmbarcados = nuevo;
    free(temp);
}



void verificarColaVacia(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    if(dest->frente == NULL){
        printf("La cola esta vacia\n");
    }
    else{
        printf("La cola tiene pasajeros\n");
    }
}

void buscarPasajeroDocumento(){

    int documento;

    printf("Documento a buscar: ");
    scanf("%d", &documento);

    Destino *d = listaDestinos;

    while(d != NULL){

        Pasajero *p = d->frente;

        while(p != NULL){

            if(p->documento == documento){

                printf("\nPASAJERO ENCONTRADO");
                printf("\nDocumento: %d", p->documento);
                printf("\nDestino: %s", d->nombre);

                if(p->tipoDoc == 1)
                    printf("\nTipo: Cedula");

                if(p->tipoDoc == 2)
                    printf("\nTipo: Pasaporte");

                if(p->tipoDoc == 3)
                    printf("\nTipo: Tarjeta Identidad");

                printf("\nEstado: En espera\n");

                return;
            }

            p = p->sig;
        }

        d = d->sig;
    }

    printf("Pasajero no encontrado\n");
}

Viaje* crearViaje(int codigo, int capacidad){

    Viaje *nuevo = (Viaje*)malloc(sizeof(Viaje));

    nuevo->codigoViaje = codigo;
    nuevo->capacidad = capacidad;

    nuevo->color = ROJO;

    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->padre = NULL;

    return nuevo;
}


Viaje* insertarBST(Viaje *raiz, Viaje *nuevo){

    if(raiz == NULL){
        return nuevo;
    }

    if(nuevo->codigoViaje < raiz->codigoViaje){

        raiz->izq =
            insertarBST(raiz->izq, nuevo);

        raiz->izq->padre = raiz;
    }
    else if(nuevo->codigoViaje > raiz->codigoViaje){

        raiz->der =
            insertarBST(raiz->der, nuevo);

        raiz->der->padre = raiz;
    }

    return raiz;
}


void registrarViaje(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){

        printf("Destino no encontrado\n");
        return;
    }

    int codigoViaje;
    int capacidad;

    printf("Codigo viaje: ");
    scanf("%d",&codigoViaje);
    if(buscarViaje(dest->raizViajes,
               codigoViaje) != NULL){

    printf("Ese codigo de viaje ya existe\n");
    return;
}

    printf("Capacidad: ");
    scanf("%d",&capacidad);

    insertarRB(
    &dest->raizViajes,
    codigoViaje,
    capacidad
);
}

void mostrarInorden(Viaje *raiz){

    if(raiz == NULL){
        return;
    }

    mostrarInorden(raiz->izq);

    printf("\nCodigo: %d",
       raiz->codigoViaje);

if(raiz->color == ROJO)
    printf(" (ROJO)");
else
    printf(" (NEGRO)");

    printf("\nCapacidad: %d\n",
           raiz->capacidad);

    mostrarInorden(raiz->der);
}


void mostrarViajesDestino(){

    int codigoDestino;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){

        printf("Destino no encontrado\n");
        return;
    }

    if(dest->raizViajes == NULL){

        printf("No hay viajes registrados\n");
        return;
    }

    printf("\nVIAJES DE %s\n",
           dest->nombre);

    mostrarInorden(dest->raizViajes);
}

Viaje* buscarViaje(Viaje *raiz, int codigo){

    if(raiz == NULL){
        return NULL;
    }

    if(codigo == raiz->codigoViaje){
        return raiz;
    }

    if(codigo < raiz->codigoViaje){
        return buscarViaje(raiz->izq, codigo);
    }

    return buscarViaje(raiz->der, codigo);
}


void buscarViajeDestino(){

    int codigoDestino;
    int codigoViaje;

    printf("Codigo destino: ");
    scanf("%d",&codigoDestino);

    Destino *dest = buscarDestino(codigoDestino);

    if(dest == NULL){
        printf("Destino no encontrado\n");
        return;
    }

    printf("Codigo viaje: ");
    scanf("%d",&codigoViaje);

    Viaje *encontrado =
        buscarViaje(dest->raizViajes,
                    codigoViaje);

    if(encontrado == NULL){

        printf("Viaje no encontrado\n");
    }
    else{

        printf("\nVIAJE ENCONTRADO");
        printf("\nCodigo: %d",
                encontrado->codigoViaje);

        printf("\nCapacidad: %d\n",
                encontrado->capacidad);
    }
}


void rotacionIzquierda(Viaje **raiz, Viaje *x){

    Viaje *y = x->der;

    x->der = y->izq;

    if(y->izq != NULL){
        y->izq->padre = x;
    }

    y->padre = x->padre;

    if(x->padre == NULL){
        *raiz = y;
    }
    else if(x == x->padre->izq){
        x->padre->izq = y;
    }
    else{
        x->padre->der = y;
    }

    y->izq = x;
    x->padre = y;
}


void rotacionDerecha(Viaje **raiz, Viaje *y){

    Viaje *x = y->izq;

    y->izq = x->der;

    if(x->der != NULL){
        x->der->padre = y;
    }

    x->padre = y->padre;

    if(y->padre == NULL){
        *raiz = x;
    }
    else if(y == y->padre->izq){
        y->padre->izq = x;
    }
    else{
        y->padre->der = x;
    }

    x->der = y;
    y->padre = x;
}


void fixInsert(Viaje **raiz, Viaje *nuevo){

    while(nuevo != *raiz &&
          nuevo->padre->color == ROJO){

        Viaje *padre = nuevo->padre;
        Viaje *abuelo = padre->padre;

        if(padre == abuelo->izq){

            Viaje *tio = abuelo->der;

            if(tio != NULL &&
               tio->color == ROJO){

                padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;

                nuevo = abuelo;
            }
            else{

                if(nuevo == padre->der){

                    nuevo = padre;
                    rotacionIzquierda(raiz, nuevo);

                    padre = nuevo->padre;
                    abuelo = padre->padre;
                }

                padre->color = NEGRO;
                abuelo->color = ROJO;

                rotacionDerecha(raiz, abuelo);
            }
        }
        else{

            Viaje *tio = abuelo->izq;

            if(tio != NULL &&
               tio->color == ROJO){

                padre->color = NEGRO;
                tio->color = NEGRO;
                abuelo->color = ROJO;

                nuevo = abuelo;
            }
            else{

                if(nuevo == padre->izq){

                    nuevo = padre;
                    rotacionDerecha(raiz, nuevo);

                    padre = nuevo->padre;
                    abuelo = padre->padre;
                }

                padre->color = NEGRO;
                abuelo->color = ROJO;

                rotacionIzquierda(raiz, abuelo);
            }
        }
    }

    (*raiz)->color = NEGRO;
}


void insertarRB(Viaje **raiz,
                int codigo,
                int capacidad){

    Viaje *nuevo =
        crearViaje(codigo, capacidad);

    *raiz = insertarBST(*raiz, nuevo);

    fixInsert(raiz, nuevo);
}


Viaje* buscarViaje(Viaje *raiz, int codigo);

void insertarRB(Viaje **raiz,
                int codigo,
                int capacidad);



void destinoMayorEspera(){

    Destino *d = listaDestinos;
    Destino *mayor = NULL;
    int max = -1;

    while(d != NULL){

        int cont = 0;
        Pasajero *p = d->frente;

        while(p != NULL){
            cont++;
            p = p->sig;
        }

        if(cont > max){
            max = cont;
            mayor = d;
        }

        d = d->sig;
    }

    if(mayor != NULL){
        printf("\nDestino con mas pasajeros:");
        printf("\nCodigo: %d", mayor->codigo);
        printf("\nNombre: %s", mayor->nombre);
        printf("\nPasajeros: %d\n", max);
    }
}


void destinoMenorEspera(){

    Destino *d = listaDestinos;
    Destino *menor = NULL;
    int min = 999999;

    while(d != NULL){

        int cont = 0;
        Pasajero *p = d->frente;

        while(p != NULL){
            cont++;
            p = p->sig;
        }

        if(cont < min){
            min = cont;
            menor = d;
        }

        d = d->sig;
    }

    if(menor != NULL){
        printf("\nDestino con menos pasajeros:");
        printf("\nCodigo: %d", menor->codigo);
        printf("\nNombre: %s", menor->nombre);
        printf("\nPasajeros: %d\n", min);
    }
}


void promedioPasajerosDestino(){

    int totalPasajeros = 0;
    int totalDestinos = 0;

    Destino *d = listaDestinos;

    while(d != NULL){

        totalDestinos++;

        Pasajero *p = d->frente;

        while(p != NULL){
            totalPasajeros++;
            p = p->sig;
        }

        d = d->sig;
    }

    if(totalDestinos == 0){
        printf("No hay destinos\n");
        return;
    }

    printf("\nPromedio: %.2f\n",
           (float)totalPasajeros / totalDestinos);
}

void consultarEstadoPasajero(){

    int documento;

    printf("Documento: ");
    scanf("%d",&documento);

    Destino *d = listaDestinos;

    while(d != NULL){

        Pasajero *p = d->frente;

        while(p != NULL){

            if(p->documento == documento){

                printf("\nEN ESPERA");
                printf("\nDestino: %s\n",
                       d->nombre);

                return;
            }

            p = p->sig;
        }

        d = d->sig;
    }

    Embarcado *e = listaEmbarcados;

    while(e != NULL){

        if(e->documento == documento){

            printf("\nEMBARCADO");
            printf("\nDestino: %s\n",
                   e->destino);

            return;
        }

        e = e->sig;
    }

    printf("Pasajero no encontrado\n");
}

int main(){

    int opcion;

    do{

        printf("\n\n=== TERMINAL PORTUARIO ===");
        printf("\n1. Registrar destino");
        printf("\n2. Mostrar destinos");
        printf("\n3. Registrar pasajero");
        printf("\n4. Mostrar pasajeros destino");
        printf("\n5. Cantidad pasajeros");
        printf("\n6. Consultar primer pasajero");
        printf("\n7. Embarcar pasajero");
        printf("\n8. Verificar cola vacia");
        printf("\n9. Buscar pasajero por documento");
        printf("\n10. Registrar viaje");
        printf("\n11. Buscar viajes");
        printf("\n12. Mostrar viajes");
         printf("\n13. Consulta de pasajeros");
        printf("\n15. Destino con mayor espera");
        printf("\n16. Destino con menor espera");
        printf("\n17. Promedio pasajeros por destino");
        printf("\n0. Salir");
        printf("\nOpcion: ");
        scanf("%d",&opcion);

        switch(opcion){

            case 1:
                registrarDestino();
                break;

            case 2:
                mostrarDestinos();
                break;

            case 3:
                registrarPasajero();
                break;

            case 4:
                mostrarPasajerosDestino();

            case 5:
                 consultarCantidadPasajeros();
                 break;   
                 
            case 6:
                 consultarPrimerPasajero();
                 break;
            case 7:
                 embarcarPasajero();
                 break;

            case 8:
                 verificarColaVacia();
                 break;

                 case 9:
                 buscarPasajeroDocumento();
                 break;

                 case 10:
                 registrarViaje();
                 break;

                 case 11:
                mostrarViajesDestino();
                 break;

                 case 12:
                mostrarViajesDestino();
                 break;

                 case 13:
    consultarEstadoPasajero();
    break;
                 case 15:
    destinoMayorEspera();
    break;

case 16:
    destinoMenorEspera();
    break;

case 17:
    promedioPasajerosDestino();
    break;


            case 0:
                printf("Fin del programa\n");
                break;

            default:
                printf("Opcion invalida\n");
        }

    }while(opcion != 0);

    return 0;
}

