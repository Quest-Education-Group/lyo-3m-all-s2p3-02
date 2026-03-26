#ifndef FOUNDRY_ACTIONMAPPROXY__H_
#define FOUNDRY_ACTIONMAPPROXY__H_

#include "ActionMap.h"
#include "Event.hpp"
#include "Registries/AutomaticRegisterProxy.hpp"
#include "Scripting/Binder.h"
#include "sol/sol.hpp"

#include <string_view>
#include <unordered_map>
#include <string>

namespace actionmap_proxy
{
	inline auto Create = []()
		{
			return ActionMap();
		};

	inline auto Emplace = [](ActionMap& actionMap, std::string const& name, Action* pAction)
		{
			actionMap.Emplace(name, pAction);
		};

	inline auto Erase = [](ActionMap& actionMap, std::string_view const& name)
		{
			actionMap.Erase(name);
		};

	inline auto GetAction = [](ActionMap& actionMap, std::string_view const& name)
		{
			return actionMap[name];
		};

	inline auto Length = [](ActionMap& actionMap)
		{
			return actionMap.Length();
		};

	inline auto Rename = [](ActionMap& actionMap, std::string_view const& old, std::string_view const& name)
		{
			actionMap.Rename(old, name);
		}

};

struct ActionMapProxyBinding
{
	static void Bind(Binder& binder)
	{
		auto actionMap = binder.GetOrCreateNamespace("actionmap");
		actionMap.new_usertype<ActionMap>("ActionMap", sol::constructors<ActionMap()>(),
			"m_actions", &ActionMap::m_actions);
		actionMap.set_function("Create", actionmap_proxy::Create);
		actionMap.set_function("Emplace", actionmap_proxy::Emplace);
		actionMap.set_function("Erase", actionmap_proxy::Erase);
		actionMap.set_function("GetAction", actionmap_proxy::GetAction);
		actionMap.set_function("Length", actionmap_proxy::Length);
		actionMap.set_function("Rename", actionmap_proxy::Rename);
	}
};

REGISTER_PROXY(ActionMapProxyBinding, ActionMapProxy);

#endif