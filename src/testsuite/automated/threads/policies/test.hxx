
#include <yuni/yuni.h>
#include <yuni/threads/policy.h>
#include <iostream>


template<template<class> class TP> class Dummy;


template<template<class> class TP>
class Dummy : public TP <Dummy<TP> >
{
public:
	//! The Threading policy
	typedef TP<Dummy> ThreadingPolicy;

public:
	Dummy()
	{
		std::cout << "Begin\n";
	}
	~Dummy()
	{
		std::cout << "End\n";
	}

	void runWithLock()
	{
		// Assignation
		pDummyVar = 42;

		typename ThreadingPolicy::MutexLocker locker(*this);
		// Displaying informations to avoid some permissive optimisation of gcc
		std::cout << "Threading policy Infos\n";
		std::cout << "Threadsafe : " << ThreadingPolicy::threadSafe << "\n";
		std::cout << "Dummy var  : " << pDummyVar << "\n";
	}

private:
	//! A volatile variable
	typename ThreadingPolicy:: template Volatile<int>::Type pDummyVar;

}; // class Dummy



