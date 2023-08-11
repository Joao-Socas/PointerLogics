#include <iostream>
#include "boost/interprocess/shared_memory_object.hpp"
#include "boost/interprocess/mapped_region.hpp"
#include "Connection.h"
#include "Request.h"

boost::interprocess::shared_memory_object* OpenSharedMemory(const char* MemoryBlockName)
{
	boost::interprocess::shared_memory_object* shm_obj = new boost::interprocess::shared_memory_object
	(
		boost::interprocess::open_only,
		MemoryBlockName,
		boost::interprocess::read_write
	);
	return shm_obj;
}

int main()
{
	boost::interprocess::shared_memory_object* memory_block_pointer = OpenSharedMemory("SharedMemory");
	boost::interprocess::mapped_region MemoryRegion(*memory_block_pointer, boost::interprocess::read_write);
	Connection* connection = (Connection*)MemoryRegion.get_address();

	boost::asio::ip::tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(connection->raw_ip_address), connection->port_num);
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());
	try
	{
		std::cout << "Trying to connect with client" << std::endl;
		socket.connect(endpoint);
	}
	catch (const boost::system::system_error& err)
	{
		std::cout << err.what() << std::endl;
		delete memory_block_pointer;
		return 0;
		
	}
	std::cout << "Connected to client" << std::endl;
	std::string greet;
	greet = "hello!";
	size_t buffer_size = greet.size();
	char* buffer = new char[buffer_size];
	bool exit = false;
	while (not exit)
	{
		boost::asio::read(socket, boost::asio::buffer(buffer, buffer_size));
		std::memcpy((void*)greet.c_str(), buffer, buffer_size);
		std::cout << greet << std::endl;

		if (greet.compare(std::string("close!")) == 0)
		{
			
		}
	}

	delete memory_block_pointer;
}
