//esto es una modificacion de prueba
#include "sapi.h"

#define LED_BLUE_PRENDIDO 1
#define LED_BLUE_APAGADO  2
#define LED_1_PRENDIDO 3
#define LED_1_APAGADO  4
#define LED_2_PRENDIDO 5
#define LED_2_APAGADO  6
#define LED_3_PRENDIDO 7
#define LED_3_APAGADO  8
#define TIEMPO_1 50
#define TIEMPO_2 100
#define TIEMPO_3 200
#define TIEMPO_4 500
#define TIEMPO_DEFAULT 250

//---------prototipo de funciones
int leer_teclado_pc ();
int parpadear ();
int leer_teclado_ciaa ();

//-------configuro las teclas como entrada
void setup(void)
{
   gpioConfig(TEC1, GPIO_INPUT);
   gpioConfig(TEC2, GPIO_INPUT);
   gpioConfig(TEC3, GPIO_INPUT);
   gpioConfig(TEC4, GPIO_INPUT);
}

//variables globales

int estado=0;
delay_t tiempo;
int aux_tiempo=TIEMPO_DEFAULT;

//-----MAIN-----------
int main( void )
{
   boardConfig();
   uartConfig( UART_USB, 115200 );
   delayInit(&tiempo,aux_tiempo);
   setup();

   while( TRUE ) {

      leer_teclado_pc ();
      leer_teclado_ciaa ();
      parpadear();

   }
   return 0;
}//llave del main



int leer_teclado_pc ()
{
   char tecla;
   if (uartReadByte( UART_USB, &tecla ))

      switch (tecla) {

      case 'a':
         estado= LED_BLUE_PRENDIDO;
         tecla=0;
         break;
      case '1':
         estado=LED_1_PRENDIDO;
         tecla=0;
         break;
      case '2':
         estado=LED_2_PRENDIDO;
         tecla=0;
         break;
      case '3':
         estado=LED_3_PRENDIDO;
         tecla=0;
         break;
      } //llave switch tecla

   return 0;
}//llave funcion leer teclado




int leer_teclado_ciaa ()
{
   int pulsador =0;

   if  (gpioRead (TEC1)==FALSE) {
      pulsador=TEC1;

   }
   if  (gpioRead (TEC2)==FALSE) {
      pulsador=TEC2;
   }
   if  (gpioRead (TEC3)==FALSE) {
      pulsador=TEC3;
   }
   if  (gpioRead (TEC4)==FALSE) {
      pulsador=TEC4;
   }
   switch (pulsador) {

   case TEC1:
      aux_tiempo=TIEMPO_1;
      delayInit(&tiempo,aux_tiempo);
      break;
   case TEC2:
      aux_tiempo=TIEMPO_2;
      delayInit(&tiempo,aux_tiempo);
      break;
   case TEC3:
      aux_tiempo=TIEMPO_3;
      delayInit(&tiempo,aux_tiempo);
      break;
   case TEC4:
      aux_tiempo=TIEMPO_4;
      delayInit(&tiempo,aux_tiempo);
      break;

   }//llave switch pulsador
   //delayInit(&tiempo,aux_tiempo);
   //si dejo este aca que me parece lo correcto no anda.
   //si lo comento y dejo los delayInit de cada case anda bien. preguntar!!!

   return 0;

}//llave leer_teclado_ciaa


int parpadear ( )
{

   switch (estado) {

   case LED_BLUE_PRENDIDO:
      gpioWrite(LED1, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LEDB, ON);
      if(delayRead(&tiempo)) {
         estado=LED_BLUE_APAGADO;
      }

      break;

   case LED_BLUE_APAGADO:
      gpioWrite(LED1, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LEDB, OFF);
      if(delayRead(&tiempo)) {
         estado=LED_BLUE_PRENDIDO;
      }

      break;

   case LED_1_PRENDIDO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LED1, ON);
      if(delayRead(&tiempo)) {
         estado=LED_1_APAGADO;
      }
      break;

   case LED_1_APAGADO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LED1, OFF);
      if(delayRead(&tiempo)) {
         estado=LED_1_PRENDIDO;
      }

      break;

   case LED_2_PRENDIDO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED1, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LED2, ON);
      if(delayRead(&tiempo)) {
         estado=LED_2_APAGADO;
      }
      break;

   case LED_2_APAGADO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED1, OFF);
      gpioWrite(LED3, OFF);
      gpioWrite(LED2, OFF);
      if(delayRead(&tiempo)) {
         estado=LED_2_PRENDIDO;
      }
      break;

   case LED_3_PRENDIDO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED1, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, ON);
      if(delayRead(&tiempo)) {
         estado=LED_3_APAGADO;
      }
      break;

   case LED_3_APAGADO:
      gpioWrite(LEDB, OFF);
      gpioWrite(LED1, OFF);
      gpioWrite(LED2, OFF);
      gpioWrite(LED3, OFF);
      if(delayRead(&tiempo)) {
         estado=LED_3_PRENDIDO;
      }

      break;

      return 0;
   }//llave switch estado

}//llave parpadear





