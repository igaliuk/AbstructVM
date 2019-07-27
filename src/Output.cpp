#include "Output.hpp"

Output::Output() : _fileName("AVM_logfile.log")
{
}

Output::Output(const Output & obj)
{
	*this = obj;
}

Output &		Output::operator = (const Output & obj)
{
	this->_fileName = obj._fileName;
	return (*this);
}

////////////////////////////////////////////////////////

void			Output::writeData(std::vector<std::string> & messages,
									std::vector<std::string> & errors) const
{
	std::string		quetion;

	if (errors.empty())
		std::cout << "\nThe assembly program complete!\n\n";
	else
		std::cout << "\nThe assembly program includes one or several lexical errors or syntactic errors!\n\n";
	while (1) {
		std::cout << "Display results (1) or write in LogFile (2)?\n";
		std::getline(std::cin, quetion);
		if (quetion == "1" || quetion == "2")
			break ;
	}
	if (quetion == "1" && errors.empty())
		inOutput(messages);
	if (quetion == "1" && !errors.empty())
		inOutput(errors);
	if (quetion == "2" && errors.empty())
		inFile(messages);
	if (quetion == "2" && !errors.empty())
		inFile(errors);
}

////////////////////////////////////////////////////////

void			Output::inOutput(std::vector<std::string> & vec) const
{
	std::cout << "--------------------------------------------" << std::endl;
	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << std::endl;
}

void			Output::inFile(std::vector<std::string> & vec) const
{
	std::ofstream	fout(_fileName);

	for (std::vector<std::string>::const_iterator i = vec.begin(); i != vec.end(); ++i)
		fout << *i << std::endl;
	fout.close();
}

////////////////////////////////////////////////////////

Output::~Output()
{
}
