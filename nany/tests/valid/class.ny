# This test checks a simple class
published unit SimpleClass;

uses Dummy.Package;

class MyClass
{
public
	#! A method declaration
	method name: string { "Baka!" }

	#! A complete method declaration
	threadunsafe method boom(t, s: string, k := 0) { 0 }

private
	#! A constant with inferred type
	var PI : const := 3.14159265359;

	#! An attribute
	var name: string;
}
