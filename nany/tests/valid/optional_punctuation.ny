#! This test uses optional semi-colons and commas, and the parser should ideally allow them

private class OptionalPunctuation
{
public
#*    enum e
    {
        Value1,
        Value2, # Optional comma
    }
*#

    method foo(a): int
    {
        if a > 1 then
            if a < 4 then
                a;
            else
                foo(a - 1);
        else
            foo(a + 1);
    }
}; # Optional semi-colon

function main()
{
  0; # Optional return
}

