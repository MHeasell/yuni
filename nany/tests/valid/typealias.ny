#! This test uses type aliases

class Typedef
{
public
	type A := Typedef;
}

type B := Typedef.A;

function main
{
	0
}
