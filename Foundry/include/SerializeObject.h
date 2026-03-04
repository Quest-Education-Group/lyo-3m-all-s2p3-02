#ifndef _SERIALIZEOBJECT__H
#define _SERIALIZEOBJECT__H

#include "ISerializable.h"
#include "json.hpp"

#include <Define.h>
#include <Logger.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;


class SerializedObject
{
public:

	void SetType(std::string type);
	
	void AddArray(std::string arrayName);
	void AddDictionnary(std::string dictionnaryName);

	template <typename T>
	void AddElement(std::string variableName, T const& variableData);
	template<ISerializable const&>
	void AddElement(std::string variableName, ISerializable const& variableData);

	template <typename T>
	void AddElementInDictionnary(std::string disctionnaryName, std::string name, T const& element);
	template<ISerializable const&>
	void AddElementInDictionnary(std::string disctionnaryName, std::string name, ISerializable const& variableData);

	template <typename T>
	void AddElementInArray(std::string arrayName,T const& element);
	template<ISerializable const&>
	void AddElementInArray(std::string arrayName, ISerializable const& variableData);


	void GetType(std::string& type) const;
	
	template <typename T>
	void GetElement(std::string elementName, T& outVariable) const;
	template <ISerializable&>
	void GetElement(std::string elementName, ISerializable& outVariable) const;

	template <typename T>
	void GetElementInArray(std::string arrayName, uint32 index, std::string elementName, T& outVariable) const;
	template <ISerializable&>
	void GetElementInArray(std::string arrayName, uint32 index, std::string elementName, ISerializable& outVariable) const;

	template <typename T>
	void GetElementInDictionnary(std::string dictionnaryName, std::string elementName, T& outVariable) const;
	template <ISerializable&>
	void GetElementInDictionnary(std::string dictionnaryName, std::string elementName, ISerializable& outVariable) const;

private:
	std::vector<std::string> m_existingNames;
	json m_elementsInSerializedObject;
	friend class EditorSerializer;
};

template <typename T>
void SerializedObject::AddElement(std::string variableName, T const& variableData)
{
	if (std::find(m_existingNames.begin(),m_existingNames.end(),variableName) != m_existingNames.end())
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Variable " + variableName + " already store in Data");
		return;
	}
	m_elementsInSerializedObject[variableName] = variableData;
	m_existingNames.push_back(variableName);
}
template <ISerializable const&>
void SerializedObject::AddElement(std::string variableName, ISerializable const& variableData)
{
	if (std::find(m_existingNames.begin(), m_existingNames.end(), variableName) != m_existingNames.end())
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Variable " + variableName + " already store in Data");
		return;
	}

	SerializedObject object = {};
	variableData.Serialize(object);

	m_elementsInSerializedObject[variableName] = object.m_elementsInSerializedObject;
	m_existingNames.push_back(variableName);
}


template <typename T>
void SerializedObject::AddElementInDictionnary(std::string disctionnaryName, std::string name, T const& element)
{
	if (std::find(m_existingNames.begin(), m_existingNames.end(), disctionnaryName +"d"+name) != m_existingNames.end())
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Variable " + name + " already store in Dictionnary " + disctionnaryName);
		return;
	}
	m_elementsInSerializedObject[disctionnaryName][name] = element;
	m_existingNames.push_back(disctionnaryName+"d"+name);
}
template <ISerializable const&>
void SerializedObject::AddElementInDictionnary(std::string disctionnaryName, std::string name, ISerializable const& variableData)
{
	if (std::find(m_existingNames.begin(), m_existingNames.end(), disctionnaryName + "d" + name) != m_existingNames.end())
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Variable " + name + " already store in Dictionnary " + disctionnaryName);
		return;
	}
	SerializedObject object = {};
	variableData.Serialize(object);
	m_elementsInSerializedObject[disctionnaryName][name] = object.m_elementsInSerializedObject;
	m_existingNames.push_back(disctionnaryName + "d" + name);
}

template <typename T>
void SerializedObject::AddElementInArray(std::string arrayName, T const& element)
{
	m_elementsInSerializedObject[arrayName].push_back(element);
}
template <ISerializable const&>
void SerializedObject::AddElementInArray(std::string arrayName, ISerializable const& variableData)
{
	SerializedObject object = {};
	variableData.Serialize(object);
	m_elementsInSerializedObject[arrayName].push_back(object.m_elementsInSerializedObject);
}

/// ==========================================================================================

template <typename T>
void SerializedObject::GetElement(std::string elementName, T& outVariable) const
{
	outVariable = m_elementsInSerializedObject[elementName];
}
template <ISerializable&>
void SerializedObject::GetElement(std::string elementName, ISerializable& outVariable) const
{
	SerializedObject object = {};
	object.m_elementsInSerializedObject = m_elementsInSerializedObject[elementName];
	outVariable.Deserialize(object);
}


template <typename T>
void SerializedObject::GetElementInDictionnary(std::string dictionnaryName, std::string elementName, T& outVariable) const
{
	outVariable = m_elementsInSerializedObject[dictionnaryName][elementName];
}
template <ISerializable&>
void SerializedObject::GetElementInDictionnary(std::string dictionnaryName, std::string elementName, ISerializable& outVariable) const
{
	SerializedObject object = {};
	object.m_elementsInSerializedObject = m_elementsInSerializedObject[dictionnaryName][elementName];
	outVariable.Deserialize(object);

}

template <typename T>
void SerializedObject::GetElementInArray(std::string arrayName, uint32 index, std::string elementName, T& outVariable) const
{
	outVariable = m_elementsInSerializedObject[arrayName][index];
}
template <ISerializable&>
void SerializedObject::GetElementInArray(std::string arrayName, uint32 index, std::string elementName, ISerializable& outVariable) const
{
	SerializedObject object = {};
	object.m_elementsInSerializedObject = m_elementsInSerializedObject[arrayName][index];
	outVariable.Deserialize(object);
}


#endif

