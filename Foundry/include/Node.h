#ifndef NODE__H_
#define NODE__H_

#include "Debug.h"
#include "Define.h"
#include "Event.hpp"
#include "Logger.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <sstream>
#include <type_traits>
#include <vector>

class Node;
class SceneTree;

template <typename T>
concept NodeType = std::is_base_of_v<Node, T>;

//Maybe move this in a global namespace
template <typename T>
using OptionalRef = std::optional<std::reference_wrapper<T>>;

//Base class off every node in the tree
class Node
{

protected:
	//private constructor for in-class initialization
	//====Constructors======
	Node();
	Node(std::string const& name);
	Node(Node const& other) = delete;
	Node(Node&& other) noexcept = delete;

	Node& operator=(Node const& other) = delete;
	Node& operator=(Node&& other) noexcept = delete;

public:
	virtual ~Node();

	virtual void OnUpdate(float delta) { DEBUG("Node : " << m_name << ANSI_GOLD << " is updated" << ANSI_RESET << std::endl); };
	void Update(float delta);

	void AddChild(std::unique_ptr<Node>&& child);
	void AddChild(std::unique_ptr<Node>& child);
	void AddSibling(std::unique_ptr<Node>&& sibling);
	void AddSibling(std::unique_ptr<Node>& sibling);

	void RemoveChild(Node& child);
	void RemoveChild(std::string const& childName);

	template <NodeType T>
	OptionalRef<T> FindChild(); //recursive children search
	OptionalRef<Node> FindChild(std::string const& name); //recursive children search

	Node& GetChild(uint32 index);
	std::vector<std::reference_wrapper<Node>> GetChildren();
	int32 GetChildCount();

	template <NodeType T>
	T& GetNode(std::string const& path);

	//Only destroy the node if it has a parent
	void Destroy();
	virtual void Reparent(Node& newParent, bool keepGlobalTransform = true);
	void MoveChild(Node const& child, int32 to);

	//override this method if the inherited node is not trivially copyable
	virtual std::unique_ptr<Node> Clone();

	std::string GetName();
	Node* GetParent();
	SceneTree* GetSceneTree();

	//====Static Methods======
	template <NodeType T>
	static std::unique_ptr<T> CreateNode(std::string const& name);


	//====Event======
	Event<void(Node&)> OnSceneEnter;
	Event<void(Node&)> OnSceneLeave;

private:
    void AttachChildImmediate(std::unique_ptr<Node>& child);

    friend class EngineServer;

private:
	std::string m_name; //unique among siblings
	Node* m_pOwner = nullptr;
	SceneTree* m_pSceneTree = nullptr;

	std::unordered_map<std::string, std::unique_ptr<Node>> m_children {};
	std::vector<std::string> m_childrenOrder {};

	friend class unique_ptr;
};


//=== Templated function def ====
template <NodeType T>
std::unique_ptr<T> Node::CreateNode(std::string const& name)
{
    struct concrete_Node: public T {
        concrete_Node(std::string const& name) : T(name) {}
    };

    return std::make_unique<concrete_Node>(name);
}

template <NodeType T>
OptionalRef<T> Node::FindChild()
{
	for (auto&[nodeName, nodePtr] : m_children)
	{
		if (dynamic_cast<T*>(nodePtr.get()))
			return {*nodePtr.get()};
	}
	return {};
}

template <NodeType T>
T& Node::GetNode(std::string const& path)
{
    std::stringstream ss(path);
    std::string token;

    //TODO Add this when scene tree is done
    //Node* pNode = path[0] == '/' ? m_pSceneTree.root : this;

    Node* pNode = this;
    while(std::getline(ss, token, '/'))
    {
        pNode = pNode->m_children[token].get();
    }

    return *static_cast<T*>(pNode);
}

#endif // !NODE__H_
