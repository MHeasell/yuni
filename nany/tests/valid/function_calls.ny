#! Several function declarations and calls
program FunctionCalls;

function foo(a: int, b: int, c: char)
{
	c: int := a + b
}

function bar(k: uint): bool
{
	return true
}

function foobar()
{
	k: string := "test"
}


function main: int
{
	a: int := 22;
	foo(a, 44, '@');
	bar(1u);
	foobar;
	return 0
}
