#ifndef __YUNI_TOOLBOX_GETOPT_OPTION_H__
# define __YUNI_TOOLBOX_GETOPT_OPTION_H__

# include "../../yuni.h"
# include <list>
# include "../string.h"


namespace Yuni
{
namespace Toolbox
{
namespace GetOpt
{

	class AOption
	{
	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		** \param sOpt Short name of the option
		** \param lOpt Long name of the option
		** \param ndValue if an extra value is required
		** \param comm Comments for the option
		*/
		AOption(const String::Char sOpt, const String& lOpt, bool ndValue,
			const String& comm);
		//! Copy constructor
		AOption(const AOption&);
		/*!
		** \brief Destructor
		*/
		virtual ~AOption() {}
		//@}

		//! Get the short name of the option
		char shortName() const {return pShortName;}
		//! Get the long name of the option
		const String& longName() const {return pLongName;}

		const String& comments() const {return pComments;}

		String fullNameForHelp();
		String bestSuitableName();

		/*!
		** \brief Reset the value of the option
		*/
		virtual void reset();

		/*!
		** \brief Get if an extra value is required
		** \return True if an extra value is required
		*/
		bool valueIsRequired() const {return pNeedValue;}

		//! \name Modified
		//@{
		/*!
		** \brief Get if the option has been modified
		** \return True if the option has been modified, false otherwise
		*/
		bool modified() const {return pModified;}
		/*!
		** \brief Set if the option has been modified
		** \param value The new value
		*/
		void modified(const bool value) {pModified = value;}
		//@}

		virtual void addValue(const String& v) = 0;

		virtual bool empty() const = 0;

	protected:
		//! The short name of the option
		const char pShortName;
		//! The long name of the option
		const String pLongName;
		//! If the option has been modified
		bool pModified;
		//! Need extra value
		bool pNeedValue;
		//! Comments for this option
		const String pComments;

	}; // class AOption







	/*!
	** \brief Single Option
	**
	** This class defines all parameters that an option could have.
	**
	** \tparam T The type of the option
	**
	** \bug Not fully compliant with the original getopt : -a<value> does not work
	*/
	template<typename T>
	class Option : public AOption
	{
	public:
		//! The original type
		typedef T Type;
		//! List of Values
		typedef typename std::list<T> ValueList;

		//! Typedef for the iterator (const)
		typedef typename ValueList::const_iterator const_iterator;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Constructor
		**
		** \param sOpt The short name of the option
		** \param lOpt The long name of the option
		** \param oComments The comments for this option
		** \param ndValue If requires an extra value
		** \param defValue The default value for the option
		*/
		Option(const char sOpt, const String& lOpt = String(),
			const String& oComments = String(),
			const bool ndValue = false, const T& defValue = T());
		/*!
		** \brief Copy constructor
		*/
		Option(const Option<T>&);
		/*!
		** \brief Destructor
		*/
		virtual ~Option();
		//@}

		//! \name Values
		//@{
		/*!
		** \brief Get the value of the option
		**
		** For options with multiple values, the last one will be returned
		** \return The value of the option
		*/
		T value() const;
		//! \see value()
		T operator () () const;

		/*!
		** \brief Iterator on the begining of the list of values
		*/
		const_iterator begin() const {return pValues.begin();}
		/*!
		** \brief Iterator on the end of the list of values
		*/
		const_iterator end() const {return pValues.end();}

		/*!
		** \brief Add a value in the list
		**
		** When a new value is added, the option is considered as modified.
		**
		** \param v The new value to add
		** \see modified()
		*/
		virtual void addValue(const String& v);
		//! \see addValue
		Option<T>& operator += (const String& v) {this->addValue(v);return *this;}
		//@}

		/*!
		** \brief Get if the list of values is empty
		** \return True if the list of values is empty, false otherwise
		*/
		virtual bool empty() const {return pValues.empty();}

		/*!
		** \brief Reset the values for this option
		*/
		virtual void reset();

	private:
		//! Its default value
		T pDefaultValue;
		//! The list of values
		ValueList pValues;

	}; // class Option




} // namespace GetOpt
} // namespace Toolbox
} // namespace Yuni


# include "option.hxx"


#endif // __YUNI_TOOLBOX_GETOPT_OPTION_H__
