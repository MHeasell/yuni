
#ifndef __LIB_3D_METAOBJECT_H__
# define __LIB_3D_METAOBJECT_H__

namespace W
{
namespace GUI3D
{

    /*! class MetaObject
    ** 
    ** Meta objects define implicit surfaces using a generic field function.
    ** This class is abstract.
    */
    class MetaObject
    {
    public:
	MetaObject(bool pPositive = true) {}
        virtual ~MetaObject() {}
    
        //! Calculate the value of a point through the object's function
        virtual float operator()(const Point& p) const = 0;

    private:
        //! Is the object a positive or negative force? (usually true)
	bool pPositive;

    }; // class MetaObject

} // GUI3D
} // W

#endif // __LIB_3D_METAOBBJECT_H_
