program OptionalSemiComma;

private class Test
{
public
#*    enum e
    {
        Value1,
        Value2,
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
};

function main()
{
  0;
}

