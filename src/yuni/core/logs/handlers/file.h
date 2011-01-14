#ifndef __YUNI_CORE_LOGS_HANDLERS_FILE_H__
# define __YUNI_CORE_LOGS_HANDLERS_FILE_H__

# include "../null.h"
# include "../../io/file.h"



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
			// Assigning the new filename
			pOutputFilename = filename;
			// Opening the log file
			pFile.open(pOutputFilename,
				Core::IO::OpenMode::write | Core::IO::OpenMode::append);
		}

		String outputFilename() const
		{
			return pOutputFilename;
		}

		bool logFileIsOpened()
		{
			return (pFile.opened());
		}

	public:
		template<class LoggerT, class VerbosityType, class StringT>
		void internalDecoratorWriteWL(LoggerT& logger, const StringT& s)
		{
			if (pFile.opened())
			{
				typedef typename LoggerT::DecoratorsType DecoratorsType;
				// Append the message to the file
				logger.DecoratorsType::template internalDecoratorAddPrefix<File, VerbosityType>(pFile, s);

				// Flushing the result
				# ifdef YUNI_OS_WINDOWS
				pFile << "\r\n";
				# else
				pFile << '\n';
				# endif
				pFile.flush();
			}

			// Transmit the message to the next handler
			NextHandler::template internalDecoratorWriteWL<LoggerT, VerbosityType, StringT>(logger, s);
		}


	private:
		//! The originale filename
		String pOutputFilename;
		//! File
		Core::IO::File::Stream pFile;

	}; // class File




} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_LOGS_HANDLERS_FILE_H__
