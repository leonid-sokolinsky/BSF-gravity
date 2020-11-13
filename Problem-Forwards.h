/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsf-Forwards.h (Problem Function Forwards)
Author: Leonid B. Sokolinsky 
This source code is a part of BSF Skeleton
==============================================================================*/
#include "Problem-bsfTypes.h"	// Predefined Problem Parameters
#include "Problem-Types.h"		// Problem Types

inline double Y_Coordinates(int i, int j);
inline double Y_Mass(int i);
//====================== Macros ================================
#define PF_MIN(x,y) (x<y?x:y)