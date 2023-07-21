#pragma once
#include <memory>
#include "Request.h"
class Shared
{
public:
	bool Exit = false;
	bool New_Request = false;
	void (Request::* SayHi)(void) = nullptr;
	void (Request::* SayHello)(void) = nullptr;
	std::unique_ptr<char> buffer = std::make_unique<char>(new char[sizeof(void(Request::*)())]);
};