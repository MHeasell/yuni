
#include <yuni/yuni.h>
#include <yuni/toolbox/event/event.h>
#include <yuni/toolbox/string.h>
#include <iostream>


using namespace Yuni;


// An event
//
// Each template parameter is the type for each argument
// Here is an event with 2 arguments :
Event::E2<void, const Yuni::String&, const Yuni::String&> emailHasBeenReceived;




/*!
 * A subscriber class
 *
 * To be able to receive events, the class must inherit from the base class
 * `Yuni::Event::Receiver`
 */
class Subscriber : public Event::Observer<Subscriber>
{
public:
	//! Constructor
	Subscriber()
	{
		// This class want to be aware when an event is fired
		emailHasBeenReceived.connect(this, &Subscriber::onMailReceived);
	}

	//! Destructor
	virtual ~Subscriber()
	{
		// It is really encouraged to disconnect all events as soon as possible.
		// The base class will do it, however the inherited class will already
		// be removed from the vtable and it might lead to a critical error
		destroyingObserver();
	}

	/*!
	 * This method will be called each time the event `emailHasBeenReceived`
	 * is fired
	 */
	void onMailReceived(const String& subject, const String& from)
	{
		std::cout << "a mail has been received :" << std::endl
			<< "\tFrom    : " << from << std::endl
			<< "\tSubject : " << subject << std::endl;
	}
};



int main(void)
{
	// A subscriber, able to receive some events
	Subscriber sc;
	// A new event
	emailHasBeenReceived("My great subject !", "paul@utopia.org");

	return 0;
}

