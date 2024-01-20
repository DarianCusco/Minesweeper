#pragma once
#include <random>
using namespace std;
class Random
{
	static mt19937 random;
public:
	static int rollInt(int min, int max);
	static int rollFloat(float min, float max);
};

