//-----------------------------------------------------
// Support.h
//   Support classes & helper functions for TL-Engine
//-----------------------------------------------------

#ifndef SUPPORT_H_INCLUDED
#define SUPPORT_H_INCLUDED

#include <TL-Engine.h>

class CVector3
{
public:
	float x;
	float y;
	float z;

	CVector3() {/* Default */}

	CVector3(float X, float Y, float Z) :
		x{X}, y{Y}, z{Z}
	{}
};

/*-----------------------------------------------------------------------------------------
Non-member Operators
-----------------------------------------------------------------------------------------*/

// Vector addition
inline CVector3 operator+
(
	const CVector3& v1,
	const CVector3& v2
	)
{
	return CVector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// Vector subtraction
inline CVector3 operator-
(
	const CVector3& v1,
	const CVector3& v2
	)
{
	return CVector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

// Vector multiplied by scalar
inline CVector3 operator*
(
	const CVector3& v,
	const float  s
	)
{
	return CVector3(v.x*s, v.y*s, v.z*s);
}

// Dot product of two given vectors (order not important) - non-member version
inline float Dot
(
	const CVector3& v1,
	const CVector3& v2
)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

// Test if a float value is approximately 0. Epsilon value is the range around zero that
// is considered equal to zero. Default value requires zero to 6 decimal places
inline bool IsZero
(
	const float x,
	const float fEpsilon = 0.5e-6f
)
{
	return fabs(x) < fEpsilon;
}

// 1 / Sqrt
inline float InvSqrt(const float x)
{
	if (x == 0.0f)
	{
		return 0.0f;
	}

	return 1.0f / sqrtf(x);
}

//----------------------------------------------------------------------------
// Additional functions
//----------------------------------------------------------------------------

// Return unit length vector in the same direction as given one
CVector3 NormaliseVector(const CVector3& v);



class CMatrix4x4
{
public:
	// Matrix elements
	float e00, e01, e02, e03;
	float e10, e11, e12, e13;
	float e20, e21, e22, e23;
	float e30, e31, e32, e33;

	// Construct through pointer to 16 floats
	CMatrix4x4(const float* pfElts)
	{
		e00 = pfElts[0];
		e01 = pfElts[1];
		e02 = pfElts[2];
		e03 = pfElts[3];

		e10 = pfElts[4];
		e11 = pfElts[5];
		e12 = pfElts[6];
		e13 = pfElts[7];

		e20 = pfElts[8];
		e21 = pfElts[9];
		e22 = pfElts[10];
		e23 = pfElts[11];

		e30 = pfElts[12];
		e31 = pfElts[13];
		e32 = pfElts[14];
		e33 = pfElts[15];
	}

	// Return the given CVector3 transformed by this matrix (pre-multiplication: V' = V*M)
	// Assuming it is a point rather then a vector, i.e. assume the vector's 4th element is 1
	CVector3 TransformPoint(const CVector3& p) const
	{
		CVector3 pOut;
		pOut.x = p.x*e00 + p.y*e10 + p.z*e20 + e30;
		pOut.y = p.x*e01 + p.y*e11 + p.z*e21 + e31;
		pOut.z = p.x*e02 + p.y*e12 + p.z*e22 + e32;

		return pOut;
	}
};



//------------------------------------------
// UI functions
//------------------------------------------

// Get global camera position as a CVector3
CVector3 CameraPosition(tle::ICamera* cam);
// Get global camera facing direction as a CVector3
CVector3 CameraFacing(tle::ICamera* cam);

//------------------------------------------
// Picking Function
//------------------------------------------


// Calculate the world coordinates of a point on the near clip plane corresponding to given 
// x and y pixel coordinates using this camera and near clip distance
CVector3 WorldPointFromPixel( int x, int y, tle::ICamera* camera, float nearClip, tle::I3DEngine* engine );


#endif