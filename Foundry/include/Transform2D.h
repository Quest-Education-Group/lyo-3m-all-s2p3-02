#ifndef TRANSFORM2D__H_
#define TRANSFORM2D__H_

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

class Transform2D
{
public:
	Transform2D() = default;
	Transform2D(Transform2D const& other);
	Transform2D(Transform2D&& other) noexcept;
	Transform2D(glm::vec2 const& position, float rotation);
	Transform2D(glm::vec2 const& positon, float rotation, glm::vec2 const& scale);

	void Identity();

	void SetPosition(glm::vec2 const& position); 
	void SetRotation(float rotation);
	void SetScale(glm::vec2 const& scale);
	
	//dont forget to update the dirty flag
	glm::vec2 GetPosition() const;
	float GetRotation() const;
	glm::vec2 GetScale() const;

	//multiply matrices of transforms
	Transform2D operator*(Transform2D const& right);
	Transform2D operator*=(Transform2D const& right);


private:
	void UpdateMatrix();

private:
	float m_x;
	float m_y;
	float rotation;
	glm::mat3 m_matrix {};

	bool m_needUpdate = false;
};

#endif // !TRANSFORM2D__H_
