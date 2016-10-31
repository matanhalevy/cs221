#include <iostream>
#include <ctime>   // for timing
#include <cstdlib> // for atoi

// Straightforward and direct implementation of the mathematical
// definition of the fibonacci sequence.
//
// This takes rapidly increasing time to run as n gets larger.  Why?

unsigned long long fib(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    else {
        return fib(n-1) + fib(n-2);
    }
}




// See below for a description of the data structure we wanted.  We
// actually "implemented" it with an array and code spread across
// several functions.  This is a dangerous way to implement a data
// structure, since small changes in one place can have unpredictable
// results in another!


// Briefly: We wanted a data structure to remember fib values
// associated with their number in the sequence (their index).  Access
// the values should be quick and reliable, given the index.

int const SIZE = 100000000;
unsigned long long ANSWERS[SIZE];

// We decided to remember old results so we wouldn't need to
// recalculate them.  Describing the algorithm to do that naturally
// required describing a data structure with various capabilities.  By
// the time we were done, we'd described a "dictionary" or "map" data
// structure that could check if a key ("index") is present and find
// and set the value associated with a key.
//
// The resulting algorithm was TREMENDOUSLY faster than the original
// version.
unsigned long long memoized_fib(int n) {
    // Go to the nth position (index) in the data structure and..
    // check if there's a value there.
    // If there is: retrieve the value and return it.
    // If there is not: do the stuff below and store it in the data
    // structure at the nth index.
    
    // We're using 0 to mean "no value calculated yet".  (Not -1 anymore
    // because I changed the ints to unsigned long long values, which
    // are 64 bits on my machine and unsigned (i.e., don't "waste a bit"
    // on negative values).)
    if (ANSWERS[n] > 0) {
        // There's a value in ANSWERS[n].
        return ANSWERS[n];
    }
    else {
        // We have not yet calculated the nth fib number.
        unsigned long long result;
        if (n == 1 || n == 2) {
            result = 1;
        }
        else {
            result = memoized_fib(n-1) + memoized_fib(n-2);
        }
        ANSWERS[n] = result;
        return result;
    }
}

// Calculate the nth Fibonacci number using a "dynamic programming"
// approach.  We've now modified our algorithm to proceed in a
// "bottom-up" fashion.  We can still think of it as working through
// the tree we drew in class, but now it computes those nodes in an
// order that guarantees each value is available (already calculated)
// when it is needed and that only two "old" values are ever needed to
// calculate the next value.  As a result, we now get the performance
// of the memoized solution but without significant memory cost!
unsigned long long dp_fib(int n) {
    unsigned long long answer=0;
    unsigned long long answerminus1 = 1;
    unsigned long long answerminus2 = 1;
    for (int i = 3; i <= n; i++) {
        answer = answerminus1 + answerminus2;
        answerminus2 = answerminus1;
        answerminus1 = answer;
    }
    return answer;
}

// This is Fibonacci using matrix exponentiation and iterative squaring.
// Note that I am writing this with poor style, putting everything into
// a single, big function, with hardwired constants.  This is just to make
// it easier for you to see that nothing magical is happening in the code.
// In real life, you should use a standard matrix or linear-algebra library.
unsigned long long  matrix_fib(int n) {
    if (n==1) return 1;
    if (n==2) return 1;
    
    // The above two lines handle the n=1 and n=2 cases.
    // For larger n, we raise a special matrix to the (n-2)th power.
    // (The n-2 is because each matrix multiplication computes the
    // next Fibonacci number, and we've done the first 2 already.)
    
    unsigned long long exponent = n-2;
    unsigned long long result[2][2] = {1, 0, 0, 1}; // The identity matrix
    unsigned long long fibstep[2][2] = {1, 1, 1, 0}; // The special Fibonacci matrix
    unsigned long long temp[2][2];
    // This is matrix exponentiation via iterative squaring, as explained in class
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            // This is a 2x2 matrix multiplication, written out explicitly.
            // As mentioned, this is bad programming style (This should be
            // a method in a separate class, if you were writing your own,
            // or in real life, you should use a standard matrix library.)
            // but I want you to be able to see all the code at once.
            for (int i=0; i<2; i++) {
                for (int j=0; j<2; j++) {
                    temp[i][j] = 0;
                    for (int k=0; k<2; k++) {
                        temp[i][j] += fibstep[i][k]*result[k][j];
                    }
                }
            }
            // Copy result back into result
            for (int i=0; i<2; i++) {
                for (int j=0; j<2; j++) {
                    result[i][j] = temp[i][j];
                }
            }
        }
        exponent /= 2;
        // Another matrix multiplication written out.
        // This one is squaring the fibstep matrix.
        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                temp[i][j] = 0;
                for (int k=0; k<2; k++) {
                    temp[i][j] += fibstep[i][k]*fibstep[k][j];
                }
            }
        }
        // Copy result back into fibstep
        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                fibstep[i][j] = temp[i][j];
            }
        }
    }
    
    // And now, the nth Fibonacci number is just the sum of the first row
    // of the matrix...
    return result[0][0]+result[0][1];
}




void usage(int argc, char * argv[]) {
    std::cout << argv[0] << " [n]" << std::endl;
    std::cout << "\tCalculates fib(n) for positive ints n." << std::endl;
}

int main() {
    int n;
    std::cout << "Which element in the Fibonacci sequence would you like to compute? ";
    std::cin >> n;
    std::cout << std::endl<< std::endl;
    if (n > SIZE) {
        std::cout << "Uh-oh; we didn't allocate enough space." << std::endl;
    }
    
    
    // We'll say "0 means nothing there"
    for (int i = 0; i <= n; i++) {
        ANSWERS[i] = 0;
    }
    std::clock_t begin;
    std::clock_t end;
    double elapsed_secs;
    
    begin = std::clock();
    std::cout << "Plain, recursive fib(" << n << ") =\t" << fib(n);
    end = std::clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< " computed in " << elapsed_secs << " seconds."<< std::endl;
    
    begin = std::clock();
    std::cout << "Memoized recursive fib(" << n << ") =\t" << memoized_fib(n);
    end = std::clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< " computed in " << elapsed_secs << " seconds."<< std::endl;
    
    begin = std::clock();
    std::cout << "Dynamic programming fib(" << n << ") =\t" << dp_fib(n);
    end = std::clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< " computed in " << elapsed_secs << " seconds."<< std::endl;
    
    
    begin = std::clock();
    std::cout << "Matrix Multiplication fib(" << n << ") =\t" << matrix_fib(n);
    end = std::clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout<< " computed in " << elapsed_secs << " seconds."<< std::endl;
    
}




