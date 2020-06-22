//
// Created by David on 11/06/2020.
//

#include "IntMatrix.h"
#include "Auxiliaries.h"

namespace mtm
{
    IntMatrix::IntMatrix(const Dimensions dims, const int value) : dimensions(dims)
    {
        this->build2DArray();
        this->initialize2DArray(value);
    }

    IntMatrix::IntMatrix(const IntMatrix& to_copy) : dimensions(to_copy.dimensions)
    {
        this->build2DArray();
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                data[i][j] = to_copy.data[i][j];
            }
        }
    }

    IntMatrix::~IntMatrix()
    {
        this->deleteData();
    }

    IntMatrix IntMatrix::operator=(const IntMatrix& to_assign)
    {
        if(this == &to_assign)
        {
            return *this;
        }

        if(this->dimensions != to_assign.dimensions)
        {
            this->deleteData();
            this->dimensions = to_assign.dimensions;
            this->build2DArray();
        }

        for(int i = 0; i < this->dimensions.getRow(); i++)
        {
            for(int j = 0; j < this->dimensions.getCol(); j++)
            {
                this->data[i][j] = to_assign.data[i][j];
            }
        }
        return *this;
    }

    IntMatrix IntMatrix::Identity(const int dimension)
    {
        IntMatrix identity(Dimensions(dimension, dimension));
        for(int i = 0; i < dimension; i++)
        {
            identity.data[i][i] = 1;
        }
        return identity;
    }

    IntMatrix IntMatrix::transpose() const
    {
        IntMatrix transposed(Dimensions(this->dimensions.getCol(), this->dimensions.getRow()));
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                transposed.data[j][i] = this->data[i][j];
            }
        }
        return transposed;
    }



    IntMatrix& IntMatrix::operator+=(const IntMatrix& matrix)
    {
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                this->data[i][j] += matrix.data[i][j];
            }
        }
        return *this;
    }

    IntMatrix& IntMatrix::operator+=(const int num)
    {
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                this->data[i][j] += num;
            }
        }
        return *this;
    }

    IntMatrix& IntMatrix::operator-()
    {
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            for(int j = 0; j < dimensions.getCol(); j++)
            {
                data[i][j] = -data[i][j];
            }
        }
        return *this;
    }

    IntMatrix operator+(const IntMatrix& mat1, const IntMatrix& mat2)
    {
        IntMatrix temp = mat1;
        return temp += mat2;
    }

    IntMatrix operator+(const IntMatrix& mat, const int num)
    {
        IntMatrix temp = mat;
        return temp += num;
    }

    IntMatrix operator+(const int num, const IntMatrix& mat)
    {
        return mat + num;
    }

    IntMatrix operator-(const IntMatrix& mat1, const IntMatrix& mat2)
    {
        IntMatrix temp = mat2;
        temp = -temp;
        return temp += mat1;
    }



    std::ostream& operator<<(std::ostream& os, const IntMatrix& output_matrix)
    {
        int* flat_matrix = IntMatrix::flattenMatrix(output_matrix);
        std::string output = printMatrix(flat_matrix, output_matrix.dimensions);
        os << output;
        delete[] flat_matrix;
        return os;
    }

    IntMatrix IntMatrix::operator==(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] == num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    IntMatrix IntMatrix::operator!=(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] != num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    IntMatrix IntMatrix::operator>=(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] >= num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    IntMatrix IntMatrix::operator<=(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] <= num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    IntMatrix IntMatrix::operator<(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] < num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    IntMatrix IntMatrix::operator>(const int num) const
    {
        IntMatrix output(this->dimensions);
        for(int i = 0; i < output.height(); i++)
        {
            for(int j = 0; j < output.width(); j++)
            {
                output.data[i][j] = (this->data[i][j] > num) ? MATRIX_TRUE : MATRIX_FALSE;
            }
        }
        return output;
    }

    bool any(const IntMatrix& matrix)
    {
        for(int i = 0; i < matrix.height(); i++)
        {
            for(int j = 0; j < matrix.width(); j++)
            {
                if(matrix(i,j) != 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool all(const IntMatrix& matrix)
    {
        for(int i = 0; i < matrix.height(); i++)
        {
            for(int j = 0; j < matrix.width(); j++)
            {
                if(matrix(i,j) == 0)
                {
                    return false;
                }
            }
        }
        return true;
    }

    IntMatrix::iterator IntMatrix::begin()
    {
        return iterator(this);
    }

    IntMatrix::iterator IntMatrix::end()
    {
        return iterator(this, this->dimensions.getRow());
    }

    IntMatrix::const_iterator IntMatrix::begin() const
    {
        return const_iterator(this);
    }

    IntMatrix::const_iterator IntMatrix::end() const
    {
        return const_iterator(this, this->dimensions.getRow());
    }

    void IntMatrix::initialize2DArray(const int value)
    {
       for(int i = 0; i < dimensions.getRow(); i++)
       {
           for(int j = 0; j < dimensions.getCol(); j++)
           {
               data[i][j] = value;
           }
       }
    }

    void IntMatrix::build2DArray()
    {
        data = new int*[dimensions.getRow()];
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            data[i] = new int[dimensions.getCol()];
        }
    }

    int* IntMatrix::flattenMatrix(const IntMatrix& matrix)
    {
        int* flat_matrix = new int[matrix.size()];
        int flat_matrix_counter = 0;
        for(int i = 0; i < matrix.height(); i++)
        {
            for(int j = 0; j < matrix.width(); j++)
            {
                flat_matrix[flat_matrix_counter++] = matrix(i,j);
            }
        }
        return flat_matrix;
    }

    void IntMatrix::deleteData()
    {
        for(int i = 0; i < dimensions.getRow(); i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
}