#include "Action.h"
#include "IControl.h"

Action::Action() : m_controls(), m_event() 
{
	EventManager::getKey += [&](EventInput in, EventAction ac)
		{
			for (int i = 0; i < m_controls.size(); i++)
			{
				if (in == m_controls[i]->GetEventInput())
					m_event.Invoke(*m_controls[i]);
			}
		};
}

Action::Action(ControlType controlType, Event<void(IControl&)> event, EventInput eventInput) :
	m_event(event)
{
	AddControl(controlType, eventInput);
	EventManager::getKey += [&](EventInput in, EventAction ac)
		{
			for (int i = 0; i < m_controls.size(); i++)
			{
				if (in == m_controls[i]->GetEventInput() && ac == EventAction::PRESS)
					m_event.Invoke(*m_controls[i]);
			}
		};
}

Action::~Action() {}


void Action::SetEvent(Event<void(IControl&)> event)
{
	m_event = event;
}

Event<void(IControl&)> Action::GetEvent() const
{
	return m_event;
}

uint32 Action::AddControl(ControlType const& type, EventInput const& eventInput)
{
	switch (type)
	{
	case ControlType::BUTTON:
		m_controls.push_back(new ButtonControl(eventInput, this));
		break;
	case ControlType::SLIDER:
		m_controls.push_back(new SliderControl(eventInput, this));
		break;
	case ControlType::STICK:
		m_controls.push_back(new StickControl(eventInput, this));
		break;
	}

	m_controls.back()->SetAction(this);

	return m_controls.size() - 1;
}

IControl* Action::GetControl(uint32 index)
{
	if (index > m_controls.size())
		return nullptr;

	return m_controls[index];
}
