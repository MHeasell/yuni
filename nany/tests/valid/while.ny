# This test uses a `while` clause

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
