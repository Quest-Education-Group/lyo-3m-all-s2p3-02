#ifndef FOUNDRY_NODE2D__H_
#define FOUNDRY_NODE2D__H_

#include "Node.h"
#include "Transform2D.h"

class Node2D : public Node
{
public:
	class Proxy;

	Node2D(
		float _x = 0.0f, float _y = 0.0f,
		float _scaleX = 1.0f, float _scaleY = 1.0f,
		float _theta = 0.0f,
		bool _statism = false
	);
	~Node2D();


	Node2D  operator*(Node2D const& other) const;
	Node2D& operator*=(Node2D const& other);
	
	Node2D  operator+(Node2D const& other) const;
	Node2D& operator+=(Node2D const& other);
	
	Node2D  operator-(Node2D const& other) const;
	Node2D& operator-=(Node2D const& other);
	
	Node2D  operator/(Node2D const& other) const;
	Node2D& operator/=(Node2D const& other);


	void		SetScale(glm::vec2 _scale);
	void		SetScale(float _width, float _height);
	glm::uvec2	GetScale() const;

	void		SetRotation(float _theta);
	glm::mat2	GetRotationMatrix() const;

	void		SetPosition(glm::vec2 _pos);
	void		SetPosition(float _x, float _y);
	glm::vec2	GetPosition() const;

	glm::mat3	GetTransformationMatrix() const;

	void		SetStatism(bool _statism);
	bool		IsStatic() const;

	void		Update();

private:
	Transform2D m_transform;
};

#include "Scripting/Proxies/Node2DProxy.inl"

#endif