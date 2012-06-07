/*
 * Copyright (c) 2009 by Florian Schäfer <florian.schaefer@gmail.com>
 *  Processor: ATMEGA 32
 *  CLOCK: 16MHZ
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * For more information on the GPL, please go to:
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <avr/io.h>
#include "config.h"

#ifdef PWM_SERVO_SUPPORT

#include "pwm_servo.h"

/************************************************************************

   unsigned char servo_pos
   the current servo position
***************************************************************************/
volatile unsigned char servo_pos;

/************************************************************************

   void init(void)
   initialize the prozessor registers
***************************************************************************/
void
pwm_servo_init (void)
{
    //set up fast pwm mode:  
    #define WGM_CFG (1<<WGM21 | 1<<WGM20)	//fast pwm
    #define COM_CFG (1<<COM21 | 0<<COM20)	//clr on match, set on max
    #define CLK_CFG (1<<CS22 | 1<<CS21 | 0<<CS20)	//set up clock source
    TCCR2 = WGM_CFG | COM_CFG | CLK_CFG;

    //set pin as output
    DDRD |= (1 << 7);

    //initialise
    setservo (127);
}

/************************************************************************

   void setservo(byte value)

   Set servo position
   value: 0..255

***************************************************************************/
void
setservo (uint8_t value)
{
    #define CALC_1MS F_CPU/256/1000
    servo_pos = value;
    OCR2 = CALC_1MS  + (servo_pos * CALC_1MS / 255);
}

/*
  -- Ethersex META --
  header(hardware/pwm/pwm_servo.h)
  init(pwm_servo_init)
*/

#endif /* PWM_SERVO_SUPPORT */
