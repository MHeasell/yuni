#ifndef __YUNI_TEST_CHECKPOINT_H__
# define __YUNI_TEST_CHECKPOINT_H__


# define YUNI_TEST_ID_MAXLENGTH 255


namespace Yuni
{
namespace Test
{


	class Checkpoint
	{
	public:
		explicit Checkpoint(const char* id);
		~Checkpoint();

		bool operator () (bool b);
		bool operator () (bool b, const char* msg);

	private:
		//! ID
		char pID[YUNI_TEST_ID_MAXLENGTH];
		//! Result
		bool pResult;

	}; // class Checkpoint


	class TimedCheckpoint
	{
	public:
		explicit TimedCheckpoint(const char* id);
		~TimedCheckpoint();

		bool operator () (bool b);
		bool operator () (bool b, const char* msg);

	private:
		//! ID
		char pID[YUNI_TEST_ID_MAXLENGTH];
		//! Start time
		unsigned int pStartTime;

		//! Result
		bool pResult;

	}; // class Checkpoint




} // namespace Test
} // namespace Yuni

#endif // __YUNI_TEST_CHECKPOINT_H__
