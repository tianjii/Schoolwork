class Matrix{
public:
	Matrix();
	Matrix(unsigned int r, unsigned int c, double f);
	Matrix(const Matrix &m);
	~Matrix();
	void operator=(const Matrix& m);
	bool operator==(const Matrix& m);
	bool operator!=(const Matrix& m);
	unsigned int num_rows() const;
	unsigned int num_cols() const;
	void clear();
	bool get(unsigned int i, unsigned int j, double &n) const;
	bool set(unsigned int r, unsigned int c, double n);
	void multiply_by_coefficient(double c);
	void swap_row(unsigned int r1, unsigned int r2);
	void transpose();
	bool add(const Matrix &m);
	bool subtract(const Matrix &m);
	double* get_row(unsigned int r);
	double* get_col(unsigned int c);
	void returndata();
	void printnum(unsigned int i, unsigned int j);
	Matrix* quarter();
	void resize(unsigned int new_rows, unsigned int new_cols, double f);

private:
	unsigned int rows;
	unsigned int cols;
	double fill;
	double** data;

};

std::ostream& operator<<(std::ostream& out, const Matrix& m);