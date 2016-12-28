#include "cli.h"
#include <cli/Actions.h>


namespace cli
{
	// global variables
	namespace internal
	{
		std::unique_ptr<CLIServer> processorCLIServer;
	}


    void addAction(const char*, const char*, ActionHandler)
    {
    	// TODO:...
    }


    Server& getCLIServer()
	{
		return *internal::processorCLIServer->getResource();
	}


	void initializeCLIServer(unsigned int port, unsigned int maxConnections, g3::LogWorker *logWorkerPtr)
	{
		// TODO: lock
		// TODO: only once
		internal::processorCLIServer = std::make_unique<conwrap::ProcessorAsio<Server>>(port, maxConnections, logWorkerPtr);

		// registering default actions
		auto actions = getCLIServer().getActions();
		actions.addDefaultCLIActions();
		actions.addDefaultLogActions();
	}


	void startCLIServer()
	{
		// starting CLI server on its separate thread
		internal::processorCLIServer->process(
			[](auto context) {
				context.getResource()->start();
			}
		);
	}


	void stopCLIServer()
	{
		// stopping CLI server
		internal::processorCLIServer->process(
			[](auto context) {
				context.getResource()->stop();
			}
		);

		// deleting CLI server; it will wait for all tasks to complete
		internal::processorCLIServer.reset();
	}
}
