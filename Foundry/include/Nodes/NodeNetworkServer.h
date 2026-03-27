#ifndef FOUNDRY_NODENETWORK_SERVER__H_
#define FOUNDRY_NODENETWORK_SERVER__H_

#include <thread>

#include "Node.h"
#include "Servers/NetworkServer.h"

class NodeNetworkServer : public Node
{
public:
	NodeNetworkServer(std::string const& name) : Node(name) {};
	~NodeNetworkServer() override;

	virtual void OnUpdate(double delta) override;

	bool Init(uint16 port);
	void SetNetworkRate(uint16 const rate) { m_networkRate = rate; }

private:
	void EventLoop();

protected:
	bool m_threadRunning = false;
	uint16 m_networkRate = 500;
	std::thread m_thread;
};

#endif