#ifndef FOUNDRY_ACTIONMAP__H_
#define FOUNDRY_ACTIONMAP__H_

#include "IAction.h"

#include <string_view>
#include <unordered_map>
#include <vector>

// string ==> string_view const non modifiable readonly

class ActionMap /*: public ISerializable*/
{
public:
	ActionMap() : m_actions() {};
	~ActionMap() = default;

	ActionMap(ActionMap const& other) = delete;
	void operator=(ActionMap const& other) = delete;

	ActionMap(ActionMap&& other) = delete;
	void operator=(ActionMap&& other) = delete;


	bool			AddAction(std::string const& name, IAction* input);
	bool			DeleteAction(std::string const& name);

	bool			SetAction(std::string const& name, Event* pAction);
	void			ExecuteAction(std::string const& name) const;
	
	ButtonControl&  GetActionButton(std::string const& name) const;
	SliderControl&  GetActionSlider(std::string const& name) const;
	StickControl&   GetActionStick(std::string const& name) const;
	

	void			Length() const { return m_actions.size(); }
	void			Pop(std::string const& name);
	void			Replace(std::string const& old, std::string const& name);

private:
	std::unordered_map<std::string, std::vector<IAction*>> m_actions;
};


#endif