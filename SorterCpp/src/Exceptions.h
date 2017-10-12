#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

class Exception 
{
private:
	const char* m_what;
public:
	Exception(const char* what = "")
		: m_what(what)
	{}

	const char* What() const { return m_what; }
};

class ArgumentOutOfRange : public Exception 
{
public:
	ArgumentOutOfRange(const char* what = "")
		: Exception(what)
	{}
};
