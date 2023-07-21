#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <Shared.h>
#include <ServerRequest.h>

boost::interprocess::shared_memory_object* AllocateSharedMemory(const char* MemoryBlockName)
{
	boost::interprocess::shared_memory_object* shm_obj = new boost::interprocess::shared_memory_object
	(
		boost::interprocess::create_only,
		MemoryBlockName,
		boost::interprocess::read_write
	);
	shm_obj->truncate(sizeof(Shared));
	return shm_obj;
}

int main()
{
	int stopper = 0;
	ServerRequest server_object;

	boost::interprocess::shared_memory_object* MemoryBlockPointer = AllocateSharedMemory("SharedMemory2");
	boost::interprocess::mapped_region MemoryRegion(*MemoryBlockPointer, boost::interprocess::read_write);
	Shared* shared_object_pointer = new (MemoryRegion.get_address()) Shared;

	shared_object_pointer->SayHi = (void (Request::*)())(&(ServerRequest::SayHi));
	shared_object_pointer->SayHello = (void (Request::*)())(&(ServerRequest::SayHello));


	while (not shared_object_pointer->Exit)
	{
		if (shared_object_pointer->New_Request)
		{
			shared_object_pointer->New_Request = false;
			(server_object.*((void (ServerRequest::*)())shared_object_pointer->buffer))();
		}
	}

	boost::interprocess::shared_memory_object::remove(MemoryBlockPointer->get_name());
	delete MemoryBlockPointer;

	return 0;
}