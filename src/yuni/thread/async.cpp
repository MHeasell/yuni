#include "async.h"
#ifdef YUNI_HAS_CPP_MOVE
# include <utility>
#endif



namespace Yuni
{

	class AsyncThread final : public Thread::IThread
	{
	public:
		AsyncThread(const Bind<void ()>& callback) :
			pCallback(callback)
		{}

		virtual ~AsyncThread()
		{
			// mandatory, the user is unlikely to call it when using 'async'
			stop();
		}

	protected:
		virtual bool onExecute() override
		{
			pCallback();
			return false; // this thread is unlikely to be reused
		}

	private:
		Bind<void ()> pCallback;
	};



	Thread::IThread::Ptr  async(const Bind<void ()>& callback, bool autostart)
	{
		Thread::IThread* thread;
		# ifdef YUNI_HAS_CPP_MOVE
		thread = new AsyncThread(std::move(callback));
		# else
		thread = new AsyncThread(callback);
		# endif
		if (autostart)
			thread->start();
		return thread;
	}





} // namespace Yuni


