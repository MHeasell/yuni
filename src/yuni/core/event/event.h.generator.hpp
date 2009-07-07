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
#ifndef __YUNI_CORE_EVENT_EVENT_H__
# define __YUNI_CORE_EVENT_EVENT_H__

# include "../../yuni.h"
# include <list>
# include "../../threads/policy.h"
# include "event.declaration.h"
# include "ievent.h"
# include "observer/observer.h"
# include "observer/item.h"



namespace Yuni
{

/*!
** \brief Events
** \ingroup Events
*/
namespace Event
{


	/*!
	** \todo Implement several methods for executing the event
	*/
	class Immediate
	{
	};



<?php
for ($i = 0; $i <= ARG_MAX; ++$i)
{
	$genArgs = GenerateArguments($i);
	$genArgsWithName = GenerateArgumentsWithName($i);
	$genArgsNameOnly = GenerateArgumentsNameOnly($i);
	$genTpl = GenerateTemplateParameters($i);
?>


	/*!
	** \brief Event with <? if ($i == 0) echo("no parameter\n");else {if ($i == 1) echo("a single parameter\n"); else echo($i." parameters\n");}?>
	**
	** \tparam R Type of the returned value
<?=GenerateTemplateComments($i)?>
	** \tparam TP The threading policy
	*/
	template<class R<?=$genTpl ? ", ".$genTpl : ""?>, template<class> class TP>
	class E<?=$i?> : public TP<E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP> >, public IEvent
	{
	public:
		//! The Threading Policy
		typedef TP<E<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>, TP> > ThreadingPolicy;
		//! List of observers
		typedef std::list<IObserverItemA<?=$i?><R<?=$genArgs ? ", ".$genArgs : ""?>>*> ObserverList;

	public:
		//! \name Constructor & Destructor
		//@{
		/*!
		** \brief Default Constructor
		*/
		E<?=$i?>();
		//! Destructor
		virtual ~E<?=$i?>();
		//@}

		/*!
		** \brief Connect an observer to the event
		**
		** Multiple connection of the same observer with the same
		** pointer-to-member is allow and will result in multiple calls.
		**
		** \param observer A descendant of the template class Observer<>
		** \param method Pointer-to-method
		*/
		template<class C>
		void connect(C* observer, R (C::*method)(<?=$genArgs?>));

		/*!
		** \brief Disconnect an observer attached to the event
		**
		** \param o The observer to remove from the event
		*/
		void disconnect(IObserver* o);

		/*!
		** \brief Disconnect all observers attached to the event
		*/
		void disconnectAll();

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void execute(<?=$genArgsWithName?>);

		/*!
		** \brief Trigger the event
		**
		** All attached observers will be notified with the given parameters.
		*/
		void operator () (<?=$genArgsWithName?>);

	private:
		/*!
		** \brief Remove an observer from the list
		*/
		bool removeFromObserverList(const IObserver* o);

		virtual void internalDetachObserver(const IObserver* o);

	private:
		//! List of observers
		ObserverList pObservers;

	}; // class E<?=$i?>




<?php
}
?>



} // namespace Event
} // namespace Yuni

# include "event.hxx"
# include "event.undef.h"

#endif // __YUNI_CORE_EVENT_OBSERVER_ITEM_H__
<?php
$file = ob_get_clean();
 file_put_contents(dirname(__FILE__)."/event.h", $file);
 die();
?>
