#pragma once
#include <vector>
using std::vector;

class Observer
{
public:
	virtual void update() = 0;

	~Observer() = default;

};

class Observable
{
private:
	vector < Observer* > subsribers;

public:

	void addsubsriber(Observer*);
	void detachsubsriber(Observer*);
	void notify();
};

