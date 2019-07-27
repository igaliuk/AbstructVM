#ifndef OPERAND_HPP
# define OPERAND_HPP

# include <limits>
# include <iomanip>
# include <sstream>
# include "IOperand.hpp"
# include "Creator.hpp"

template <class T>
class Operand : public IOperand
{
	public:

		class ErrorOverflow : public std::exception
		{
			public:
				ErrorOverflow()
				{
				}
				ErrorOverflow(const ErrorOverflow & obj)
				{
					*this = obj;
				}
				ErrorOverflow &			operator = (ErrorOverflow const & obj)
				{
					(void)obj;
					return (*this);
				}
				virtual const char *	what() const throw()
				{
					return ("Error : Overflow on a value");
				}
				~ErrorOverflow() throw()
				{
				}
		};

		class ErrorUnderflow : public std::exception
		{
			public:
				ErrorUnderflow()
				{
				}
				ErrorUnderflow(const ErrorUnderflow & obj)
				{
					*this = obj;
				}
				ErrorUnderflow &		operator = (ErrorUnderflow const & obj)
				{
					(void)obj;
					return (*this);
				}
				virtual const char *	what() const throw()
				{
					return ("Error : Underflow on a value");
				}
				~ErrorUnderflow() throw()
				{
				}
		};

		class ErrorModFP : public std::exception
		{
			public:
				ErrorModFP()
				{
				}
				ErrorModFP(const ErrorModFP & obj)
				{
					*this = obj;
				}
				ErrorModFP &			operator = (ErrorModFP const & obj)
				{
					(void)obj;
					return (*this);
				}
				virtual const char *	what() const throw()
				{
					return ("Error : Modulo FP");
				}
				~ErrorModFP() throw()
				{
				}
		};

		class ErrorByZero : public std::exception
		{
			public:
				ErrorByZero()
				{
				}
				ErrorByZero(const ErrorByZero & obj)
				{
					*this = obj;
				}
				ErrorByZero &			operator = (ErrorByZero const & obj)
				{
					(void)obj;
					return (*this);
				}
				virtual const char *	what() const throw()
				{
					return ("Error : Division/modulo by 0");
				}
				~ErrorByZero() throw()
				{
				}
		};

		Operand() : _valueT(0), _type(Int8), _precision(0)
		{
		}
		Operand(std::string const & value, eOperandType type, int precision, Creator const * creator) :
			_valueStr(value), _type(type), _precision(precision), _creator(creator)
		{
			_valueT = toNumber(type, value);
		}
		Operand(const Operand & obj)
		{
			*this = obj;
		}

		Operand &				operator = (Operand const & obj)
		{
			this->_valueStr = obj._valueStr;
			this->_valueT = obj._valueT;
			this->_type = obj._type; 
			this->_precision = obj._precision;
			this->_creator = obj._creator;
			return (*this);
		}

		eOperandType			getType() const
		{
			return (_type);
		}
		int						getPrecision() const
		{
			return (_precision);
		}

		IOperand const *		operator + (IOperand const & rhs) const
		{
			eOperandType	typeRhs;
			eOperandType	typeReturn;
			int				precisionRhs;
			int				precisionReturn;
			T				valueTRhs;

			typeRhs = rhs.getType();
			typeReturn = this->_type > typeRhs ? this->_type : typeRhs;
			precisionRhs = rhs.getPrecision();
			precisionReturn = this->_precision > precisionRhs ? this->_precision : precisionRhs;
			valueTRhs = toNumber(typeRhs, rhs.toString());
			return (_creator->createOperand(typeReturn, this->toStr(precisionReturn,
				_valueT + valueTRhs)));
		}
		IOperand const *		operator - (IOperand const & rhs) const
		{
			eOperandType	typeRhs;
			eOperandType	typeReturn;
			int				precisionRhs;
			int				precisionReturn;
			T				valueTRhs;

			typeRhs = rhs.getType();
			typeReturn = this->_type > typeRhs ? this->_type : typeRhs;
			precisionRhs = rhs.getPrecision();
			precisionReturn = this->_precision > precisionRhs ? this->_precision : precisionRhs;
			valueTRhs = toNumber(typeRhs, rhs.toString());
			return (_creator->createOperand(typeReturn, this->toStr(precisionReturn,
				_valueT - valueTRhs)));
		}
		IOperand const *		operator * (IOperand const & rhs) const
		{
			eOperandType	typeRhs;
			eOperandType	typeReturn;
			int				precisionRhs;
			int				precisionReturn;
			T				valueTRhs;

			typeRhs = rhs.getType();
			typeReturn = this->_type > typeRhs ? this->_type : typeRhs;
			precisionRhs = rhs.getPrecision();
			precisionReturn = this->_precision > precisionRhs ? this->_precision : precisionRhs;
			valueTRhs = toNumber(typeRhs, rhs.toString());
			return (_creator->createOperand(typeReturn, this->toStr(precisionReturn,
				_valueT * valueTRhs)));
		}
		IOperand const *		operator / (IOperand const & rhs) const
		{
			eOperandType	typeRhs;
			eOperandType	typeReturn;
			int				precisionRhs;
			int				precisionReturn;
			T				valueTRhs;

			typeRhs = rhs.getType();
			typeReturn = this->_type > typeRhs ? this->_type : typeRhs;
			precisionRhs = rhs.getPrecision();
			precisionReturn = this->_precision > precisionRhs ? this->_precision : precisionRhs;
			valueTRhs = toNumber(typeRhs, rhs.toString());
			if (!valueTRhs)
				throw ErrorByZero();
			return (_creator->createOperand(typeReturn, this->toStr(precisionReturn,
				_valueT / valueTRhs)));
		}
		IOperand const *		operator % (IOperand const & rhs) const
		{
			eOperandType	typeRhs;
			eOperandType	typeReturn;
			int				precisionRhs;
			int				precisionReturn;
			T				valueTRhs;

			typeRhs = rhs.getType();
			if (typeRhs == Float || typeRhs == Double
				|| this->_type == Float || this->_type == Double)
				throw ErrorModFP();
			typeReturn = this->_type > typeRhs ? this->_type : typeRhs;
			precisionRhs = rhs.getPrecision();
			precisionReturn = this->_precision > precisionRhs ? this->_precision : precisionRhs;
			valueTRhs = toNumber(typeRhs, rhs.toString());
			if (!valueTRhs)
				throw ErrorByZero();
			return (_creator->createOperand(typeReturn, this->toStr(precisionReturn,
				int(_valueT) % int(valueTRhs))));
		}
	
		std::string const &		toString() const
		{
			return (_valueStr);
		}

		~Operand()
		{
		}

	private:

		std::string const		toStr(int precision, long double const & value) const
		{
			std::stringstream	stream;
			std::string			str;

			stream << std::fixed << std::setprecision(precision) << value;
			str = stream.str();
			for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
			{
				if (*it >= '1' && *it <= '9')
				{
					return (str);
				}
			}
			return ("0");
		}
		T const					toNumber(eOperandType type, std::string const & value) const
		{
			T const		(Operand<T>::*listFunc[5])(std::string const & value) const =
				{&Operand<T>::toInt8, &Operand<T>::toInt16, &Operand<T>::toInt32,
				&Operand<T>::toFloat, &Operand<T>::toDouble};

			return ((this->*(listFunc[type]))(value));
		}
		T const					toInt8(std::string const & value) const
		{
			long			l = std::stoll(value);

			if (l > std::numeric_limits<int8_t>::max())
				throw ErrorOverflow();
			if (l < std::numeric_limits<int8_t>::min())
				throw ErrorUnderflow();
			return (l);
		}
		T const					toInt16(std::string const & value) const
		{
			long			l = std::stoll(value);

			if (l > std::numeric_limits<int16_t>::max())
				throw ErrorOverflow();
			if (l < std::numeric_limits<int16_t>::min())
				throw ErrorUnderflow();
			return (l);
		}
		T const					toInt32(std::string const & value) const
		{
			long			l = std::stoll(value);

			if (l > std::numeric_limits<int32_t>::max())
				throw ErrorOverflow();
			if (l < std::numeric_limits<int32_t>::min())
				throw ErrorUnderflow();
			return (l);
		}
		T const					toFloat(std::string const & value) const
		{
			long double		ld = std::stold(value);

			if (ld > std::numeric_limits<float>::max())
				throw ErrorOverflow();
			if (ld < -std::numeric_limits<float>::max())
				throw ErrorUnderflow();
			return (ld);
		}
		T const					toDouble(std::string const & value) const
		{
			long double		ld = std::stold(value);

			if (ld > std::numeric_limits<double>::max())
				throw ErrorOverflow();
			if (ld < -std::numeric_limits<double>::max())
				throw ErrorUnderflow();
			return (ld);
		}

		std::string				_valueStr;
		T						_valueT;
		eOperandType			_type;
		int						_precision;
		Creator const *			_creator;
};

#endif
