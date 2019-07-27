#ifndef PARSER_HPP
# define PARSER_HPP

# include <regex>
# include <string>
# include <map>
# include <vector>

class Parser
{
	public:

		Parser();
		Parser(const Parser & obj);

		Parser &							operator = (Parser const & obj);

		void								parsing(std::map<int, std::vector<std::string>> const mapCountCommand);

		std::vector<std::string> const &	getErrors() const;

		~Parser();

	private:

		void								errorSyntax(int const count);
		void								errorLexical(int const count);

		std::vector<std::string>			_errors;
};

#endif
