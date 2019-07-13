#include "sapi.h"        // <= Biblioteca sAPI
#include <stdlib.h>
#include <string.h>
uint8_t TecladoPinesFilas[4] = {
   RS232_TXD,
   CAN_RD,
   CAN_TD,
   T_COL1,
};

uint8_t TecladoPinesColumnas[4] = {
   T_FIL0,
   T_FIL3,
   T_FIL2,
   T_COL0,
};


int8_t indiceACaracter[] = {
   '1', '2', '3', '/',  // 1/2 Enter
   '4', '5', '6', '+' ,
   '7', '8', '9', '-' ,
   '*', '0', '#', '?' ,  // 8 = Retroceso
};

#define TECLADO_SCAN 40
#define TECLADO_MOSTRAR 100

void tecladoInit( void );
int8_t escanearTeclado( void );

char angulo_servo[3];
int indice = 0;

int val_angulo;


int main( void )
{
   boardConfig();
   // Habilitar pwm de servos
   servoConfig( 0, SERVO_ENABLE );
   // Habilitar salida SERVOn (n puede ser 0...8)
   servoConfig( SERVO0, SERVO_ENABLE_OUTPUT );
   int8_t teclaAnt = -1;
   int8_t tecla = -1;

   tecladoInit();
   delay_t escaneoTeclado;
   delayInit( &escaneoTeclado, TECLADO_SCAN );

   delay_t mostrarTeclado;
   delayInit( &mostrarTeclado, TECLADO_MOSTRAR );

   tecla = teclaAnt = -1;
   while( TRUE ) {
      if( delayRead(&escaneoTeclado) ) {
         tecla = escanearTeclado();
         if (teclaAnt != tecla) {
            switch (tecla) {
            case -1:
               break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
               angulo_servo[indice] = tecla;
               indice++;
               angulo_servo[indice] = 0;
               sscanf(angulo_servo, "%d", &val_angulo);
               if ((val_angulo>180)||(val_angulo<0)) {
                  printf("ingreso un valor de angulo incorrecto\r\n", angulo_servo);
               }
               printf("angulo_servo %s\r\n", angulo_servo);
               if (indice == 3)
                  indice = 0;

               break;

            case '*':
               printf("usted ingreso %s\r\n", angulo_servo);
               servoWrite( SERVO0, atoi(angulo_servo));

               break;

            }
         }
         teclaAnt = tecla;
      }
   }
   return 0;
}

void tecladoInit( void )
{
   uint8_t pin = 0;
   for( pin=0; pin<4; pin++ ) {
      // Configuro las filas como salida
      gpioInit( TecladoPinesFilas[pin], GPIO_OUTPUT );
      gpioWrite( TecladoPinesFilas[pin], ON );
      // Configuro las columnas como entradas, con resistencias de pull-up internas
      gpioInit( TecladoPinesColumnas[pin], GPIO_INPUT_PULLUP );
   }
}

int8_t escanearTeclado( void ) // devuelve el indice de tecla [0,15] o -1 si no hay tecla presionada
{
   int8_t f = 0;
   int8_t i = 0;
   int8_t c = 0;

   // Escanear todas las filas
   for( f=0; f<4; f++ ) {

      // Prendo todas las filas (el estado normal por las resistencias de pull-up)
      for( i=0; i<4; i++ ) {
         gpioWrite( TecladoPinesFilas[i], ON );
      }

      // Apago la fila que quiero escanear
      gpioWrite( TecladoPinesFilas[f], OFF );

      // Chequeo si alguna columna lee el OFF de mi fila actual
      for( c=0; c<4; c++ ) {
         // Chequeo que la columna actual este en OFF (hay una en OFF si se presiona algun boton)
         if( gpioRead( TecladoPinesColumnas[c] ) == OFF ) {
            return indiceACaracter[4*f + c];
         }
      }
   }
   return -1;
}

