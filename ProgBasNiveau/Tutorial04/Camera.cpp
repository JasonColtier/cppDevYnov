#include "Camera.h"


Camera::Camera():Eye(g_XMZero), LookAt(g_XMIdentityR2), Up(g_XMIdentityR1), Focale(XM_PIDIV4)
{
}


void Camera::GetView(XMMATRIX& v) const
{
	v = XMMatrixLookAtLH(Eye, LookAt, Up);
}
void Camera::GetProjection(XMMATRIX& p) const
{
	// Initialize the projection matrix
	p = XMMatrixPerspectiveFovLH(XM_PIDIV4, 16 / (FLOAT)9, 0.01f, 100.0f);
}
