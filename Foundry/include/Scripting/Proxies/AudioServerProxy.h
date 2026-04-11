#ifndef FOUNDRY_AUDIOPROXY__H_
#define FOUNDRY_AUDIOPROXY__H_

class Binder;

struct AudioChannel;

struct AudioProxyBinding 
{
	static void Bind(Binder& binder);
};

#endif