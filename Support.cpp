//-----------------------------------------------------
// Support.cpp
//   Support classes & helper functions for TL-Engine
//-----------------------------------------------------

#include "Support.h"
#include "Globals.h"

//----------------------------------------------------------------------------
// Additional functions
//----------------------------------------------------------------------------

// Return unit length vector in the same direction as given one
CVector3 NormaliseVector(const CVector3& v)
{
	float lengthSq = v.x*v.x + v.y*v.y + v.z*v.z;

	// Ensure vector is not zero length (use BaseMath.h float approx. fn with default epsilon)
	if (IsZero(lengthSq))
	{
		return CVector3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		float invLength = InvSqrt(lengthSq);
		return CVector3(v.x * invLength, v.y * invLength, v.z * invLength);
	}
}


//------------------------------------------
// UI functions
//------------------------------------------

// Get global camera position as a CVector3
CVector3 CameraPosition(tle::ICamera* cam)
{
	return CVector3(cam->GetX(), cam->GetY(), cam->GetZ());
}

// Get global camera facing direction as a CVector3
CVector3 CameraFacing(tle::ICamera* cam)
{
	float cameraMatrixElts[16];
	cam->GetMatrix(cameraMatrixElts);
	return CVector3(cameraMatrixElts[8], cameraMatrixElts[9], cameraMatrixElts[10]);
}


//------------------------------------------
// Picking Function
//------------------------------------------

// Calculate the world coordinates of a point on the near clip plane corresponding to given 
// x and y pixel coordinates using this camera and near clip distance
CVector3 WorldPointFromPixel( int x, int y, tle::ICamera* camera, float nearClip, tle::I3DEngine* engine )
{
	// Calculate horizontal and vertical field of view to match TL-Engine internal settings
	const float fovMin = PI / 3.55f/*3.4f*/; // Default TL FOV for minimum of width or height
	float fovX;
	float fovY;
	float width = static_cast<float>(engine->GetWidth());
	float height = static_cast<float>(engine->GetHeight());
	if (width > height)
	{
		fovY = fovMin;
		fovX = atanf( width * tanf(fovY * 0.5f) / height ) * 2.0f;
	}
	else
	{
		fovX = fovMin;
		fovY = atanf( height * tanf(fovX * 0.5f) / width ) * 2.0f;
	}

	// Reverse procedure in function above
	CVector3 cameraPoint;
	cameraPoint.x = static_cast<float>(x) / (width * 0.5f) - 1.0f;
	cameraPoint.y = 1.0f - static_cast<float>(y) / (height * 0.5f);
	
	cameraPoint.x *= nearClip;
	cameraPoint.y *= nearClip;
	cameraPoint.z = nearClip;

	cameraPoint.x *= tanf( fovX * 0.5f );
	cameraPoint.y *= tanf( fovY * 0.5f );

	float cameraMatrixElts[16];
	camera->GetMatrix( cameraMatrixElts );
	CMatrix4x4 cameraMatrix = CMatrix4x4(cameraMatrixElts);
	CVector3 worldPoint = cameraMatrix.TransformPoint( cameraPoint );

	return worldPoint;
}
