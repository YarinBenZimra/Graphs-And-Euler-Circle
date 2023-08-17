#pragma once
#include <iostream>
#include <string>

class Exceptions : public std::exception
{
private:

	std::string m_str;

public:

	Exceptions(const std::string& s)
	{
		m_str = s;
	}

	char const* what() const noexcept
	{
		std::cout << std::endl;
		return m_str.c_str();
	}

};

