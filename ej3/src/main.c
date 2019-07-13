
//includes

#include <stdio.h>

//--------DEFINES------

#define SECUENCIA 7
#define FILAS     3

//prototipo de funciones

int funcion (int, int);

//---------MAIN-----------------------------


int main ()
{


    funcion (SECUENCIA, FILAS);

    return 0;
}//llave del main


//-----FUNCIONES------------


int funcion (int s, int f)
{
    int a=0; //variable auxiliar, me sirve para ir corriendo de lugar el inicio de impresion, e ir sumando.
    for (int i=0; i <f ; i++) {
        for (int j=0; j<a; j++) { //cuando a=0, no imprime el espacio en blanco
            printf (" ");
        }
        for (int z=1+a; z<=s+a; z++) {

            printf ("%d",z);
        }

        printf ("\n"); //al terminar de imprimir la fila, hago un salto de renglon
        a++;
    }

    return 0;  
}