 //includes
#include <stdio.h>

//defines
#define N 4
#define M 13

//este programa imprime la siguiente figura:
/*

   *******
  *       *
 *         *
*************

( N filas y base de M caracteres: )

*/

int main( void )
{
    printf("Ejercicio del examen 2\r\n");

    int f,c = 0;
    for (f=1; f<=N; f++) {
        for(c=1; c<=M; c++) {
            if ( ( f==N ) || ((f==1) && ((c>N-1) && (c<(M-2)))) || (c==(N-f)+1) || (c==f+(2*N+1)  )) {
                printf ("*");
            } //llave del if
            else {
                printf (" ");
            }//llave del else
        }//llave for columnas
        printf ("\r\n");

    } //llave del for filas
    return 0;
}//llave del main