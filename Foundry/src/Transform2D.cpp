#include "../include/Transform2D.h"

Transform2D::Transform2D(
	float _x,
	float _y,
	float _scaleX,
	float _scaleY,
	float _theta,
	bool _statism) :
	m_position(_x, _y),
	m_scale(_scaleX, _scaleY),
	m_theta(_theta),
	m_isStatic(_statism),
	m_pParent(nullptr) {}

Transform2D::~Transform2D() {}


Transform2D::Transform2D(Transform2D const& other)
{
	m_position = other.m_position;
	m_scale    = other.m_scale;
	m_theta    = other.m_theta;
	m_isStatic = other.m_isStatic;
	m_pParent = other.m_pParent;
}

Transform2D& Transform2D::operator=(Transform2D const& other)
{
	m_position = other.m_position;
	m_scale    = other.m_scale;
	m_theta    = other.m_theta;
	m_isStatic = other.m_isStatic;
	m_pParent = other.m_pParent;

	return *this;
}


Transform2D::Transform2D(Transform2D&& other) noexcept
{
	m_position = other.m_position;
	m_scale    = other.m_scale;
	m_theta    = other.m_theta;
	m_isStatic = other.m_isStatic;
	m_pParent = other.m_pParent;
}
Transform2D& Transform2D::operator=(Transform2D&& other) noexcept
{
	m_position = other.m_position;
	m_scale    = other.m_scale;
	m_theta    = other.m_theta;
	m_isStatic = other.m_isStatic;
	m_pParent = other.m_pParent;

	return *this;
}


Transform2D Transform2D::operator*(Transform2D const& other) const
{
	Transform2D toReturn = {};
	toReturn.m_position = m_position * other.m_position;
	toReturn.m_scale    = m_scale    * other.m_scale;
	toReturn.m_theta    = m_theta    * other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator*=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position *= other.m_position;
	m_scale    *= other.m_scale;
	m_theta    *= other.m_theta;

	return *this;
}

Transform2D Transform2D::operator+(Transform2D const& other) const
{
	Transform2D toReturn = {};
	toReturn.m_position = m_position + other.m_position;
	toReturn.m_scale    = m_scale    + other.m_scale;
	toReturn.m_theta    = m_theta    + other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator+=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position += other.m_position;
	m_scale    += other.m_scale;
	m_theta    += other.m_theta;

	return *this;
}

Transform2D Transform2D::operator-(Transform2D const& other) const
{
	Transform2D toReturn = {};
	toReturn.m_position = m_position - other.m_position;
	toReturn.m_scale    = m_scale    - other.m_scale;
	toReturn.m_theta    = m_theta    - other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator-=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position -= other.m_position;
	m_scale    -= other.m_scale;
	m_theta    -= other.m_theta;

	return *this;
}

Transform2D Transform2D::operator/(Transform2D const& other) const
{
	Transform2D toReturn = {};
	toReturn.m_position = m_position / other.m_position;
	toReturn.m_scale    = m_scale    / other.m_scale;
	toReturn.m_theta    = m_theta    / other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator/=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position /= other.m_position;
	m_scale    /= other.m_scale;
	m_theta    /= other.m_theta;

	return *this;
}

////////////////////////////////////////////////////////////////////

void Transform2D::SetPosition(vec2 _pos)
{
	if (m_isStatic) return;

	m_position = _pos;
}
void Transform2D::SetPosition(float _x, float _y)
{
	if (m_isStatic) return;

	m_position.x = _x;
	m_position.y = _y;
}
vec2 Transform2D::GetPosition() const
{
	return m_position;
}

void Transform2D::SetScale(vec2 _scale)
{
	if (m_isStatic) return;

	m_scale = _scale;
}
void Transform2D::SetScale(float _width, float _height)
{
	if (m_isStatic) return;

	if (_width < 0.f || _height < 0.f)
		return;

	m_scale.x = _width;
	m_scale.y = _height;
}
uvec2 Transform2D::GetScale() const
{
	return m_scale;
}

void Transform2D::AddTheta(float _theta)
{
	if (m_isStatic) return;

	m_theta += _theta;

	if (m_theta > 180.0f)
		m_theta = -180 + (int)_theta % 180;
	else if (m_theta < -180.0f)
		m_theta = 180 - (int)_theta % 180;
}
void Transform2D::SetTheta(float _theta)
{
	if (m_isStatic) return;

	if (_theta < -180.0f)
		m_theta = -180 - (int)_theta % 180;
	else if (_theta > 180.0f)
		m_theta = -180 + (int)_theta % 180;
	else
		m_theta = _theta;
}
float Transform2D::GetTheta() const
{
	return m_theta;
}

void Transform2D::SetStatism(bool _statism)
{
	m_isStatic = _statism;
}
bool Transform2D::IsStatic() const
{
	return m_isStatic;
}

void Transform2D::SetParent(Transform2D& _parent)
{
	m_pParent = &_parent;
}
Transform2D* Transform2D::GetParent()
{
	return m_pParent;
}