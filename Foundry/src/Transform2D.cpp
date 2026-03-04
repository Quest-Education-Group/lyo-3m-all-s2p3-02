#include "../include/Transform2D.h"

#include <cmath>

Transform2D::Transform2D(
	float _x,		     float _y,
	float _scaleX,	     float _scaleY,
	float _theta,
	float _translationX, float _translationY,
	bool _statism) :
	m_position(_x, _y),
	m_isStatic(_statism) 
{
	m_scale = mat3::mat(
		_scaleX, 0, 0, 
		0, _scaleY, 0,
		0,    0,    1
	);
	m_rotation = mat3::mat(
		cos(_theta), -sin(_theta),	0,
		sin(_theta), cos(_theta),	0,
		0,				0,			1
	);
	m_translation = mat3::mat(
		1, 0, _translationX,
		0, 1, _translationY,
		0, 0,		1
	);

	Update();
}

Transform2D::~Transform2D() {}


Transform2D::Transform2D(Transform2D const& other)
{
	m_position = other.m_position;

	m_scale = other.m_scale;
	m_rotation = other.m_rotation;
	m_translation = other.m_translation;

	m_transformationMatrix = (m_scale * m_rotation) * m_translation;

	m_isStatic = other.m_isStatic;
	m_isDirty = other.m_isDirty;
}

Transform2D& Transform2D::operator=(Transform2D const& other)
{
	m_position = other.m_position;

	m_scale = other.m_scale;
	m_rotation = other.m_rotation;
	m_translation = other.m_translation;

	m_transformationMatrix = (m_scale * m_rotation) * m_translation;

	m_isStatic = other.m_isStatic;
	m_isDirty = other.m_isDirty;

	return *this;
}


Transform2D::Transform2D(Transform2D&& other) noexcept
{
	m_position = other.m_position;

	m_scale = other.m_scale;
	m_rotation = other.m_rotation;
	m_translation = other.m_translation;

	m_transformationMatrix = (m_scale * m_rotation) * m_translation;

	m_isStatic = other.m_isStatic;
	m_isDirty = other.m_isDirty;
}
Transform2D& Transform2D::operator=(Transform2D&& other) noexcept
{
	m_position = other.m_position;

	m_scale = other.m_scale;
	m_rotation = other.m_rotation;
	m_translation = other.m_translation;

	m_transformationMatrix = (m_scale * m_rotation) * m_translation;

	m_isStatic = other.m_isStatic;
	m_isDirty = other.m_isDirty;

	return *this;
}


Transform2D Transform2D::operator*(Transform2D const& other) const
{
	Transform2D toReturn  = {};
	toReturn.m_position   = m_position   * other.m_position;
	toReturn.m_scale      = m_scale      * other.m_scale;
	toReturn.m_theta      = m_theta      * other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator*=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position   *= other.m_position;
	m_scale      *= other.m_scale;
	m_theta      *= other.m_theta;

	return *this;
}

Transform2D Transform2D::operator+(Transform2D const& other) const
{
	Transform2D toReturn  = {};
	toReturn.m_position   = m_position   + other.m_position;
	toReturn.m_scale      = m_scale      + other.m_scale;
	toReturn.m_theta      = m_theta      + other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator+=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position   += other.m_position;
	m_scale      += other.m_scale;
	m_theta      += other.m_theta;

	return *this;
}

Transform2D Transform2D::operator-(Transform2D const& other) const
{
	Transform2D toReturn  = {};
	toReturn.m_position   = m_position   - other.m_position;
	toReturn.m_scale      = m_scale      - other.m_scale;
	toReturn.m_theta      = m_theta      - other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator-=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position   -= other.m_position;
	m_scale      -= other.m_scale;
	m_theta      -= other.m_theta;

	return *this;
}

Transform2D Transform2D::operator/(Transform2D const& other) const
{
	Transform2D toReturn = {};
	toReturn.m_position   = m_position   / other.m_position;
	toReturn.m_scale      = m_scale      / other.m_scale;
	toReturn.m_theta      = m_theta      / other.m_theta;

	return toReturn;
}
Transform2D& Transform2D::operator/=(Transform2D const& other)
{
	if (m_isStatic) return *this;

	m_position   /= other.m_position;
	m_scale      /= other.m_scale;
	m_theta      /= other.m_theta;

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

	m_scale[0][0] = _scale.x;
	m_scale[1][0] = _scale.y;

	m_isDirty = true;
}
void Transform2D::SetScale(float _x, float _y)
{
	if (m_isStatic) return;

	if (_x < 0.f || _y < 0.f)
		return;

	m_scale[0][0] = _x;
	m_scale[1][0] = _y;

	m_isDirty = true;
}
uvec2 Transform2D::GetScale() const
{
	return { m_scale[0][0], m_scale[1][0] };
}

void Transform2D::SetRotation(float _theta)
{
	if (m_isStatic) return;

	m_rotation[0][0] = cos(_theta);
	m_rotation[0][1] = -sin(_theta);
	m_rotation[1][0] = sin(_theta);
	m_rotation[1][1] = cos(_theta);

	m_isDirty = true;
}
mat2 Transform2D::GetRotationMatrix() const
{
	return mat2::mat(
		m_rotation[0][0], m_rotation[0][1],
		m_rotation[1][0], m_rotation[1][1]
	);
}

void Transform2D::SetTranslation(float _u, float _v)
{
	if (m_isStatic) return;

	m_translation[0][2] = _u;
	m_translation[1][2] = _v;

	m_isDirty = true;
}
void Transform2D::SetTranslation(vec2 _translation)
{
	if (m_isStatic) return;

	m_translation[0][2] = _translation.x;
	m_translation[1][2] = _translation.y;

	m_isDirty = true;
}
vec2 Transform2D::GetTranslation() const
{
	return { m_translation[0][2], m_translation[1][2] };
}

void Transform2D::SetStatism(bool _statism)
{
	m_isStatic = _statism;
}
bool Transform2D::IsStatic() const
{
	return m_isStatic;
}

void Transform2D::Update()
{
	if (m_isStatic) return;

	m_transformationMatrix = mat3::mat(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1 
	);

	m_transformationMatrix = (m_scale * m_rotation) * m_translation;

	vec3 newPos = vec3(m_position.x, m_position.y, 1) * m_transformationMatrix;

	m_position.x = newPos.x;
	m_position.y = newPos.y;

	m_isDirty = false;
}