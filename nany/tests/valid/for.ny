# This test checks for a simple for loop

function main : int
{
	mySet : int[] := new int[];
	for i in mySet do
		io.cout << i;
	myStringSet : string[] := new string[];
	return 0;
}
