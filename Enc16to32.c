/**
 **********************************************************************************
 * @file   Enc16to32.c
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

//* Private Includes -------------------------------------------------------------- //
#include "Enc16to32.h"

//* Others ------------------------------------------------------------------------ //
#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

/**
 ** ==================================================================================
 **                           ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The Library
 * @note   This function must be called after enabling encoder and its interrupt
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
ForceInline void
Enc16to32_Init(Enc16to32_Handler_t *Encoder_Handler) { Encoder_Handler->HighRegisterValue = 0; }

/**
 * @brief  Gets the encoder value in 32 bits signed number between -2^31 to 2^31-1
 * @note   To get the encoder value in 32 bits unsigned number between 0 to 2^32-1, you can cast return value in uint32_t
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval Encoder value in 32 bits signed number
 */
ForceInline int32_t
Enc16to32_GetEncoderValue(Enc16to32_Handler_t *Encoder_Handler) { return ((Encoder_Handler->HighRegisterValue << 16) | (Encoder_Handler->GetTimerValue())); }

//* IRQ Handler Functions --------------------------------------------------------- //

/**
 * @brief  Handles the timer Overflow and Underflow IRQ
 * @note   Use this function OR TimerUnderflow AND TimerOverflow functions
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
ForceInline void
Enc16to32_IRQ_TimerOverUnderflow(Enc16to32_Handler_t *Encoder_Handler) {
  if ((Encoder_Handler->GetTimerValue() >= 0x7FFF) && (Encoder_Handler->HighRegisterValue >= 0)) Encoder_Handler->HighRegisterValue--;
  else if ((Encoder_Handler->GetTimerValue() <= 0x7FFF) && (Encoder_Handler->HighRegisterValue <= 0xFFFF)) Encoder_Handler->HighRegisterValue++; }

/**
 * @brief  Handles the timer Overflow IRQ 
 * @note   Use this function AND TimerUnderflow OR TimerOverUnderflow function
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
ForceInline void
Enc16to32_IRQ_TimerOverflow(Enc16to32_Handler_t *Encoder_Handler) { if(Encoder_Handler->HighRegisterValue <= 0xFFFF) Encoder_Handler->HighRegisterValue++; }

/**
 * @brief  Handles the timer Underflow IRQ 
 * @note   Use this function AND TimerOverflow OR TimerOverUnderflow function
 * @param  Encoder_Handler: Pointer Of Library Handler
 * @retval None
 */
ForceInline void
Enc16to32_IRQ_TimerUnderflow(Enc16to32_Handler_t *Encoder_Handler) { if(Encoder_Handler->HighRegisterValue >= 0) Encoder_Handler->HighRegisterValue--; }

