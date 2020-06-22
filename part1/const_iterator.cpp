//
// Created by David on 13/06/2020.
//


#include <iostream>
#include <cassert>
#include "IntMatrix.h"
#include "Auxiliaries.h"


namespace mtm
{
    IntMatrix::const_iterator::const_iterator(const IntMatrix *my_matrix, int current_row, int current_column) :
            data(my_matrix), current_row(current_row), current_column(current_column) {}

    const int &IntMatrix::const_iterator::operator*() const
    {
        assert(current_column <= data->dimensions.getCol() - 1 && current_row <= data->dimensions.getRow() - 1);
        return data->data[current_row][current_column];
    }

    IntMatrix::const_iterator &IntMatrix::const_iterator::operator++()
    {
        if (this->current_column == this->data->dimensions.getCol() - 1)
        {
            this->current_row++;
            this->current_column = 0;
        }
        else
        {
            this->current_column++;
        }
        return *this;
    }

    IntMatrix::const_iterator IntMatrix::const_iterator::operator++(int)
    {
        const_iterator temp = *this;
        ++*this;
        return temp;
    }

    bool IntMatrix::const_iterator::operator==(const const_iterator &it) const
    {
        return (this->data == it.data && this->current_row == it.current_row &&
                this->current_column == it.current_column);
    }

    bool IntMatrix::const_iterator::operator!=(const const_iterator &it) const
    {
        return !(*this == it);
    }
}