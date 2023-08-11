#pragma once
#include <iostream>
#include "Request.h"

class ServerRequest : public Request
{
public:
	void SayHi() { std::cout << "Hi from server, asked from client!" << std::endl; }
	void SayHello() { std::cout << "Hello from server, asked from client!" << std::endl; }
};