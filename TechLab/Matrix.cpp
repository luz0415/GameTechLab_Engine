#include "Matrix.h"
#include "Vector.h"
#include <math.h>

const FMatrix FMatrix::Identity()
{
    FMatrix Result{};
    Result[0][0] = 1;
    Result[1][1] = 1;
    Result[2][2] = 1;
    Result[3][3] = 1;
    return Result;
}


const FMatrix FMatrix::TransformMatrix(FVector trans)
{
    FMatrix Result = Identity();
    Result[3][0] = trans.x;
    Result[3][1] = trans.y;
    Result[3][2] = trans.z;
    return Result;
}

const FMatrix FMatrix::ScaleMatrix(FVector trans)
{
    FMatrix Result = Identity();
    Result[0][0] = trans.x;
    Result[1][1] = trans.y;
    Result[2][2] = trans.z;
    return Result;
}

const FMatrix FMatrix::RotateMatrixX(float angle)
{
    FMatrix Result = Identity();
    Result[1][1] = cos(angle);
    Result[1][2] = sin(angle);
    Result[2][1] = -sin(angle);
    Result[2][2] = cos(angle);

    return Result;
}

const FMatrix FMatrix::RotateMatrixY(float angle)
{
    FMatrix Result = Identity();
    Result[0][0] = cos(angle);
    Result[0][2] = -sin(angle);
    Result[2][0] = sin(angle);
    Result[2][2] = cos(angle);
    return Result;
}

const FMatrix FMatrix::RotateMatrixZ(float angle)
{
    FMatrix Result = Identity();
    Result[0][0] = cos(angle);
    Result[0][1] = sin(angle);
    Result[1][0] = -sin(angle);
    Result[1][1] = cos(angle);
    return Result;
}

const FMatrix FMatrix::ViewMatrix(const FVector& eye, const FVector& at, const FVector& up)
{
    FVector zaxis = at - eye;
    zaxis.Normalize();
    FVector xaxis = up.Cross(zaxis);
    xaxis.Normalize();

    FVector yaxis = zaxis.Cross(xaxis);
    yaxis.Normalize();

    FMatrix Result = FMatrix::Identity();

    
    Result.M[0][0] = xaxis.x; Result.M[0][1] = xaxis.y; Result.M[0][2] = xaxis.z;
    Result.M[1][0] = yaxis.x; Result.M[1][1] = yaxis.y; Result.M[1][2] = yaxis.z;
    Result.M[2][0] = zaxis.x; Result.M[2][1] = zaxis.y; Result.M[2][2] = zaxis.z;

    
    Result.M[3][0] = -xaxis.Dot(eye);
    Result.M[3][1] = -yaxis.Dot(eye);
    Result.M[3][2] = -zaxis.Dot(eye);
    return Result;
}

const FMatrix FMatrix::ProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ, float farZ)
{
    FMatrix Result{};
    float halfAngleY = fovAngleY / 2.0f;
    float height = 1.0f / tan(halfAngleY);
    float width = height / aspectRatio;
    Result[0][0] = width;
    Result[1][1] = height;
    Result[2][2] = farZ / (farZ - nearZ);
    Result[3][2] = -nearZ * Result[2][2];

    Result[2][3] = 1.0f;
    return Result;
}

FMatrix FMatrix::operator*(const FMatrix& Other) const
{
    FMatrix Result{};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            Result.M[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k)
            {
                Result.M[i][j] += M[i][k] * Other.M[k][j];
            }
        }
    }
    return Result;
}


float(&FMatrix::operator[](unsigned row))[4]
{
    return M[row];
}

