

class DoublyLinkedList
{
public
	var first: Node;
	var last: Node;

	method default
	{
		return new class: IEnumerable
		{
			var i := first;

			method next
			{
				i := i.next;
			}
			method previous
			{
				i := i.previous;
			}
			method valid
			{
				i != nil
			}
		}
	}
} // class DoublyLinkedList

function main
{
	var l := new DoublyLinkedList;
	for i in l do
		io.out << i << io.endl;
	0
}
