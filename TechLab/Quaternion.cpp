#include "Quaternion.h"

FQuaternion FQuaternion::FromAxisAngleLH(const FVector& axis, float angleRad)
{
	FVector a = axis;
	a.Normalize();
	float s = std::sinf(angleRad * 0.5f);
	float c = std::cosf(angleRad * 0.5f);
	return FQuaternion(a.X * s, a.Y * s, a.Z * s, c);
}

FQuaternion FQuaternion::FromYawPitchRollLH(float yawY, float pitchX, float rollZ) {
    FQuaternion qYaw = FromAxisAngleLH(FVector(0, 1, 0), yawY);
    FQuaternion qPitch = FromAxisAngleLH(FVector(1, 0, 0), pitchX);
    FQuaternion qRoll = FromAxisAngleLH(FVector(0, 0, 1), rollZ);
    // 조합: Q = Qz ⨂ Qx ⨂ Qy  (적용 순서: Y → X → Z)
    FQuaternion Q = qRoll * qPitch * qYaw;
    Q.Normalize();
    return Q;
}


FVector FQuaternion::RotateVector(const FVector& v) const {
    FVector u(x, y, z);
    float s = w;
    FVector uxv = u.Cross(v);
    FVector uxu = u.Cross(uxv);
    return v + (uxv * (2.0f * s)) + (uxu * 2.0f);
}

// Row-major + Row-vector 규약용 3D 회전행렬(4x4) 생성 (LH 기준)
// 주의: 아래는 "열-벡터 표준식"의 전치를 사용하여 row-vector 곱셈에 맞춘 형태입니다.
FMatrix FQuaternion::ToMatrix4x4_RowMajor_LH() const {
    FQuaternion q = *this;
    q.Normalize();
    const float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    const float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
    const float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

    FMatrix R = FMatrix::Identity();

    // row-vector 규약용(= column-vector 표준식의 전치)
    R[0][0] = 1.f - 2.f * (yy + zz);
    R[0][1] = 2.f * (xy + wz);
    R[0][2] = 2.f * (xz - wy);

    R[1][0] = 2.f * (xy - wz);
    R[1][1] = 1.f - 2.f * (xx + zz);
    R[1][2] = 2.f * (yz + wx);

    R[2][0] = 2.f * (xz + wy);
    R[2][1] = 2.f * (yz - wx);
    R[2][2] = 1.f - 2.f * (xx + yy);

    return R;
}

FVector FQuaternion::ToYawPitchRoll() const
{
    FVector eulerAngles;

    // YXZ 회전 순서에 맞는 공식 (Y→X→Z 적용 순서의 역변환)

    // Roll (Z-axis, 마지막 적용)
    float sinr_cosp = 2.0f * (w * z + x * y);
    float cosr_cosp = 1.0f - 2.0f * (z * z + x * x);
    eulerAngles.Z = std::atan2(sinr_cosp, cosr_cosp);

    // Pitch (X-axis, 중간 적용) - 짐벌락 체크
    float sinp = 2.0f * (w * x - y * z);
    if (std::abs(sinp) >= 1.0f)
        eulerAngles.X = std::copysign((float)PI / 2, sinp);
    else
        eulerAngles.X = std::asin(sinp);

    // Yaw (Y-axis, 첫 번째 적용)
    float siny_cosp = 2.0f * (w * y + z * x);
    float cosy_cosp = 1.0f - 2.0f * (x * x + y * y);
    eulerAngles.Y = std::atan2(siny_cosp, cosy_cosp);

    return eulerAngles;
}
