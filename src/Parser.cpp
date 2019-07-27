#include "Parser.hpp"

Parser::Parser()
{
}

Parser::Parser(const Parser & obj)
{
	*this = obj;
}

Parser &							Parser::operator = (Parser const & obj)
{
	this->_errors = obj._errors;
	return (*this);
}

////////////////////////////////////////////////////////

void								Parser::parsing(std::map<int, std::vector<std::string>> const mapCountCommand)
{
	std::smatch		result;

	for (std::map<int, std::vector<std::string>>::const_iterator i = mapCountCommand.begin();
		i != mapCountCommand.end(); ++i)
	{
		if (i->second.size() == 1)
		{
			if (!std::regex_match(i->second[0], result,
				std::regex{"^(pop|dump|add|sub|mul|div|mod|print|exit)$"}))
				errorSyntax(i->first);
		}
		else if (i->second.size() == 2)
		{
			if (!std::regex_match(i->second[0], result,
				std::regex{"^(push|assert)$"})
				|| !std::regex_match(i->second[1], result,
				std::regex{"^((int(8|16|32)[(][-]?[0-9]*[)])|((float|double)[(][-]?[0-9]*[.]?[0-9]*[)]))$"}))
				errorSyntax(i->first);
		}
		else
		{
			errorLexical(i->first);
		}
	}
}

////////////////////////////////////////////////////////

std::vector<std::string> const &	Parser::getErrors() const
{
	return (_errors);
}

////////////////////////////////////////////////////////

void								Parser::errorSyntax(int const count)
{
	_errors.push_back("Line " + std::to_string(count) + " : Error : Syntax error");
}

void								Parser::errorLexical(int const count)
{
	_errors.push_back("Line " + std::to_string(count) + " : Error : Lexical error");
}

////////////////////////////////////////////////////////

Parser::~Parser()
{
}
