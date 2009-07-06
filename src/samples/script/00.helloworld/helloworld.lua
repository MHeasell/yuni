-- Lua basic program

print "[ Lua] Hello, world. I have been evaluated."

function foo()
	print "[ Lua] The Lua foo() was called.";
	return 1;
end

function callMeOnly()
	print "[ Lua] callMeOnly() called, successful.";
	return 1;
end

function callMeWithArg(arg, arg2)
	print ("[ Lua] callMeWithArg() called with arg " .. arg .. " and " .. arg2 .. " successful.");
	return 1, 2, 3;
end

function callBar()
	print "[ Lua] Let's call the C++ bar().";
	print ("[ Lua] bar(4242, 2.4, 'nyu', 2, nil, nil) returned [" .. bar(4242, 2.4, "nyu", 0, 0, 0) .. "].");
end
