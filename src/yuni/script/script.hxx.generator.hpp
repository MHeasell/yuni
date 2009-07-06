<?php

// Generated templates parameters, from A0 to Ai.
function GenerateTemplateParameters($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
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
	for ($j = 0; $j < $i; $j++)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'A'.$j;
	}
	return $ret;
}

ob_start();
?>
#ifndef __YUNI_SCRIPT_SCRIPT_HXX__
# define __YUNI_SCRIPT_SCRIPT_HXX__

/*
**
** WARNING !
** -----------------------------------------------------------------
** This file was automatically generated by <?=basename(__FILE__)?>.
** Please make any modifications you wish to this script instead of
** this file, as they will otherwise be lost at the next generation.
** -----------------------------------------------------------------
**
*/

// Included from script.h
// No system headers here !

namespace Yuni
{
namespace Script
{

<?php for ($i = 0; $i < 17; $i++) { 
	$genArgs = GenerateArguments($i);
	$genTpl = GenerateTemplateParameters($i);
?>
	template <class R<?=$genTpl ? ", ".$genTpl : ""?>>
	bool AScript::bind(const char* functionName, R (*f)(<?=$genArgs?>))
	{
		ThreadingPolicy::MutexLocker locker(*this);

		if (pBoundFunctions.end() == pBoundFunctions.find(functionName))
		{
			typedef Function::F<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>> RealFunctionType;
			Private::Bind::IBinding* intF = new Private::Bind::Binding<RealFunctionType, typename RealFunctionType::ReturnType>(f);

			// TODO: check return value
			internalBindWL(functionName, intF);
			pBoundFunctions.insert(std::pair<String, Private::Bind::IBinding*>(functionName, intF));
			return true;
		}
		return false;
	}

<?php } /* end for */ ?>


} // namespace Script
} // namespace Yuni

#endif // __YUNI_SCRIPT_SCRIPT_HXX__
<?php $file = ob_get_clean();
 file_put_contents(dirname(__FILE__)."/script.hxx", $file);
 die();
?>
