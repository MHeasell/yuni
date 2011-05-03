# This test checks for complex nested if-else situations
program NestedIf;

implementation

function main: int
{
	if (true)
		if (4 > 0)
		{
			n := 0;
			if (32 != 21)
			{
				n := 21;
			}
		}
		else
			n := 1;
	else
		n := 2;
	return 0;
}
