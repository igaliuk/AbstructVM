#include "Creator.hpp"
#include "Operand.hpp"

Creator::Creator()
{
}

Creator::Creator(const Creator & obj)
{
	*this = obj;
}

Creator &			Creator::operator = (Creator const & obj)
{
	(void)obj;
	return (*this);
}

//////////////////////////////////////////////////////////

IOperand const *	Creator::createInt8(std::string const & value) const
{
	return (new Operand<int8_t>(value, Int8, 0, this));
}

IOperand const *	Creator::createInt16(std::string const & value) const
{
	return (new Operand<int16_t>(value, Int16, 0, this));
}

IOperand const *	Creator::createInt32(std::string const & value) const
{
	return (new Operand<int32_t>(value, Int32, 0, this));
}

IOperand const *	Creator::createFloat(std::string const & value) const
{
	return (new Operand<float>(value, Float, 7, this));
}

IOperand const *	Creator::createDouble(std::string const & value) const
{
	return (new Operand<double>(value, Double, 15, this));
}

////////////////////////////////////////////////////////

IOperand const *	Creator::createOperand(eOperandType type,
											std::string const & value) const
{
	IOperand const *	(Creator::*listFunc[5])(std::string const & value) const =
		{&Creator::createInt8, &Creator::createInt16, &Creator::createInt32,
		&Creator::createFloat, &Creator::createDouble};

	return ((this->*(listFunc[type]))(value));
}

////////////////////////////////////////////////////////

Creator::~Creator()
{
}
