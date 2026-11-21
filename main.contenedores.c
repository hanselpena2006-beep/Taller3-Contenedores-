#include <stdio.h>
#include <stdlib.h>

typedef struct Contenedor {
    int id;
    float tara;
    float pesoCarga;
    float pesoTotal;
    float costo;

    struct Contenedor *anterior;
    struct Contenedor *siguiente;

} Contenedor;

Contenedor *inicio = NULL;
Contenedor *fin = NULL;

int siguienteID = 1;

void insertarContenedor();
Contenedor *buscarContenedor(int id);
void actualizarContenedor();
void eliminarContenedor();
void mostrarAdelante();
void mostrarAtras();
void liberarMemoria();

void insertarContenedor() {

    Contenedor *nuevo;

    nuevo = (Contenedor *) malloc(sizeof(Contenedor));

    if (nuevo == NULL) {
        printf("Error al reservar memoria.\n");
        return;
    }

    nuevo->id = siguienteID++;

    printf("\n--- REGISTRAR CONTENEDOR ---\n");

    printf("Ingrese el peso vacio (tara): ");
    scanf("%f", &nuevo->tara);

    printf("Ingrese el peso de carga: ");
    scanf("%f", &nuevo->pesoCarga);

    printf("Ingrese el costo: ");
    scanf("%f", &nuevo->costo);

    nuevo->pesoTotal = nuevo->tara + nuevo->pesoCarga;

    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    if (inicio == NULL) {

        inicio = nuevo;
        fin = nuevo;

    } else {

        fin->siguiente = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;

    }

    printf("\nContenedor registrado correctamente.\n");
    printf("ID asignado: %d\n", nuevo->id);
}

Contenedor *buscarContenedor(int id) {

    Contenedor *actual = inicio;

    while (actual != NULL) {

        if (actual->id == id) {
            return actual;
        }

        actual = actual->siguiente;
    }

    return NULL;
}

void actualizarContenedor() {

    int id;

    printf("\nIngrese el ID del contenedor: ");
    scanf("%d", &id);

    Contenedor *actual = buscarContenedor(id);

    if (actual == NULL) {

        printf("Contenedor no encontrado.\n");

    } else {

        printf("\nIngrese la nueva tara: ");
        scanf("%f", &actual->tara);

        printf("Ingrese el nuevo peso de carga: ");
        scanf("%f", &actual->pesoCarga);

        printf("Ingrese el nuevo costo: ");
        scanf("%f", &actual->costo);

        actual->pesoTotal =
            actual->tara + actual->pesoCarga;

        printf("\nContenedor actualizado correctamente.\n");
    }
}

void eliminarContenedor() {

    int id;

    printf("\nIngrese el ID del contenedor a eliminar: ");
    scanf("%d", &id);

    Contenedor *actual = buscarContenedor(id);

    if (actual == NULL) {

        printf("Contenedor no encontrado.\n");
        return;
    }

    if (actual == inicio) {
        inicio = actual->siguiente;
    } else {
        actual->anterior->siguiente = actual->siguiente;
    }

    if (actual == fin) {
        fin = actual->anterior;
    } else {
        actual->siguiente->anterior = actual->anterior;
    }

    free(actual);

    printf("Contenedor eliminado correctamente.\n");
}

void mostrarAdelante() {

    Contenedor *actual = inicio;

    if (inicio == NULL) {
        printf("\nNo hay contenedores registrados.\n");
        return;
    }

    printf("\n--- CONTENEDORES HACIA ADELANTE ---\n");

    while (actual != NULL) {

        printf("\nID: %d\n", actual->id);
        printf("Tara: %.2f\n", actual->tara);
        printf("Peso de carga: %.2f\n", actual->pesoCarga);
        printf("Peso total: %.2f\n", actual->pesoTotal);
        printf("Costo: %.2f\n", actual->costo);

        actual = actual->siguiente;
    }
}

void mostrarAtras() {

    Contenedor *actual = fin;

    if (fin == NULL) {
        printf("\nNo hay contenedores registrados.\n");
        return;
    }

    printf("\n--- CONTENEDORES HACIA ATRAS ---\n");

    while (actual != NULL) {

        printf("\nID: %d\n", actual->id);
        printf("Tara: %.2f\n", actual->tara);
        printf("Peso de carga: %.2f\n", actual->pesoCarga);
        printf("Peso total: %.2f\n", actual->pesoTotal);
        printf("Costo: %.2f\n", actual->costo);

        actual = actual->anterior;
    }
}

void liberarMemoria() {

    Contenedor *actual = inicio;

    while (actual != NULL) {

        Contenedor *temporal = actual;

        actual = actual->siguiente;

        free(temporal);
    }

    inicio = NULL;
    fin = NULL;
}

int main() {

    int opcion;

    do {

        printf("\n===== SISTEMA DE CONTENEDORES =====\n");
        printf("1. Registrar contenedor\n");
        printf("2. Buscar contenedor\n");
        printf("3. Actualizar contenedor\n");
        printf("4. Eliminar contenedor\n");
        printf("5. Mostrar hacia adelante\n");
        printf("6. Mostrar hacia atras\n");
        printf("7. Salir\n");

        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                insertarContenedor();
                break;

            case 2: {
                int id;

                printf("Ingrese el ID: ");
                scanf("%d", &id);

                Contenedor *resultado =
                    buscarContenedor(id);

                if (resultado != NULL) {

                    printf("\nContenedor encontrado.\n");
                    printf("ID: %d\n", resultado->id);
                    printf("Tara: %.2f\n", resultado->tara);
                    printf("Peso de carga: %.2f\n",
                           resultado->pesoCarga);
                    printf("Peso total: %.2f\n",
                           resultado->pesoTotal);
                    printf("Costo: %.2f\n",
                           resultado->costo);

                } else {

                    printf("Contenedor no encontrado.\n");
                }

                break;
            }

            case 3:
                actualizarContenedor();
                break;

            case 4:
                eliminarContenedor();
                break;

            case 5:
                mostrarAdelante();
                break;

            case 6:
                mostrarAtras();
                break;

            case 7:
                liberarMemoria();
                printf("\nMemoria liberada.\n");
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 7);

    return 0;
}