/*
 File:        init_master_api.c
 Purpose:     Set up the Master Core API
 */

#ifndef INIT_MASTER_API_H
#define INIT_MASTER_API_H

#include "master_API.h"

#ifndef EXTERN_GLOBAL_DC
	#define EXTERN_GLOBAL_DC
	extern volatile int16_t new_s_dc;
#endif

void init_master_api(void);

#endif