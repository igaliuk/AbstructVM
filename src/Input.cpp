#include "Input.hpp"

Input::ErrorBadFile::ErrorBadFile()
{
}

Input::ErrorBadFile::ErrorBadFile(const ErrorBadFile & obj)
{
	*this = obj;
}

typename Input::ErrorBadFile &		Input::ErrorBadFile::operator = (Input::ErrorBadFile const & obj)
{
	(void)obj;
	return (*this);
}

const char *						Input::ErrorBadFile::what() const throw()
{
	return ("Error : Bad file");
}

Input::ErrorBadFile::~ErrorBadFile() throw()
{
}

////////////////////////////////////////////////////////

Input::Input()
{
}

Input::Input(const Input & obj)
{
	*this = obj;
}

Input &								Input::operator = (const Input & obj)
{
	this->_operations = obj._operations;
	return (*this);
}

////////////////////////////////////////////////////////

void								Input::readData()
{
	std::string		str;

	while (std::getline(std::cin, str))
	{
		if (str == ";;")
			return ;
		_operations.push_back(str);
	}
}

void								Input::readData(std::string const fileName)
{
	std::string		str;
	std::ifstream	source;

	source.open(fileName);
	if (!source.is_open())
		throw ErrorBadFile();
	while (std::getline(source, str))
	{
		_operations.push_back(str);
	}
	source.close();
}

////////////////////////////////////////////////////////

std::vector<std::string> const &	Input::getOperations() const
{
	return (_operations);
}

////////////////////////////////////////////////////////

Input::~Input()
{
}
