#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>
#include <Shared.h>

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
	boost::interprocess::shared_memory_object* memory_block_pointer = OpenSharedMemory("SharedMemory2");
	boost::interprocess::mapped_region MemoryRegion(*memory_block_pointer, boost::interprocess::read_write);
	Shared* shared_object_pointer = (Shared*)MemoryRegion.get_address();

	std::cout << "Press x to say hi, y to say hello, and z to exit!" << std::endl;
	char input = '0';
	while (input != 'z')
	{
		if (not shared_object_pointer->New_Request)
		{
			std::cin >> input;
			if (input == 'x')
			{
				for (int i = 0; i < sizeof(void(Request::*)()); i++)
				{
					shared_object_pointer->buffer.get()[i] = 
				}
				(int)&shared_object_pointer->SayHi;
			}
			if (input == 'y')
			{
				shared_object_pointer->buffer = shared_object_pointer->SayHello;
			}
			shared_object_pointer->New_Request = true;
			Sleep(20);
		}
	}
	shared_object_pointer->Exit = true;
	delete memory_block_pointer;
	return 0;
}
