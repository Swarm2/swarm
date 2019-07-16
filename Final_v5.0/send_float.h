/*
 * send_float.h
 *
 *  Created on: 13-Jun-2019
 *      Author: Mayuresh
 */

#ifndef SEND_FLOAT_H_
#define SEND_FLOAT_H_

extern void send_float(float w);

typedef struct {
    char identifier;
    int data[3];
}div_param;

extern div_param store[400];



#endif /* SEND_FLOAT_H_ */
