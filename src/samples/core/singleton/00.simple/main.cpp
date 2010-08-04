
#include <iostream>
#include <yuni/core/singleton/singleton.h>

class MyManager: public Yuni::Singleton<MyManager>
{
public:
	typedef Yuni::Singleton<MyManager> Singleton;

public:
	void doSomething()
	{
		std::cout << "Ping" << std::endl;
	}

	MyManager() {}

private:
	// Hide the rest of the constructors and assignment operators
	MyManager(const MyManager&);
	MyManager& operator = (const MyManager&);
	size_t operator & () { throw; }
	size_t operator & () const { throw; }
};


int main(void)
{
	MyManager& managerInstance = MyManager::Singleton::Instance();

	managerInstance.doSomething();
}
