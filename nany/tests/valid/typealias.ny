#! This test uses type aliases

class Typedef
{
public
	type A := Typedef;

	var k := 0;
}

type B := Typedef.A;

function main
{
	var b : B;
	b.k
}
