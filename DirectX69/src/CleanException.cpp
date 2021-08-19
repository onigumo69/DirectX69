#include "CleanException.h"

CleanException::CleanException(const char* file, int line) noexcept
	:
	file{ file },
	line{ line }
{}

const char* CleanException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << "\n"
		<< GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* CleanException::GetType() const noexcept
{
	return "Clean Exception";
}

int CleanException::GetLine() const noexcept
{
	return line;
}

const std::string& CleanException::GetFile() const noexcept
{
	return file;
}

std::string CleanException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << "\n"
		<< "[Line] " << line;

	return oss.str();
}