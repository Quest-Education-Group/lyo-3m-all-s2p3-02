#ifndef _SERIALIZEOBJECT__H
#define _SERIALIZEOBJECT__H

#include "ISerializable.h"
#include "json.hpp"
#include "Registries/AutomaticRegister.hpp"
#include "Serialization/ISerializableEncaps.h"

#include <Define.h>
#include <Logger.hpp>
#include <string>

using json = nlohmann::json;

/*
	* Object used to convert Data of an object in json
*/
class SerializedObject
{
public:
	SerializedObject();

	void SetType(std::string className);

	std::string GetType() const;
	
	// Public
	void AddPrivateArray(std::string arrayName);
	void AddPrivateDictionnary(std::string dictionnaryName);

	template <typename T>
	void AddPrivateElement(std::string variableName, T const* variableData);

	template <typename T>
	void AddPrivateElementInDictionnary(std::string disctionnaryName, std::string name, T const* element);

	template <typename T>
	void AddPrivateElementInArray(std::string arrayName,T const* element);

	template <typename T>
	void GetPrivateElement(std::string elementName, T* outVariable) const;

	template <typename T>
	std::vector<T> GetPrivateArray(std::string arrayName) const;

	template <typename T>
	void GetPrivateElementInDictionnary(std::string dictionnaryName, std::string elementName, T* outVariable) const;

	// PUBLIC
	void AddPublicArray(std::string arrayName);
	void AddPublicDictionnary(std::string dictionnaryName);

	template <typename T>
	void AddPublicElement(std::string variableName, T const* variableData);

	template <typename T>
	void AddPublicElementInDictionnary(std::string disctionnaryName, std::string name, T const* element);

	template <typename T>
	void AddPublicElementInArray(std::string arrayName, T const* element);

	template <typename T>
	void GetPublicElement(std::string elementName, T* outVariable) const;

	template <typename T>
	std::vector<T> GetPublicArray(std::string arrayName) const;

	template <typename T>
	void GetPublicElementInDictionnary(std::string dictionnaryName, std::string elementName, T* outVariable) const;


	json const& GetJson() {return m_elementsInSerializedObject;}
	void SetJson(json const& json) { m_elementsInSerializedObject = json; } // Check d'error

private:
	json m_elementsInSerializedObject;
	friend class EditorSerializer;
};

// PRIVATE ELEMENT
template <typename T>
inline void SerializedObject::AddPrivateElement(std::string variableName, T const* variableData)
{
	m_elementsInSerializedObject["PRIVATE_DATAS"][variableName] = *variableData;
}
template <>
inline void SerializedObject::AddPrivateElement<ISerializable>(std::string variableName, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PRIVATE_DATAS"][variableName] = object.m_elementsInSerializedObject;
}
template <>
inline void SerializedObject::AddPrivateElement<glm::vec2>(std::string variableName, glm::vec2 const* variableData)
{
	SVec2 sVar = SVec2(*variableData);
	AddPrivateElement(variableName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElement<glm::vec3>(std::string variableName, glm::vec3 const* variableData)
{
	SVec3 sVar = SVec3(*variableData);
	AddPrivateElement(variableName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElement<glm::vec4>(std::string variableName, glm::vec4 const* variableData)
{
	SVec4 sVar = SVec4(*variableData);
	AddPrivateElement(variableName, static_cast<ISerializable const*>(&sVar));
}

// PRIVATE DICTIONNARY
template <typename T>
inline void SerializedObject::AddPrivateElementInDictionnary(std::string disctionnaryName, std::string name, T const* element)
{
	m_elementsInSerializedObject["PRIVATE_DATAS"][disctionnaryName][name] = *element;
}
template <>
inline void SerializedObject::AddPrivateElementInDictionnary<ISerializable>(std::string disctionnaryName, std::string name, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PRIVATE_DATAS"][disctionnaryName][name] = object.m_elementsInSerializedObject;
}
template <>
inline void SerializedObject::AddPrivateElementInDictionnary<glm::vec2>(std::string disctionnaryName, std::string name, glm::vec2 const* element)
{
	SVec2 sVar = SVec2(*element);
	AddPrivateElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElementInDictionnary<glm::vec3>(std::string disctionnaryName, std::string name, glm::vec3 const* element)
{
	SVec3 sVar = SVec3(*element);
	AddPrivateElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElementInDictionnary<glm::vec4>(std::string disctionnaryName, std::string name, glm::vec4 const* element)
{
	SVec4 sVar = SVec4(*element);
	AddPrivateElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}

// PRIVATE ARRAY
template <typename T>
inline void SerializedObject::AddPrivateElementInArray(std::string arrayName, T const* element)
{
	m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName].push_back(*element);
}
template <>
inline void SerializedObject::AddPrivateElementInArray<ISerializable>(std::string arrayName, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName].push_back(object.m_elementsInSerializedObject);
}
template <>
inline void SerializedObject::AddPrivateElementInArray<glm::vec2>(std::string arrayName, glm::vec2 const* element)
{
	SVec2 sVar = SVec2(*element);
	AddPrivateElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElementInArray<glm::vec3>(std::string arrayName, glm::vec3 const* element)
{
	SVec3 sVar = SVec3(*element);
	AddPrivateElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPrivateElementInArray<glm::vec4>(std::string arrayName, glm::vec4 const* element)
{
	SVec4 sVar = SVec4(*element);
	AddPrivateElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}

/// ==========================================================================================

// GET PRIVATE ELEMENT
template <typename T>
inline void SerializedObject::GetPrivateElement(std::string elementName, T* outVariable) const
{
	*outVariable = m_elementsInSerializedObject["PRIVATE_DATAS"][elementName];
}
template <>
inline void SerializedObject::GetPrivateElement<ISerializable>(std::string elementName, ISerializable* outVariable) const
{
	SerializedObject jsonObject = {};
	jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PRIVATE_DATAS"][elementName];
	ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
	outVariable->Deserialize(jsonObject);
}
template <>
inline void SerializedObject::GetPrivateElement<glm::vec2>(std::string elementName, glm::vec2* outVariable) const
{
	SVec2 sVar = SVec2(*outVariable);
	GetPrivateElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y };
}
template <>
inline void SerializedObject::GetPrivateElement<glm::vec3>(std::string elementName, glm::vec3* outVariable) const
{
	SVec3 sVar = SVec3(*outVariable);
	GetPrivateElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z };
}
template <>
inline void SerializedObject::GetPrivateElement<glm::vec4>(std::string elementName, glm::vec4* outVariable) const
{
	SVec4 sVar = SVec4(*outVariable);
	GetPrivateElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z, sVar.w };
}


// GET PRIVATE DICTIONNARY
template <typename T>
inline void SerializedObject::GetPrivateElementInDictionnary(std::string dictionnaryName, std::string elementName, T* outVariable) const
{
	*outVariable = m_elementsInSerializedObject["PRIVATE_DATAS"][dictionnaryName][elementName];
}
template <>
inline void SerializedObject::GetPrivateElementInDictionnary<ISerializable>(std::string dictionnaryName, std::string elementName, ISerializable* outVariable) const
{
	SerializedObject jsonObject = {};
	jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PRIVATE_DATAS"][dictionnaryName][elementName];
	ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
	outVariable->Deserialize(jsonObject);
}
template <>
inline void SerializedObject::GetPrivateElementInDictionnary<glm::vec2>(std::string dictionnaryName, std::string elementName, glm::vec2* outVariable) const
{
	SVec2 sVar = SVec2(*outVariable);
	GetPrivateElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y };
}
template <>
inline void SerializedObject::GetPrivateElementInDictionnary<glm::vec3>(std::string dictionnaryName, std::string elementName, glm::vec3* outVariable) const
{
	SVec3 sVar = SVec3(*outVariable);
	GetPrivateElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z };
}
template <>
inline void SerializedObject::GetPrivateElementInDictionnary<glm::vec4>(std::string dictionnaryName, std::string elementName, glm::vec4* outVariable) const
{
	SVec4 sVar = SVec4(*outVariable);
	GetPrivateElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z, sVar.w };
}

// GET PRIVATE ARRAY
template <typename T>
inline std::vector<T> SerializedObject::GetPrivateArray(std::string arrayName) const
{
	std::vector<T> array = {};

	for (uint32 i = 0; i < m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName].size(); i++)
	{
		array.push_back(*m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName][i]);
	}

	return array;
}
template <>
inline std::vector<ISerializable*> SerializedObject::GetPrivateArray(std::string arrayName) const
{
	std::vector<ISerializable*> array = {};
	for (uint32 i = 0; i < m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName].size(); i++)
	{
		SerializedObject jsonObject = {};
		jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PRIVATE_DATAS"][arrayName][i];
		ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
		outObject->Deserialize(jsonObject);
		array.push_back(outObject);
	}

	return array;
}
template <>
inline std::vector<glm::vec2> SerializedObject::GetPrivateArray(std::string arrayName) const
{
	std::vector<glm::vec2> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPrivateArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec2* vec = static_cast<SVec2*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y });
	}
	return arrayOfElement;
}
template <>
inline std::vector<glm::vec3> SerializedObject::GetPrivateArray(std::string arrayName) const
{
	std::vector<glm::vec3> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPrivateArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec3* vec = static_cast<SVec3*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y,vec->z });
	}
	return arrayOfElement;
}
template <>
inline std::vector<glm::vec4> SerializedObject::GetPrivateArray(std::string arrayName) const
{
	std::vector<glm::vec4> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPrivateArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec4* vec = static_cast<SVec4*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y,vec->z,vec->w });
	}
	return arrayOfElement;
}

// =============== PUBLIC =================
// PUBLIC ELEMENT
template <typename T>
inline void SerializedObject::AddPublicElement(std::string variableName, T const* variableData)
{
	m_elementsInSerializedObject["PUBLIC_DATAS"][variableName] = *variableData;
}
template <>
inline void SerializedObject::AddPublicElement<ISerializable>(std::string variableName, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PUBLIC_DATAS"][variableName] = object.m_elementsInSerializedObject;
}
template <>
inline void SerializedObject::AddPublicElement<glm::vec2>(std::string variableName, glm::vec2 const* variableData)
{
	SVec2 sVar = SVec2(*variableData);
	AddPublicElement(variableName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElement<glm::vec3>(std::string variableName, glm::vec3 const* variableData)
{
	SVec3 sVar = SVec3(*variableData);
	AddPublicElement(variableName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElement<glm::vec4>(std::string variableName, glm::vec4 const* variableData)
{
	SVec4 sVar = SVec4(*variableData);
	AddPublicElement(variableName, static_cast<ISerializable const*>(&sVar));
}


// PUBLIC DICTIONNARY
template <typename T>
inline void SerializedObject::AddPublicElementInDictionnary(std::string disctionnaryName, std::string name, T const* element)
{
	m_elementsInSerializedObject["PUBLIC_DATAS"][disctionnaryName][name] = *element;
}
template <>
inline void SerializedObject::AddPublicElementInDictionnary<ISerializable>(std::string disctionnaryName, std::string name, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PUBLIC_DATAS"][disctionnaryName][name] = object.m_elementsInSerializedObject;
}
template <>
inline void SerializedObject::AddPublicElementInDictionnary<glm::vec2>(std::string disctionnaryName, std::string name, glm::vec2 const* element)
{
	SVec2 sVar = SVec2(*element);
	AddPublicElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElementInDictionnary<glm::vec3>(std::string disctionnaryName, std::string name, glm::vec3 const* element)
{
	SVec3 sVar = SVec3(*element);
	AddPublicElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElementInDictionnary<glm::vec4>(std::string disctionnaryName, std::string name, glm::vec4 const* element)
{
	SVec4 sVar = SVec4(*element);
	AddPublicElementInDictionnary(disctionnaryName, name, static_cast<ISerializable const*>(&sVar));
}


// ADD PUBLIC ARRAY
template <typename T>
inline void SerializedObject::AddPublicElementInArray(std::string arrayName, T const* element)
{
	m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName].push_back(element);
}
template <>
inline void SerializedObject::AddPublicElementInArray<ISerializable>(std::string arrayName, ISerializable const* variableData)
{
	SerializedObject object = SerializedObject();
	if (variableData != nullptr)
		variableData->Serialize(object);

	m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName].push_back(object.m_elementsInSerializedObject);
}
template <>
inline void SerializedObject::AddPublicElementInArray<glm::vec2>(std::string arrayName, glm::vec2 const* element)
{
	SVec2 sVar = SVec2(*element);
	AddPublicElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElementInArray<glm::vec3>(std::string arrayName, glm::vec3 const* element)
{
	SVec3 sVar = SVec3(*element);
	AddPublicElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}
template <>
inline void SerializedObject::AddPublicElementInArray<glm::vec4>(std::string arrayName, glm::vec4 const* element)
{
	SVec4 sVar = SVec4(*element);
	AddPublicElementInArray(arrayName, static_cast<ISerializable const*>(&sVar));
}


/// ==========================================================================================

// GET PUBLIC ELEMENT
template <typename T>
inline void SerializedObject::GetPublicElement(std::string elementName, T* outVariable) const
{
	*outVariable = m_elementsInSerializedObject["PUBLIC_DATAS"][elementName]/*["DATA"]*/;
}
template <>
inline void SerializedObject::GetPublicElement<ISerializable>(std::string elementName, ISerializable* outVariable) const
{
	SerializedObject jsonObject = {};
	jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PUBLIC_DATAS"][elementName];
	ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
	outVariable->Deserialize(jsonObject);
}
template <>
inline void SerializedObject::GetPublicElement<glm::vec2>(std::string elementName, glm::vec2* outVariable) const
{
	SVec2 sVar = SVec2(*outVariable);
	GetPublicElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y };
}
template <>
inline void SerializedObject::GetPublicElement<glm::vec3>(std::string elementName, glm::vec3* outVariable) const
{
	SVec3 sVar = SVec3(*outVariable);
	GetPublicElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z };
}
template <>
inline void SerializedObject::GetPublicElement<glm::vec4>(std::string elementName, glm::vec4* outVariable) const
{
	SVec4 sVar = SVec4(*outVariable);
	GetPublicElement(elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z, sVar.w };
}

// GET PUBLIC DICTIONNARY
template <typename T>
inline void SerializedObject::GetPublicElementInDictionnary(std::string dictionnaryName, std::string elementName, T* outVariable) const
{
	*outVariable = m_elementsInSerializedObject["PUBLIC_DATAS"][dictionnaryName][elementName];
}
template <>
inline void SerializedObject::GetPublicElementInDictionnary<ISerializable>(std::string dictionnaryName, std::string elementName, ISerializable* outVariable) const
{
	SerializedObject jsonObject = {};
	jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PUBLIC_DATAS"][dictionnaryName][elementName];
	ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
	outVariable->Deserialize(jsonObject);
}
template <>
inline void SerializedObject::GetPublicElementInDictionnary<glm::vec2>(std::string dictionnaryName, std::string elementName, glm::vec2* outVariable) const
{
	SVec2 sVar = SVec2(*outVariable);
	GetPublicElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y };
}
template <>
inline void SerializedObject::GetPublicElementInDictionnary<glm::vec3>(std::string dictionnaryName, std::string elementName, glm::vec3* outVariable) const
{
	SVec3 sVar = SVec3(*outVariable);
	GetPublicElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z };
}
template <>
inline void SerializedObject::GetPublicElementInDictionnary<glm::vec4>(std::string dictionnaryName, std::string elementName, glm::vec4* outVariable) const
{
	SVec4 sVar = SVec4(*outVariable);
	GetPublicElementInDictionnary(dictionnaryName, elementName, static_cast<ISerializable*>(&sVar));
	*outVariable = { sVar.x,sVar.y, sVar.z, sVar.w };
}


// GET PUBLIC ARRAY
template <typename T>
inline std::vector<T> SerializedObject::GetPublicArray(std::string arrayName) const
{
	std::vector<T> array = {};

	for (uint32 i = 0; i < m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName].size(); i++)
	{
		array.push_back(m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName][i]);
	}

	return array;
}
template <>
inline std::vector<ISerializable*> SerializedObject::GetPublicArray(std::string arrayName) const
{
	std::vector<ISerializable*> array = {};
	for (uint32 i = 0; i < m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName].size(); i++)
	{
		SerializedObject jsonObject = {};
		jsonObject.m_elementsInSerializedObject = m_elementsInSerializedObject["PUBLIC_DATAS"][arrayName][i];
		ISerializable* outObject = AutomaticRegisterISerializable<ISerializable>::create(jsonObject.GetType());
		outObject->Deserialize(jsonObject);
		array.push_back(outObject);
	}

	return array;
}
template <>
inline std::vector<glm::vec2> SerializedObject::GetPublicArray(std::string arrayName) const
{
	std::vector<glm::vec2> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPublicArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec2* vec = static_cast<SVec2*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y });
	}
	return arrayOfElement;
}
template <>
inline std::vector<glm::vec3> SerializedObject::GetPublicArray(std::string arrayName) const
{
	std::vector<glm::vec3> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPublicArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec3* vec = static_cast<SVec3*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y,vec->z });
	}
	return arrayOfElement;
}
template <>
inline std::vector<glm::vec4> SerializedObject::GetPublicArray(std::string arrayName) const
{
	std::vector<glm::vec4> arrayOfElement = {};
	std::vector<ISerializable*> array = GetPublicArray<ISerializable*>(arrayName);
	for (uint32 i = 0; i < array.size(); i++)
	{
		SVec4* vec = static_cast<SVec4*>(array[i]);
		arrayOfElement.push_back({ vec->x,vec->y,vec->z,vec->w });
	}
	return arrayOfElement;
}


#endif

