/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Data.h (Problem Data)
Prefix: PP
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton
==============================================================================*/
#include "Problem-Types.h"		// Problem Parameters 
//========================== Problem variables ====================================
static double* PD_coordinates;
static double* PD_velosity;
//========================== Problem structures ====================================
static PT_smallMassPoint_T PD_X;
static PT_largeMassPoint_T PD_Y[PP_N];
