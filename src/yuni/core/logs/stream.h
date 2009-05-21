#ifndef __YUNI_CORE_LOGS_STREAM_H__
# define __YUNI_CORE_LOGS_STREAM_H__


/* !!! Do not use includes here !!! */


template<class V, int E>
class StreamWriter
{
public:
	StreamWriter(LoggerType& l)
		:pLogger(l)
	{
	}
	template<typename U>
	StreamWriter(LoggerType& l, U u)
		:pLogger(l)
	{
		pBuffer.append(u);
	}

	~StreamWriter()
	{
		pLogger.internalFlush<V>(pBuffer);
	}

	template<typename U> StreamWriter& operator << (const U& u) {pBuffer.append(u);return *this;}

private:
	//! Reference to the original logger
	LoggerType& pLogger;
	//! Buffer that contains the message
	String pBuffer;

}; // class StreamWriter




template<class V>
class StreamWriter<V,0>
{
public:
	StreamWriter(LoggerType&)
	{}
	template<typename U>
	StreamWriter(LoggerType&, U)
	{}

	~StreamWriter()
	{}

	template<typename U> StreamWriter& operator << (const U&) {return *this;}

}; // class StreamWriter




#endif // __YUNI_CORE_LOGS_STREAM_H__
