#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <map>
# include <vector>

class Lexer
{
	public:

		Lexer();
		Lexer(const Lexer & obj);

		Lexer &												operator = (Lexer const & obj);

		void												lexing(std::vector<std::string> const & operations);

		std::map<int, std::vector<std::string>> const &		getMapCountCommand() const;

		~Lexer();

	private:

		std::vector<std::string>							strsplit(std::string const str);

		std::map<int, std::vector<std::string>>				_mapCountCommand;
};

#endif
