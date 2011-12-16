# This test checks a simple class
unit SimpleClass;

uses Dummy.Package;

published class MyClass
{
public
	#! A method declaration
	method name: string { "Baka!" }

	#! A complete method declaration
	threadunsafe method boom(t, s: string, k := 0) { 0 }

private
	#! A constant with inferred type
	attribute PI : const := 3.14159265359;

	#! An attribute
	attribute name: string;
}
