#ifndef __YUNI_COMMONS_H__
# define __YUNI_COMMONS_H__

/*!
** \mainpage The Yuni Framework
**
** \section what What is Yuni ?
**
** The Yuni project is a high-level cross-platform framework. This framework
** intend to provide the most complete set as possible of coherent API related
** to 3D programming, especially game programming. It intends to be a reliable and
** simple bridge between different worlds to make all sort of applications,
** letting the user focus on its real work.
**
** The Yuni project is connected with all those domains :
** - Simulation
** - Game development
** - Artificial Intelligence, mainly on 3D objects
** - Real-time and multi-user Collaboration
** - 3D graphics
** - Physics
** - Threading / Parallel computing
** - 2D/3D User Interface in 3D context
** - 2D/3D Input devices
** - Networking
** - Sound, playback of 2D/3D sounds
** - Scripting languages
** - And Any other domain related to multimedia or user interaction.
*/





/*! \name Informations about the Yuni Library */
/*@{*/
//! The hi part of the version of the yuni library
# define YUNI_VERSION_HI  0
/*! The lo part of the version of the yuni library */
# define YUNI_VERSION_LO  1
/*@}*/


/* The Yuni Framework is a C++ Library, even if some parts are voluntary C compatible */
# ifndef __cplusplus
#	error C++ Only
# endif

/* Standard Preprocessor tools */
# include "core/preprocessor/std.h"
/* Operating System / Capabilities auto-detection */
# include "core/system/capabilities.h"
/* Standard Types */
# include "core/system/stdint.h"





/*!
** \brief The Yuni Framework
*/
namespace Yuni
{}



#endif /* __YUNI_COMMONS_H__ */
