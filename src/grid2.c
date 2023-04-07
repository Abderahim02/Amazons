#include <gsl/gsl_spmatrix.h>
#include <stdio.h>

void print_sparse_matrix(gsl_spmatrix_uint *mat) {
    printf("Sparse matrix:\n");
    printf("size1 = %zu, size2 = %zu, nz = %zu\n", mat->size1, mat->size2, mat->nz);

    for (size_t i = 0; i < mat->size1; i++) {
        for (gsl_spmatrix_uint_const_iter row_iter = gsl_spmatrix_uint_const_row_iterator(mat, i); 
             !gsl_spmatrix_uint_iter_end(row_iter); 
             gsl_spmatrix_uint_const_iter_next(row_iter)) {
            size_t j = gsl_spmatrix_uint_iter_col(row_iter);
            unsigned int val = gsl_spmatrix_uint_iter_get(row_iter);
            printf("(%zu, %zu) = %u\n", i, j, val);
        }
    }
}

int main() {
    // Create a 3x3 sparse matrix
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(3, 3);
    gsl_spmatrix_uint_set(mat, 0, 1, 2);
    gsl_spmatrix_uint_set(mat, 1, 0, 1);
    gsl_spmatrix_uint_set(mat, 2, 2, 3);

    // Print the matrix
    print_sparse_matrix(mat);

    // Free the matrix memory
    gsl_spmatrix_uint_free(mat);
    return 0;
}

// This code defines a print_sparse_matrix function that takes a pointer to a gsl_spmatrix_uint struct and prints the matrix size and the non-zero elements in the matrix. It uses the gsl_spmatrix_uint_const_row_iterator function to iterate over the rows of the matrix and the gsl_spmatrix_uint_iter_col and gsl_spmatrix_uint_iter_get functions to get the column index and value of each non-zero element in the row.

// In the main function, a sparse matrix is created with three non-zero elements, and the print_sparse_matrix function is called to print the matrix. Finally, the memory allocated for the matrix is freed using the gsl_spmatrix_uint_free function.
// Moussa Al
// what is a sprase matrix

// A sparse matrix is a type of matrix in which most of the elements are zero. In contrast, a dense matrix has a significant number of non-zero elements. The sparsity of a matrix is defined as the ratio of the number of zero elements to the total number of elements in the matrix.

// Sparse matrices often arise in scientific and engineering applications, such as finite element analysis, network analysis, and linear programming. In many cases, the matrices involved are too large to be stored efficiently in memory, so it is essential to exploit their sparsity to reduce storage requirements and computation time.

// One way to represent a sparse matrix is to store only its non-zero elements and their locations in memory. There are several different data structures that can be used to represent sparse matrices, such as coordinate format (COO), compressed sparse row (CSR), and compressed sparse column (CSC). Each of these data structures has its advantages and disadvantages, depending on the particular application and access patterns.
