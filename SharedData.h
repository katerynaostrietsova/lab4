#pragma once
#include <mutex>
#include <string>
#include <cstddef>

using namespace std;

class SharedData2
{
public:
    SharedData2();

    int get(size_t index) const;

    void set(size_t index, int value);

    string toString() const;

    operator string() const;

private:
    int field0;
    int field1;

    mutable mutex mutex0;
    mutable mutex mutex1;

    int getFieldUnchecked(size_t index) const;

    void setFieldUnchecked(size_t index, int value);
};
