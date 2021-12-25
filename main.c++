// C++ program to find adjoint and inverse and determinan of a matrix and finally solve an equation system
#include<bits/stdc++.h>
using namespace std;

using two_d_vector = std::vector<std::vector<double>>;

class Matrix {
    public:

        Matrix(std::vector<std::vector<double>> _new_matrix) {
             _size = _new_matrix.size();
            _matrix = _new_matrix;
        };

        Matrix(int row_size , int col_size) {
            _matrix.resize(row_size);
            _size = row_size;
            for (size_t i = 0; i < row_size; i++)
            {
                _matrix[i].resize(col_size);
            }
        }

        Matrix(int size) {
            _matrix.resize(size);
            for (size_t i = 0; i < size; i++)
            {
                _matrix[i].resize(size);
            }
        }

        Matrix(std::vector<double> vec , int is_col = 1) {

            if(is_col)
            {
                _matrix.resize(vec.size());
                _size = vec.size();
                for (size_t i = 0; i < vec.size(); i++)
                {
                    _matrix[i].resize(1);
                    _matrix[i][0] = vec[i];
                }
            } else {
                _matrix.resize(1);
                _matrix[0] = vec;
            }

        };

        std::vector<double> operator[](int i) const {return _matrix[i];}
        std::vector<double>& operator[](int i) {return _matrix[i];}
        two_d_vector value() { return _matrix;}

        static void print(Matrix matrix) {
            for (size_t i = 0; i < matrix.size(); i++)
              {
                for (size_t j = 0; j < matrix[i].size(); j++)
                  {
                    std::cout<<matrix[i][j]<<" ";
                  }
                std::cout<<"\n";
             }
        };

        static Matrix submatrix(Matrix matrix , int deleted_row , int deleted_col) {
            
            int i = 0 ,j = 0;

            int row_size = matrix.size();
            int col_size = matrix[0].size();

            Matrix temp = Matrix( row_size-1, col_size-1 );

            for (size_t row = 0; row < row_size ; row++)
            {
                for (size_t col = 0; col < col_size ; col++)
                {
                    if(row != deleted_row && col != deleted_col) {

                        temp[i][j++] = matrix[row][col];

                        if(j == col_size-1) {
                            j = 0;
                            i++;
                        }

                    };
                    
                }
            }

            return temp;

        };

        
        static int det(Matrix matrix) {

          int determinan = 0;
          int sign = 1;

          if(matrix.size() == 1)
           return matrix[0][0];

          if(matrix.size() == 2 && matrix[0].size() == 2 )
           return ( (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]) );

           for (size_t i = 0; i < matrix[0].size(); i++)
            {
             Matrix temp = Matrix::submatrix(matrix , 0 ,i);
             determinan += (sign * matrix[0][i] * det(temp));
             sign = -sign;
            }
    
            return determinan;

        };

        static Matrix adj(Matrix matrix) {

            int sign = 0;

            Matrix temp1 = Matrix(matrix.size() , matrix[0].size());

            for (size_t row = 0; row < matrix.size(); row++)
            {
                for (size_t col = 0; col < matrix[0].size(); col++)
                {
                    sign = (row+1+col+1)%2 == 0 ? 1 : -1;
                    temp1[row][col] = sign*det(submatrix(matrix,row,col));
                }
            }

            Matrix temp2 = Matrix(matrix[0].size() , matrix.size());

            for (size_t row = 0; row < matrix.size(); row++)
            {
                for (size_t col = 0; col < matrix[0].size(); col++)
                {
                    temp2[col][row] = temp1[row][col];
                }
            }

            return temp2;
            

        };

        static Matrix inverse(Matrix matrix) {
            return adj(matrix)/det(matrix);
        }

        Matrix operator= (Matrix& _matrix_b) { 
            _matrix = _matrix_b.value();
        }; 

        Matrix operator* (int value) {

            Matrix temp = Matrix((*this)); 

            for (size_t row = 0; row < temp.size() ; row++)
            {
                for (size_t col = 0; col < temp[0].size(); col++)
                {
                    temp[row][col] *= value;
                }
                
            }

            return temp;
            
        }

        Matrix operator/ (int value) {
            
            Matrix temp = Matrix((*this)); 

            for (size_t row = 0; row < temp.size() ; row++)
            {
                for (size_t col = 0; col < temp[0].size(); col++)
                {
                    temp[row][col] /= value;
                }
                
            }

            return temp;
            
        }

        //i didn't overload the += and /= signs beacuse i am lazy

        
        Matrix operator* (Matrix& _matrix_b) {

            Matrix temp = Matrix(_size , _matrix_b[0].size());

            for (int row1 = 0; row1 < _matrix.size(); row1++) {
                for (int col2 = 0; col2 < _matrix_b[0].size(); col2++) {
                 for (int k = 0; k < _matrix_b.size(); k++) {
                   temp[row1][col2] += _matrix[row1][k] * _matrix_b[k][col2];
                 }
               }
            }
            return temp;
        }

        int size() {return _size;}

    private:
         two_d_vector _matrix;
         int _size = 0;
};

int main()
{

    Matrix matrix1 = Matrix({
        {1,2,3},
        {4,5,6},
    });

    Matrix matrix2 = Matrix({
        {10,11},
        {20,21},
        {30,31}
    });

    vector<double> vec = {10,12,15,19};

    Matrix matrix3 = Matrix(vec);

    Matrix::print(matrix1 * matrix2);

	return 0;
}
