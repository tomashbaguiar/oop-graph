#include "Edge.h"
#include <iostream>

Edge::Edge()
{
	after = -1;
	before = -1;
}

Edge::Edge(const int& first, const int& second)
{
	after = first;
	before = second;
}
