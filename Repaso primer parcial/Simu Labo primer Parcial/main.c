#include <stdio.h>
#include <stdlib.h>
#define color system("COLOR B")
#include <conio.h>
#include<string.h>
#define ESC 27


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


///PROTOTIPADO
NodoPedido*iniclista();
NodoPedido* crearNodo(RegistroCompraCliente regis);
NodoPedido *agregarAlFinal(NodoPedido *lista, NodoPedido *nuevo);
NodoPedido *crearListaPedidos(NodoPedido *lista, char Archivo[]);
void mostrarLista(NodoPedido *lista);
void liberarLista (NodoPedido **lista);
RegistroCompraCliente cargar_registro();
NodoPedido* insertarPedido(NodoPedido *lista);
float calcularMontoCompraTotal(NodoPedido *lista);
RegistroCompraCliente * cargaMayoresA5000(int *cant, NodoPedido *lista);
void mostrarPedidos5000(RegistroCompraCliente *arreglo,int cant);



int main()
{
    color;
    char Archivo[]="Archivo binario.dat";
    FILE *archi=fopen(Archivo,"r+b");
        NodoPedido *lista=iniclista();

    if(archi)
    {
        crearListaPedidos(lista,Archivo);
        lista = crearListaPedidos(lista,Archivo);

        mostrarLista(lista);
        NodoPedido **listaa=&lista;
        liberarLista(*&listaa);
        mostrarLista( lista);





       lista= insertarPedido(lista);
        mostrarLista(lista);
system("pause");
system("cls");


       printf("EL MONTO TOTAL ES: %.2f",calcularMontoCompraTotal(lista));

    int  cant=0;

    RegistroCompraCliente *arreglo = cargaMayoresA5000(&cant,lista);
    mostrarPedidos5000( arreglo,cant);
    }
    else
    {
        printf("ERROR AL ABRIR ARCHIVO \n");

    }


    fclose(archi);
    return 0;
}


NodoPedido *iniclista()
{

    return NULL;
}
NodoPedido* crearNodo(RegistroCompraCliente regis)
{

    NodoPedido*nuevo= (NodoPedido*)malloc(sizeof(NodoPedido));

    nuevo ->siguiente =NULL;
    nuevo ->cliente.NroCliente =regis.NroCliente;
    strcpy(nuevo->cliente.NyA,regis.NyA);
    nuevo ->MontoCompra=regis.MontoCompra;
    nuevo ->NroPedido =regis.NroPedido;
    return nuevo;
}


NodoPedido *agregarAlFinal(NodoPedido *lista, NodoPedido *nuevo)
{

    NodoPedido *seg=lista;

    if(lista==NULL)
    {
        lista=nuevo;
    }
else{
    while (seg->siguiente !=NULL)
    {

        seg=seg->siguiente;

    }
    seg->siguiente=nuevo;

}
    return lista;
}

NodoPedido *crearListaPedidos(NodoPedido *lista, char Archivo[])
{
    FILE *archi=fopen(Archivo,"r+b");
    RegistroCompraCliente regis;
    if(archi)
    {


        while(fread(&regis,sizeof(RegistroCompraCliente),1,archi)>0)
        {

            lista= agregarAlFinal(lista,crearNodo(regis));

        }

    }
    else
    {
        printf("ERROR AL AABRIR EL ARCHIVO \n");
    }
    fclose(archi);
    return lista;

}


void mostrarLista(NodoPedido *  lista){
NodoPedido *seg=lista;

if(lista){
printf(" Nombre y apellido: %s \n" ,seg->cliente.NyA);
printf("Nro Cliente: %d \n",seg->cliente.NroCliente);
printf("Numero Pedido: %d \n",seg->NroPedido);
printf("Monto de compra: %.2f \n",seg->MontoCompra);
mostrarLista(seg->siguiente);
}

}

void liberarLista (NodoPedido **listaa){

NodoPedido *seg= *listaa;
NodoPedido *ante= *listaa;


if(seg){
 while(seg !=NULL){
    ante=seg;
    seg=seg->siguiente;
    free(ante);
 }
}
else{
printf("La lista ya esta vacia \n");
}
*listaa=seg;
}

RegistroCompraCliente cargar_registro(){

RegistroCompraCliente regis;
printf("Ingrese Nombre y apellido \n");
fflush(stdin);
gets(regis.NyA);
printf("Ingrese Nro Cliente \n");
scanf("%d",&regis.NroCliente);
printf("Ingrese Nro Pedido \n");
scanf("%d",&regis.NroPedido);
printf("Ingrese monto \n");
scanf("%f",&regis.MontoCompra);

return regis;
}

NodoPedido *insertarPedido(NodoPedido *lista){


char o=0;

while(o!=27){

    lista=agregarAlFinal(lista,crearNodo(cargar_registro()));
    printf("Presione ESC para salir o any key to continue \n");
    fflush(stdin);
    o=getch();
}



return lista;
}


float calcularMontoCompraTotal(NodoPedido *lista){

float total=0;
NodoPedido *seg=lista;
if(seg){

    total=seg->MontoCompra+calcularMontoCompraTotal(seg->siguiente);

}

return total;
}


RegistroCompraCliente *cargaMayoresA5000(int *cant,NodoPedido *lista){


NodoPedido *seg=lista;

int i=0;

    while(seg!=NULL){
        if(seg->MontoCompra>5000){
        i++;
    }
    seg=seg->siguiente;
    }
RegistroCompraCliente *a = (RegistroCompraCliente*)malloc( i*sizeof(RegistroCompraCliente));
seg=lista;
int j=0;
        while(seg!=NULL){
                if(seg->MontoCompra>5000){
            strcpy(a[j].NyA,seg->cliente.NyA);
            a[j].NroCliente =seg->cliente.NroCliente;
            a[j].NroPedido=seg->NroPedido;
            a[j].MontoCompra=seg->MontoCompra;
            j++;
        }
   seg=seg->siguiente;
        }

        *cant=i;

        return a;
}


void mostrarPedidos5000(RegistroCompraCliente *arreglo,int cant){
int i=0;
while(i<cant){

printf("Nombre: %s \n",arreglo[i].NyA);
printf(" NRO CLIENTE : %d \n",arreglo[i].NroCliente);
printf(" NRO PEDIDO : %d \n",arreglo[i].NroPedido);
printf(" MONTO COMPRA : %.2f \n",arreglo[i].MontoCompra);
i++;
}
}


