//
// Created by David on 10/06/2020.
//

#ifndef EX03_INTMATRIX_H
#define EX03_INTMATRIX_H


#include "Auxiliaries.h"

namespace mtm
{
    class IntMatrix
    {
        Dimensions dimensions;
        int** data;

        IntMatrix& operator+=(const IntMatrix& matrix);
        void deleteData();
        void initialize2DArray(const int value = 0);
        void build2DArray();
        static int* flattenMatrix(const IntMatrix&);


    public:
        class iterator;
        class const_iterator;
        IntMatrix(const Dimensions dims, const int value = 0);
        IntMatrix(const IntMatrix&);
        ~IntMatrix();
        IntMatrix operator=(const IntMatrix&);

        int height() const
        {
            return dimensions.getRow();
        }

        int width() const
        {
            return dimensions.getCol();
        }

        int size() const
        {
            return dimensions.getRow() * dimensions.getCol();
        }

        IntMatrix transpose() const;
        IntMatrix& operator+=(const int num);
        IntMatrix& operator-();

        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& output_matrix);
        friend IntMatrix operator+(const IntMatrix& mat1, const IntMatrix& mat2);
        friend IntMatrix operator-(const IntMatrix& mat1, const IntMatrix& mat2);

        int& operator()(const int row, const int column)
        {
            return data[row][column];
        }

        const int& operator()(const int row, const int column) const
        {
            return data[row][column];
        }

        IntMatrix operator==(const int num) const;
        IntMatrix operator!=(const int num) const;
        IntMatrix operator<=(const int num) const;
        IntMatrix operator>=(const int num) const;
        IntMatrix operator<(const int num) const;
        IntMatrix operator>(const int num) const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        static IntMatrix Identity(const int dimension);

        static const int MATRIX_TRUE = 1;
        static const int MATRIX_FALSE = 0;

        class iterator
        {
            const IntMatrix* data;
            int current_row;
            int current_column;
            iterator(IntMatrix* my_matrix, int current_row = 0, int current_column = 0);

            friend class IntMatrix;

        public:

            int& operator*();
            iterator& operator++();
            iterator operator++(int);
            bool operator==(const iterator& it) const;
            bool operator!=(const iterator& it) const;
            iterator(const iterator&) = default;
            iterator& operator=(const iterator&) = default;
            ~iterator() = default;
        };

       class const_iterator
       {
           const IntMatrix* data ;
           int current_row;
           int current_column;
           const_iterator(const IntMatrix* my_matrix, int current_row = 0, int current_column = 0);

           friend class IntMatrix;

       public:
           const int& operator*() const;
           const_iterator& operator++();
           const_iterator operator++(int);
           bool operator==(const const_iterator& it) const;
           bool operator!=(const const_iterator& it) const;
           const_iterator(const const_iterator&) = default;
           const_iterator& operator=(const const_iterator&) = default;
           ~const_iterator() = default;
       };
    };

    IntMatrix operator+(const IntMatrix& mat, const int num);
    IntMatrix operator+(const int num, const IntMatrix& mat);
    bool any(const IntMatrix& matrix);
    bool all(const IntMatrix& matrix);
}

#endif //EX03_INTMATRIX_H