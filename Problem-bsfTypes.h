/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfTypes.h (Predefined Problem Types)
Prefix: PT_bsf
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton
==============================================================================*/
#pragma once
#include "Problem-Types.h"		// Problem Types 
//=========================== BSF Types =========================
struct PT_bsf_parameter_T {			// Parameter for workers
	double coordinates[PP_SPACE_DIMENSION];
	double velosity[PP_SPACE_DIMENSION];
};

struct PT_bsf_mapElem_T {			// Element of map list
	int massPointNo;
};

struct PT_bsf_reduceElem_T {			// Element of reduce list	
	double acceleration[PP_SPACE_DIMENSION];
};

struct PT_bsf_reduceElem_T_1 {				
	// optional filling
};

struct PT_bsf_reduceElem_T_2 {
	// optional filling
};

struct PT_bsf_reduceElem_T_3 {
	// optional filling
};