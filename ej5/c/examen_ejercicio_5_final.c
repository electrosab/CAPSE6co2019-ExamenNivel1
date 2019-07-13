//includes
#include <stdio.h>
#include <sapi.h>
//--DEFINES--
struct joystick {
   int x, y;
};

//prototipo de funciones
struct joystick leerJoystick ();

//---------MAIN--------------
int main ()
{
   boardInit();

   while(TRUE) {

      leerJoystick ();

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





