
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
		typename ThreadingPolicy::MutexLocker locker(*this);
		std::cout << "Juste do something\n";
	}
};



