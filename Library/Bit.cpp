#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <numeric>
#include <tuple>
#include <valarray>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <typeinfo>
#include <functional>

using namespace std;

// BEGIN CUT HERE

using Index = size_t;
using Count = size_t;

class Bit
{
public:
    Bit(Index N);
    void add(Index index_, Count value_);

    Count      count(Index index_                ) const;
    Count rangeCount(Index indexA_, Index indexB_) const;

private:
    void          doAdd(Index index_, Count value_);
    Count   singleCount(Index index_) const;
    Count fromLeftCount(Index index_) const;
    vector<Index> _vector;
};

Index toZeroBased(Index index_)
{
    return index_ - 1;
}

Index toOneBased(Index index_)
{
    return index_ + 1;
}


Bit::Bit(Index N)
: _vector(N)
{
}

void Bit::add(Index index_, Count value_)
{
    doAdd(toOneBased(index_), value_);
}

Count Bit::count(Index index_) const
{
    return singleCount(toOneBased(index_));
}

Count Bit::rangeCount(Index indexA_, Index indexB_) const
{
    Count count = 0 < indexA_ ? fromLeftCount(toOneBased(indexA_ - 1)) : 0;
    return fromLeftCount(toOneBased(indexB_)) - count;
}

void Bit::doAdd(Index index_, Count value_)
{
    while (toZeroBased(index_) < _vector.size())
    {
        _vector[toZeroBased(index_)] += value_;
        index_                       += (index_ & -index_);
    }
}

Count Bit::singleCount(Index index_) const
{
    Count sum = _vector[toZeroBased(index_)];
    if (1 < index_) {
        const Index z = index_ - (index_ & -index_);
        index_--;
        while (z != index_) {
            sum    -= _vector[toZeroBased(index_)];
            index_ -= (index_ & -index_);
        }
    }
    return sum;
}

Count Bit::fromLeftCount(Index index_) const
{
    Count sum = 0;
    while (0 < index_)
    {
        sum    += _vector[toZeroBased(index_)];
        index_ -= (index_ & -index_);
    }
    return sum;
}

// END CUT HERE

size_t countRange(vector<size_t> vector_, size_t indexA_, size_t indexB_)
{
    size_t sum = 0;
    for (size_t i = indexA_; i <= indexB_; ++i)
    {
        sum += vector_[i];
    }
    return sum;
}

bool checkBitRange(const vector<size_t>& vector_, const Bit& bit_)
{
    bool ok = true;
    size_t N = vector_.size();
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = i; j < N; ++j)
        {
            size_t vectorSum = countRange(vector_, i, j);
            size_t bitSum = bit_.rangeCount(i, j);
            if (vectorSum != bitSum)
            {
                cerr << "Range count different for [" << i << ", " << j << "], vector = " << vectorSum << ", BIT = " << bitSum << "\n";
                ok = false;
            }
        }
    }
    for (size_t i = 0; i < N; ++i)
    {
        Count bitCount = bit_.count(i);
        if (vector_[i] != bitCount)
        {
            cerr << "Count different for [" << i << "], vector = " << vector_[i] << ", BIT = " << bitCount << "\n";
            ok = false;
        }
    }
    return ok;
}

void testSmall()
{
    size_t testSize = 10;
    Bit bit(testSize);
    vector<size_t> v(testSize);
    size_t index, count;

    index = 5;
    count = 1;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));

    index = 3;
    count = 2;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));

    index = 3;
    count = 2;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));

    index = 9;
    count = 5;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));

    index = 0;
    count = 10;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));

    index = 5;
    count = 1000;
    bit.add(index, count);
    v[index] += count;
    assert(checkBitRange(v, bit));
}

// TODO: Test negative values

void testLarge()
{
    size_t testSize = 100;
    size_t mul = 123;
    Bit bit(testSize);
    vector<size_t> v(testSize);
    for (size_t i = 1; i < 10 * testSize; ++i)
    {
        size_t index = (i * mul) % testSize;
        size_t count = i;
        bit.add(index, count);
        v[index] += count;
        assert(checkBitRange(v, bit));
    }
}

int main( int argc, char* argv[] )
{
    testSmall();
    testLarge();
    cout << "OK!" << endl;
    return 0;
}
