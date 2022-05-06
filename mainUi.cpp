#include "Engine.hpp"
#include <iostream>

int main() 
{
	MSQ::Engine e;

	std::vector<const PaDeviceInfo*> devices = e.getDevices();

	for(int i = 0; i < devices.size(); i++) 
	{
		std::cout << i << ": " << MSQ::Engine::deviceInfoToString(devices[i]);
	}

	return 0;
}
