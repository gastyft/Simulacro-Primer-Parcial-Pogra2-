#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct
{
    int edad;
    char nombre[30];
}persona;

typedef struct nodoD
{
    persona pers;
    struct nodoD * siguiente;
    struct nodoD * anterior;
}nodoD;

typedef struct
{
    struct nodoD *pri;
    struct nodoD *fin;

}Fila;

nodoD * iniclista ();
nodoD * crearnodoD (persona perso);
nodoD *agregaralprincipio (nodoD *lista,nodoD * nuevo);
nodoD *agregaralfinal (nodoD * lista,nodoD *nuevo);
nodoD *buscarnodo(nodoD *lista);
nodoD *cargarnodos (nodoD * lista);
void mostrarrecusivo (nodoD *lista);
nodoD* borrarnodosd(nodoD *lista,char nombre[30]);
void inicfila (Fila *f);
void agregarfila(Fila *f);

int main()
{
      nodoD * lista = iniclista();
      lista=cargarnodos(lista);

      lista=borrarnodosd(lista,"gasty");
      mostrarrecusivo(lista);


    return 0;
}

nodoD * iniclista ()
{
    return NULL;
}

nodoD * crearnodoD (persona perso)
{
    nodoD *aux=(nodoD *)malloc(sizeof(nodoD));
    aux->pers=perso;
    aux->anterior=NULL;
    aux->siguiente=NULL;
    return aux;
}

nodoD *agregaralprincipio (nodoD *lista,nodoD * nuevo)
{
    nuevo->siguiente=lista;
    if(lista!=NULL)
    {
    lista->anterior=nuevo;
    }
    return nuevo;
}

nodoD* agregaralfinal(nodoD *lista,nodoD *nuevo)
{
    if(lista==NULL)
    {
        lista=nuevo;
    }
    else
    {
    nodoD *seg=buscarnodo(lista);
    seg->siguiente=nuevo;
    nuevo->anterior=seg;

    }
    return lista;
}

nodoD * buscarnodo(nodoD *lista)
{
    nodoD *seg=lista;
    if(seg!=NULL)
    {
        while(seg->siguiente!=NULL)
        {
            seg=seg->siguiente;
        }
    }
    return seg;
}

nodoD *cargarnodos (nodoD * lista)
{
    persona person;
    char opc=0;
    while(opc!=27)
    {
        printf("INGRESE EL NOMBRE DE LA PERSONA \n");
        fflush(stdin);
        gets(person.nombre);
        printf("INGRESE LA EDAD DE LA PERSONA\n");
        scanf("%d",&person.edad);
        lista=agregaralprincipio(lista,crearnodoD(person));
        fflush(stdin);
        opc=getch();
    }
    return lista;
}

void mostrarrecusivo (nodoD *lista)
{
    nodoD *seg=lista;
    if(seg!=NULL)
    {
        printf("NOMBRE : %s",seg->pers.nombre);
        printf("EDAD : %d\n\n",seg->pers.edad);
        mostrarrecusivo(seg->siguiente);
    }
}

nodoD* borrarnodosd(nodoD *lista, char nombre[30]) {
    nodoD *seg = lista;

    // Busca el nodo a borrar
    while (seg != NULL && strcmp(seg->pers.nombre, nombre) != 0) {
        seg = seg->siguiente;
    }

    if (seg != NULL) {
        // Verifica si el nodo a borrar es el primero
        if (seg == lista) {
            lista = lista->siguiente;
            if (lista) {
                lista->anterior = NULL;
            }
        } else {
            // En caso contrario, ajusta los punteros para saltar el nodo a borrar
            seg->anterior->siguiente = seg->siguiente;
            if (seg->siguiente) {
                seg->siguiente->anterior = seg->anterior;
            }
        }

        free(seg); // Libera la memoria del nodo borrado
    }

    return lista;
}
