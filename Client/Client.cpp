#include <iostream>
#include <string>
#include "boost/asio.hpp"

int main()
{
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	boost::asio::ip::tcp::endpoint server_endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(raw_ip_address), port_num);
	boost::asio::io_service server_io_service;
	boost::asio::ip::tcp::socket server_socket(server_io_service, server_endpoint.protocol());
	std::cout << "Connecting to server" << std::endl;
	server_socket.connect(server_endpoint);
	std::cout << "Connected to server" << std::endl;
	
	boost::asio::ip::tcp::endpoint driver_endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(raw_ip_address), port_num);
	boost::asio::io_context server_io_context;
	boost::asio::ip::tcp::acceptor Acceptor = boost::asio::ip::tcp::acceptor(server_io_context, driver_endpoint);
	std::cout << "Waiting driver" << std::endl;
	boost::asio::ip::tcp::socket driver_socket = Acceptor.accept();
	std::cout << "Connected to driver" << std::endl;
	std::string greet;
	std::cout << "Press x to say hey ya, y to say hello, and z to exit!" << std::endl;
	char input = '0';
	while (input != 'z')
	{
			std::cin >> input;
			if (input == 'x')
			{
				
				greet = "hey ya";
				size_t greet_size = greet.size();
				char* buffer = new char[greet_size];

				std::memcpy(buffer, greet.c_str(), greet_size);
				boost::asio::write(driver_socket, boost::asio::buffer(buffer, greet_size));

				delete[] buffer;
			}
			if (input == 'y')
			{
				greet = "hello!";
				size_t greet_size = greet.size();
				char* buffer = new char[greet_size];

				std::memcpy(buffer, greet.c_str(), greet_size);
				boost::asio::write(driver_socket, boost::asio::buffer(buffer, greet_size));

				delete[] buffer;
			}
			if (input == 'z')
			{
				greet = "close!";
				size_t greet_size = greet.size();
				char* buffer = new char[greet_size];

				std::memcpy(buffer, greet.c_str(), greet_size);
				boost::asio::write(driver_socket, boost::asio::buffer(buffer, greet_size));

				delete[] buffer;
			}
			
	}

	return 0;
}
