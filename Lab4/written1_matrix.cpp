
#include <iostream>
#include <assert.h>
using namespace std;

double * matrix_exp1(double * a, int n, int m);
double * matrix_exp2(double * a, int n, int m);


int main(void) {
  // Tester program for the matrix operations.
  int n;	// matrix dimension (nxn)
  int m;	// exponent

  cout << "Raise an nxn matrix to the mth power." << endl;
  cout << "Enter n: ";
  cin >> n;
  cout << "Enter m: ";
  cin >> m;

  // Initialize a matrix for testing.
  double * test_matrix = new double [n*n];
  // This creates a matrix with 1s on the off-diagonal.
  // As we multiply it, the values will "rotate".
  // However, you don't need to understand what's happening
  // to do the problem.
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if ((i+1)%n == j) test_matrix[i*n+j] = 1;
      else test_matrix[i*n+j] = 0;
    }
  }
  // Uncomment the next line if you want to see the values growing.
  //test_matrix[0] = 2;

  // You might need to adjust this loop to repeat the
  // next call to exponentiate a whole bunch of times to have
  // the runtime be long enough to measure.  Do not include
  // this loop in your asymptotic analysis.

  double * result;
  for (int i=0; i<1000; i++) {
    //result = matrix_exp1(test_matrix,n,m);
    result = matrix_exp2(test_matrix,n,m);
  }

  // Optionally, print result matrix for debugging.
  // Comment this out before timing the execution!
  /*for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cout << result[i*n+j] << "\t";
    }
    cout << endl;
  }*/


  return 0;
}


//
// Returns a newly allocated nxn matrix that is the matrix product of a and b
//
double * matrix_mult(double * a, double * b, int n) {
  double * result = new double[n*n];

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      result[i*n+j] = 0;
      for (int k=0; k<n; k++) {
	result[i*n+j] += a[i*n+k] * b[k*n+j];
      }
    }
  }

  return result;
}

// Raise an nxn matrix to the m power
// -- First algorithm
//
double * matrix_exp1(double * a, int n, int m) {
  assert (m>=0);

  if (m==0) {
    // Create an identity matrix to return.
    double * result = new double[n*n];
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
	if (i==j) result[i*n+j]=1;
	else result[i*n+j]=0;
      }
    }
    return result;
  }

  double * temp = matrix_exp1(a,n,m-1);
  double * result = matrix_mult(a,temp,n);
  delete[] temp;	// Recycle memory we won't need anymore.
  return result;
}


// Raise an nxn matrix to the m power
// -- Second algorithm
//
double * matrix_exp2(double * a, int n, int m) {
  assert (m>=0);

  if (m==0) {
    // Create an identity matrix to return.
    double * result = new double[n*n];
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
	if (i==j) result[i*n+j]=1;
	else result[i*n+j]=0;
      }
    }
    return result;
  }

  double * temp1 = matrix_exp2(a,n,m/2);
  double * temp2;
  if (m%2 == 0) {
    temp2 = matrix_mult(temp1,temp1,n);
    delete[] temp1;
    return temp2;
  } else {
    temp2 = matrix_mult(temp1,temp1,n);
    delete[] temp1;
    temp1 = matrix_mult(a,temp2,n);
    delete[] temp2;
    return temp1;
  }
}