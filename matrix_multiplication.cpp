// Operating Systems - CS444/544
// Spring 2023
// Your Name
// Assignment Info
// Program Description: Parallel Matrix Multiplication using Pthreads
// Last Modified: 2023-02-11
// YouTube Code Review & Demo link

#include<iostream>
#include<pthread.h>
#include<cstdlib>

const int MAX_THREADS = 1024;

// Global Variables
int m1_rows, m1_cols, m2_rows, m2_cols;
int matrix1[1024][1024];
int matrix2[1024][1024];
int result[1024][1024];

void *matrix_mult(void *threadid) {
   long tid;
   tid = (long)threadid;
   int sum = 0;

   for (int j = 0; j < m2_cols; j++) {
      sum = 0;
      for (int k = 0; k < m1_cols; k++) {
         sum += matrix1[tid][k] * matrix2[k][j];
      }
      result[tid][j] = sum;
   }
   pthread_exit(NULL);
}

int main() {
   std::cout << "Enter the number of rows in matrix 1: ";
   std::cin >> m1_rows;
   std::cout << "Enter the number of columns in matrix 1: ";
   std::cin >> m1_cols;
   std::cout << "Enter the number of rows in matrix 2: ";
   std::cin >> m2_rows;
   std::cout << "Enter the number of columns in matrix 2: ";
   std::cin >> m2_cols;

   // Verify that matrix multiplication is possible
   if (m1_cols != m2_rows) {
      std::cout << "Error: Cannot perform matrix multiplication" << std::endl;
      return 1;
   }

   // Fill matrices with random numbers
   for (int i = 0; i < m1_rows; i++) {
      for (int j = 0; j < m1_cols; j++) {
         matrix1[i][j] = rand() % 10;
      }
   }
   for (int i = 0; i < m2_rows; i++) {
      for (int j = 0; j < m2_cols; j++) {
         matrix2[i][j] = rand() % 10;
      }
   }

   // Print matrices
   std::cout << "Matrix 1: " << std::endl;
   for (int i = 0; i < m1_rows; i++) {
      for (int j = 0; j < m1_cols; j++) {
         std::cout << matrix1[i][j] << " ";
      }
      std::cout << std::endl;
   }
   std::cout << "Matrix 2: " << std::endl;
   for (int i = 0; i < m2_rows; i++) {
      for (int j = 0; j < m2_cols; j++) {
    std::cout << matrix2[i][j] << " ";
}
    std::cout << std::endl;
}

    pthread_t threads[MAX_THREADS];
    int rc;
    long t;
    for (t = 0; t < m1_rows; t++) {
    rc = pthread_create(&threads[t], NULL, matrix_mult, (void *)t);
    if (rc) {
    std::cout << "Error: Unable to create thread, " << rc << std::endl;
    exit(-1);
    }
    }

    // Join all threads
    for (t = 0; t < m1_rows; t++) {
    pthread_join(threads[t], NULL);
    }

    // Print result matrix
    std::cout << "Result matrix: " << std::endl;
    for (int i = 0; i < m1_rows; i++) {
    for (int j = 0; j < m2_cols; j++) {
    std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
    }

    pthread_exit(NULL);
    return 0;
    }