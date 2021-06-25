
#include "MyServer.h"
#include "MyThread.h"
#include "Manager.h"
#include "ProcessSingleClient.h"
#include <iostream>     ///< cout
#include <cstring>      ///< memset
#include <errno.h>      ///< errno
#include <sys/socket.h> ///< socket
#include <netinet/in.h> ///< sockaddr_in
#include <arpa/inet.h>  ///< getsockname
#include <unistd.h>     ///< close
#include "GetLocalAddress.h"
#include <boost/program_options.hpp>
#include <boost/program_options.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <algorithm>
#include <iterator>
using namespace boost;
namespace po = boost::program_options;

const char logName[] = "server.log";


int main(int argc, char const *argv[])
{

	int returnValue;
	std::string localIP;
	std::string logServer;
	std::string logPath = "./log/";
	unsigned short localPort;
	unsigned short maxConnexion;
	// command parser
	try 
		{
			po::options_description desc("Allowed options");
			desc.add_options()
				("help,h", "produce help message")
				("port,p", po::value<unsigned short>(&localPort)->implicit_value(60000)
					->default_value(0,"no"),
					"server port number.")
				("connexion,c", po::value<unsigned short>(&maxConnexion)->implicit_value(10)
					->default_value(5,"few"),
					"server max connexion.")
				("log,l", po::value<std::string>(&logServer)->default_value("server.log")->implicit_value("server.log"), "server log name"
				);	
			// Point out that all unknown values ​​should be converted to the value of the "input-file" option.
					// Also use the command_line_parser class instead of parse_command_line 
			po::variables_map vm;        
			po::store(po::parse_command_line(argc, argv, desc), vm);
			po::notify(vm);  

			if (vm.count("help")) 
			{
				std::cout<< "Usage: options_description [options]\n";
				std::cout<< desc;
				return 0;
			}
		}
		catch(std::exception& e)
		{
			std::cout<< e.what() << "\n";
			return 1;
		}

	// End of command parser

	za::MyServer myServer(localPort, maxConnexion);
	if(myServer.setLog(logPath + myServer.getCurrentTime()+logName) < 0) return -1;
	if(myServer.showServerIP() < 0) return -1;
	if(myServer.createServerForBindAndListen() < 0) return -1;
	if(myServer.bindServerToPortNumber() < 0) return -1;
	if(myServer.showServerPort() < 0) return -1;
	if(myServer.listenToNewClientConnexion()< 0) return -1;

	while (true)
	{

        if(myServer.acceptToMakeConnexionWithClient() < 0) return -1;

        za::MyThread *myThread = new za::MyThread(new za::ProcessSingleClient(), myServer);
        myThread -> createMyThread();
	}
	
	return 0;
}
