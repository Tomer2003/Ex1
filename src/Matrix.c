#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"




ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
	*matrix = (PMatrix)malloc(sizeof(Matrix));
	if (*matrix == NULL) {
		return OUT_OF_MEMORY_ERROR;
	}
	(*matrix)->height = height;
	(*matrix)->width = width;
	(*matrix)->matrixArr = (double**)malloc(sizeof(double*) * height);
	if ((*matrix)->matrixArr == NULL) {
		return OUT_OF_MEMORY_ERROR;
	}
	for (uint32_t i = 0; i < height; ++i) {
		(*matrix)->matrixArr[i] = (double*)calloc(width, sizeof(double));
		if ((*matrix)->matrixArr[i] == NULL) {
			return OUT_OF_MEMORY_ERROR;
		}
	}
	return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
	if (matrix) {
		for (uint32_t row = 0; row < matrix->height; ++row) {
			free(matrix->matrixArr[row]);
		}
		free(matrix->matrixArr);
		free(matrix);
	}
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
	ErrorCode matrixCreateCode;
	if (source == NULL) {
		return NULL_ERROR;
	}
	matrixCreateCode = matrix_create(result, source->height, source->width);
	if(matrixCreateCode != ERROR_SUCCESS){
		return matrixCreateCode;
	}
	for (uint32_t row = 0; row < source->height; ++row) {
		for (uint32_t column = 0; column < source->width; ++column) {
			(*result)->matrixArr[row][column] = source->matrixArr[row][column];
		}
	}
	return ERROR_SUCCESS;
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
	if (matrix == NULL) {
		return NULL_ERROR;
	}
	*result = matrix->height;
	return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
	if (matrix == NULL) {
		return NULL_ERROR;
	}
	*result = matrix->width;
	return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value) {
	if (matrix == NULL) {
		return NULL_ERROR;
	}
	if (rowIndex >= matrix->height || colIndex >= matrix->width) {
		return EXCEED_MATRIX_SIZE_ERROR;
	}
	matrix->matrixArr[rowIndex][colIndex] = value;
	return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
	ErrorCode matrixCreateCode;
	if (lhs == NULL || rhs == NULL) {
		return NULL_ERROR;
	}
	if (lhs->height != rhs->height || lhs->width != rhs->width) {
		return MATRIX_ADD_ERROR;
	}
	matrixCreateCode = matrix_create(result, lhs->height, lhs->width);
	if(matrixCreateCode != ERROR_SUCCESS){
		return matrixCreateCode;
	}
	for (uint32_t row = 0; row < lhs->height; ++row) {
		for (uint32_t column = 0; column < lhs->width; ++column) {
			(*result)->matrixArr[row][column] = lhs->matrixArr[row][column] + rhs->matrixArr[row][column];
		}
	}
	return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
	double valueOfCell = 0;
	ErrorCode matrixCreateCode;
	if (lhs == NULL || rhs == NULL) {
		return NULL_ERROR;
	}
	if (lhs->width != rhs->height) {
		return MATRIX_MULT_ERROR;
	}
	matrixCreateCode = matrix_create(result, lhs->height, rhs->width);
	if(matrixCreateCode != ERROR_SUCCESS){
		return matrixCreateCode;
	}
	for (uint32_t rowL = 0; rowL < lhs->height; ++rowL) {
		for (uint32_t columnR = 0; columnR < rhs->width; ++columnR) {
			for (uint32_t i = 0; i < rhs->height; ++i) {
				valueOfCell += lhs->matrixArr[rowL][i] * rhs->matrixArr[i][columnR];
			}
			(*result)->matrixArr[rowL][columnR] = valueOfCell;
		}
	}
	return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
	if (matrix == NULL) {
		return NULL_ERROR;
	}
	for (uint32_t row = 0; row < matrix->height; ++row) {
		for (uint32_t column = 0; column < matrix->width; ++column) {
			matrix->matrixArr[row][column] *= scalar;
		}
	}
	return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value){
	if (matrix == NULL) {
		return NULL_ERROR;
	}
	if (rowIndex >= matrix->height || colIndex >= matrix->width) {
		return EXCEED_MATRIX_SIZE_ERROR;
	}
	*value = matrix->matrixArr[rowIndex][colIndex];
	return ERROR_SUCCESS;
}