#ifndef __YUNI_THREADS_THREAD_ABSTRACT_H__
# define __YUNI_THREADS_THREAD_ABSTRACT_H__

# include <yuni/yuni.h>
# include <yuni/threads/mutex.h>
# include <yuni/threads/abstract.thread.h>



namespace Yuni
{
namespace Threads
{

    /*!
    ** \brief A simple Thread
    **
    ** To create your own thread, you only have to implement the methode execute(), as follow:
    ** \code
    ** class Job : public Yuni::Threads::Abstract
    ** {
    ** public:
    **     Job(int p): Yuni::Thread(), pTag(p)  {}
    **     virtual ~Job() {stop();} // Absolutely needed
    **
    ** protected:
    **     virtual void execute();
    **
    ** private:
    **     int pTag;
    ** };
    **
    ** void Job::execute()
    ** {
    **     for (int i = 0; i < 50; ++i)
    **        std::cout << "Thread " << pTag << ": Do some stuff here" << std::endl;
    ** }
    **
    ** int main(void)
    ** {
    **     Job job1(1);
    **     Job job2(2);
    **     job1.start();
    **     job2.start();
    **     job1.stop();
    **     job2.stop();
    **     return 0;
    ** }
    ** \endcode
    */
    class Abstract : public Private::AbstractThreadModel
    {
    public:
        //! \name Constructor & Destructor
        //@{
        //! Default constructor
        Abstract();
        //! Destructor
        virtual ~Abstract();
        //@}

    protected:
        virtual void baseExecute() {execute();}

        /*!
        ** \brief Code to execute when the thread has just started
        */
        virtual bool startTimer() {return false;}
        /*!
        ** \brief Code to execute when the thread is running
        */
        virtual void execute() = 0;
        /*!
        ** \brief Code to execute when the thread has just stopped
        */
        virtual void stopTimer() {}

    }; // class Abstract



} // namespace Threads
} // namespace Yuni

#endif // __YUNI_THREADS_THREAD_ABSTRACT_H__
