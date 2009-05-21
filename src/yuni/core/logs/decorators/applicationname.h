#ifndef __YUNI_CORE_LOGS_DECORATORS_APPLICATION_NAME_H__
# define __YUNI_CORE_LOGS_DECORATORS_APPLICATION_NAME_H__

# include "../null.h"


namespace Yuni
{
namespace Logs
{


	template<class LeftType = NullDecorator>
	class ApplicationName : public LeftType
	{
	public:
		ApplicationName()
			:pApplicationName("noname")
		{}


		//! \name Apllication Name
		//@{
		const String& applicationName() const {return pApplicationName;}

		/*!
		** \brief Set the Application name
		**
		** \warning This method is not thread-safe and should only be used after the creation
		** of the logger
		*/
		void applicationName(const char* s) {pApplicationName = s;}
		void applicationName(const String& s) {pApplicationName = s;}
		//@}


		template<class Handler, class VerbosityType, class O>
		void internalDecoratorAddPrefix(O& out, const String& s)
		{
			// Write the verbosity to the output
			out.put('[');
			out.write(pApplicationName.c_str(), pApplicationName.size());
			out.put(']');
			// Transmit the message to the next handler
			LeftType:: template internalDecoratorAddPrefix<Handler, VerbosityType,O>(out, s);
		}

	private:
		//! The Application name
		String pApplicationName;

	}; // class ApplicationName





} // namespace Logs
} // namespace Yuni

#endif // __YUNI_CORE_LOGS_DECORATORS_APPLICATION_NAME_H__
