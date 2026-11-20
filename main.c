#include <stdio.h>
#include <stdlib.h>

struct Contenedor {
    int id;
    float tara;
    float pesoCarga;
    float pesoTotal;
    float precio;
    struct Contenedor *anterior;
    struct Contenedor *siguiente;
};

struct Contenedor *inicio = NULL;
int contadorID = 1;

void insertar() {
    struct Contenedor *nuevo = (struct Contenedor*) malloc(sizeof(struct Contenedor));
    if (nuevo == NULL) {
        printf("Error: sin memoria.\n");
        return;
    }

    nuevo->id = contadorID++;
    printf("\n--- Nuevo Contenedor ID: %d ---\n", nuevo->id);
    printf("Peso vacio (Tara): ");
    scanf("%f", &nuevo->tara);
    printf("Peso de carga: ");
    scanf("%f", &nuevo->pesoCarga);
    printf("Precio / costo: ");
    scanf("%f", &nuevo->precio);

    nuevo->pesoTotal = nuevo->tara + nuevo->pesoCarga;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        struct Contenedor *aux = inicio;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = nuevo;
        nuevo->anterior = aux;
    }
    printf("Contenedor registrado. Peso Total: %.2f\n", nuevo->pesoTotal);
}

struct Contenedor* buscarPorID(int id) {
    struct Contenedor *aux = inicio;
    while (aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

void mostrarUno(struct Contenedor *c) {
    printf("\n--- Contenedor %d ---\n", c->id);
    printf("Tara: %.2f\n", c->tara);
    printf("Peso Carga: %.2f\n", c->pesoCarga);
    printf("Peso Total: %.2f\n", c->pesoTotal);
    printf("Precio: %.2f\n", c->precio);
}

void buscar() {
    int id;
    printf("Ingrese ID a buscar: ");
    scanf("%d", &id);
    struct Contenedor *encontrado = buscarPorID(id);
    if (encontrado == NULL) {
        printf("No se encontro el contenedor %d.\n", id);
    } else {
        mostrarUno(encontrado);
    }
}

void actualizar() {
    int id;
    printf("Ingrese ID a actualizar: ");
    scanf("%d", &id);
    struct Contenedor *c = buscarPorID(id);
    if (c == NULL) {
        printf("No se encontro el contenedor %d.\n", id);
        return;
    }
    printf("Nuevos datos para ID %d:\n", id);
    printf("Peso vacio (Tara): ");
    scanf("%f", &c->tara);
    printf("Peso de carga: ");
    scanf("%f", &c->pesoCarga);
    printf("Precio / costo: ");
    scanf("%f", &c->precio);
    c->pesoTotal = c->tara + c->pesoCarga;
    printf("Actualizado. Nuevo Peso Total: %.2f\n", c->pesoTotal);
}

void eliminar() {
    int id;
    printf("Ingrese ID a eliminar: ");
    scanf("%d", &id);
    struct Contenedor *c = buscarPorID(id);
    if (c == NULL) {
        printf("No se encontro el contenedor %d.\n", id);
        return;
    }
    if (c->anterior != NULL) {
        c->anterior->siguiente = c->siguiente;
    } else {
        inicio = c->siguiente;
    }
    if (c->siguiente != NULL) {
        c->siguiente->anterior = c->anterior;
    }
    free(c);
    printf("Contenedor %d eliminado.\n", id);
}

void mostrarAdelante() {
    struct Contenedor *aux = inicio;
    if (aux == NULL) { printf("Lista vacia.\n"); return; }
    printf("\n--- Recorrido Adelante ---\n");
    while (aux != NULL) {
        printf("ID: %d | Tara: %.2f | Carga: %.2f | Total: %.2f | Precio: %.2f\n",
               aux->id, aux->tara, aux->pesoCarga, aux->pesoTotal, aux->precio);
        aux = aux->siguiente;
    }
}

void mostrarAtras() {
    if (inicio == NULL) { printf("Lista vacia.\n"); return; }
    struct Contenedor *aux = inicio;
    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    printf("\n--- Recorrido Atras ---\n");
    while (aux != NULL) {
        printf("ID: %d | Tara: %.2f | Carga: %.2f | Total: %.2f | Precio: %.2f\n",
               aux->id, aux->tara, aux->pesoCarga, aux->pesoTotal, aux->precio);
        aux = aux->anterior;
    }
}

int main() {
    int opcion;
    do {
        printf("\n===== TERMINAL PORTUARIA =====\n");
        printf("1. Insertar contenedor\n");
        printf("2. Buscar contenedor\n");
        printf("3. Actualizar contenedor\n");
        printf("4. Eliminar contenedor\n");
        printf("5. Mostrar adelante\n");
        printf("6. Mostrar atras\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: insertar(); break;
            case 2: buscar(); break;
            case 3: actualizar(); break;
            case 4: eliminar(); break;
            case 5: mostrarAdelante(); break;
            case 6: mostrarAtras(); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 0);
    return 0;
}