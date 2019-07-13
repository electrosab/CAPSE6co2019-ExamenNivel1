
//includes

#include <stdio.h>


#define FILAS 6
#define COLUMNAS 1


//---------MAIN------------


int main()
{
    int filas = FILAS;
    int coef = COLUMNAS;

    for(int a=0; a<filas; a++) {
        for(int b=0; b <= a; b++) {
            if (b==0 || a==0) {
                coef = 1;
            } else {
                coef = coef*(a-b+1)/b;
            }

            printf("%d ", coef);
        }
        printf("\n");
    }

    return 0;
}