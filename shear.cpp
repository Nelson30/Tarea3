/**
 * LEAD University
 * Data Science Program
 * BCD-9218: Parallel and Distributed Computing
 * Instructor Diego Jimenez, Eng. (diego.jimenez@ulead.ac.cr)
 *  OpenMP parallel shear sort.
 */

#include <cstdio>
#include <cstdlib>
// #include <omp.h>
#include <math.h>
#include "timer.h"
#include "io.h"
#include "/usr/local/opt/libomp/include/omp.h"
#include <vector>

#define MAX_VALUE 10000


// Shear sort function
void shear_sort(int **A, int M){
	// YOUR CODE GOES HERE

    int pasos, temp, temp2, temp3, i, j, f, p, min, max, max2, row, col;
    pasos = log(M);
    for (i=1; i <= pasos; i++) {
        for (row = 0; row < M-1; row++){
            if (row % 2 == 0){
                for(col=0;col < M-1;col++) {
                    min = col;
                    for (j = col + 1; j < M-1; j++) {
                        if (A[row][j] < A[row][min]) {
                            min = j;
                        }
                        temp = A[row][col];
                        A[row][col] = A[row][min];
                        A[row][min] = temp;
                    }
                }
            } else {
                for(col=0;col < M-1;col++) {
                    max = col;
                    for (p = col + 1; p < M-1; j++) {
                        if (A[row][p] > A[row][max]) {
                            min = p;
                        }
                        temp2 = A[row][col];
                        A[row][col] = A[row][max];
                        A[row][max] = temp2;
                    }
                }

            }
        }
        for (col = 0; col < M-1; col++) {
            for (col = 0; col < M - 1; col++) {
                max2 = row;
                for (f = row + 1; f < M - 1; f++) {
                    if (A[f][col] < A[col][max2]) {
                        max2 = f;
                    }
                    temp3 = A[row][col];
                    A[row][col] = A[row][max2];
                    A[row][max2] = temp3;
                }
            }
        }
    }

}





// Main method
int main(int argc, char* argv[]) {
	int N, M;
	int **A;
	double elapsedTime;

	// checking parameters
	if (argc != 2 && argc != 3) {
		cout << "Parameters: <N> [<file>]" << endl;
		return 1;
	}
	N = atoi(argv[1]);
	M = (int) sqrt(N);
	if(N != M*M){
		cout << "N has to be a perfect square!" << endl;
		exit(1);
	}

	// allocating matrix A
	A = new int*[M];
	for (int i=0; i<M; i++){
		A[i] = new int[M];
	}

    shear_sort(A, M);

	// reading files (optional)
	if(argc == 3){
		readMatrixFile(A,M,argv[2]);
	} else {
		srand48(time(NULL));
		for(int i=0; i<M; i++){
			for(int j=0; j<M; j++){
				A[i][j] = lrand48() % MAX_VALUE;
			}
		}
	}

	// starting timer
	timerStart();

	// calling shear sort function
	shear_sort(A,M);

	// testing the results is correct
	if(argc == 3){
		printMatrix(A,M);
	}

	// stopping timer
	elapsedTime = timerStop();

	cout << "Duration: " << elapsedTime << " seconds" << std::endl;

	// releasing memory
	for (int i=0; i<M; i++) {
		delete [] A[i];
	}
	delete [] A;

	return 0;
}
