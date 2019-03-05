#ifndef MPPT_H
#define MPPT_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "../mcc_generated_files/mcc.h"
#include "pwm_interface.h"
#include "adc1.h"

#define PERTUBATION 0x0002
#define INIT_PHASE	0x0000
#define INIT_PER	0x006E
#define INIT_DC		0x0000
#define MAX_DC_VAL 	0x0062
#define MIN_DC_VAL  0x0000
#define KA			0x0001
#define KB 			0x0001
#define KC 			0x0001
#define DEMO2

/* Store two contiguous 16-bit integers in memory */
typedef struct 
{
	uint16_t k;
	uint16_t k_1;
} RAM_BLOCK;

/* Store three contiguous 16-bit integers in memory */
typedef struct 
{
	uint16_t k;
	uint16_t k_1;
	uint16_t k_2;
} RAM_BLOCK_3;

/* Store three contiguous 32-bit integers in memory */
typedef struct 
{
	uint32_t k;
	uint32_t k_1;
} RAM_BLOCK_32;

void mppt_init(void);
uint16_t mppt(void);
uint16_t mppt_pid(void);
void mppt_increase_dc(void);
void mppt_decrease_dc(void);
void mppt_pid_init(void);
uint16_t pidoptimal(void);

#endif