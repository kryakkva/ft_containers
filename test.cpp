#include <iostream>
#include "vector.hpp"
#include <vector>
#include <map>

int main()
{
	std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    std::swap(vector, tmp4);
    g_end1 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}