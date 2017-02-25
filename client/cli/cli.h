#pragma once

#include <cli/Context.h>
#include <cli/Messages.h>
#include <cli/Server.h>
#include <conwrap/ProcessorAsio.hpp>
#include <g3log/logworker.hpp>
#include <string>


namespace cli
{
	using CLIServer = conwrap::ProcessorAsio<Server>;


    void    addAction(std::string, std::string, std::function<void(Context&)>);
	Server& getCLIServer();
	void    initializeCLIServer(unsigned int port, unsigned int maxConnections, g3::LogWorker* logWorkerPtr);
	void    startCLIServer();
	void    stopCLIServer();
}
