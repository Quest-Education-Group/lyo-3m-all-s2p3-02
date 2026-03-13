#ifndef FOUNDRY_IAction__H_
#define FOUNDRY_IAction__H_

#include "Define.h"
#include "ISerializable.h"
#include "Core/Event.hpp"

#include <glm/glm.hpp>

enum class ControlType : byte
{
	BUTTON = 0,
	SLIDER = 1,
	STICK = 2
};



class IAction /*: public ISerializable*/
{
public:
	ControlType GetType() const
	{
		return m_type;
	}

private:
	ControlType m_type;
	Event m_event;
};


class ButtonControl : public IAction
{
public:
	enum class ButtonState : byte
	{
		UP,
		DOWN
	};
	
	bool IsPressed();
	bool IsDown();
	bool IsUp();

	ButtonState GetCurrentState();

	Event m_event;

private:
	uint16 m_keyCode; // KEY_A
};


class SliderControl : public IAction
{
public:
	float GetPos();

	Event m_event;

private:
	float m_pos; // [-1;1]
};


class StickControl : public IAction
{
public:
	bool IsFlicked() const;
	glm::vec2 GetPos() const;

	Event m_event;

private:
	glm::vec2 m_pos; // [(-1; -1), (1; 1)]
};


#endif