#pragma once
#include <exception>
#include <string>
#include <sstream>

class CleanException : public std::exception
{
public:
	CleanException(const char* file, int line) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	std::string file;
	int line;

protected:
	mutable std::string whatBuffer;
};