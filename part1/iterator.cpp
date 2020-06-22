//
// Created by David on 13/06/2020.

#include <cassert>
#include "IntMatrix.h"

namespace mtm
{
    IntMatrix::iterator::iterator(IntMatrix* my_matrix, int current_row, int current_column) :
        data(my_matrix), current_row(current_row), current_column(current_column)
    {}

    int& IntMatrix::iterator::operator*()
    {
        assert(current_column <=data->dimensions.getCol() -1 && current_row<= data->dimensions.getRow() -1);
        return data->data[current_row][current_column];
    }

    IntMatrix::iterator& IntMatrix::iterator::operator++()
    {
        if (this->current_column == this->data->dimensions.getCol() - 1)
        {
            this->current_row++;
            this->current_column=0;
        }
        else
        {
            this->current_column++;
        }
        return *this;
    }

    IntMatrix::iterator IntMatrix::iterator::operator++(int)
    {
        iterator temp=*this;
        ++*this;
        return temp;
    }

    bool IntMatrix::iterator::operator==(const iterator& it) const
    {
        return (this->data == it.data && this->current_row == it.current_row
        && this->current_column == it.current_column);
    }

    bool IntMatrix::iterator::operator!=(const iterator& it) const
    {
        return !(*this == it);
    }
}