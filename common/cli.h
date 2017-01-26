#pragma once

#include <cli/Action.h>
#include <cli/Context.h>
#include <cli/Messages.h>
#include <cli/Server.h>
#include <conwrap/ProcessorAsio.hpp>
#include <g3log/logworker.hpp>


namespace cli
{
	using CLIServer = conwrap::ProcessorAsio<Server>;


    void    addAction(const char*, const char*, ActionHandler);
	Server& getCLIServer();
	void    initializeCLIServer(unsigned int port, unsigned int maxConnections, g3::LogWorker* logWorkerPtr);
	void    startCLIServer();
	void    stopCLIServer();
}
