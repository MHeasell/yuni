-- Lua basic program

print "Hello, world. I have been evaluated."

function foo()
	print "The Lua foo() was called.";
	return 1;
end

function callMeOnly()
	print "callMeOnly() called, successful.";
	return 1;
end

function callMeWithArg(arg, arg2)
	print ("callMeWithArg() called with arg " .. arg .. " and " .. arg2 .. " successful.");
	return 1, 2, 3;
end

function callBar()
	print "Let's call the C++ bar().";
	bar(2);
end
