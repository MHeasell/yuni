#! A function declaration and call with no type

function foo(a, b, c)
{
	a << b << c;
}

function main: int
{
	foo("Plop", 42, '@');
	return 0;
}
