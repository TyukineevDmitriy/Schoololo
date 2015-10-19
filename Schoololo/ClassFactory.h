#pragma once

#include <map>
#include <string>

using namespace std;

template<class BaseClass, class ... Args>
class ClassFactory {
private:

	typedef BaseClass* (*FPcreator)(Args ...);

	map<string, FPcreator> classStore;

	template<class Derived>
	static BaseClass* Creator(Args... args) {
		return new Derived(args...);
	}

public:

	template<class Derived>
	void AddClass(string id) {
		classStore[id] = &Creator<Derived>;
	}

	FPcreator Get(string id) {
		return classStore[id];
	}


};