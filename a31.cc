

#include <iostream>
#include <iomanip>
#include "matrix.h"
using std::endl;
/// can't change public interface
/// look for the guards thing we gotta do


// Requires numRows >= 0 && numCols >= 0.   (in the test harness taken care of?)
// If both dimensions are 0, then array pointer is set to nullptr.
// If only one dimension is 0, also treat as 0x0 matrix; otherwise,
// allocate space and set values in 2-D array to 0--fill later using
// either operator>> or set().
Matrix::Matrix( int numRows, int numCols ) : numCols{numCols}, numRows{numRows} {
        arr = (!numRows || !numCols) ? nullptr : new int*[numRows];
        if (arr) {
                for (int i = 0; i < numRows; i++) {
                        arr[i] = new int[numCols];
                        for (int j = 0; j < numCols; j++) {
                                arr[i][j] = 0;
                        }
                }
        }
}

// copy constructor
Matrix::Matrix( const Matrix &n ) : numRows {n.numRows}, numCols {n.numCols},
        arr {n.arr ? new int*[numRows] : nullptr} {
        if (n.arr) {
                for (int i = 0; i < numRows; i++) {
                        arr[i] = new int[numCols];
                        for (int j = 0; j < numCols; j++) {
                                arr[i][j] = n.arr[i][j];
                        }
                }

        }
}


// destructor
Matrix::~Matrix(){
        for (int i = 0; i < numRows; i++) {
                delete [] arr[i];
        }
        delete [] arr;
}
////////////////////////////////////////////////////
// SO FAR LOOKING AITE
////////////////////////////////////////////////////

// copy assignment operator
Matrix & Matrix::operator=( const Matrix &other ){
        if (this == &other) return *this;
        for (int i = 0; i < numRows; i++) {
                delete [] arr[i];
        }
        //delete arr;
        numRows = other.numRows;
        numCols = other.numCols;
        // resize arr
        arr = other.arr ? new int*[numRows] : nullptr;
        if (arr) {
                for (int i = 0; i < numRows; i++) {
                        arr[i] = new int[numCols];
                        for (int j = 0; j < numCols; j++) {
                                arr[i][j] = other.arr[i][j];
                        }
                }
        }
        return *this;
}

// move constructor
// test with s2{ [[1,2], [2,3], [4,5]] };
Matrix::Matrix( Matrix && other) {

        for (int i = 0; i< numRows; i++) {
                delete [] arr[i];
        }
        std::swap(numRows, other.numRows);
        std::swap(numCols, other.numCols);
        arr = ( other.arr && numRows && numCols ) ? new int*[numRows] : nullptr;
        if (arr) {
                for (int i = 0; i < numRows; i++) {
                        std::swap(arr[i], other.arr[i]);
                }
        }
        delete [] other.arr;
        other.arr = nullptr;
        other.numCols = 0;
        other.numRows = 0;
}

// move assignment operator
Matrix & Matrix::operator=( Matrix && other){
        for (int i = 0; i< numRows; i++) {
                delete [] arr[i];
        }
        delete [] arr;
        std::swap(numCols, other.numCols);
        std::swap(numRows, other.numRows);
        // resize !!!
        arr = (other.arr && numCols && numRows ) ? new int*[numRows] : nullptr;
        if (arr) {
                for (int i = 0; i < numRows; i++) {
                        //arr[i] = new int[numCols];
                        std::swap(arr[i], other.arr[i]);
                }
        }
        delete [] other.arr;
        other.arr = nullptr;
        other.numCols = 0;
        other.numRows = 0;
        return *this;
}

// add two matrices (dimensions must be equal tho?)
Matrix Matrix::operator+( const Matrix & other) const {
        Matrix result{numRows, numCols};
        for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                        result.arr[i][j] = arr[i][j] + other.arr[i][j];
                }
        }
        return result;
}
Matrix Matrix::operator*( const Matrix & rhs) const {    // multiply two matrices
        Matrix result{numRows, rhs.numCols};
        for (int i=0; i<result.numRows; i++) {
                for (int j=0; j < result.numCols; j++) {
                        for(int k = 0; k < result.numCols; ++k) {
                                result.arr[i][j] += arr[i][k] * rhs.arr[k][j];
                        }
                }
        }
        return result;
}


// returns the number of rows in the matrix
int Matrix::rows() const {
        if ( !arr) return 0;
        return numRows;
}
// returns the number of columns in the matrix
int Matrix::cols() const {
        if ( !arr) return 0;
        return numCols;
}
// Requires 0 <= row < this->rows() && 0 <= col < this->cols()
// Sets this's [row][col] = value
void Matrix::set( int row, int col, int value ) {
        arr[row][col] = value;
}

// Requires 0 <= row < this->rows() && 0 <= col < this->cols()
// Returns this's [row][col]
int Matrix::get( int row, int col ) const {
        return arr[row][col];
}


// Reads in the number of rows, the number of columns, and then the values from
// standard input.
std::istream & operator>>( std::istream &in, Matrix &m) {
        int rows, cols;
        in >> rows;
        in >> cols;
        m = Matrix {rows, cols}; // resize // should already initialize all to 0
        for (int i = 0; i< m.rows(); i++) {
                for (int j = 0; j< m.cols(); j++) {
                        int value;
                        if (!(in >> value)) {
                                if (in.eof()) return in; // don't even bother
                                in.clear();
                                in.ignore();
                                return in;
                        } else {
                                m.set(i, j, value);
                        }
                }
        }
        return in;
}

// Prints the contents of the Matrix
std::ostream & operator<<( std::ostream & out, const Matrix &m ) {
        if (!m.rows() || !m.cols()) {
                //out<< m.rows() << "by" << m.cols()<< endl;
                out << "[]";
                return out;
        }
        for (int i = 0; i< m.rows(); i++) {
                for (int j = 0; j< m.cols(); j++) {
                        out << std::setw(4) << m.get(i,j) << " ";
                }
                out << endl;
        }
        return out;
}
