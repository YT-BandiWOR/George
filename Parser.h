#pragma once
#include "Types.h"
#include "RealTree.h"
#include "VirtualTree.h"


class Parser
{
public:
	Parser();
	RealTree* parse(VirtualTree* tree);
};

