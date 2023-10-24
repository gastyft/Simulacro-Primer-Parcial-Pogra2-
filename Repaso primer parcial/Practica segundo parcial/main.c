#include <stdio.h>
#include <stdlib.h>
#define color system("COLOR B")
#include <conio.h>
#include <string.h>
#define ESC 27

///STRUCTS

typedef struct
{
    int
    NroCliente;
    char
    NyA[30];
    int
    NroPedido;
    float MontoCompra;
} RegistroCompraCliente;

typedef struct
{
    int
    NroCliente;
    char
    NyA[30];
} Cliente;
typedef struct NodoPedido
{
    int
    NroPedido;
    Cliente cliente;
    float MontoCompra;
    struct NodoPedido * siguiente;
    struct NodoPedido *anterior;
} NodoPedido;

typedef struct Fila
{

    NodoPedido *primero;
    NodoPedido *ultimo;
} Fila;



///PROTOTIPADOS
NodoPedido *crearNodo(RegistroCompraCliente regis);
NodoPedido *inicLista();
NodoPedido *agregar_al_final(NodoPedido *lista,NodoPedido* nuevo);
NodoPedido *crearListaPedidos(char archivo[]);
void mostrarLista(NodoPedido *lista);
void liberarLista(NodoPedido **lista);
NodoPedido *ingresarPedido(NodoPedido *lista);
RegistroCompraCliente carga_un_registro( );
float calcularTotalMontoCompra(NodoPedido *lista);
RegistroCompraCliente *copiarPedidosMayores5000(NodoPedido *lista,int *cant);
void mostrarListaArre(RegistroCompraCliente *arre,int cant);
void inicFila(Fila *f);
void agregar_a_fila(Fila *f,NodoPedido *nuevo);
void armaFilaPedidos(Fila *f,char archivo[]);
void buscaPedido(Fila f,int dato);

int main()
{
    color;
    char archivo[]="Archivo binario.dat";
    //  NodoPedido *lista=inicLista();
    //   lista=crearListaPedidos(archivo);
    /// mostrarLista(lista);

    //  liberarLista(&lista);
    //  mostrarLista(lista);

    // lista=ingresarPedido(lista);
    // mostrarLista(lista);
    // printf(" \n El monto es  %.2f\n",calcularTotalMontoCompra(lista));
    // int cantidad=0;
    // RegistroCompraCliente *arregloo=NULL;
    // arregloo=copiarPedidosMayores5000(lista,&cantidad);
    // mostrarListaArre(arregloo,cantidad);
    Fila F;
    inicFila(&F);
    armaFilaPedidos(&F,archivo);

    // printf("Los Montos Mayores a 20000 son: ");
     mostrarLista(F.primero);
     system("pause");
    int dato=20799;
    printf("\n\n\n");
    buscaPedido(F,dato);

    return 0;
}


NodoPedido *inicLista()
{
    return NULL;
}

NodoPedido *crearNodo(RegistroCompraCliente regis)
{
    NodoPedido *nuevo =(NodoPedido*)malloc(sizeof(NodoPedido));
    nuevo->anterior=NULL;
    nuevo->siguiente=NULL;
    strcpy(nuevo->cliente.NyA,regis.NyA);
    nuevo->cliente.NroCliente=regis.NroCliente;
    nuevo->MontoCompra=regis.MontoCompra;
    nuevo->NroPedido=regis.NroPedido;
    return nuevo;
}

NodoPedido *agregar_al_final(NodoPedido *lista,NodoPedido* nuevo)
{
    NodoPedido *seg= lista;

    if(lista==NULL)
    {

        lista=nuevo;

    }
    else
    {
        while(seg->siguiente !=NULL)
        {

            seg=seg->siguiente;

        }
        seg->siguiente=nuevo;
        nuevo->anterior=seg;
    }

    return lista;
}

NodoPedido *crearListaPedidos(char archivo[])
{
    FILE *archi=fopen(archivo,"r+b");
    RegistroCompraCliente regis;
    NodoPedido*lista=inicLista();

    if(archi)
    {

        while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0)
        {
            lista=agregar_al_final(lista,crearNodo(regis));

        }
    }
    fclose(archi);
    return lista;
}

void mostrarLista(NodoPedido *lista)
{

    NodoPedido *seg=lista;
    if(seg)
    {
        printf(" \n NroCliente: %d \n",seg->cliente.NroCliente);
        printf("NyA %s \n",seg->cliente.NyA);
        printf("MontoCompra: %.2f \n",seg->MontoCompra);
        printf("NroPedido: %d",seg->NroPedido);

        mostrarLista(seg->siguiente);
    }
}

void liberarLista(NodoPedido **lista)
{

    NodoPedido *seg=*lista;
    NodoPedido *anterior=*lista;
    int i=0;
    if(lista)
    {

        while(seg)
        {
            anterior=seg;
            seg=seg->siguiente;
            free(anterior);
            i++;
            printf("BORRE %d vez \n",i);

        }
    }
    else
    {
        printf("No hay datos \n");

    }
    *lista=seg;
}


RegistroCompraCliente carga_un_registro()
{
    RegistroCompraCliente regis;
    printf("Ingrese nombre \n");
    fflush(stdin);
    gets(regis.NyA);
    printf("Ingrese NroCliente \n");
    scanf("%d",&regis.NroCliente);
    printf("Ingrese Montoto \n");
    scanf("%f",&regis.MontoCompra);
    printf("Ingrese NroPedido \n");
    scanf("%d",&regis.NroPedido);

    return regis;
}



NodoPedido *ingresarPedido(NodoPedido *lista)
{

    char o=0;


    while(o!=27)
    {



        lista=agregar_al_final(lista,crearNodo(carga_un_registro()));
        printf("PRESS ANY KEY TO CONTINUE OR ESC TO EXIT \n");
        fflush(stdin);
        o=getch();
    }
    return lista;
}


float calcularTotalMontoCompra(NodoPedido *lista)
{
    float total=0;
    NodoPedido *seg=lista;
    if(seg)
    {

        total=seg->MontoCompra+ calcularTotalMontoCompra(seg->siguiente);

    }


    return total;
}

RegistroCompraCliente  *copiarPedidosMayores5000(NodoPedido *lista,int *cant)
{
    int i=0;
    NodoPedido *seg=lista;
    while(seg!=NULL )
    {
        if((seg->MontoCompra)>5000)
        {
            i++;
        }
        seg=seg->siguiente;
    }
    RegistroCompraCliente *arre=(RegistroCompraCliente*)malloc(i*sizeof(RegistroCompraCliente));

    int j=0;
    seg=lista;
    while(seg!=NULL)
    {
        if(seg->MontoCompra>5000)
        {
            printf("Me rompi \n");
            arre[j].MontoCompra=seg->MontoCompra;
            arre[j].NroCliente=seg->cliente.NroCliente;
            strcpy(arre[j].NyA,seg->cliente.NyA);
            arre[j].NroPedido =seg->NroPedido;
            j++;
        }
        seg=seg->siguiente;
    }
    *cant= i;
    return arre;
}


void mostrarListaArre(RegistroCompraCliente *arre,int cant)
{
    int i=0;
    while(i<cant)
    {
        printf("Nombre : %s \n",arre[i].NyA);
        printf("NroCliente: %d \n",arre[i].NroCliente);
        printf("NroPedido: %d \n",arre[i].NroPedido);
        printf("Montoo: %f \n",arre[i].MontoCompra);
        i++;
    }
}


void inicFila(Fila *F)
{
    (*F).primero=NULL;
    (*F).ultimo=NULL;
}



void agregar_a_fila(Fila *f,NodoPedido *nuevo)
{
    if(!((*f).primero))
    {
        (*f).primero=nuevo;
        (*f).ultimo=nuevo;
    }
    else
    {
        (*f).ultimo->siguiente=nuevo;
        nuevo->anterior=(*f).ultimo;
        (*f).ultimo=nuevo;
    }
}
void armaFilaPedidos(Fila *f,char archivo[])
{
    FILE *archi= fopen(archivo,"r+b");
    RegistroCompraCliente regis;
    while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0)
    {
        if(regis.MontoCompra>20000)
        {
            agregar_a_fila(f, crearNodo(regis));
        }
    }
}

void buscaPedido(Fila f,int dato)
{

if((f.primero->NroPedido) == dato){
      printf("El NroPedido es %d",f.primero->NroPedido);
}
    else if((f.primero->NroPedido) != dato)
    {
        f.primero=f.primero->siguiente;

        buscaPedido((f),dato);
    }
}


