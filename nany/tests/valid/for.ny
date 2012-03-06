# This test checks for a simple for loop

function main : int
{
	var mySet : int[] := new int[];
	for i in mySet do
		io.cout << i;
	var myStringSet : string[] := new string[];
	return 0;
}
