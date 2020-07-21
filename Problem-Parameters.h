/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-Parameters.h (Problem Parameters)
Prefix: PP
Author: Leonid B. Sokolinsky

This source code is a part of BSF Skeleton
==============================================================================*/
#pragma once

//=========================== Problem Parameters =========================
#define PP_SPACE_DIMENSION 3	// Dimension of space = 3 (change is prohibited)

#define PP_NUNBER_OF_LARGE_MASS_POINTS		5		// Number of large mass points PD_Y[*] per one dimension
#define PP_STEP	1E2		// Distance between coodinates of neighbour points in one dimension
#define PP_N  (PP_NUNBER_OF_LARGE_MASS_POINTS * PP_SPACE_DIMENSION)	// Number of large mass points PD_Y[*]
#define PP_TIME_SLOT 1				// \Delta t (in sec.)        
#define PP_GRAVITATIONAL_CONSTANT 6.67408E-11		// Gravitational Constant
#define PP_VELOSITY 1			// Initial velosity of small mass point PD_X
#define PP_SMALL_MASS 10			// Mass of small mass point PD_X
#define PP_BIG_MASS 1E12			// Mass of bvig mass point PD_Y[*]
//-------------------------- Outpoot Parameters ---------------------------
#define PP_ITER_COUNT 10			
#define PP_OUTPUT_LIMIT 25	// Maximal count of points to output