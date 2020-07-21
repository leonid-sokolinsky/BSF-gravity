/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Types.h (Problem Types)
Prefix: PT
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton
==============================================================================*/
#pragma once
#include "Problem-Include.h"		// Problem "Include" Files
#include "Problem-Parameters.h"		// Problem Parameters 
//=========================== Problem Types =========================
struct PT_smallMassPoint_T {
	double coordinates[PP_SPACE_DIMENSION];
	double velosity[PP_SPACE_DIMENSION];
	double acceleration[PP_SPACE_DIMENSION];
	double mass;
};
struct PT_largeMassPoint_T {
	double coordinates[PP_SPACE_DIMENSION];
	double mass;
};