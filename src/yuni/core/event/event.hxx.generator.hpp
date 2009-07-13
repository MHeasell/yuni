<?php

define('ARG_MAX', 16);


// Generated templates parameter comments, from A0 to Ai.
function GenerateTemplateComments($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		$ret .= '	** \tparam A'.$j.' Type of the '.($j + 1).'th argument'."\n";
	}
	return $ret;
}

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

function GenerateArgumentsWithName($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'A'.$j.' a'.$j;
	}
	return $ret;
}

function GenerateArgumentsNameOnly($i)
{
	if (!$i)
		return '';
	$ret = '';
	for ($j = 0; $j < $i; $j++)
	{
		if ($j)
			$ret .= ', ';
		$ret .= 'a'.$j;
	}
	return $ret;
}



ob_start();
?>
#ifndef __YUNI_CORE_EVENT_EVENT_HXX__
# define __YUNI_CORE_EVENT_EVENT_HXX__



namespace Yuni
{
namespace Event
{


<?php
for ($i = 0; $i <= ARG_MAX; ++$i)
{
	$genArgs = GenerateArguments($i);
	$genArgsWithName = GenerateArgumentsWithName($i);
	$genArgsNameOnly = GenerateArgumentsNameOnly($i);
	$genTpl = GenerateTemplateParameters($i);
?>
	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	inline E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::E<?=$i?>()
	{}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	inline E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::~E<?=$i?>()
	{
		// Disconnecting all attached observers
		disconnectAll();
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	template<class C>
	void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::connect(C* observer, R (C::*method)(<?=$genArgs?>))
	{
		if (observer)
		{
			typename ThreadingPolicy::MutexLocker locker(*this);
			pObservers.push_back(new ObserverItemA<?=$i?><C,Immediate,R<?=$genArgs ? ", ".$genArgs : ""?>>(observer, method));
			observer->internalAttachEvent(this);
		}
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::disconnect(IObserver* o)
	{
		if (NULL != o && removeFromObserverList(o))
			o->internalDetachEvent(this);
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::disconnectAll()
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::iterator end = pObservers.end();
			for (typename ObserverList::iterator i = pObservers.begin(); i != end; ++i)
			{
				((*i)->observer())->internalDetachEvent(this);
				delete *i;
			}
			pObservers.clear();
		}
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::execute(<?=$genArgsWithName?>)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(<?=$genArgsNameOnly?>);
		}
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::operator () (<?=$genArgsWithName?>)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			const typename ObserverList::const_iterator end = pObservers.end();
			for (typename ObserverList::const_iterator i = pObservers.begin(); i != end; ++i)
				(*i)->fireEvent(<?=$genArgsNameOnly?>);
		}
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	bool
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::removeFromObserverList(const IObserver* o)
	{
		typename ThreadingPolicy::MutexLocker locker(*this);
		if (!pObservers.empty())
		{
			// Disconnecting all events connected to a single observer
			// A single observer may have several connections
			const typename ObserverList::iterator end = pObservers.end();
			typename ObserverList::iterator i = pObservers.begin();
			while (i != end)
			{
				if ((*i)->observer() == o)
				{
					// Erasing the item
					delete *i;
					pObservers.erase(i++);
					continue;
				}
				++i;
			}
		}
		return false;
	}


	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	inline void
	E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP>::internalDetachObserver(const IObserver* o)
	{
		removeFromObserverList(o);
	}


<?php
}
?>



} // namespace Event
} // namespace Yuni

#endif // __YUNI_CORE_EVENT_OBSERVER_ITEM_HXX__
<?php
$file = ob_get_clean();
file_put_contents(dirname(__FILE__)."/event.hxx", $file);
die();
?>
