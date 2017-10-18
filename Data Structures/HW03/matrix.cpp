#include <iostream>
#include "Matrix.h"
#include <fstream>
#include <cmath>
	//Initialize null pointer for empty matrix
	Matrix::Matrix() {
		rows = 0;
		cols = 0;

		data = NULL;
	}

	//Standard constructor
	//pointer **p points to an array of pointers that point to arrays of doubles
	//Loop through matrix to assign fill to every value
	Matrix::Matrix(unsigned int r, unsigned int c, double f) {
		rows = r;
		cols = c;
		fill = f;

		data = new double*[rows];

		for (int i = 0; i < rows; i++) {
			data[i] = new double[cols];}

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				data[i][j] = fill;
			}
		}

		
		}

	//Copies rows, cols, and every index of matrix to be copied
	Matrix::Matrix(const Matrix &m) {
		rows = m.num_rows();
		cols = m.num_cols();
		double n;
		data = new double*[rows];
		for (unsigned int i = 0; i < rows; i++) {
			data[i] = new double[cols];}

		for(unsigned int i = 0; i< rows; i++) {
			for (unsigned int j = 0; j < cols; j++) {
				m.get(i,j,n);
				data[i][j] = n;
			}
		}
	}

	//Loops through each pointer in pointer array to delete contents, 
	//then deletes pointer array itself
	Matrix::~Matrix() {
		for (unsigned int i = 0; i < rows; i++) {
			delete [] data[i];
		}
			delete [] data;
	}

	//Identical to copy constructor
	void Matrix::operator=(const Matrix& m) {
		rows = m.num_rows();
		cols = m.num_cols();
		double n;
		data = new double*[rows];
		for (unsigned int i = 0; i < rows; i++) {
			data[i] = new double[cols];}

		for(unsigned int i = 0; i< rows; i++) {
			for (unsigned int j = 0; j < cols; j++) {
				m.get(i,j,n);
				data[i][j] = n;
			}
		}
	}

	//False (!=) if at least one spot in matrices differ
	bool Matrix::operator==(const Matrix& m) {
		double n;
		if (rows != m.num_rows() || cols != m.num_cols()) {
			return false;
		}
		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < cols; j++) {
				m.get(i,j,n);
				if (data[i][j] != n) {
					return false;}}}
		return true;
	}

	//True (!=) if at least one spot in matrices differ
	bool Matrix::operator!=(const Matrix& m) {
		double n;
		if (rows != m.num_rows() || cols != m.num_cols()) {
			return true;
		}
		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < cols; j++) {
				m.get(i,j,n);
				if (data[i][j] != n) {
					return true;}}}
		return false;
	}

	unsigned int Matrix::num_rows() const {
		return rows;
	}
	unsigned int Matrix::num_cols() const {
		return cols;
	}

	//Delete every row array, set dimensions to 0
	void Matrix::clear() {
		for (unsigned int i = 0; i < rows; i++) {
			delete [] data[i];
		}

		rows = 0;
		cols = 0;
	}

	//Returns value to a double&
	bool Matrix::get(unsigned int i, unsigned int j, double &n) const {
		if (i < rows && j < cols) {
			n =  data[i][j];
			return true;
		}

		return false;

	}
	//Takes in a value and stores it
	bool Matrix::set(unsigned int r, unsigned int c, double n) {
		if (( r < rows) && (c < cols)) {
			data[r][c] = n;
			return true;}
		return false;

	}

	//Loop through matrix and multiply each num by c. O(M*N)
	void Matrix::multiply_by_coefficient(double c) {
		for (unsigned int i = 0; i<rows; i ++) {
			for (unsigned int j = 0; j < cols; j++) {
				data[i][j] *= c;
			}
		}
	}

	//Stores row 1 in temporary array q, puts row 2 into row 1
	//Inserts the row in q into row 2
	//Delete temp array q
	void Matrix::swap_row(unsigned int r1, unsigned int r2) {
		double *q = new double[cols];
		for (unsigned int i = 0; i < cols; i++) {
			q[i] = data[r1][i];
			data[r1][i] = data[r2][i];
			data[r2][i] = q[i];
		}

		delete [] q;

	}
	//Makes new 2D pointer array with rows and cols switched
	//For each number place into new pointer array but
	//switch the rows and cols (i and j)

	void Matrix::transpose() {
		unsigned int tmp = rows;
		rows = cols;
		cols = tmp;

		double **q = new double*[rows];
		for (unsigned int i = 0; i < rows; i++) {
			q[i] = new double[cols];
			for (unsigned int j = 0; j < cols; j++) {
				q[i][j] = data[j][i];
			}
		}

		for (unsigned int i = 0; i< cols; i++) {
			delete [] data[i];
		}
		delete [] data;

		data = q;


	}

	//BINARY MATRIX OPERATIONS

	//IFF Matrices have equal dimensions
	//For every position, add the argument matrix's value
	//to the current matrix's value
	//argument matrix remains unchanged
	bool Matrix::add(const Matrix &m) {
		double n;
		if (rows == m.num_rows() && cols == m.num_cols()) {
			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					m.get(i,j,n);
					data[i][j] += n;
				}
			}
			return true;}
		return false;
	}
	//Same as add()
	bool Matrix::subtract(const Matrix &m) {
		double n;
		if (rows == m.num_rows() && cols == m.num_cols()) {
			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < cols; j++) {
					m.get(i,j,n);
					data[i][j] -= n;
				}
			}
			return true;}
		return false;

	}

	//Store data for a certain row r into an array on the heap
	//Return pointer that points to that array
	double* Matrix::get_row(unsigned int r) {
		double *q = new double[cols];
		for (unsigned int j = 0; j < cols; j++) {
			q[j] = data[r][j];
		}
		return q;
	}
	//Store data for a certain col c into an array on the heap
	//Return pointer that points to that array
	double* Matrix::get_col(unsigned int c) {
		double *q = new double[rows];
		for (unsigned int i = 0; i < rows; i++) {
			q[i] = data[i][c];
		}
		return q;
	}

	
	//Create a new array of 4 matrices on the heap
	//Initialize each Matrix
	//Assign values from each quadrant of the original
	//matrix to respective matrix in the new array
	Matrix* Matrix::quarter() {

		//If there is an odd number of rows or cols, round up
		unsigned int new_rows,new_cols;
		double n = 0;

		float tmp_r = (float)rows/2.0;
		new_rows = ceil(tmp_r);

		float tmp_c = (float)cols/2.0;
		new_cols = ceil(tmp_c);

		//All 4 matrices are the same size
		Matrix* quad = new Matrix[4];
		for (int i = 0; i<4; i++) {
		quad[i] = Matrix(new_rows, new_cols, 0.0);}
		
		//Assign values from original matrix based on which
		//quadrant you are assigning to
		for (unsigned int i = 0; i < new_rows; i++) {
			for (unsigned int j = 0; j < new_cols; j++) {
				get(i,j,n);
				quad[0].set(i,j,n);
			}}
		for (unsigned int i = 0; i < new_rows; i++) {
			for (unsigned int j = 0; j < new_cols; j++) {
				get(i,(cols-new_cols+j), n);
				quad[1].set(i,j,n);}}

		
		for (unsigned int i = 0; i < new_rows; i++) {
			for (unsigned int j= 0; j < new_cols; j++) {
				get((rows-new_rows+i),j, n);
				quad[2].set(i,j,n);	}} 

		
		for (unsigned int j = 0; j < new_rows; j++) {
			for (unsigned int k = 0; k < new_cols; k++) {
				get(rows-new_rows+j,(cols-new_cols+k), n);
				quad[3].set(j,k,n);}}

		return quad;
		
		}
		

		//Decreases or increases Matrix size
		//Makes a new 2D pointer array, q
		//Copy certain values, fill when needed
	void Matrix::resize(unsigned int new_rows, unsigned int new_cols, double f) {
		double** q = new double*[new_rows];
		double n = 0;
		//Dimensions for resized are absolute, no 
		//matter the dimensions of original
		for (unsigned int i = 0; i < new_rows; i++) {
			q[i] = new double[new_cols];
			//If there are still valid rows to copy from original, copy.
			//If there are no more cols to take from original
			//fill rest of row with filler #
			//If original matrix runs out of rows to copy, 
			//fill new rows with filler #
			if (i < rows) {
				for (unsigned int j = 0; j < new_cols; j++) {
				if (j < cols) {
					get(i,j,n);
					q[i][j] = n;
				}
				else { q[i][j] = f;}
			}
			}
			else {
				for (unsigned int j = 0; j < new_cols; j++) {
					q[i][j] = f;}
				}
		
		}
		//Delete original matrix, assign data to new pointer array
		//Change dimensions to dimensions of new matrix
		for (unsigned int i = 0; i < rows; i++) {
			delete [] data[i];
		}
			delete [] data;

		data = q;

		rows = new_rows;
		cols = new_cols;

	}
	//Loop through matrix, print every position
	std::ostream& operator<<(std::ostream& out, const Matrix& m) {
		double n;
		out<<m.num_rows()<<" x "<<m.num_cols()<<" matrix"<<std::endl;
		out<<"[ ";
		for (unsigned int i = 0; i< m.num_rows(); i++) {
			for (unsigned int j = 0; j< m.num_cols(); j++) {
				m.get(i,j,n);
				out<< n <<" ";}
			if (i == m.num_rows() - 1) {
				out<<"]";}

			out<<std::endl;}


		return out;

	}

