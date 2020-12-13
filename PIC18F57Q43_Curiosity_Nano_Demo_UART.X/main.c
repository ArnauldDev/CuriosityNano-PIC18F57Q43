/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"

//#define DEMO_SW0_STATUS_LED0
#define DEMO_SW0_TOGGLE_LED0

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Séquence de clignotement de la LED0
    int i;
    for (i = 0; i < 10; i++)
    {
        // LED0 flashing sequence
        LED0_Toggle();
        __delay_ms(200);
    }

    // Compile file path (internal file of compilation proccess)
    printf("__FILE__: ");
    printf(__FILE__);
    printf("\r\n");

    // Current line (but in __FILE__)
//    printf("__LINE__: " __LINE__ "\r\n");
    printf("__LINE__: %u\r\n", __LINE__);

    // Name of current function
    // https://stackoverflow.com/questions/4384765/whats-the-difference-between-pretty-function-function-func
//    printf("__func__: " __func__ "\r\n");
    printf("__func__: %s\r\n", __func__);

    // Date of compliation
    printf("__DATE__: " __DATE__ "\r\n");

    // Time of compilation
    printf("__TIME__: " __TIME__ "\r\n");

    // Version of comilator (avr-gcc) 
    printf("__VERSION__: " __VERSION__ "\r\n");

    // Counter
    printf("__COUNTER__: "); // 0 
    printf(__COUNTER__); // 0 
    printf("\r\n"); // 0 
    //    printf("__COUNTER__: " __COUNTER__ "\r\n"); // 0 
    //    printf("__COUNTER__: " __COUNTER__ "\r\n"); // 1
    //    printf("__COUNTER__: " __COUNTER__ "\r\n"); // 2

    while (1)
    {
        volatile uint8_t rxData;

        // Logic to echo received data
        if (UART1_is_rx_ready())
        {
            rxData = UART1_Read();
            if (UART1_is_tx_ready())
            {
                UART1_Write(rxData);
            }
        }

#if defined(DEMO_SW0_STATUS_LED0)
        /**
         * Demo 1
         */
        if (SW0_GetValue() == 0)
        {
            LED0_SetHigh();
        } else
        {
            LED0_SetLow();
        }
#elif defined(DEMO_SW0_TOGGLE_LED0)
        /**
         * Demo 2
         */
        if (!SW0_GetValue())
        {
            __delay_ms(50); // delay for SW debounce
            if (!SW0_GetValue())
            {
                LED0_Toggle();
                printf("BUTTON PRESSED\r\n"); // send message to serial port
                // Attendre le relâchement du bouton poussoir
                while (!SW0_GetValue()); // wait for the push button to release
            }
        }
#else
#error "You must choose between one of the two configurations"
#endif
    }
}

/**
 End of File
 */
