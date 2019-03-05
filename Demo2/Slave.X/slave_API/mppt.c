/*
 * File:		mppt.c
 * Purpose:		Perturb and observe algorithm for computing the maximum power point of the 
 *				generator. 
 */

#include "mppt.h"

/*
 * Global Vars
 * 
 * v:	RAM_BLOCK which stores current voltage, v(k), and prev voltage, 
 *		v(k-1)
 * 
 * i:	unisigned 16-bit integer which stores current voltage, i(k)
 *
 * p: 	RAM_BLOCK_32 which stores current voltage, p(k), and prev voltage, 
 *		p(k-1). Note that it must be 32bits since it will store the product
 *		of two 16bit integers
 *
 * pid_constant: used to store Ka, Kb, and Kc for the pid controller
 *
 * pid_error: used to store the pid error values
 */
volatile RAM_BLOCK_32 p;
volatile RAM_BLOCK v;
volatile RAM_BLOCK_3 pid_constant;
volatile RAM_BLOCK_3 pid_err;
volatile uint16_t i;
volatile uint16_t PIDTERM, B1_PIDVKabc, B1_PIDVErrors;
volatile int16_t Vref;

/*
 * initialize all global vars to a known state. Also configures the boost converter PWM
 * module
 * 
 * RETURN: 	NULL
 * 
 * PRE: 	Boost Converter PWM module is GENERATOR_5
 * 
 * POST:	All global vars in known state. Initialize boost converter module
 */
void mppt_init(void){
	v.k = 0;
	v.k_1 = 0;
	i = 0;
	p.k = 0;
	p.k_1 = 0;

	config_PWM(PWM_GENERATOR_5, INIT_DC, INIT_PHASE, INIT_PER);
	PWM_ModuleDisable(PWM_GENERATOR_5);
    
    return;
}

/*
 * Perturb and observe algorithm. This algorthim is executed in main every loop iteration, 
 * or whenever the duty cycle needs to be updated. This is a non-blocking function. Modifies
 * the v, i, and p global variables as well as updates the duty cycle. Increasing the duty cycle
 * will result in a higher output voltage thus reducing the current drawn from the supply of the 
 * boost converter, which in this case is the generator. Decreasing the duty cycle, decreases 
 * the output voltage, increasing the current draw. 
 * 
 * RETURN:	NULL
 * 
 * PRE: 	Main has initialized the boost convertor PWM module and mppt_init(). Global variables v, p and i
 * 			exist and are RAM_BLOCKS and unint_16 respectively.
 *			SENSOR_1 => v
 *			SENSOR_2 => i
 *
 * POST: 	Updates boost converter PWM duty cycle and updates the v, i, and p global variables
 */
uint16_t mppt(void){
	int32_t deltaP;
	uint16_t debug;

	v.k 	= ADC_Read12bitAverage(SENSOR_1, 40);
	i   	= 1; //ADC_Read12bitAverage(SENSOR_5, 40);

	p.k 	= v.k * i; 
	deltaP 	= p.k - p.k_1;

	if(deltaP > 0){
		if(v.k > v.k_1){
			mppt_increase_dc();
			debug = 11;
		} 
		else{
			mppt_decrease_dc();
			debug = 22;
		}
	} 
	else {
		if(v.k > v.k_1){
			mppt_decrease_dc();
			debug = 33;
		}
		else{
			mppt_increase_dc();
			debug = 44;
		}
	}

	v.k_1 	= v.k;
	p.k_1 	= p.k;

	return debug;
}

/* 
 * Initialize the pid controller
 *
 * RETURN: 	NULL
 * 
 * PRE: 	System initialized
 *
 * POST: 	RAM_Blocks initialized with PID constants and error values set to zero
 */
void mppt_pid_init(void){
	pid_constant.k 		= KA;
	pid_constant.k_1	= KB;
	pid_constant.k_2    = KC;
	pid_err.k 			= 0;
	pid_err.k_1 	 	= 0;
	pid_err.k_2 	 	= 0;
}

/*
 * This is a wrapper for the optimized assembly code that executes the PID algorithm
 *
 * RETURN: 	PID term (increment for duty cycle)
 * 
 * PRE: 	Pid initialized
 *
 * POST: 	PID algorithm called
 */
uint16_t mppt_pid(void){
	return PERTUBATION;
	//return pidoptimal();
}

/*
 * This code is an optimized PID controller for the dsPIC. Takes advantage of the dsPIC
 * special digital signal processing instructions. Code taken from:
 * http://microchipdeveloper.com/pwr3201:dspic-dscs-implementation-part-2
 * 
 * RETURN: 	PID term (increment for duty cycle)
 * 
 * PRE: 	Pid initialized. 
 *
 * POST: 	PID algorithm executed
 */

uint16_t pidoptimal(void){
	asm(
		";init pointers to coefficient and error arrays \n"
		"mov #_B1_PIDVKabc, W8  \n"
		"mov #_B1_PIDVErrors, W10 \n"

		"mov ADCBUF1, W2 ; ADCBUF1 stores the most recent output voltage sample \n"
		"mov _Vref, W3	; computation of error e(n) \n"
		"sub W3, W2, [W10] \n"

		"movsac A, [W8] +=2, W4, [W10] += 2, W5 \n"

		"mac W4*W5, B, [W8] +=2, W4, [W10] +=2, W5 \n"

		"mac W4*W5, B, [W8], W4, [W10] -=2, W5 \n"

		"sac.r B, #7, W0 \n"

		"mov W5, [W10] \n"
		"mov [W10 +# -4], W5 \n"
		"mov W5, [--W10] \n"
		"mov W5, _PIDTERM  \n"
	);
    return PIDTERM;
}


/*
 * To increase the duty cycle the PWM module must first be stopped. The value of duty cycle
 * is the incremented by the value specified by the PID controller.
 * 
 * RETURN: 	NULL
 *
 * PRE: 	PWM module properly initialized
 *
 * POST: 	Duty cycle of PWM_GENERATOR_5 module (Boost convertor) is increased
 */
void mppt_increase_dc(void){
	uint16_t duty_cycle;
	PWM_ModuleDisable(PWM_GENERATOR_5);
	duty_cycle = PG5DC; 

	/* Prevent overflow of duty cycle */
	if(duty_cycle + mppt_pid() >= MAX_DC_VAL){
		duty_cycle = MAX_DC_VAL; 				
	}
	else { 
		duty_cycle += mppt_pid();
	}

	PWM_DutyCycleSet(PWM_GENERATOR_5, duty_cycle);
	PWM_ModuleEnable(PWM_GENERATOR_5);
}

/*
 * To decrease the duty cycle the PWM module must first be stopped. The value of duty cycle
 * is the decremented by the value specified by the PID controller.
 * 
 * RETURN: 	NULL
 *
 * PRE: 	PWM module properly initialized
 *
 * POST:	Duty cycle of PWM_GENERATOR_5 module (Boost convertor) is decreased
 */
void mppt_decrease_dc(void){
	uint16_t duty_cycle;
	PWM_ModuleDisable(PWM_GENERATOR_5);
	duty_cycle = PG5DC; 

	/* Prevent underflow of duty cycle */
	if(duty_cycle - mppt_pid() >= duty_cycle){
		duty_cycle = MIN_DC_VAL;
	}
	else{ 
		duty_cycle -= mppt_pid();
	}

	PWM_DutyCycleSet(PWM_GENERATOR_5, duty_cycle);
	PWM_ModuleEnable(PWM_GENERATOR_5);
}