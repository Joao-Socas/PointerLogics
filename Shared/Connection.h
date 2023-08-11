#pragma once
#include <memory>
#include "boost/asio.hpp"
enum IPVersion
{
	IPV4,
	IPV6
};
class Connection
{
public:
	std::string raw_ip_address = "127.0.0.1";
	unsigned short port_num = 3333;
	bool Connected = false;
	bool Exit = false;
};