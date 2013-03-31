#pragma once
#include <string>

class zip_package
{
	void * fh;
	const static int bfz;
public:
	zip_package(std::string const & file_name);

	operator bool () const;

	std::string read(std::string const & file_path);
private:
	bool locate(std::string const & file_path);
};
