#! This tests involves several types of comparisons
program Comparisons;


function main: int
{
	ok: bool := 1 < 2;
	ok := 4 > 3;
	ok := 32u = 0x20u;
	ok := 33 != 2;
	ok := 69 >= 69;
	ok := 4 <= 33;
	return 0
}
