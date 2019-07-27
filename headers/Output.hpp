#ifndef OUTPUT_HPP
# define OUTPUT_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>

class Output
{
public:

	Output();
	Output(const Output &);

	Output &			operator = (const Output &);

	void				writeData(std::vector<std::string> & messages,
									std::vector<std::string> & errors) const;

	~Output();

private:

	void				inOutput(std::vector<std::string> & vec) const;
	void				inFile(std::vector<std::string> & vec) const;

	std::string			_fileName;
};

#endif
