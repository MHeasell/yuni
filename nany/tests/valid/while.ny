# This test uses a `while` clause
program While;

function main
{
	w: int := 0;
	x: uint := 42;
	while x > w do
	{
		x := x - 1
	};
    return 0
}
