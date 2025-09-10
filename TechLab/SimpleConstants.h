#pragma once
#include "Matrix.h"
struct FSimpleConstant
{
	FMatrix Model;
	FMatrix View;
	FMatrix Projection;
};

struct FModelConstant
{
	FMatrix Model;
	int IsHighlighted;
};

struct FViewProjConstant
{
	FMatrix View;
	FMatrix Projection;
};