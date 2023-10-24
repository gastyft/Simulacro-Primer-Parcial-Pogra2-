#include <stdio.h>
#include <stdlib.h>
#define color system("COLOR B")
#include <string.h>
#include <conio.h>
#define ESC 27

///STRUCT
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

typedef struct _NodoPedido
{
    int
    NroPedido;
    Cliente cliente;
    float MontoCompra;
    struct _NodoPedido * siguiente;
} NodoPedido;

/// PROTOTIPADO
NodoPedido *agregarNodoPedido(NodoPedido *lista, NodoPedido *nuevo);
NodoPedido *crearNodoPedido(RegistroCompraCliente registro);
NodoPedido *iniclist();
NodoPedido *crearListaPedidos(char Archivo[], RegistroCompraCliente regis, NodoPedido *lista);
void mostrarLista(NodoPedido *lista);
void liberarLista(NodoPedido **listaa);
RegistroCompraCliente nuevoCliente();
NodoPedido *ingresarPedido(NodoPedido *lista );
float calcularMontoTotal(NodoPedido* lista  );

int main()
{
    color;

    char Archivo[]="Archivo binario.dat";
    FILE *archi= fopen( Archivo,"a+b");
    RegistroCompraCliente registroCliente;
    NodoPedido *lista=iniclist();

    if(archi)
    {
        lista= crearListaPedidos(Archivo,registroCliente,lista);
        NodoPedido **listaDoble= &lista;
        mostrarLista(lista);
        printf("\n El monto es %.2f\n",calcularMontoTotal(lista ));
        system("pause");
        liberarLista(*&listaDoble);
        mostrarLista(*listaDoble);
        lista= ingresarPedido(lista);
        mostrarLista(lista);
        printf(" \n El monto es %.2f \n",calcularMontoTotal(lista ));
    }
    else
    {
        printf("ERROR AL ABRIR EL ARCHIVO \n");
    }

    fclose(archi);

    return 0;
}

NodoPedido *iniclist()
{

    return NULL;
}




NodoPedido *crearNodoPedido(RegistroCompraCliente registro)
{

    NodoPedido *nuevo =(NodoPedido*)malloc(sizeof(NodoPedido));

    nuevo->siguiente=NULL;
    nuevo->cliente.NroCliente=registro.NroCliente;
    strcpy(nuevo->cliente.NyA,registro.NyA);
    nuevo->MontoCompra=registro.MontoCompra;
    nuevo->NroPedido=registro.NroPedido;

    return nuevo;
}

NodoPedido *agregarNodoPedido(NodoPedido *lista, NodoPedido *nuevo)
{



    if(lista==NULL)
    {

        lista=nuevo;
    }
    else
    {

        nuevo->siguiente =lista;
        lista=nuevo;

    }

    return lista;
}

NodoPedido *crearListaPedidos(char Archivo[],RegistroCompraCliente regis, NodoPedido *lista)
{

    FILE *archi =fopen( Archivo,"r+b");
    if(archi)
    {
        while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0)
        {
            lista=agregarNodoPedido(lista,crearNodoPedido(regis));
        }
    }
    else
    {
        printf("ERROR EN EL ARCHIVO DESDE FUNCION CREAR LISTA PEDIDOS \n");
    }
    fclose(archi);
    return lista;
}

void mostrarLista(NodoPedido *lista)
{
    NodoPedido *seg=lista;

    if(seg)
    {



        printf(" \n Nombre y apellido:%s \n",seg->cliente.NyA);
        printf(" Nro Cliente: %d \n",seg->cliente.NroCliente);
        printf("Nro de pedido: %d \n",seg->NroPedido);
        printf("Monto de compra: %.2f",seg->MontoCompra);
        mostrarLista(seg->siguiente);
    }



}



void liberarLista(NodoPedido  **listaa)
{


    NodoPedido *ante=*listaa;

    NodoPedido *seg=*listaa;
    while( seg!=NULL)
    {
        ante= seg;

        seg= seg->siguiente;
        free(ante);

    }

    *listaa=seg;
}


RegistroCompraCliente nuevoCliente()
{

    RegistroCompraCliente regis;

    printf(" \nIngrese nombre y Apellido \n");
    fflush(stdin);
    gets(regis.NyA);
    printf("Ingrese Nro cliente \n");
    scanf("%d",&regis.NroCliente);
    printf("Ingrese Monto \n");
    scanf("%f",&regis.MontoCompra);
    printf("Ingrese numero de pedido \n");
    scanf("%d",&regis.NroPedido);

    return regis;
}

NodoPedido *ingresarPedido(NodoPedido *lista )
{

    char o=0;
    while(o!=27)
    {
        lista=agregarNodoPedido(lista,crearNodoPedido(nuevoCliente()));
        printf("Presione ESC para finalizar \n");
        fflush(stdin);
        o=getch();
    }
    return lista;
}


float calcularMontoTotal(NodoPedido* lista)
{
    float total=0;

    NodoPedido *seg = lista;
    if(seg)
    {
        total = seg->MontoCompra + calcularMontoTotal(seg->siguiente);
    }
    return total;
}





