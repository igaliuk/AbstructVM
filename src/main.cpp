#include "AbstractVM.hpp"

int main(int argc, char ** argv)
{
	AbstractVM AVM;

	if (argc > 2) {
		std::cout << "read file:" << std::endl;
		std::cout << "   usage: ./abstract_vm [FILE_NAME]" << std::endl;
		std::cout << "input mode:" << std::endl;
		std::cout << "   usage: ./abstract_vm" << std::endl;
		return 0;
	}
	else 
		AVM.start(argc, argv);
	return 0;
}
