#ifndef __YUNI_CORE_LOGS_HANDLERS_FILE_H__
# define __YUNI_CORE_LOGS_HANDLERS_FILE_H__

# include "../null.h"
# include <fstream>



namespace Yuni
{
namespace Logs
{



	/*!
	** \brief Log Handler: The standard output (cout & cerr)
	*/
	template<class NextHandler = NullHandler>
	class File : public NextHandler
	{
	public:
		enum Settings
		{
			// Colors are not allowed in a file
			unixColorsAllowed = 0,
		};

	public:
		template<typename U> void outputFilename(const U& filename)
		{
			// Closing the file if already opened
			if (pFile.is_open())
				pFile.close();
			// Assigning the new filename
			pOutputFilename = filename;
			// Opening the log file
			pFile.open(pOutputFilename.c_str(), std::ios::out|std::ios::app|std::ios::binary);
		}

		String outputFilename() const
		{
			return pOutputFilename;
		}

		bool logFileIsOpened()
		{
			return (pFile.is_open());
		}

	public:
		template<class LoggerT, class VerbosityType, class StringT>
		void internalDecoratorWriteWL(LoggerT& logger, const StringT& s)
		{
			typedef typename LoggerT::DecoratorsType DecoratorsType;
			// Append the message to the file
			logger.DecoratorsType::template internalDecoratorAddPrefix<File, VerbosityType>(pFile, s);

			// Flushing the result
			# ifdef YUNI_OS_WINDOWS
			pFile.write("\r\n", 2); // We are in binary mode
			# else
			pFile.write("\n", 1);
			# endif
			pFile.flush();

			// Transmit the message to the next handler
			NextHandler::template internalDecoratorWriteWL<LoggerT, VerbosityType, StringT>(logger, s);
		}


	private:
		//! The originale filename
		String pOutputFilename;
		//! File
		std::ofstream pFile;

	}; // class StdCout




} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_LOGS_HANDLERS_FILE_H__
