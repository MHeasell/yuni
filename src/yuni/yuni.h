#ifndef __YUNI_COMMONS_H__
# define __YUNI_COMMONS_H__

/*
** The Yuni project is a high-level cross-platform framework. This framework
** intend to provide the most complete set as possible of coherent API related
** to 3D programming, especially game programming. It intends to be a reliable and
** simple bridge between different worlds to make all sort of applications,
** letting the user focus on its real work.
**
** The Yuni project is connected with all those domains :
** - 3D graphics
** - Physics
** - 2D/3D User Interface in 3D context
** - 2D/3D Input devices
** - Sound, playback of 2D/3D sounds
** - Scripting languages
** - Artificial Intelligence, mainly on 3D objects
** - Threading / Parallel computing
** - Networking
** - Real-time and multi-user Collaboration
** - Any other domain related to multimedia or user interaction.
*/





//! \name Informations about the Yuni Library
//@{
//! The hi part of the version of the yuni library
# define YUNI_VERSION_HI  0
//! The lo part of the version of the yuni library
# define YUNI_VERSION_LO  1
//@}


// Operating System / Capabilities auto-detection
# include "toolbox/system/capabilities.h"
// Standard Types
# include "toolbox/system/stdint.h"





/*!
** \brief The Yuni Framework
*/
namespace Yuni
{}



#endif // __YUNI_COMMONS_H__
