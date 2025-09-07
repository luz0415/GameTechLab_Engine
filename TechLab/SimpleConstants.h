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
};

struct FViewProjConstant
{
	FMatrix View;
	FMatrix Projection;
};