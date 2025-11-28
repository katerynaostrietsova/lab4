#include "SharedData.h"
#include <sstream>
#include <stdexcept>

using namespace std;

SharedData2::SharedData2()
    : field0(0),
    field1(0)
{
}

int SharedData2::get(size_t index) const
{
    if (index == 0)
    {
        lock_guard<mutex> lock(mutex0);
        return getFieldUnchecked(0);
    }
    else if (index == 1)
    {
        lock_guard<mutex> lock(mutex1);
        return getFieldUnchecked(1);
    }
    else
    {
        throw out_of_range("SharedData2::get: invalid field index");
    }
}

void SharedData2::set(size_t index, int value)
{
    if (index == 0)
    {
        lock_guard<mutex> lock(mutex0);
        setFieldUnchecked(0, value);
    }
    else if (index == 1)
    {
        lock_guard<mutex> lock(mutex1);
        setFieldUnchecked(1, value);
    }
    else
    {
        throw out_of_range("SharedData2::set: invalid field index");
    }
}

string SharedData2::toString() const
{
    scoped_lock<mutex, mutex> lock(mutex0, mutex1);

    int value0 = field0;
    int value1 = field1;

    ostringstream out;
    out << "field0=" << value0 << ", field1=" << value1;

    return out.str();
}

SharedData2::operator string() const
{
    return toString();
}

int SharedData2::getFieldUnchecked(size_t index) const
{
    if (index == 0)
    {
        return field0;
    }
    else if (index == 1)
    {
        return field1;
    }

    throw out_of_range("SharedData2::getFieldUnchecked: invalid field index");
}

void SharedData2::setFieldUnchecked(size_t index, int value)
{
    if (index == 0)
    {
        field0 = value;
    }
    else if (index == 1)
    {
        field1 = value;
    }
    else
    {
        throw out_of_range("SharedData2::setFieldUnchecked: invalid field index");
    }
}
