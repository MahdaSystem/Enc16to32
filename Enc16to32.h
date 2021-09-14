/**
 **********************************************************************************
 * @file   Enc16to32.h
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Change encoder timer 16 bits to 32 bits 
 **********************************************************************************
 *
 *! Copyright (c) 2021 Mahda Embedded System (MIT License)
 *!
 *! Permission is hereby granted, free of charge, to any person obtaining a copy
 *! of this software and associated documentation files (the "Software"), to deal
 *! in the Software without restriction, including without limitation the rights
 *! to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *! copies of the Software, and to permit persons to whom the Software is
 *! furnished to do so, subject to the following conditions:
 *!
 *! The above copyright notice and this permission notice shall be included in all
 *! copies or substantial portions of the Software.
 *!
 *! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *! SOFTWARE.
 *!
 **********************************************************************************
 **/
//* Define to prevent recursive inclusion ---------------------------------------- //
#ifndef ENC16TO32_H
#define ENC16TO32_H

#ifdef __cplusplus
extern "C" {
#endif

//* Includes ---------------------------------------------------------------------- //
#include <stdint.h>

//? User Configurations and Notes ------------------------------------------------- //
// ! Important Notes:
// Place timer Overflow AND Underflow OR OverUnderflow functions in their related IRQ handler
#define Debug_Enable                        // Uncomment if you want to use (depends on printf in stdio.h)
#define ForceInline                         // Place your Force Inline attribute here, otherwise functions will work normally (e.g. __forceinline for Keil)
//? ------------------------------------------------------------------------------- //

/**
 ** ==================================================================================
 **                               ##### Structs #####                               
 ** ==================================================================================
 **/
 
typedef struct
Enc16to32_Handler_s {
  uint16_t (*GetTimerValue)(void);     // Must be initialized (e.g. Getting TIMx->CNT value in STM32 Microcontrollers)
  uint16_t HighRegisterValue;          // !!! DO NOT USE OR EDIT THIS !!!
} Enc16to32_Handler_t;

/**
 ** ==================================================================================
 **                          ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The Library
 * @note   This function must be called after enabling encoder and its interrupt
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
extern ForceInline void
Enc16to32_Init(Enc16to32_Handler_t *Encoder_Handler);

/**
 * @brief  Gets the encoder value in 32 bits signed number between -2^31 to 2^31-1
 * @note   To get the encoder value in 32 bits unsigned number between 0 to 2^32-1, you can cast return value in uint32_t
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval Encoder value in 32 bits signed number
 */
extern ForceInline int32_t
Enc16to32_GetEncoderValue(Enc16to32_Handler_t *Encoder_Handler);

//* IRQ Handler Functions --------------------------------------------------------- //

/**
 * @brief  Handles the timer Overflow and Underflow IRQ
 * @note   Use this function OR TimerUnderflow AND TimerOverflow functions
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
extern ForceInline void
Enc16to32_IRQ_TimerOverUnderflow(Enc16to32_Handler_t *Encoder_Handler);

/**
 * @brief  Handles the timer Overflow IRQ 
 * @note   Use this function AND TimerUnderflow OR TimerOverUnderflow function
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
extern ForceInline void
Enc16to32_IRQ_TimerOverflow(Enc16to32_Handler_t *Encoder_Handler);

/**
 * @brief  Handles the timer Underflow IRQ 
 * @note   Use this function AND TimerOverflow OR TimerOverUnderflow function
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
extern ForceInline void
Enc16to32_IRQ_TimerUnderflow(Enc16to32_Handler_t *Encoder_Handler);

#ifdef __cplusplus
}
#endif
#endif
