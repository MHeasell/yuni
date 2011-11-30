#! This test concerns dynamic type-checking and casting
program RTTI;


function main : int
{
	a: int;

	b: int := a as int;
	c: bool := b is typeof b;
	return 0
}
