#include "AbstractVM.hpp"

AbstractVM::AbstractVM() : _exit(0)
{
}

AbstractVM::AbstractVM(const AbstractVM & obj)
{
	*this = obj;
}

AbstractVM &	AbstractVM::operator = (AbstractVM const & obj)
{
	std::stack<IOperand const *>		stackObj;
	std::stack<IOperand const *>		stackTmp;

	this->_input = obj._input;
	this->_lexer = obj._lexer;
	this->_parser = obj._parser;
	this->_creator = obj._creator;
	this->_output = obj._output;
	stackObj = obj._stack;
	while (!stackObj.empty())
	{
		stackTmp.push(stackObj.top());
		stackObj.pop();
	}
	while (!stackTmp.empty())
	{
		this->_stack.push(this->_creator.createOperand(stackTmp.top()->getType(), stackTmp.top()->toString()));
		stackTmp.pop();
	}
	this->_messages = obj._messages;
	this->_errors = obj._errors;
	this->_exit = obj._exit;
	return (*this);
}

////////////////////////////////////////////////////////

void			AbstractVM::start(int argc, char** argv)
{
	try
	{
		readData(argc, argv);
		parsingData();
	}
	catch (std::exception & e)
	{
		_errors.push_back(e.what());
	}
	if (_errors.empty())
		processingData();
	writeData();
}

////////////////////////////////////////////////////////

void			AbstractVM::readData(int argc, char** argv)
{
	if (argc == 2)
		_input.readData(argv[1]);
	else 
		_input.readData();
}

void			AbstractVM::parsingData()
{
	_lexer.lexing(_input.getOperations());
	_parser.parsing(_lexer.getMapCountCommand());
	_errors.insert(_errors.end(), _parser.getErrors().begin(), _parser.getErrors().end());
}

void			AbstractVM::processingData()
{
	std::map<int, std::vector<std::string>>		mapCountCommand = _lexer.getMapCountCommand();

	for (std::map<int, std::vector<std::string>>::const_iterator i = mapCountCommand.begin();
		i != mapCountCommand.end(); ++i)
	{
		if (_exit)
			break ;
		if (!executionCommand1(i->first, i->second[0]))
			executionCommand2(i->first, i->second[0], i->second[1]);
	}
	if (!_exit)
		errorNoExit();
}

bool			AbstractVM::executionCommand1(int const count, std::string const str1)
{
	std::string		listOperations[9] = {"pop", "dump", "add", "sub", "mul", "div", "mod", "print", "exit"};
	void			(AbstractVM::*listFuncOperations[9])(int const count) = {&AbstractVM::oPop,
						&AbstractVM::oDump, &AbstractVM::oAdd, &AbstractVM::oSub, &AbstractVM::oMul,
						&AbstractVM::oDiv, &AbstractVM::oMod, &AbstractVM::oPrint, &AbstractVM::oExit};

	for (int i = 0; i < 9; ++i)
	{
		if (str1 == listOperations[i])
		{
			(this->*(listFuncOperations[i]))(count);
			return (true);
		}
	}
	return (false);
}

void			AbstractVM::executionCommand2(int const count, std::string const str1, std::string const str2)
{
	
	std::string		listTypes[5] = {"int8", "int16", "int32", "float", "double"};
	eOperandType	type;
	std::string		value;

	for (int i = 0; i < 5; ++i)
	{
		if (str2.find(listTypes[i]) != std::string::npos)
		{
			type = static_cast<eOperandType>(i);
			break ;
		}
	}
	value = str2.substr(str2.rfind('(') + 1, str2.rfind(')') - str2.rfind('(') - 1);
	if (str1[0] == 'p')
		oPush(type, value, count);
	else
		oAssert(type, value, count);
}

void			AbstractVM::writeData()
{
	_output.writeData(_messages, _errors);
}

////////////////////////////////////////////////////////

void			AbstractVM::oPush(eOperandType type, std::string const & value, int const count)
{
	try
	{
		_stack.push(_creator.createOperand(type, value));
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
	}
}

void			AbstractVM::oPop(int const count)
{
	IOperand const *	o;

	try
	{
		if (_stack.empty())
			throw std::exception();
		o = _stack.top();
		_stack.pop();
		delete o;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : Instruction pop on an empty stack");
	}
}

void			AbstractVM::oDump(int const count)
{
	std::stack<IOperand const *>		stackTmp;

	while (!_stack.empty())
	{
		_messages.push_back(_stack.top()->toString());
		stackTmp.push(_stack.top());
		_stack.pop();
	}
	while (!stackTmp.empty())
	{
		_stack.push(stackTmp.top());
		stackTmp.pop();
	}
	(void)count;
}

void			AbstractVM::oAssert(eOperandType type, std::string const & value, int const count)
{
	try
	{
		if (_stack.empty())
			throw std::exception();
		try
		{
			if (_stack.top()->getType() != type || _stack.top()->toString() != value)
				throw std::exception();
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count)
				+ " : Error : An assept instruction is not true");
		}
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : Instruction assept on an empty stack");
	}
}

void			AbstractVM::oAdd(int const count)
{
	IOperand const *	o1;
	IOperand const *	o2;

	try
	{
		if (_stack.size() < 2)
			throw std::exception();
		o1 = _stack.top();
		_stack.pop();
		o2 = _stack.top();
		_stack.pop();
		try
		{
			_stack.push(*o2 + *o1);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
		}
		delete o1;
		delete o2;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : The stack is composed of strictly less "
			+ "that two values when an arithmetic instruction is executed");
	}
}

void			AbstractVM::oSub(int const count)
{
	IOperand const *	o1;
	IOperand const *	o2;

	try
	{
		if (_stack.size() < 2)
			throw std::exception();
		o1 = _stack.top();
		_stack.pop();
		o2 = _stack.top();
		_stack.pop();
		try
		{
			_stack.push(*o2 - *o1);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
		}
		delete o1;
		delete o2;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : The stack is composed of strictly less "
			+ "that two values when an arithmetic instruction is executed");
	}
}

void			AbstractVM::oMul(int const count)
{
	IOperand const *	o1;
	IOperand const *	o2;

	try
	{
		if (_stack.size() < 2)
			throw std::exception();
		o1 = _stack.top();
		_stack.pop();
		o2 = _stack.top();
		_stack.pop();
		try
		{
			_stack.push(*o2 * *o1);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
		}
		delete o1;
		delete o2;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : The stack is composed of strictly less "
			+ "that two values when an arithmetic instruction is executed");
	}
}

void			AbstractVM::oDiv(int const count)
{
	IOperand const *	o1;
	IOperand const *	o2;

	try
	{
		if (_stack.size() < 2)
			throw std::exception();
		o1 = _stack.top();
		_stack.pop();
		o2 = _stack.top();
		_stack.pop();
		try
		{
			_stack.push(*o2 / *o1);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
		}
		delete o1;
		delete o2;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : The stack is composed of strictly less "
			+ "that two values when an arithmetic instruction is executed");
	}
}

void			AbstractVM::oMod(int const count)
{
	IOperand const *	o1;
	IOperand const *	o2;

	try
	{
		if (_stack.size() < 2)
			throw std::exception();
		o1 = _stack.top();
		_stack.pop();
		o2 = _stack.top();
		_stack.pop();
		try
		{
			_stack.push(*o2 % *o1);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : " + e.what());
		}
		delete o1;
		delete o2;
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count)
			+ " : Error : The stack is composed of strictly less "
			+ "that two values when an arithmetic instruction is executed");
	}
}

void			AbstractVM::oPrint(int const count)
{
	try
	{
		if (_stack.empty())
			throw std::exception();
		try
		{
			if (_stack.top()->getType() != Int8)
				throw std::exception();
			std::string		str = " ";
			str[0] = std::stoi(_stack.top()->toString());
			_messages.push_back(str);
		}
		catch (std::exception & e)
		{
			_errors.push_back("Line " + std::to_string(count) + " : Error : An print instruction is not true");
		}
	}
	catch (std::exception & e)
	{
		_errors.push_back("Line " + std::to_string(count) + " : Error : Instruction print on an empty stack");
	}
}

void			AbstractVM::oExit(int const count)
{
	(void)count;
	_exit = 1;
}

////////////////////////////////////////////////////////

void			AbstractVM::errorNoExit()
{
	_errors.push_back("Error : The program does not have an exit instruction");
}

////////////////////////////////////////////////////////

AbstractVM::~AbstractVM()
{
	IOperand const *		o;

	while (!_stack.empty())
	{
		o = _stack.top();
		_stack.pop();
		delete o;
	}
}
