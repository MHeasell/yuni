#ifndef __YUNI_MISC_VERSION_H__
# define __YUNI_MISC_VERSION_H__

# include <yuni/string.h>



namespace Yuni
{

    class Version
    {
    public:
        //! \name Constructor
        //@{
        //! Default constructor
        Version();
        //@}

        int hi() const {return pHi;}
        void hi(const int h) {pHi = h;}

        int lo() const {return pLo;}
        void lo(const int l) {pLo = l;}

        int revision() const {return pRevision;}
        void revision(const int r) {pRevision = r;}

        const String& author() const {return pAuthor;}
        void author(const String& s) {pAuthor = s;}

        const String& webUrl() const {return pWebUrl;}
        void webUrl(const String& s) {pWebUrl = s;}

    private:
        //! The hi version
        int pHi;
        //! The lo version
        int pLo;
        //! The revision
        int pRevision;
        //! The author
        String pAuthor;
        //! The Web address
        String pWebUrl;

    }; // class Version


} // namespace Yuni

#endif // __YUNI_MISC_VERSION_H__
