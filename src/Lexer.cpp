#include "Lexer.hpp"

Lexer::Lexer()
{
}

Lexer::Lexer(const Lexer & obj)
{
	*this = obj;
}

Lexer &												Lexer::operator = (Lexer const & obj)
{
	this->_mapCountCommand = obj._mapCountCommand;
	return (*this);
}

////////////////////////////////////////////////////////

void												Lexer::lexing(std::vector<std::string> const & operations)
{
	std::pair<int, std::vector<std::string>>		tmpPair;

	for (int i = 0; i < static_cast<int>(operations.size()); ++i)
	{
		if (operations[i][0] == ';' || operations[i] == "")
			continue ;
		tmpPair.first = i + 1;
		tmpPair.second = strsplit(operations[i]);
		_mapCountCommand.insert(tmpPair);
	}
}

////////////////////////////////////////////////////////

std::map<int, std::vector<std::string>> const &		Lexer::getMapCountCommand() const
{
	return (_mapCountCommand);
}

////////////////////////////////////////////////////////

std::vector<std::string>							Lexer::strsplit(std::string const str)
{
	std::vector<std::string>	vec;
	int							start = 0;
	int							finish = 0;

	while (str[finish])
	{
		if (str[finish] == ';')
			break ;
		if (str[finish] == ' ' || str[finish] == '\t')
		{
			if (finish - start)
				vec.push_back(str.substr(start, finish - start));
			start = finish + 1;
		}
		finish++;
	}
	if (finish - start)
		vec.push_back(str.substr(start, finish - start));
	return (vec);
}

////////////////////////////////////////////////////////

Lexer::~Lexer()
{
}
