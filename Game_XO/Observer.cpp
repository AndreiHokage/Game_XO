#include "Observer.h"

void Observable::addsubsriber(Observer* observer) {
	subsribers.push_back(observer);
}

void Observable::detachsubsriber(Observer* observer) {
	subsribers.erase(std::remove(begin(subsribers), end(subsribers), observer), subsribers.end());
}

void Observable::notify() {
	for (Observer* observer : subsribers)
		observer->update();
}