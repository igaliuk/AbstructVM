#ifndef CREATOR_HPP
# define CREATOR_HPP

# include <string>
# include "IOperand.hpp"

class Creator
{
	public:

		Creator();
		Creator(const Creator & obj);

		Creator &			operator = (Creator const & obj);

		IOperand const *	createOperand(eOperandType type, std::string const & value) const;

		~Creator();

	private:

		IOperand const *	createInt8(std::string const & value) const;
		IOperand const *	createInt16(std::string const & value) const;
		IOperand const *	createInt32(std::string const & value) const;
		IOperand const *	createFloat(std::string const & value) const;
		IOperand const *	createDouble(std::string const & value) const;
};

#endif
