#ifndef __YUNI_SYSTEM_SCREEN_H__
# define __YUNI_SYSTEM_SCREEN_H__

# include <yuni/yuni.h>
# include <yuni/string.h>
# include <vector>


namespace Yuni
{
namespace System
{
namespace Devices
{


    /*!
    ** \brief Information about a single monitor
    */
    class Monitor
    {
    public:
        //! Handle for a single monitor
        typedef uint16  Handle;
        //! Value for an invalid handle
        static const Handle InvalidHandle = (Handle)(-1);

        /*!
        ** \brief Screen/Monitor resolution
        */
        struct Resolution
        {
            //! \name Constructors
            //@{
            //! Default constructors
            Resolution() : width(640), height(480) { /* Default valid values */ }
            //! Constructor by copy
            Resolution(const Resolution& c) : width(c.width), height(c.height) {}
            //@}

            //! The width of the monitor/screen
            uint16 width;
            //! The height of the monitor/screen
            uint16 height;

        }; // class Resolution

        //! List of monitor resolutions
        typedef std::vector<Resolution>  ResolutionList;

    public:
        //! \name Constructors and Destructor
        //@{
        //! Default constructor
        Monitor() : pHandle(Monitor::InvalidHandle);
        //! Constructor with a given handle
        explicit Monitor(const Monitor::Handle h) { select(h); }
        //! Destructor
        ~Monitor();
        //@}

        /*!
        ** \brief Get the index of the current selected monitor
        */
        Monitor::Handle handle() const {return pHandle;}
        /*!
        ** \brief Get if the handle of this monitor is valid
        */
        bool isValid() const {return pHandle != Monitor::InvalidHandle; }

        /*!
        ** \brief Select a monitor from its index
        **
        ** If the given handle is invalid, the handle will be set to `Monitor::InvalidHandle`
        ** and this method will return `false`.
        **
        ** \param indx The handle of the monitor
        ** \return True if the operation has succeeded, False otherwise
        */
        bool select(const Monitor::Handle indx);

        /*!
        ** \brief Get the current resolution of the selected monitor
        **
        ** \param[out] res The resolution of the monitor
        ** \return True if the operation has succeeded, False otherwise
        */
        bool currentResolution(Resolution& res) const;

        /*!
        ** \brief Get all supported resolutions by the monitor
        **
        ** \param[out] list List of all resolutions
        ** \return True if the operation has succeeded, False otherwise
        */
        bool getAllResolutions(ResolutionList& list) const;

        /*!
        ** \brief Get the name of the monitor, if any
        **
        ** \return The name of the monitor, or an empty value if not available
        */
        String name() const;

        /*!
        ** \brief Get an unique id for this screen
        **
        ** This ID should be considered as unique only on the local computer.
        **
        ** \return A md5 string
        */
        String guid() const;

    private:
        //! The index of the monitor
        Monitor::Handle pHandle;

    }; // class Monitor





    /*!
    ** \brief Informations about all available monitors
    */
    class Monitors
    {
    public:
        //! List of monitors
        typedef std::vector<Monitor>  MonitorList;

    public:
        /*!
        ** \brief Get the number of available monitors
        */
        static Monitor::Handle Count();

        /*!
        ** \brief Get the handle of the primary monitor
        */
        static Monitor::Handle Primary();

        /*!
        ** \brief Find all available monitors
        **
        ** \param[out] list The list of all monitors
        ** \return True if the operation has succeeded, False otherwise
        */
        static bool FindAll(MonitorList& list);

    }; // class Monitors



} // namespace Devices
} // namespace System
} // namespace Yuni

#endif // __YUNI_SYSTEM_SCREEN_H__
