#ifndef _PWM_SERVO_H
#define _PWM_SERVO_H

#ifdef PWM_SERVO_SUPPORT
#define SERVO_STARTVALUE 128

extern volatile unsigned char servo_pos;

extern void pwm_servo_init (void);
extern void setservo (uint8_t value);

#endif /* PWM_SERVO_SUPPORT */

#endif /* _PWM_SERVO_H */
