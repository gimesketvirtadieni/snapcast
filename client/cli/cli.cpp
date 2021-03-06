#include <cli/Action.h>
#include <cli/Actions.h>
#include "cli/cli.h"
#include "common/log.h"


namespace cli
{
	// global variables
	namespace internal
	{
		std::unique_ptr<CLIServer> processorCLIServer;
	}


    void addAction(std::string categoryName, std::string actionName, std::function<void(Context&)> action)
    {
		if (internal::processorCLIServer)
		{
			internal::processorCLIServer->getResource()->getActions()->addAction(Action(categoryName, actionName, action));
		}
    }


    Server& getCLIServer()
	{
		return *internal::processorCLIServer->getResource();
	}


	void initializeCLIServer(unsigned int port, unsigned int maxConnections, g3::LogWorker *logWorkerPtr)
	{
		// TODO: lock
		if (!internal::processorCLIServer)
		{
			internal::processorCLIServer = std::make_unique<conwrap::ProcessorAsio<Server>>(port, maxConnections, logWorkerPtr);

			// registering default actions
			auto actionsPtr = getCLIServer().getActions();
			actionsPtr->addDefaultCLIActions();
			actionsPtr->addDefaultLogActions();

			// registering SnapCast actions
			//actionsPtr->addAction(...Action());
		}
	}


	void startCLIServer()
	{
		if (internal::processorCLIServer)
		{
			// starting CLI server on its separate thread
			internal::processorCLIServer->process(
				[](auto context) {
					context.getResource()->start();
				}
			);
		}
	}


	void stopCLIServer()
	{
		if (internal::processorCLIServer)
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
}
