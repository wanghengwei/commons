#include <unzip.h>
#include <zip_package.h>
#include <sstream>

using namespace std;

const int zip_package::bfz = 1 << 10;

zip_package::zip_package(std::string const & file_name)
{
	fh = unzOpen(file_name.c_str());
}

zip_package::operator bool () const
{
	return fh != nullptr;
}

bool zip_package::locate(std::string const & file_path)
{
	return UNZ_OK == unzLocateFile(fh, file_path.c_str(), 1);
}

std::string zip_package::read(string const & file_path)
{
	if (!locate(file_path))
		throw "Can't find the file";

	if (UNZ_OK != unzOpenCurrentFile(fh))
		throw "Can't open current file";

	char buf[bfz];
	ostringstream oss;
	while (true)
	{
		int readed = unzReadCurrentFile(fh, buf, bfz);
		if (readed == 0)
			break;
		oss.write(buf, readed);
	}

	unzCloseCurrentFile(fh);
	return oss.str();
}
