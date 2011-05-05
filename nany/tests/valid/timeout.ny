# This test is another twist on Fibonacci with timeout features added
program timeout;

//! Fibonacci (recursive way)
immutable function Fibonacci(n) : typeof n
{
	if n < 2 then
		n;
	else
		Fibonacci(n - 1) + Fibonacci(n - 2);
}

function main
{
	x := & Fibonacci(2147483648) ^ Fibonacci(1024);
	countdown := 5;
	timeout 1s do
	{
		// we wait here for the asynchronous result of x
		println(“Fibonacci(2147483648) ^ Fibonacci(1024) = ”, x);
	}
	else
	{
		if --countdown then
		{
			system.cout << countdown << ‘\n’;
			// continue the execution of the expression and wait for 1s again
			continue;
		}
		else
		{
			abort(x);
			system.cout << “Operation timeout\n”;
			return -1;
		}
	}
	return 0;
}
