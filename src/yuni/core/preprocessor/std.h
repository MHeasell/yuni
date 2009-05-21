#ifndef __YUNI_CORE_PREPROCESSOR_STANDARD_H__
# define __YUNI_CORE_PREPROCESSOR_STANDARD_H__

/* !!! "C compatibility" header !!! */


/*! String concatenation */
# define YUNI_JOIN(X,Y)  X ## Y

/*! Convenient define to deal with temporary (or not) unused parameter */
# define YUNI_UNUSED_ARGUMENT(X) (void)(X)



#endif /* __YUNI_CORE_PREPROCESSOR_STANDARD_H__ */
