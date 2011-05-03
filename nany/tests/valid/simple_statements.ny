# This test checks for several simple statements
program SimpleStatements;

uses Dummy;
uses Dummy.Stupid;
uses Dummy.Stupid.Clever;
uses Dummy.Clever;

implementation

function main: int
{
	a: uint16 := 42;
	{
		err := 1;
		if (false)
			return err;
	}
	while (a > 0)
	{
		--a;
		if (a = 0)
			break;
		else
			continue;
	}
	return 0;
}
