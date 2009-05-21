#ifndef __YUNI_CORE_FUNCTION_FUNCTION_H__
# define __YUNI_CORE_FUNCTION_FUNCTION_H__

# include "../../yuni.h"
# include "../dynamiclibrary/symbol.h"


/*!
** \internal This header has been generated
**  Please report any changes to the appropriate script
*/



namespace Yuni
{
namespace Function
{



	/*!
	** \brief Pointer-to-function with no argument
	*/
	template<typename R = void>
	class F0
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (void);
		//! Prototype of the function
		typedef R (*value_type) (void);

		enum
		{
			//! Arguments count
			argumentsCount = 0
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F0();
		/*!
		** \brief Copy constructor
		*/
		F0(const F0& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F0(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F0(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		*/
		R call() const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F0
		F0& operator = (const F0& copy);
		//! Operator `=` from a mere pointer to function
		F0& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F0& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () () const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F0




	/*!
	** \brief Pointer-to-function with a single argument
	*/
	template<typename R, typename A0>
	class F1
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0);
		//! Prototype of the function
		typedef R (*value_type) (A0);

		enum
		{
			//! Arguments count
			argumentsCount = 1
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F1();
		/*!
		** \brief Copy constructor
		*/
		F1(const F1& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F1(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F1(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		*/
		R call(A0 a0) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F1
		F1& operator = (const F1& copy);
		//! Operator `=` from a mere pointer to function
		F1& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F1& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F1




	/*!
	** \brief Pointer-to-function with 2 arguments
	*/
	template<typename R, typename A0, typename A1>
	class F2
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1);

		enum
		{
			//! Arguments count
			argumentsCount = 2
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F2();
		/*!
		** \brief Copy constructor
		*/
		F2(const F2& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F2(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F2(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		*/
		R call(A0 a0, A1 a1) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F2
		F2& operator = (const F2& copy);
		//! Operator `=` from a mere pointer to function
		F2& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F2& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F2




	/*!
	** \brief Pointer-to-function with 3 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2>
	class F3
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2);

		enum
		{
			//! Arguments count
			argumentsCount = 3
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F3();
		/*!
		** \brief Copy constructor
		*/
		F3(const F3& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F3(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F3(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		*/
		R call(A0 a0, A1 a1, A2 a2) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F3
		F3& operator = (const F3& copy);
		//! Operator `=` from a mere pointer to function
		F3& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F3& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F3




	/*!
	** \brief Pointer-to-function with 4 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3>
	class F4
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3);

		enum
		{
			//! Arguments count
			argumentsCount = 4
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F4();
		/*!
		** \brief Copy constructor
		*/
		F4(const F4& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F4(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F4(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F4
		F4& operator = (const F4& copy);
		//! Operator `=` from a mere pointer to function
		F4& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F4& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F4




	/*!
	** \brief Pointer-to-function with 5 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
	class F5
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4);

		enum
		{
			//! Arguments count
			argumentsCount = 5
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F5();
		/*!
		** \brief Copy constructor
		*/
		F5(const F5& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F5(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F5(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F5
		F5& operator = (const F5& copy);
		//! Operator `=` from a mere pointer to function
		F5& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F5& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F5




	/*!
	** \brief Pointer-to-function with 6 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	class F6
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5);

		enum
		{
			//! Arguments count
			argumentsCount = 6
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F6();
		/*!
		** \brief Copy constructor
		*/
		F6(const F6& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F6(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F6(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F6
		F6& operator = (const F6& copy);
		//! Operator `=` from a mere pointer to function
		F6& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F6& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F6




	/*!
	** \brief Pointer-to-function with 7 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	class F7
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6);

		enum
		{
			//! Arguments count
			argumentsCount = 7
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F7();
		/*!
		** \brief Copy constructor
		*/
		F7(const F7& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F7(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F7(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F7
		F7& operator = (const F7& copy);
		//! Operator `=` from a mere pointer to function
		F7& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F7& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F7




	/*!
	** \brief Pointer-to-function with 8 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	class F8
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7);

		enum
		{
			//! Arguments count
			argumentsCount = 8
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F8();
		/*!
		** \brief Copy constructor
		*/
		F8(const F8& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F8(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F8(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F8
		F8& operator = (const F8& copy);
		//! Operator `=` from a mere pointer to function
		F8& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F8& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F8




	/*!
	** \brief Pointer-to-function with 9 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	class F9
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8);

		enum
		{
			//! Arguments count
			argumentsCount = 9
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F9();
		/*!
		** \brief Copy constructor
		*/
		F9(const F9& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F9(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F9(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F9
		F9& operator = (const F9& copy);
		//! Operator `=` from a mere pointer to function
		F9& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F9& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F9




	/*!
	** \brief Pointer-to-function with 10 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	class F10
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9);

		enum
		{
			//! Arguments count
			argumentsCount = 10
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F10();
		/*!
		** \brief Copy constructor
		*/
		F10(const F10& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F10(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F10(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F10
		F10& operator = (const F10& copy);
		//! Operator `=` from a mere pointer to function
		F10& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F10& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F10




	/*!
	** \brief Pointer-to-function with 11 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
	class F11
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10);

		enum
		{
			//! Arguments count
			argumentsCount = 11
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F11();
		/*!
		** \brief Copy constructor
		*/
		F11(const F11& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F11(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F11(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F11
		F11& operator = (const F11& copy);
		//! Operator `=` from a mere pointer to function
		F11& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F11& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F11




	/*!
	** \brief Pointer-to-function with 12 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
	class F12
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11);

		enum
		{
			//! Arguments count
			argumentsCount = 12
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F12();
		/*!
		** \brief Copy constructor
		*/
		F12(const F12& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F12(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F12(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		** \param a11 The 12e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F12
		F12& operator = (const F12& copy);
		//! Operator `=` from a mere pointer to function
		F12& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F12& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F12




	/*!
	** \brief Pointer-to-function with 13 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
	class F13
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12);

		enum
		{
			//! Arguments count
			argumentsCount = 13
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F13();
		/*!
		** \brief Copy constructor
		*/
		F13(const F13& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F13(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F13(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		** \param a11 The 12e argument
		** \param a12 The 13e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F13
		F13& operator = (const F13& copy);
		//! Operator `=` from a mere pointer to function
		F13& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F13& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F13




	/*!
	** \brief Pointer-to-function with 14 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
	class F14
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13);

		enum
		{
			//! Arguments count
			argumentsCount = 14
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F14();
		/*!
		** \brief Copy constructor
		*/
		F14(const F14& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F14(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F14(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		** \param a11 The 12e argument
		** \param a12 The 13e argument
		** \param a13 The 14e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F14
		F14& operator = (const F14& copy);
		//! Operator `=` from a mere pointer to function
		F14& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F14& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F14




	/*!
	** \brief Pointer-to-function with 15 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
	class F15
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14);

		enum
		{
			//! Arguments count
			argumentsCount = 15
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F15();
		/*!
		** \brief Copy constructor
		*/
		F15(const F15& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F15(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F15(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		** \param a11 The 12e argument
		** \param a12 The 13e argument
		** \param a13 The 14e argument
		** \param a14 The 15e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F15
		F15& operator = (const F15& copy);
		//! Operator `=` from a mere pointer to function
		F15& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F15& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F15




	/*!
	** \brief Pointer-to-function with 16 arguments
	*/
	template<typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
	class F16
	{
	public:
		//! Prototype of the function
		typedef R (*Type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15);
		//! Prototype of the function
		typedef R (*value_type) (A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15);

		enum
		{
			//! Arguments count
			argumentsCount = 16
		};
		enum
		{
			//! Has the function got a return value ?
			hasReturnValue = 1
		};

	public:
		//! \name Constructors & Destructor
		//@{
		/*!
		** \brief Default constructor
		*/
		F16();
		/*!
		** \brief Copy constructor
		*/
		F16(const F16& copy);
		/*!
		** \brief Constructor with a given pointer to function
		*/
		F16(const Type rhs);
		/*!
		** \brief Constructor from a symbol exported by a dynamic library
		*/
		F16(const DynamicLibrary::Symbol& symbol);
		//@}

		//! \name Call
		//@{
		/*!
		** \brief Call the function
		**
		** Nothing will happen if the pointer is null
		** However, the returned value may not be what we shall expect
		** (the default constructor of the returned type is used in this case).
		**
		** \see operator ()
		** \param a0 The 1e argument
		** \param a1 The 2e argument
		** \param a2 The 3e argument
		** \param a3 The 4e argument
		** \param a4 The 5e argument
		** \param a5 The 6e argument
		** \param a6 The 7e argument
		** \param a7 The 8e argument
		** \param a8 The 9e argument
		** \param a9 The 10e argument
		** \param a10 The 11e argument
		** \param a11 The 12e argument
		** \param a12 The 13e argument
		** \param a13 The 14e argument
		** \param a14 The 15e argument
		** \param a15 The 16e argument
		*/
		R call(A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15) const;
		//@}

		//! \name Pointer
		//@{
		//! Get if the pointer is null
		bool null() const;

		//! Get if the pointer is valid
		bool valid() const;

		//! Get the raw pointer
		Type ptr() const;
		//@}

		//! \name Operators
		//@{
		//! Operator `=` from another Function::F16
		F16& operator = (const F16& copy);
		//! Operator `=` from a mere pointer to function
		F16& operator = (const Type rhs);
		//! Operator `=` from a symbol exported by a dynamic library
		F16& operator = (const DynamicLibrary::Symbol& symbol);
		//! \see call()
		R operator () (A0 a0, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15) const;
		//@}

	public:
		//! Pointer
		Type pPtr;

	}; // class F16





} // namespace Function
} // namespace Yuni

# include "function.hxx"

#endif // __YUNI_CORE_FUNCTION_FUNCTION_H__
