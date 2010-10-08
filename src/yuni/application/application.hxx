#ifndef __YUNI_APPLICATION_APPLICATION_HXX__
# define __YUNI_APPLICATION_APPLICATION_HXX__


namespace Yuni
{
namespace Application
{


	inline bool IApplication::terminated() const
	{
		return pTerminated;
	}


	inline void IApplication::terminate(const int ex)
	{
		pExitCode = ex;
		pTerminated = true;
	}


	inline const IApplication::PathType& IApplication::exeName() const
	{
		return pExeName;
	}


	inline const IApplication::PathType& IApplication::rootFolder() const
	{
		return pRootFolder;
	}


	inline int IApplication::exitCode() const
	{
		return pExitCode;
	}


	inline IApplication::IApplication(const IApplication&)
		:ThreadingPolicy()
	{}


	inline IApplication& IApplication::operator = (const IApplication&)
	{
		return *this;
	}


	inline void IApplication::execute()
	{
		if (!pTerminated)
			this->onExecute();
	}



} // namespace Application
} // namespace Yuni

#endif // __YUNI_APPLICATION_APPLICATION_HXX__


