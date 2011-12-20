#! This test concerns dynamic type-checking and casting

function main : int
{
	a: int;

	b: int := a as int;
	c: bool := b is typeof b;
	return 0
}
