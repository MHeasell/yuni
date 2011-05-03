# This test checks a simple recursive program with no class, and simple math
program fibonacci;

implementation

#! \brief Fibonacci (recursive way)
immutable function Fibonacci(n) : typeof n
{
   if (n < 2)
       return n;
   return Fibonacci(n - 1) + Fibonacci(n - 2);
}


function main(argc, argv) : int
{
   print(Fibonacci(10));
   return 0;
}
