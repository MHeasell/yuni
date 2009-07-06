<?php

//
// --- Settings ---
//

$headerProtect = '__YUNI_CORE_FUNCTION_FUNCTION';
$filename      = dirname(__FILE__).'/function'; // .h | .hxx





//
// --- Code ---
//

global $h;
global $hxx;
$h = '';
$hxx = '';

function cout($s)
{
	return strlen($s) ? "\t$s\n" : "\n";
}

function GenerateTemplateParameters($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; ++$j)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'typename A'.$j;
	}
	return $ret;
}

function GenerateArguments($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; ++$j)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'A'.$j.' a'.$j;
	}
	return $ret;
}

function GenerateArgumentGetters($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; ++$j)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'ArgGetter<UserType, A'.$j.'>::Get(userData, '.$j.')';
	}
	return $ret;
}

function GeneratePrototype($i)
{
	if (!$i)
		return 'void';
	$ret = '';
	for ($j = 0; $j < $i; ++$j)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'A'.$j;
	}
	return $ret;
}

function GenerateVars($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; ++$j)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'a'.$j;
	}
	return $ret;
}




function Generate($i, $generic)
{
	global $h;
	global $hxx;

	$tmplParametersArgsOnly = GenerateTemplateParameters($i);
	$tmplParameters = 'typename R'. ($i ? ', ' : ' = void').$tmplParametersArgsOnly;
	$tmplParametersDcl = 'typename R'. ($i ? ', ' : '').$tmplParametersArgsOnly;
	$args  = GenerateArguments($i);
	$argGetters  = GenerateArgumentGetters($i);
	$proto = GeneratePrototype($i);
	$vars  = GenerateVars($i);
	$R = ($generic ? 'R' : 'void');
	$tmplImpl = 'R'. ($i ? ', '.$proto : '');

	if ($generic)
	{
		$hxx .= cout('');
		$hxx .= cout('');
		$hxx .= cout('/* Implementation class F'.$i.' */');
		$hxx .= cout('');
	}
	else
	{
		$hxx .= cout('');
		$hxx .= cout('');
		$hxx .= cout('/* Implementation class F'.$i.' Template specialization */');
		$hxx .= cout('');
	}

	$l = '';
	if ($generic)
	{
		$l .= cout('/*!');
		$l .= cout('** \brief Pointer-to-function with '.($i ? ($i == 1 ? 'a single argument' : $i.' arguments') : 'no argument'));
		$l .= cout('*/');
		$l .= cout('template<'.$tmplParameters.'>');
		$l .= cout('class F' . $i);
	}
	else
	{
		if ($i)
			$l .= cout('template<'.$tmplParametersArgsOnly.'>');
		else
			$l .= cout('template<>');
		$l .= cout('class F' . $i.' <void'. ($i ? ', '.$proto : '').'>');
	}
	$l .= cout('{');
	$l .= cout('public:');
	$l .= cout('	//! Prototype of the function');
	$l .= cout('	typedef '.$R.' (*Type) ('.$proto.');');
	$l .= cout('	//! Prototype of the function');
	$l .= cout('	typedef '.$R.' (*value_type) ('.$proto.');');
	$l .= cout('	//! Return Type');
	$l .= cout('	typedef '.$R.' ReturnType;');
	for ($z = 1; $z <= $i; $z++)
	{
		$l .= cout('	//! Type of the '.($z).($z == 1 ? 'st' : ($z == 2 ? 'nd' : ($z == 3 ? 'rd' : 'th'))).' argument');
		$l .= cout('	typedef A'.($z - 1).' A'.($z - 1).'Type;');
	}
	$l .= cout('');
	$l .= cout('	enum');
	$l .= cout('	{');
	$l .= cout('		//! Arguments count');
	$l .= cout('		argumentsCount = '.$i);
	$l .= cout('	};');
	$l .= cout('	enum');
	$l .= cout('	{');
	$l .= cout('		//! Has the function got a return value ?');
	$l .= cout('		hasReturnValue = '.($generic ? 1 : 0));
	$l .= cout('	};');
	$l .= cout('');
	$l .= cout('public:');
	if ($generic)
	{
		$l .= cout('	//! \name Constructors & Destructor');
		$l .= cout('	//@{');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Default constructor');
		$l .= cout('	*/');
		$l .= cout('	F'.$i.'();');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Copy constructor');
		$l .= cout('	*/');
		$l .= cout('	F'.$i.'(const F'.$i.'& copy);');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Constructor with a given pointer to function');
		$l .= cout('	*/');
		$l .= cout('	F'.$i.'(const Type rhs);');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Constructor from a symbol exported by a dynamic library');
		$l .= cout('	*/');
		$l .= cout('	F'.$i.'(const DynamicLibrary::Symbol& symbol);');
		$l .= cout('	//@}');
		$l .= cout('');
		$l .= cout('	//! \name Call');
		$l .= cout('	//@{');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Call the function');
		$l .= cout('	**');
		$l .= cout('	** Nothing will happen if the pointer is null');
		$l .= cout('	** However, the returned value may not be what we shall expect');
		$l .= cout('	** (the default constructor of the returned type is used in this case).');
		$l .= cout('	**');
		$l .= cout('	** \see operator ()');
		for ($z = 0; $z < $i; $z++)
		$l .= cout('	** \param a'.$z.' The '.($z+1).'e argument');
		$l .= cout('	*/');
		$l .= cout('	R call('.$args.') const;');
		$l .= cout('');
		$l .= cout('	/*!');
		$l .= cout('	** \brief Call the function using a getter for the arguments.');
		$l .= cout('	**');
		$l .= cout('	** Nothing will happen if the pointer is null');
		$l .= cout('	** However, the returned value may not be what we shall expect');
		$l .= cout('	** (the default constructor of the returned type is used in this case).');
		$l .= cout('	*/');
		$l .= cout('	template <template <class /* UserType */, class /* FuncArgumentType */> class ArgGetter,');
		$l .= cout('		class UserType>');
		$l .= cout('	R callWithArgumentGetter(UserType userData) const;');
		$l .= cout('	//@}');
		$l .= cout('');
		$l .= cout('	//! \name Pointer');
		$l .= cout('	//@{');
		$l .= cout('	//! Get if the pointer is null');
		$l .= cout('	bool null() const;');
		$l .= cout('');
		$l .= cout('	//! Get if the pointer is valid');
		$l .= cout('	bool valid() const;');
		$l .= cout('');
		$l .= cout('	//! Get the raw pointer');
		$l .= cout('	Type ptr() const;');
		$l .= cout('	//@}');
		$l .= cout('');
		$l .= cout('	//! \name Operators');
		$l .= cout('	//@{');
		$l .= cout('	//! Operator `=` from another Function::F'.$i);
		$l .= cout('	F'.$i.'& operator = (const F'.$i.'& copy);');
		$l .= cout('	//! Operator `=` from a mere pointer to function');
		$l .= cout('	F'.$i.'& operator = (const Type rhs);');
		$l .= cout('	//! Operator `=` from a symbol exported by a dynamic library');
		$l .= cout('	F'.$i.'& operator = (const DynamicLibrary::Symbol& symbol);');
		$l .= cout('	//! \see call()');
		$l .= cout('	R operator () ('.$args.') const;');
		$l .= cout('	//@}');
	}
	else
	{
		$l .= cout('	F'.$i.'()');
		$l .= cout('		:pPtr(NULL)');
		$l .= cout('	{}');
		$l .= cout('');
		$l .= cout('	F'.$i.'(const F'.$i.'& copy)');
		$l .= cout('		:pPtr(copy.pPtr)');
		$l .= cout('	{}');
		$l .= cout('');
		$l .= cout('	F'.$i.'(const Type rhs)');
		$l .= cout('		:pPtr(rhs)');
		$l .= cout('	{}');
		$l .= cout('');
		$l .= cout('	F'.$i.'(const DynamicLibrary::Symbol& symbol)');
		$l .= cout('		:pPtr((Type)(symbol.ptr()))');
		$l .= cout('	{}');
		$l .= cout('');
		$l .= cout('	void call('.$args.') const');
		$l .= cout('	{');
		$l .= cout('		if (pPtr)');
		$l .= cout('			pPtr('.$vars.');');
		$l .= cout('	}');
		$l .= cout('');
		$l .= cout('	template <template <class, class> class ArgGetter, class UserType>');
		$l .= cout('	void callWithArgumentGetter(UserType userData) const');
		$l .= cout('	{');
		$l .= cout('		pPtr('.$argGetters.');');
		$l .= cout('	}');
		$l .= cout('');
		$l .= cout('');
		$l .= cout('	bool null() const {return NULL == pPtr;}');
		$l .= cout('');
		$l .= cout('	bool valid() const {return NULL != pPtr;}');
		$l .= cout('');
		$l .= cout('	Type ptr() const {return pPtr;}');
		$l .= cout('');
		$l .= cout('	F'.$i.'& operator = (const F'.$i.'& copy)');
		$l .= cout('	{');
		$l .= cout('		pPtr = copy.pPtr;');
		$l .= cout('		return *this;');
		$l .= cout('	}');
		$l .= cout('');
		$l .= cout('	F'.$i.'& operator = (const Type rhs)');
		$l .= cout('	{');
		$l .= cout('		pPtr = rhs;');
		$l .= cout('		return *this;');
		$l .= cout('	}');
		$l .= cout('');
		$l .= cout('	F'.$i.'& operator = (const DynamicLibrary::Symbol& symbol)');
		$l .= cout('	{');
		$l .= cout('		pPtr = (Type)(symbol.ptr());');
		$l .= cout('		return *this;');
		$l .= cout('	}');
		$l .= cout('');
		$l .= cout('	void operator () ('.$args.') const');
		$l .= cout('	{');
		$l .= cout('		if (pPtr)');
		$l .= cout('			pPtr('.$vars.');');
		$l .= cout('	}');
	}
	$l .= cout('');
	$l .= cout('public:');
	$l .= cout('	//! Pointer');
	$l .= cout('	Type pPtr;');
	$l .= cout('');
	$l .= cout('}; // class F'.$i.($generic ? '' : ' - Template specialization'));
	$l .= cout('');
	$l .= cout('');
	$l .= cout('');
	$l .= cout('');


	if (!$generic)
		$hxx .= $l;
	else
		$h .= $l;

	unset($l);

	if ($generic)
	{
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>::F'.$i.'()');
		$hxx .= cout('	:pPtr(NULL)');
		$hxx .= cout('{}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>::F'.$i.'(const typename F'.$i.'<'.$tmplImpl.'>::Type p)');
		$hxx .= cout('	:pPtr(p)');
		$hxx .= cout('{}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>::F'.$i.'(const F'.$i.'<'.$tmplImpl.'>& copy)');
		$hxx .= cout('	:pPtr(copy.pPtr)');
		$hxx .= cout('{}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>::F'.$i.'(const DynamicLibrary::Symbol& symbol)');
		$hxx .= cout('	:pPtr((Type)(symbol.ptr()))');
		$hxx .= cout('{}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline R');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::call('.$args.') const');
		$hxx .= cout('{');
		$hxx .= cout('	return pPtr ? pPtr('.$vars.') : R();');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('template <template <class, class> class ArgGetter, class UserType>');
		$hxx .= cout('inline R');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::callWithArgumentGetter(UserType userData) const');
		$hxx .= cout('{');
		$hxx .= cout('	return pPtr ? pPtr('.$argGetters.') : R();');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline R');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::operator () ('.$args.') const');
		$hxx .= cout('{');
		$hxx .= cout('	return pPtr ? pPtr('.$vars.') : R();');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline bool');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::null() const');
		$hxx .= cout('{');
		$hxx .= cout('	return NULL == pPtr;');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline bool');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::valid() const');
		$hxx .= cout('{');
		$hxx .= cout('	return NULL != pPtr;');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline typename F'.$i.'<'.$tmplImpl.'>::Type');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::ptr() const');
		$hxx .= cout('{');
		$hxx .= cout('	return pPtr;');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>&');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::operator = (const F'.$i.'<'.$tmplImpl.'>& copy)');
		$hxx .= cout('{');
		$hxx .= cout('	pPtr = copy.pPtr;');
		$hxx .= cout('	return *this;');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>&');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::operator = (const typename F'.$i.'<'.$tmplImpl.'>::Type rhs)');
		$hxx .= cout('{');
		$hxx .= cout('	pPtr = rhs;');
		$hxx .= cout('	return *this;');
		$hxx .= cout('}');
		$hxx .= cout('');
		$hxx .= cout('template<'.$tmplParametersDcl.'>');
		$hxx .= cout('inline F'.$i.'<'.$tmplImpl.'>&');
		$hxx .= cout('F'.$i.'<'.$tmplImpl.'>::operator = (const DynamicLibrary::Symbol& symbol)');
		$hxx .= cout('{');
		$hxx .= cout('	pPtr = (Type)(symbol.ptr());');
		$hxx .= cout('	return *this;');
		$hxx .= cout('}');
		$hxx .= cout('');

		$hxx .= cout('');

	}
}













$h .= "#ifndef ${headerProtect}_H__\n";
$h .= "# define ${headerProtect}_H__\n";
$h .= "\n";
$h .= "# include \"../../yuni.h\"\n";
$h .= "# include \"../dynamiclibrary/symbol.h\"\n";
$h .= "\n\n";
$h .= "/*\n";
$h .= "**\n";
$h .= "** WARNING !\n";
$h .= "** -----------------------------------------------------------------\n";
$h .= "** This file was automatically generated by ".basename(__FILE__).".\n";
$h .= "** Please make any modifications you wish to this script instead of\n";
$h .= "** this file, as they will otherwise be lost at the next generation.\n";
$h .= "** -----------------------------------------------------------------\n";
$h .= "**\n";
$h .= "*/\n";
$h .= "\n\n\n";
$h .= "namespace Yuni\n";
$h .= "{\n";
$h .= "namespace Function\n";
$h .= "{\n";
$h .= "\n\n\n";


$hxx .= "#ifndef ${headerProtect}_HXX__\n";
$hxx .= "# define ${headerProtect}_HXX__\n";
$hxx .= "\n\n";
$hxx .= "/*\n";
$hxx .= "**\n";
$hxx .= "** WARNING !\n";
$hxx .= "** -----------------------------------------------------------------\n";
$hxx .= "** This file was automatically generated by ".basename(__FILE__).".\n";
$hxx .= "** Please make any modifications you wish to this script instead of\n";
$hxx .= "** this file, as they will otherwise be lost at the next generation.\n";
$hxx .= "** -----------------------------------------------------------------\n";
$hxx .= "**\n";
$hxx .= "*/\n";
$hxx .= "\n\n\n";
$hxx .= "namespace Yuni\n";
$hxx .= "{\n";
$hxx .= "namespace Function\n";
$hxx .= "{\n";
$hxx .= "\n\n\n";


for ($i = 0; $i <= 16; $i++)
{
	Generate($i, true);
	Generate($i, false);
}

$h .= "\n";
$h .= "} // namespace Function\n";
$h .= "} // namespace Yuni";
$h .= "\n\n";
$h .= "# include \"${filename}.hxx\"";
$h .= "\n\n";
$h .= "#endif // ${headerProtect}_H__\n";

$hxx .= "\n";
$hxx .= "} // namespace Function\n";
$hxx .= "} // namespace Yuni";
$hxx .= "\n\n";
$hxx .= "#endif // ${headerProtect}_HXX__\n";



file_put_contents($filename.'.h',   $h);
file_put_contents($filename.'.hxx', $hxx);


