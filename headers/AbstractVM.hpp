#ifndef ABSTRACTVM_HPP
# define ABSTRACTVM_HPP

# include <string>
# include <stack>
# include <vector>
# include <map>
# include "Input.hpp"
# include "Lexer.hpp"
# include "Parser.hpp"
# include "Creator.hpp"
# include "Output.hpp"
# include "IOperand.hpp"

class AbstractVM
{
	public:

		AbstractVM();
		AbstractVM(const AbstractVM & obj);

		AbstractVM &	operator = (AbstractVM const & obj);

		void			start(int argc, char** argv);

		~AbstractVM();

	private:

		void			readData(int argc, char** argv);
		void			parsingData();
		void			processingData();
		bool			executionCommand1(int const count, std::string const str1);
		void			executionCommand2(int const count, std::string const str1, std::string const str2);
		void			writeData();

		void			oPush(eOperandType type, std::string const & value, int const count);
		void			oPop(int const count);
		void			oDump(int const count);
		void			oAssert(eOperandType type, std::string const & value, int const count);
		void			oAdd(int const count);
		void			oSub(int const count);
		void			oMul(int const count);
		void			oDiv(int const count);
		void			oMod(int const count);
		void			oPrint(int const count);
		void			oExit(int const count);

		void			errorNoExit();

		Input							_input;
		Lexer							_lexer;
		Parser							_parser;
		Creator							_creator;
		Output							_output;
		std::stack<IOperand const *>	_stack;
		std::vector<std::string>		_messages;
		std::vector<std::string>		_errors;
		int								_exit;
};

#endif
