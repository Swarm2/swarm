/*
 * encoder_init.h
 *
 *  Created on: 06-Jun-2019
 *      Author: Mayuresh
 */

#ifndef ENCODER_INIT_H_
#define ENCODER_INIT_H_

extern void encoder_init(void);

typedef struct
{
    char pos[100];
    int direction[100];
    uint32_t velocity[100];

}encoder_parameters;

extern encoder_parameters wh1,wh2;

#endif /* ENCODER_INIT_H_ */
