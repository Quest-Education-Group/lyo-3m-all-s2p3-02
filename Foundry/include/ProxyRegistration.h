#ifndef FOUNDRY_PROXY_REG__H_
#define FOUNDRY_PROXY_REG__H_

#include "Scripting/Binder.h"

#include "Node.h"
#include "Nodes/Node3D.h"

#define BIND_PROXY(B, X) X::Proxy::ProxyBinding __##X##__; __##X##__.Bind(B)

static void REGISTER_PROXY(Binder& binder)
{
	binder.BindFunction("CreateNode", &Node::Proxy::CreateNodeProxy);

	BIND_PROXY(binder, Node);
	BIND_PROXY(binder, Node3D);
}

#endif // !FOUNDRY_PROXY_REG__H_
