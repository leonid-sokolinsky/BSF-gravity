/*==============================================================================
Project: Bulk Synchronous Farm (BSF)
Theme: BSF Skeleton
Module: Problem-bsfCode.cpp (Problem-dependent Code)
Prefix: PI
Author: Leonid B. Sokolinsky
This source code is a part of BSF Skeleton
==============================================================================*/
#include "Problem-Data.h"			// Problem Types 
#include "Problem-Forwards.h"		// Problem Function Forwards
using namespace std;

//----------------------- Access to BSF-skeleton parameters  -----------------
void PC_bsf_AssignAddressOffset(int value) { PP_BSF_addressOffset = value; };
void PC_bsf_AssignIterCounter(int value) { PP_BSF_iterCounter = value; };
void PC_bsf_AssignJobCase(int value) { PP_BSF_jobCase = value; };
void PC_bsf_AssignMpiRank(int value) { PP_BSF_mpiRank = value; };
void PC_bsf_AssignNumberInSublist(int value) { PP_BSF_numberInSublist = value; };
void PC_bsf_AssignNumOfWorkers(int value) { PP_BSF_numOfWorkers = value; };
void PC_bsf_AssignSublistLength(int value) { PP_BSF_sublistLength = value; };

//----------------------- Predefined problem-dependent functions -----------------
void PC_bsf_Init(bool* success) { // success=false if initialization is unsuccessful
	if (PP_SPACE_DIMENSION != 3) {
		if (PP_BSF_mpiRank == 0) {
			cout << "Error PC_bsf_Init: PP_SPACE_DIMENSION must be equal to 3!" << endl;
		}
		*success = false;
		return;
	}

	PD_X.mass = PP_SMALL_MASS;
	for (int j = 0; j < PP_SPACE_DIMENSION; j++) {
		PD_X.coordinates[j] = 0;
		PD_X.velosity[j] = PP_VELOSITY;
		PD_X.acceleration[j] = 0;
	};

	// Generating PD_Y[*]
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		for (int l = 0; l < PP_NUNBER_OF_LARGE_MASS_POINTS; l++)
			PD_Y[l + j * PP_NUNBER_OF_LARGE_MASS_POINTS].coordinates[j] = (l + 1) * PP_STEP;
	for (int i = 0; i < PP_N; i++)
		PD_Y[i].mass = PP_BIG_MASS;

	return;
}

void PC_bsf_AssignListSize(int* listSize) {
	*listSize = PP_N;
};

void PC_bsf_CopyParameter(PT_bsf_parameter_T* parameterIn, PT_bsf_parameter_T* parameterOut) {
	for (int j = 0; j < PP_SPACE_DIMENSION; j++) {
		parameterOut->coordinates[j] = parameterIn->coordinates[j];
		parameterOut->velosity[j] = parameterIn->velosity[j];
	}
}

void PC_bsf_SetParameter(PT_bsf_parameter_T* parameter) {
	PD_coordinates = parameter->coordinates;
	PD_velosity = parameter->velosity;
}

void PC_bsf_MapF(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T* reduceElem,
	int* success // 1 - reduceElem was produced successfully (default); 0 - otherwise
) {
	double squareOfNorm = 0;
	for (int i = 0; i < PP_SPACE_DIMENSION; i++) {
		double difference;
		difference = PD_Y[mapElem->massPointNo].coordinates[i] - PD_X.coordinates[i];
		squareOfNorm += difference * difference;
	}

	for (int i = 0; i < PP_SPACE_DIMENSION; i++) {
		reduceElem->acceleration[i] = PP_GRAVITATIONAL_CONSTANT * PD_Y[mapElem->massPointNo].mass
			* (PD_Y[mapElem->massPointNo].coordinates[i] - PD_X.coordinates[i]) / squareOfNorm;
	}
}

void PC_bsf_MapF_1(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_1* reduceElem,
	int* success // 1 - reduceElem was produced successfully (default); 0 - otherwise
) {
	// optional filling
};

void PC_bsf_MapF_2(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_2* reduceElem,
	int* success // 1 - reduceElem was produced successfully (default); 0 - otherwise
	) {
	// optional filling
};

void PC_bsf_MapF_3(PT_bsf_mapElem_T* mapElem, PT_bsf_reduceElem_T_3* reduceElem,
	int* success // 1 - reduceElem was produced successfully (default); 0 - otherwise
	) {
	// optional filling
};

void PC_bsf_ReduceF(PT_bsf_reduceElem_T* x, PT_bsf_reduceElem_T* y, PT_bsf_reduceElem_T* z) { // z = x + y
	for (int i = 0; i < PP_SPACE_DIMENSION; i++)
		z->acceleration[i] = x->acceleration[i] + y->acceleration[i];
};

void PC_bsf_ReduceF_1(PT_bsf_reduceElem_T_1* x, PT_bsf_reduceElem_T_1* y, PT_bsf_reduceElem_T_1* z) {
	// optional filling
};

void PC_bsf_ReduceF_2(PT_bsf_reduceElem_T_2* x, PT_bsf_reduceElem_T_2* y, PT_bsf_reduceElem_T_2* z) {
	// optional filling
};

void PC_bsf_ReduceF_3(PT_bsf_reduceElem_T_3* x, PT_bsf_reduceElem_T_3* y, PT_bsf_reduceElem_T_3* z) {
	// optional filling
};

void PC_bsf_ProcessResults(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T* reduceResult,
	int reduceCounter, // Number of successfully produced Elrments of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* newJobCase
) {
	static int counter = 0;	// Iteration Counter
	counter++;
	if (counter < PP_ITER_COUNT)
		*exit = false;
	else
		*exit = true;

	for (int i = 0; i < PP_SPACE_DIMENSION; i++) {
		parameter->velosity[i] = parameter->velosity[i] + reduceResult->acceleration[i] * PP_TIME_SLOT;
		parameter->coordinates[i] = parameter->coordinates[i] + parameter->velosity[i] * PP_TIME_SLOT;
	}
};

void PC_bsf_ProcessResults_1(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T_1* reduceResult,
	int reduceCounter, // Number of successfully produced Elrments of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* newJobCase
) {
	// optional filling
};

void PC_bsf_ProcessResults_2(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T_2* reduceResult,
	int reduceCounter, // Number of successfully produced Elrments of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* newJobCase
	) {
	// optional filling
};

void PC_bsf_ProcessResults_3(
	bool* exit, // "true" if Stopping Criterion is satisfied, and "false" otherwise
	PT_bsf_reduceElem_T_3* reduceResult,
	int reduceCounter, // Number of successfully produced Elrments of Reduce List
	PT_bsf_parameter_T* parameter, // Current Approximation
	int* newJobCase
	) {
	// optional filling
};

void PC_bsf_ParametersOutput(int numOfWorkers, PT_bsf_parameter_T parameter) {
	cout << "=================================================== Jacobi M ====================================================" << endl;
	cout << "Number of Workers: " << numOfWorkers << endl;
#ifdef PP_BSF_OMP
#ifdef PP_BSF_NUM_THREADS
	cout << "Number of Threads: " << PP_BSF_NUM_THREADS << endl;
#else
	cout << "Number of Threads: " << omp_get_num_procs() << endl;
#endif // PP_BSF_NUM_THREADS
#else
	cout << "OpenMP is turned off!" << endl;
#endif // PP_BSF_OMP
	cout << "===================================== BSF-Gravity =====================================" << endl;
	cout << "Number of workers: " << numOfWorkers << endl;
	cout << "Number of large mass points: " << PP_N << endl;
	cout << "---------- X mass point -----------" << endl;
	cout << "Initial coordinates:\t";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.coordinates[j] << "\t";
	cout << endl;
	cout << "Initial velosity:\t";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.velosity[j] << "\t";
	cout << endl;
	cout << "Mass:\t" << PD_X.mass << endl;

	cout << "---------- Y mass points -----------" << endl;
	for (int i = 0; i < PF_MIN(PP_OUTPUT_LIMIT, PP_N); i++) {
		cout << "PD_Y[" << i << "].coordinates:\t";
		for (int j = 0; j < PP_SPACE_DIMENSION; j++)
			cout << PD_Y[i].coordinates[j] << "\t";
		cout << "\tmass:\t" << PD_Y[i].mass << endl;
	};
	cout << (PP_OUTPUT_LIMIT < PP_N ? "..." : "") << endl;
	/**/
	cout << "___________________________________________________________________________" << endl;
};

void PC_bsf_IterOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {
	cout << "------------------ " << PP_BSF_iterCounter << " ------------------" << endl;
	cout << "Coordinates:\t";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.coordinates[j] << "\t";
	cout << endl;
	cout << "Velosity: ";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.velosity[j] << "\t";
	cout << endl;
}

void PC_bsf_IterOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {
	cout << "------------------ " << PP_BSF_iterCounter << " ------------------" << endl;
	// optional filling

};

void PC_bsf_IterOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {
	cout << "------------------ " << PP_BSF_iterCounter << " ------------------" << endl;
	// optional filling

};

void PC_bsf_IterOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double elapsedTime, int jobCase) {
	cout << "------------------ " << PP_BSF_iterCounter << " ------------------" << endl;
	// optional filling

};

void PC_bsf_ProblemOutput(PT_bsf_reduceElem_T* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {// Output Function
	cout << "============ Stop point ===============" << endl;
	cout << "Coordinates:\t";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.coordinates[j] << "\t";
	cout << endl;
	cout << "Velosity: ";
	for (int j = 0; j < PP_SPACE_DIMENSION; j++)
		cout << parameter.velosity[j] << "\t";
	cout << endl;
	cout << "Runtime = " << t << endl;
};

void PC_bsf_ProblemOutput_1(PT_bsf_reduceElem_T_1* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {// Output Function
	// optional filling
};

void PC_bsf_ProblemOutput_2(PT_bsf_reduceElem_T_2* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {// Output Function
	// optional filling
};

void PC_bsf_ProblemOutput_3(PT_bsf_reduceElem_T_3* reduceResult, int reduceCounter, PT_bsf_parameter_T parameter,
	double t) {// Output Function
	// optional filling
};

void PC_bsf_SetInitParameter(PT_bsf_parameter_T* parameter) {
	for (int j = 0; j < PP_SPACE_DIMENSION; j++) {
		parameter->coordinates[j] = PD_X.coordinates[j];
		parameter->velosity[j] = PD_X.velosity[j];
	};
};

void PC_bsf_SetMapSubList(PT_bsf_mapElem_T* sublist, int sublistLength, int offset, bool* success) {
	for (int j = 0; j < sublistLength; j++)
		sublist[j].massPointNo = j + offset;
};

//----------------------------- User functions -----------------------------
