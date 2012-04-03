# Test for type parameters on both classes and methods

class SListItem
{
public
    #! Constructor with item value
    method new(Type, value: Type)
	{
		item := value;
	}

    var next: ref SListItem := nil;
    var item: T;
}

class List
{
public
    #! Empty constructor
    method new(Type)
	{
	}

    #! Get the nth item or nil if there are not enough items
    method get(n)
    {
        if head = nil then return nil;

        current := head;
        while n > 0 and current != nil do
        {
            current := current.next;
            n--
        };
        current
    }

    #! Add an item to the beginning of the list
    method prepend(item)
    {
        queue := if head = nil then nil else head.next;
        head := new ListItem(T, item);
        head.next := queue
    }

    method addToEach(value)
    {
		for item in self do
			item += value;
    }

	method print
	{
		for item in self do
			io.out << "\t" << item << io.endl;
	}

	#! Default enumerator
	method default
	{
		return new class: IEnumerable
		{
			var i := first;

			method next
			{
				i := i.next;
			}
			method valid
			{
				i != nil
			}
		}
	}


private
	type T : Type;
	var head : ref SListItem := nil;

} // class SList


# Test function type parameters


function main
{
    var l := new SList(int);
    l.prepend(24);
    l.prepend(12);
    l.addToEach(2);
    l.print(l);
    l.get(1);
	0
}
