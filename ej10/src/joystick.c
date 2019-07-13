#include "joystick.h"

/* ejercicio 5 */
struct joystick leerJoystick ()
{
   struct joystick valores;

   valores.x = adcRead(CH1);
   valores.y = adcRead(CH2);

   return valores;
}

/* ejercicio 6 */

int imprimirValores(struct joystick valores)
{
   printf("[ %d,%d ]\r\n", valores.x, valores.y);
   return 0;
}