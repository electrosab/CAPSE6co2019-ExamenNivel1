//includes
#include <stdio.h>
#include "sapi.h"
//--DEFINES--
struct joystick {
    int x, y;
};

//prototipo de funciones
struct joystick leerJoystick ();
int imprimirValores(struct joystick);
//---------MAIN--------------
int main ()
{
    boardInit();
    delay_t tiempo;
    delayConfig( &tiempo, 1000 );
    while(TRUE) {
         
        leerJoystick ();

        if(delayRead(&tiempo)) {

            imprimirValores(leerJoystick ());
        }

    }
    return 0;
}

struct joystick leerJoystick ()
{
    struct joystick valores;

    valores.x = adcRead(CH1);
    valores.y = adcRead(CH2);

    return valores;
}




