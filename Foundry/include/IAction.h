#ifndef FOUNDRY_IAction__H_
#define FOUNDRY_IAction__H_

#include "Define.h"
#include "ISerializable.h"
#include "Event.hpp"

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
	virtual IAction();
	virtual IAction(std::string name, ControlType type, Event event);
	virtual ~IAction();

	void SetControlType(ControlType& type);
	ControlType GetControlType() const;

	template <typename RV, typename... Args>
	void SetEvent<RV(Args...)>(Event& event);
	Event& GetEvent() const;

private:
	std::string m_name;
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

private:
	uint16 m_keyCode; // KEY_A
};


class SliderControl : public IAction
{
public:
	float GetPos();

private:
	float m_pos; // [-1;1]
};


class StickControl : public IAction
{
public:
	bool IsFlicked() const;
	glm::vec2 GetPos() const;

private:
	glm::vec2 m_pos; // [(-1; -1), (1; 1)]
};


#endif