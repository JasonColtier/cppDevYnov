#ifndef TCAMERA_H
#define TCAMERA_H

#include "TPoint3D.h"
#include "TVec3D.h"
#include <type_traits>

template<typename T>
class TCamera
{
public:

	TCamera()
		: TCamera(TPoint3D<T>(), TVec3D<T>(0, 0, 1), TVec3D<T>(0, 0, 0), TVec3D<T>(0, 0, 0))
	{
	}
	
	TCamera(const TPoint3D<T>& _cameraPosition
			, const	TVec3D<T>& _cameraDirection
			, const	TVec3D<T>& _cameraRight
			, const	TVec3D<T>& _cameraDown)
		: m_cameraPosition(_cameraPosition)
		, m_cameraDirection(_cameraDirection)
		, m_cameraRight(_cameraRight)
		, m_cameraDown(_cameraDown)
	{
		
	}

	~TCamera() = default;

	TCamera(const TCamera<T>& _camera) = default;
	TCamera(TCamera<T>&& _camera) = default;
	TCamera<T>& operator=(const TCamera<T>& _camera) = default;
	TCamera<T>& operator=(TCamera<T>&& _camera) = default;

	TPoint3D<T> GetCameraPosition() const { return m_cameraPosition; }
	TVec3D<T> GetCameraDirection() const { return m_cameraDirection; }
	TVec3D<T> GetCameraRight() const { return m_cameraRight; }
	TVec3D<T> GetCameraDown() const { return m_cameraDown; }

private:
	TPoint3D<T> m_cameraPosition;
	TVec3D<T> m_cameraDirection;
	TVec3D<T> m_cameraRight;
	TVec3D<T> m_cameraDown;
	
};

#endif // TCAMERA_H
