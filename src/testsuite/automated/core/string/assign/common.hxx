
# include <yuni/test/test.h>



template<typename C>
struct StringTest
{
	typedef Yuni::StringBase<C>  TestString;

	static void WithCStar()
	{
		{
			Yuni::Test::Checkpoint checkpoint("With a C[]");
			TestString a;
			a = "Hello world";
			std::cout << a << std::endl;
		}
		{
			Yuni::Test::Checkpoint checkpoint("With a C*");
			const C* cstr = "Hello world !";
			TestString a;
			a = cstr;
			std::cout << a << std::endl;
		}
	}


	static void AnotherString()
	{
		Yuni::Test::Checkpoint checkpoint("With another string");
		TestString a;
		TestString b("Dummy text");
		a = b;
		std::cout << a << std::endl;
	}

	static void StdString()
	{
		Yuni::Test::Checkpoint checkpoint("With a std::string");
		TestString a;
		std::basic_string<C> b("Dummy text");
		a = b;
		std::cout << a << std::endl;
	}

	static void WithInt()
	{
		Yuni::Test::Checkpoint checkpoint("With an integer");
		TestString a;
		a = 42;
		std::cout << a << std::endl;
	}


	static void Run()
	{
		WithCStar();
		AnotherString();
		StdString();
		WithInt();
	}

}; // class StringTest



