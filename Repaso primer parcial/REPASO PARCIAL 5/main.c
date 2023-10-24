#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define ESC 27
#define color system("COLOR B")


///ESTRUCTURAS
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
} NodoPedido;

typedef struct NodoPedidoD
{
    int NroPedido;
    Cliente cliente;
    float MontoCompra;
    struct NodoPedidoD * siguiente;
    struct NodoPedidoD *anterior;
} NodoPedidoD;
/// ESTRUCTURAS SECUNDARIAS
typedef struct
{

    NodoPedidoD * primero;
    NodoPedidoD  *ultimo;
} Fila;



///PROTOTIPADO
NodoPedido *inicLista();
NodoPedido *crearNodoPedido(RegistroCompraCliente regis);
NodoPedido *crearListaPedidos(char archivo[]);
void muestra_1_lista(NodoPedido *lista);
void mostrarLista(NodoPedido *lista);
void liberarLista(NodoPedido **lista);
NodoPedido *ingresarPedido(NodoPedido *lista);
float calcularTotalMontoCompra(NodoPedido *lista);
RegistroCompraCliente *copiarPedidosMayores5000(NodoPedido *lista,int *cant);
void mostrarPedidos(RegistroCompraCliente *a,int cant);
NodoPedidoD *crearNodoPedidoDoble(RegistroCompraCliente regis);
void inicFila(Fila *f);
void agregar_a_fila(Fila *f,RegistroCompraCliente regis);
void armaFilaPedidos(Fila *f,char archivo[]);
void muestra_1_fila(Fila f);
void buscaPedido(Fila f,int dato);
void mostrarFila(Fila f);




int main()
{
    color;
    NodoPedido *lista=inicLista();
    char archivo[]="Archivo binario.dat";
    lista=crearListaPedidos(archivo);
    mostrarLista(lista);
    liberarLista(&lista);
    mostrarLista(lista);
    lista=ingresarPedido(lista);
    printf("El monto total de las compras es %.2f\n",calcularTotalMontoCompra(lista));
    int cant=0;
    RegistroCompraCliente *a=NULL;
    a=copiarPedidosMayores5000(lista,&cant);
    mostrarPedidos(a,cant);
    Fila f;
    inicFila(&f);
        armaFilaPedidos(&f,archivo);
        buscaPedido(f,20799);
system("pause");
system("cls");
mostrarFila(f);
    return 0;
}


///FUNCIONES QUE DEBERiAN FUNCIONAR

NodoPedido *inicLista()
{

    return NULL;
}

NodoPedido *crearNodoPedido(RegistroCompraCliente regis)
{
    NodoPedido *nuevo=(NodoPedido*)malloc(sizeof(NodoPedido));
    strcpy(nuevo->cliente.NyA,regis.NyA);
    nuevo->cliente.NroCliente=regis.NroCliente;
    nuevo->MontoCompra=regis.MontoCompra;
    nuevo->NroPedido=regis.NroPedido;
    nuevo->siguiente=NULL;
    return nuevo;

}


NodoPedido *agregarNodoPedido(NodoPedido *lista, RegistroCompraCliente regis)
{

    NodoPedido *seg=lista;

    NodoPedido *nuevo=crearNodoPedido(regis);
    if(!seg)
        lista=nuevo;

    else
    {
        while(seg->siguiente)
        {

            seg=seg->siguiente;

        }

        seg->siguiente=nuevo;
    }



    return lista;
}


NodoPedido *crearListaPedidos(char archivo[])
{

    FILE *archi=fopen(archivo,"r+b");
    RegistroCompraCliente regis;
    NodoPedido *lista=inicLista();
    if(archi)
    {

        while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0)
        {

            lista= agregarNodoPedido(lista,regis);

        }


    }
    else
        printf("ERROR EN EL ARCHIVO \n");
fclose(archi);
    return lista;
}

void muestra_1_lista(NodoPedido *lista)
{
    printf("Nombre y apellido %s \n",lista->cliente.NyA);
    printf("Nro Cliente %d\n",lista->cliente.NroCliente);
    printf("Nro Pedido %d \n",lista->NroPedido);
    printf("Monto de la compra %.2f \n",lista->MontoCompra);

}

void mostrarLista(NodoPedido *lista)
{

    if(lista)
    {
        muestra_1_lista(lista);

        mostrarLista(lista->siguiente);
    }
}


void liberarLista(NodoPedido **lista)
{

    NodoPedido *seg=*lista;
    NodoPedido *ante=inicLista();

    if(seg)
    {
        while(seg)
        {
            ante=seg;
            seg=seg->siguiente;
            free(ante);
        }
    }
    else
        printf("La lista no tiene datos");

    *lista=seg;
}

RegistroCompraCliente carga_1_registro()
{
    RegistroCompraCliente regis;
    printf("Ingrese Nombre y Apellido \n");
    fflush(stdin);
    gets(regis.NyA);
    printf("Ingrese Nro Cliente \n \b");
    scanf("%d",&regis.NroCliente);
    printf("Ingrese Nro Pedido \n ");
    scanf("%d",&regis.NroPedido);
    printf("Ingrese Monto de la compra \n");
    scanf("%f",&regis.MontoCompra);
    return regis;

}

NodoPedido *ingresarPedido(NodoPedido *lista)
{

    char o=0;

    while(o!=27)
    {
        lista= agregarNodoPedido(lista,carga_1_registro());
        printf("PRESS ANY KEY TO CONTINUE OR ESC TO FINISH \n");
        fflush(stdin);
        o=getch();
    }
    return lista;
}

float calcularTotalMontoCompra(NodoPedido *lista)
{
    float total=0;

    if(lista)
        total=lista->MontoCompra+calcularTotalMontoCompra(lista->siguiente);


    return total;
}

RegistroCompraCliente *copiarPedidosMayores5000(NodoPedido *lista,int *cant)
{
    NodoPedido *seg=lista;
    int i=0;
    while(seg)
    {
        if(seg->MontoCompra>5000)
            i++;
        seg=seg->siguiente;
    }
    *cant=i;
    RegistroCompraCliente *a=(RegistroCompraCliente*)malloc(i*sizeof(RegistroCompraCliente));

    int j=0;
    seg=lista;
    while(seg)
    {
        if(seg->MontoCompra>5000)
        {
            strcpy(a[j].NyA,seg->cliente.NyA);
            a[j].NroPedido=seg->NroPedido;
            a[j].NroCliente=seg->cliente.NroCliente;
            a[j].MontoCompra=seg->MontoCompra;
            j++;
        }
        seg=seg->siguiente;
    }
    return a;
}

void mostrarPedidos(RegistroCompraCliente *a,int cant)
{

    int i=0;
    while(i<cant)
    {
        printf("Nombre y apellido %s \n",a[i].NyA);
        printf("Nro Cliente %d\n",a[i].NroCliente);
        printf("Nro Pedido %d \n",a[i].NroPedido);
        printf("Monto de la compra %.2f",a[i].MontoCompra);
        i++;
    }
}

///FILAS

void inicFila(Fila *f)
{
    (*f).primero=NULL;
    (*f).ultimo=NULL;
}
NodoPedidoD *crearNodoPedidoDoble(RegistroCompraCliente regis)
{
    NodoPedidoD *nuevo=(NodoPedidoD*)malloc(sizeof(NodoPedidoD));
    strcpy(nuevo->cliente.NyA,regis.NyA);
    nuevo->cliente.NroCliente=regis.NroCliente;
    nuevo->MontoCompra=regis.MontoCompra;
    nuevo->NroPedido=regis.NroPedido;
    nuevo->siguiente=NULL;
    nuevo->anterior =NULL;
    return nuevo;
}
void agregar_a_fila(Fila *f,RegistroCompraCliente regis)
{

    NodoPedidoD *nuevo=crearNodoPedidoDoble(regis);
    if((*f).primero == NULL)
    {
        (*f).primero =nuevo;
        (*f).ultimo=nuevo;

    }
    else
    {
        (*f).ultimo->siguiente=nuevo;
        nuevo->anterior=(*f).ultimo;
        (*f).ultimo =nuevo;

    }

}

void armaFilaPedidos(Fila *f,char archivo[]){
RegistroCompraCliente regis;
FILE *archi=fopen(archivo,"r+b");


if(archi){
    while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0){
            if(regis.MontoCompra >20000)
               agregar_a_fila(f,regis);
    }
}
else
    printf("ERROR EN EL ARCHIVO \n");
    fclose(archi);
}

void muestra_1_fila(Fila f){
 printf("Nombre y apellido %s \n",f.primero->cliente.NyA);
        printf("Nro Cliente %d\n",f.primero->cliente.NroCliente);
        printf("Nro Pedido %d \n",f.primero->NroPedido);
        printf("Monto de la compra %.2f",f.primero->MontoCompra);
}



void buscaPedido(Fila f,int dato){

if(f.primero->NroPedido !=dato){
f.primero=f.primero->siguiente;
    buscaPedido(f,dato);
}
else
    muestra_1_fila(f);
}


void mostrarFila(Fila f){

if(f.primero)
{
    muestra_1_fila(f);
    f.primero=f.primero->siguiente;
    mostrarFila(f);
}

}
