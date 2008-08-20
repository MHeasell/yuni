#ifndef __YUNI_APPLICATION_ABSTRACT_H__
# define __YUNI_APPLICATION_ABSTRACT_H__

# include <yuni/yuni.h>
# include <yuni/string.h>


namespace Yuni
{
namespace Application
{


    class Abstract
    {
    public:
        /*!
        ** \brief Get the global instance of the application
        */
        static Abstract* Instance();

    public:
        //! \name Constructor & Destructor
        //@{
        //! Constructor
        Abstract(int argc, char* argv[]);
        //! Destructor
        virtual ~Abstract();
        //@}

        /*!
        ** \brief Get if the application should stop as soon as possible
        */
        bool terminated() const {return pTerminated;}
        /*!
        ** \brief Indicate that the application should stop as soon as possible
        */
        void terminate() {pTerminated = true;}

        /*!
        ** \brief Get the full filename of the application
        */
        const String& exeName() const {return pExeName;}

        /*!
        ** \brief Get the root folder of the application
        */
        const String& rootFolder() const {return pRootFolder;}


    private:
        /*!
        ** \brief Parse the command line
        ** \return True to stop the application
        */
        bool parseCommandLine(int argc, char* argv[]);

    private:
        //! Indicates if the application should stop as soon as possible
        bool pTerminated;
        //! The full filename of the application
        String pExeName;
        //! The root folder of the application
        String pRootFolder;

    }; // class Application::Abstract






} // namespace Application
} // namespace Yuni


#endif // __YUNI_APPLICATION_ABSTRACT_H__
