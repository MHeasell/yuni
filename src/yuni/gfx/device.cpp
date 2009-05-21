
#include "device.h"
#include "../device/display/list.h"


namespace Yuni
{
namespace Gfx
{

# ifdef YUNI_OS_WINDOWS
	//! The Default device on Microsoft Windows should be DirectX
	const Device::Type Device::DefaultType = ygdtDirectX9;
# else
	//! The Default device on Unixes should be OpenGL
	const Device::Type Device::DefaultType = ygdtOpenGL;
# endif



	String Device::TypeToString(const Type t)
	{
		switch (t)
		{
			case ygdtNull:	   { return "Null"; }
			case ygdtSoftware: { return "Software"; }
			case ygdtOpenGL:   { return "OpenGL"; }
			case ygdtDirectX9: { return "Microsoft DirectX"; } // The latest version of DirectX
			case ygdtDirectX8: { return "Microsoft DirectX (v8)"; }
		}
		return "Null";
	}

	Device::Type Device::StringToType(String s)
	{
		if (s.empty()) // no data
			return DefaultType;

		// Some cleanup to the string
		s.trim();
		s.toLower();

		// OpenGL
		if ("opengl" == s || "open gl" == s)
			return ygdtOpenGL;
		// Microsoft DirectX
		if ("directx" == s || "microsoft Directx") // The latest version of DirectX
			return ygdtDirectX9;
		if ("directx8" == s || "directx v8" == s || "directx (v8)" == s || "microsoft directx (v8)" == s)
			return ygdtDirectX8;
		if ("directx9" == s || "directx v9" == s || "directx (v9)" == s || "microsoft directx (v9)" == s)
			return ygdtDirectX9;
		// Software
		if ("software" == s)
			return ygdtSoftware;
		// Null Device
		if ("null" == s)
			return DefaultType;
		return DefaultType;
	}




	Device::Device()
		:pLocked(false), pType(DefaultType), pMonitor(), pResolution(), pFullscreen(false),
		pStencilbuffer(false), pVSync(false)
	{}

	Device::Device(const Device& c)
		:pLocked(false), pType(c.pType), pMonitor(c.pMonitor), pResolution(c.pResolution), pFullscreen(c.pFullscreen),
		pStencilbuffer(c.pStencilbuffer), pVSync(c.pVSync)
	{}


	Device::~Device()
	{}


	bool Device::type(const Type newType)
	{
		if (!pLocked && newType != ygdtNull)
		{
			// On platforms other than Microsoft Windows only the OpenGL and software devices
			// are available
			# ifndef YUNI_OS_WINDOWS
			if (newType == ygdtOpenGL || newType == ygdtSoftware)
			{
			# endif
				pType = newType;
				return true;
			# ifndef YUNI_OS_WINDOWS
			}
			# endif
		}
		return false;
	}

	bool Device::type(const String& s)
	{
		return pLocked ? false : type(StringToType(s));
	}

	void Device::fullscreen(const bool f)
	{
		if (!pLocked)
			pFullscreen = f;
	}

	bool Device::toggleFullscreen()
	{
		pFullscreen = !pFullscreen;
		return pFullscreen;
	}

	void Device::monitor(const SmartPtr<Yuni::Device::Display::Monitor>& m)
	{
		if (!pLocked && NULL != m)
			pMonitor = m;
	}

	void Device::resolution(const SmartPtr<Yuni::Device::Display::Resolution>& r)
	{
		if (!pLocked && NULL != r)
			pResolution = r;
	}

	void Device::resolution(const uint32 w, const uint32 h, const uint8 d)
	{
		if (!pLocked)
			pResolution = new Yuni::Device::Display::Resolution(w, h, d);
	}


	void Device::stencilbuffer(const bool s)
	{
		if (!pLocked)
			pStencilbuffer = s;
	}


	void Device::vsync(const bool v)
	{
		if (!pLocked)
			pVSync = v;
	}

	void Device::ensuresSettingsAreValid()
	{
		// The monitor must be valid
		if (!pMonitor)
		{
			// The monitor does not seem valid. We'll grab the whole list and we
			// will pick up the primary display as the default monitor
			Yuni::Device::Display::List allDisplays;
			pMonitor = allDisplays.primary();
		}
		// The resolution must be valid for the given monitor
		// It is especially important on OS X where the color depth must be
		// the same as the user's desktop to allow switching to full-screen mode
		if (!pMonitor->resolutionIsValid(pResolution))
			pResolution = pMonitor->recommendedResolution();
	}

	void Device::lock()
	{
		pLocked = true;
	}

	void Device::unlock()
	{
		pLocked = false;
	}


	std::ostream& Device::print(std::ostream& out) const
	{
		out << TypeToString(pType) << " - ";
		if (NULL != pResolution)
			out << "<Invalid Resolution>";
		else
			out << *pResolution;
		out << " - Fullscreen:" << String(pFullscreen) << ", "
			<< "VSync:" << String(pVSync) << ", "
			<< "Stencilbuffer:" << String(pStencilbuffer);
		return out;
	}



} // namespace Gfx
} // namespace Yuni

