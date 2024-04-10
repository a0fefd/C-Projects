#include <stdio.h>
#include <stdlib.h>

#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
    extern "C" {
#endif

#define SET_BIT(byte, bit) ((byte) |= (1 << bit))
#define CLEAR_BIT(byte, bit) ((byte) &= ~(1 << bit))
#define TOGGLE_BIT(byte, bit) ((byte) ^= (1 << bit))
#define CHECK_BIT(byte, bit) ((byte) & (1 << bit))

void clrscr();
void invert(int *var);
void pauseEnter();

int isPrime(int num);
long long int factorial(int num);

#ifdef __cplusplus
    }
#endif

#endif /* UTILS_H_ */
