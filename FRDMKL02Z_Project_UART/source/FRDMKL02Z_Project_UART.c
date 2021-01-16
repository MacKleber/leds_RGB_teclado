
 /**
 * @file    FRDMKL02Z_Project_UART.c
 * @brief   Application entry point.
 **/
 
 
 /****************************************************************************
  *librerias
 ****************************************************************************/ 

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "clock_config.h"
#include "pin_mux.h"
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"
#include "sdk_hal_uart0.h"
 
 /*******************************************************************************
 * Definiciones
 *******************************************************************************/
#define BOARD_LED_GPIO BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN


 /*******************************************************************************
 * Codigo
 ******************************************************************************/

void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 500000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}


int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200);
    
  /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };
    
   /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();


    /* Init output LED GPIO. */
    //Configura LED ROJO (PTB6) como salida
    //GPIO_PinInit(GPIOB, 6U, &led_config);

    //Configura LED VERDE (PTB7) como salida
    //GPIO_PinInit(GPIOB, 7U, &led_config);

    //Configura LED AZUL (PTB10) como salida
    //GPIO_PinInit(GPIOB, 10U, &led_config);

    while(1) {
    
    	status_t status;
    	uint8_t nuevo_byte;

    	    if(uart0NuevosDatosEnBuffer()>0){
    		   status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);
    		       if(status==kStatus_Success){
    			       printf("dato:%c\r\n",nuevo_byte);
    		        }else{
    			        printf("error\r\n");
    		          }
    		
    		if(nuevo_byte=='R'){
              GPIO_PortClear(GPIOB,1u<<BOARD_LED_RED_GPIO_PIN);//Rojo prende
              delay();
              }
            if(nuevo_byte=='r'){
              GPIO_PortSet(GPIOB,1u<<BOARD_LED_RED_GPIO_PIN);//Rojo Apaga
              delay();
              }
            if(nuevo_byte=='A'){
               GPIO_PortClear(GPIOB,1u<<BOARD_LED_BLUE_GPIO_PIN);//Azul Prende
               delay();
               }
            if(nuevo_byte=='a'){
               GPIO_PortSet(GPIOB,1u<<BOARD_LED_BLUE_GPIO_PIN);//Azul Apaga
               delay();
               }
            if(nuevo_byte=='V'){
               GPIO_PortClear(GPIOB,1u<<BOARD_LED_GREEN_GPIO_PIN);//Verde Prende
               delay();
               }
            if(nuevo_byte=='v'){
               GPIO_PortSet(GPIOB,1u<<BOARD_LED_GREEN_GPIO_PIN);//Verde Apaga
               delay();
               }
    	}
    	    	
    }
    return 0 ;
}