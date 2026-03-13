#ifndef FOUNDRY_ACTION__H_
#define FOUNDRY_ACTION__H_

#include "Define.h"
#include "Serialization/ISerializable.h"
#include "Event.hpp"

#include <glm/glm.hpp>
#include <vector>

enum class ControlType : byte
{
	BUTTON = 1,
	SLIDER = 2,
	STICK = 3,

	UNDEFINED = 0
};

//template <typename RV, typename... Args>
class Action /*: public ISerializable*/
{
public:
	Action();
	virtual ~Action();
	
	template <typename RV, typename... Args>
	Action(std::string name, ControlType type, Event<RV(Args...)> event);


	void SetControlType(ControlType& type);
	ControlType GetControlType() const;


	template <typename RV, typename... Args>
	void SetEvent(Event<RV(Args...)> event);

	template <typename RV, typename... Args>
	Event<RV(Args...)>& GetEvent() const;

private:
	std::string m_name;
	std::vector<IControl*> m_controls; // besoin du 'p' si objet interfacique ? On se retrouve à la fin avec un objet pas un pointeur ?

	//Event<RV, Args...> m_event; // pointeur opaque ??
};


class IControl
{
public:
	IControl(ControlType type);
	IControl() = default;
	virtual ~IControl();

protected:
	ControlType m_type;

	friend Action;
};

class ButtonControl : public IControl
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


class SliderControl : public IControl
{
public:
	float GetPos();

private:
	float m_pos; // [-1;1]
};


class StickControl : public IControl
{
public:
	bool IsFlicked() const;
	glm::vec2 GetPos() const;

private:
	glm::vec2 m_pos; // [(-1; -1), (1; 1)]
};


#endif