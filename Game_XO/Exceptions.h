#pragma once
#include <string>
using std::string;

class Exceptions
{
private:
	string msg;
public:
	Exceptions(const string& msg) :msg{ msg } {

	}

	string get_msg() const {
		return msg;
	}
};

class GameError :public Exceptions
{
public:
	GameError(const string& msg) :Exceptions{ msg } {

	}
};

class FileError :public Exceptions
{
public:
	FileError(const string& msg) :Exceptions{ msg } {

	}
};

class RepoError :public Exceptions
{
public:
	RepoError(const string& msg) :Exceptions{ msg } {

	}
};