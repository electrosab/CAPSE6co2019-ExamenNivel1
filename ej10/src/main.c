//includes
#include <stdio.h>
#include "sapi.h"
#include "joystick.h"


//prototipo de funciones

int mover_servo (struct joystick valores);

//---------MAIN--------------
int main ()
{
   boardInit();
   delay_t tiempo;
   delayConfig( &tiempo, 1000 );
   // Habilitar pwm de servos
   servoConfig( 0, SERVO_ENABLE );
   // Habilitar salida SERVOn (n puede ser 0...8)
   servoConfig( SERVO0, SERVO_ENABLE_OUTPUT );


   while(TRUE) {

      leerJoystick ();

      if(delayRead(&tiempo)) {

         imprimirValores(leerJoystick ());
         mover_servo (leerJoystick ());
      }

   }
   return 0;
}

/* ejercicio 7 */

int mover_servo (struct joystick valores)
{
   int valor_pote_x=0;
   int grados_servo =0;
   valor_pote_x=valores.x;
   grados_servo = ((valor_pote_x/1023.0) *180);
   // Escribir el servo con el angulo

   servoWrite( SERVO0, grados_servo );

}