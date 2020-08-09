/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Data.h (Problem Data)
Prefix: PP
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton
==============================================================================*/
#include "Problem-Types.h"		// Problem Parameters 

//=========================== Variables for BSF-skeleton Parameters =========================
static int PP_BSF_addressOffset;
static int PP_BSF_iterCounter;
static int PP_BSF_jobCase;
static int PP_BSF_mpiRank;
static int PP_BSF_numberInSublist;
static int PP_BSF_numOfWorkers;
static int PP_BSF_sublistLength;

//========================== Problem variables ====================================
static double* PD_coordinates;
static double* PD_velosity;
//========================== Problem structures ====================================
static PT_smallMassPoint_T PD_X;
static PT_largeMassPoint_T PD_Y[PP_N];
