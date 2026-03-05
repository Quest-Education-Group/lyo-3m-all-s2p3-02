#include "Nodes/Node2D.h"

Node2D::Node2D(
	float _x, float _y, 
	float _scaleX, float _scaleY, 
	float _theta, 
	bool _statism) : 
	Node(), 
	m_transform(
		_x, _y, 
		_scaleX, _scaleY, 
		_theta, 
		_statism) 
{}

Node2D::~Node2D() {}


Node2D Node2D::operator*(Node2D const& other) const
{
	return m_transform * other.m_transform;
}
Node2D& Node2D::operator*=(Node2D const& other)
{
	m_transform *= other.m_transform;
	return *this;
}
		
Node2D Node2D::operator+(Node2D const& other) const
{
	return m_transform + other.m_transform;
}
Node2D& Node2D::operator+=(Node2D const& other)
{
	m_transform += other.m_transform;
	return *this;
}

Node2D Node2D::operator-(Node2D const& other) const
{
	return m_transform - other.m_transform;
}
Node2D& Node2D::operator-=(Node2D const& other)
{
	m_transform -= other.m_transform;
	return *this;
}

Node2D Node2D::operator/(Node2D const& other) const
{
	return m_transform / other.m_transform;
}
Node2D& Node2D::operator/=(Node2D const& other)
{
	m_transform /= other.m_transform;
	return *this;
}


void Node2D::SetScale(glm::vec2 _scale)
{
	m_transform.SetScale(_scale);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetScale(_Scale);
	}
}

void Node2D::SetScale(float  _width, float _height)
{
	m_transform.SetScale(_width, _height);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetScale(_width, _height);
	}
}

glm::uvec2 Node2D::GetScale() const
{
	return m_transform.GetScale();
}


void Node2D::SetRotation(float _theta)
{
	m_transform.SetRotation(_theta);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetRotation(_theta);
	}
}
glm::mat2 Node2D::GetRotationMatrix() const
{
	return m_transform.GetRotationMatrix();
}

void Node2D::SetPosition(glm::vec2 _pos)
{
	m_transform.SetPosition(_pos);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetPosition(_pos);
	}
}
void Node2D::SetPosition(float _x, float _y)
{
	m_transform.SetPosition(_x, _y);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetPosition(_x, _y);
	}
}
glm::vec2 Node2D::GetPosition() const
{
	return m_transform.GetPosition();
}

glm::mat3 Node2D::GetTransformationMatrix() const
{
	return m_transform.GetTransformationMatrix();
}

void Node2D::SetStatism(bool _statism)
{
	m_transform.SetStatism(_statism);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		reinterpret_cast<Node2D&>(GetChild(i)).SetStatism(_statism);
	}
}
bool Node2D::IsStatic() const
{
	return m_transform.IsStatic();
}

void Node2D::Update()
{
	m_transform.Update();

	if (GetParent() == nullptr) 
		return;

	for (int i = 0; i < GetChildren().size(); i++)
	{
		Node2D current = reinterpret_cast<Node2D&>(GetChild(i));
		current *= (*this);
		current.Update();
	}
}


