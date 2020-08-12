#include "ErrorCode.h"
#include <stdbool.h>
#include <string.h>

bool error_isSuccess(ErrorCode code) {
	return ERROR_SUCCESS == code;
}

const char* error_getErrorMessage(ErrorCode code) {
	switch (code) {
	case ERROR_SUCCESS:
		return "The operation completed successfully";
	case SET_VALUE_ERROR:
		return "ERROR: The column or row index given exceed the matrix boundaries or negative(in matrix_setValue function)!";
	case MATRIX_ADD_ERROR:
		return "ERROR: The matrix sizes are not equal and therefore it is not possible to perform an add operation(in matrix_add function)!";
	case MATRIX_MULT_ERROR:
		return "ERROR: The number of rows in the left matrix is not equal to the number of columns in the right matrix and therefore it is not possible to perform a multiplication operation(in matrix_multiplyMatrices function)!";
	case NULL_ERROR:
		return "ERROR: The matrix that given is null!";
	case OUT_OF_MEMORY_ERROR:
		return "ERROR: Allocation memory failed(in matrix_create function)!";
	default:
		return "Unexpected error";
	}
}