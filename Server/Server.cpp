#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <memory>
#include <Connection.h>



boost::interprocess::shared_memory_object* AllocateSharedMemory(const char* MemoryBlockName)
{
	boost::interprocess::shared_memory_object* shm_obj = new boost::interprocess::shared_memory_object
	(
		boost::interprocess::open_or_create,
		MemoryBlockName,
		boost::interprocess::read_write
	);
	shm_obj->truncate(sizeof(Connection));
	return shm_obj;
}

int main()
{
	int stopper = 0;
	unsigned short port_num = 3333;

	boost::interprocess::shared_memory_object* memory_block_pointer = AllocateSharedMemory("SharedMemory");
	boost::interprocess::mapped_region memory_region(*memory_block_pointer, boost::interprocess::read_write);
	Connection* connection = new (memory_region.get_address()) Connection;
	boost::asio::io_context server_io_context;
	boost::asio::ip::tcp::endpoint Endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port_num);;
	boost::asio::ip::tcp::acceptor Acceptor = boost::asio::ip::tcp::acceptor(server_io_context, Endpoint);
	boost::asio::ip::tcp::socket Socket = boost::asio::ip::tcp::socket(server_io_context);
	std::cout << "Waiting connection..." << std::endl;
	Acceptor.accept(Socket);

	connection->raw_ip_address = Socket.remote_endpoint().address().to_string();
	connection->port_num = 3333;

	//shared_object_pointer->SayHi = (void (Request::*)())(&(ServerRequest::SayHi));
	//shared_object_pointer->SayHello = (void (Request::*)())(&(ServerRequest::SayHello));

	std::cout << "Connected!" << std::endl;
	char input = '0';
	while (input != 'z')
	{
		std::cin >> input;
		/*std::this_thread::sleep_for(std::chrono::seconds(20));*/
	}

	boost::interprocess::shared_memory_object::remove(memory_block_pointer->get_name());
	delete memory_block_pointer;

	return 0;
}