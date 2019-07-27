#ifndef INPUT_HPP
# define INPUT_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>

class Input
{
	public:

		class ErrorBadFile : public std::exception
		{
			public:
				ErrorBadFile();
				ErrorBadFile(const ErrorBadFile & obj);
				ErrorBadFile &				operator = (ErrorBadFile const & obj);
				virtual const char *		what() const throw();
				~ErrorBadFile() throw();
		};

		Input();
		Input(const Input &);

		Input &								operator = (const Input &);

		void								readData();
		void								readData(std::string const fileName);

		std::vector<std::string> const &	getOperations() const;

		~Input();

	private:

		std::vector<std::string>			_operations;
};

#endif
