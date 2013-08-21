
#include "ftfont.h"
#include "../core/math.h"
#include "../core/noncopyable.h"
#include "../core/dictionary.h"
#include <map>
#include <ft2build.h>

#include FT_FREETYPE_H // defined from ft2build.h
#include FT_GLYPH_H // defined from ft2build.h


namespace Yuni
{
namespace UI
{

	//! FreeType Library object (actually a pointer type)
	static ::FT_Library ftLibrary = nullptr;


	namespace // anonymous
	{

		//! Access to the FreeType Library object
		static inline ::FT_Library FT()
		{
			if (!ftLibrary)
			{
				if (::FT_Init_FreeType(&ftLibrary))
				{
					std::cerr << "Could not init freetype library !" << std::endl;
					return nullptr;
				}
			}
			return ftLibrary;
		}




		//! Wrapper around a freetype glyph
		class Glyph final : private NonCopyable<Glyph>
		{
		public:
			//! Smart pointer
			typedef SmartPtr<Glyph>  Ptr;
			//! Glyph cache type
			typedef Dictionary<uint, Ptr>::Hash  Cache;

		public:
			//! Constructor
			explicit Glyph(::FT_GlyphSlot slot, uint glyphIndex):
				pIndex(glyphIndex),
				pGlyph(nullptr)
			{
				::FT_Get_Glyph(slot, &pGlyph);
				pHAdvance = (int)(slot->metrics.horiAdvance >> 6);
				pXBearing = (uint)(slot->metrics.horiBearingX >> 6);
				pYBearing = (uint)(slot->metrics.horiBearingY >> 6);
				if (pGlyph->format != FT_GLYPH_FORMAT_BITMAP)
				{
					::FT_Glyph_To_Bitmap(&pGlyph, FT_RENDER_MODE_NORMAL, nullptr, 1);
				}
			}

			//! Destructor
			~Glyph()
			{
				::FT_Done_Glyph(pGlyph);
			}

			//! Glyph index in the face
			uint index() const
			{
				return pIndex;
			}

			//! How much horizontal space the glyph requires (with margins) (in pixels)
			int advance() const
			{
				return pHAdvance;
			}

			//! Left offset of the glyph (in pixels)
			uint xBearing() const
			{
				return pXBearing;
			}

			//! How much the glyph goes above the baseline (in pixels)
			uint yBearing() const
			{
				return pYBearing;
			}

			//! Actual width of the rendered glyph (in pixels)
			uint width() const
			{
				return (uint)((FT_BitmapGlyph)pGlyph)->bitmap.width;
			}

			//! Actual height of the rendered glyph (in pixels)
			uint height() const
			{
				return (uint)((FT_BitmapGlyph)pGlyph)->bitmap.rows;
			}

			//! Bitmap data for the glyph, can be null for whitespaces e.g.
			uint8* bitmap() const
			{
				return ((FT_BitmapGlyph)pGlyph)->bitmap.buffer;
			}

		private:
			//! Store the glyph index for use by other FT functions
			uint pIndex;

			//! The glyph
			::FT_Glyph pGlyph;

			//! Horizontal advance
			int pHAdvance;

			//! Horizontal bearing
			uint pXBearing;

			//! Vertical bearing
			uint pYBearing;

		}; // class Glyph


	} // namespace anonymous




	//! FTFont hidden data
	class FTFontImpl final
	{
	public:
		//! Constructor
		FTFontImpl(const AnyString& faceName, float size):
			pFace(nullptr),
			pValid(false)
		{
			if (not FT() or ::FT_New_Face(FT(), faceName.c_str(), 0, &pFace) or  not pFace)
			{
				std::cerr << "Could not open font \"" << pFace << "\" !" << std::endl;
				return;
			}
			::FT_Set_Char_Size(pFace, 0, (long int)(size * 64), 96, 96);

			pValid = true;
		}

		//! Destructor
		~FTFontImpl()
		{
			if (pValid)
			{
				clearCache();
				::FT_Done_Face(pFace);
			}
		}

		//! Get a glyph
		Glyph::Ptr getGlyph(unsigned long charCode) const
		{
			if (not pValid)
				return nullptr;

			// Search in the cache
			auto it = pCache.find(charCode);
			if (pCache.end() != it)
				return it->second;

			// Retrieve glyph index from character code
			uint glyphIndex = ::FT_Get_Char_Index(pFace, charCode);
			// Load glyph image into the slot (erase previous one)
			if (!glyphIndex or ::FT_Load_Glyph(pFace, glyphIndex, FT_LOAD_DEFAULT))
				return nullptr;
			::FT_GlyphSlot slot = pFace->glyph;
			// Store the glyph in cache
			Glyph::Ptr glyph = new Glyph(slot, glyphIndex);
			pCache[charCode] = glyph;
			return glyph;
		}

		//! Get the kerning values between two glyphs
		void getKerning(uint leftGlyph, uint rightGlyph, int& x, int& y) const
		{
			x = 0;
			y = 0;
			if (not pValid or !FT_HAS_KERNING(pFace))
				return;
			FT_Vector kerning;
			if (::FT_Get_Kerning(pFace, leftGlyph, rightGlyph, FT_KERNING_DEFAULT, &kerning))
				return;
			x = kerning.x >> 6;
			y = kerning.y >> 6;
		}

		//! Clear the glyph cache
		void clearCache()
		{
			pCache.clear();
		}

		//! Is the font face properly loaded ?
		bool valid() const
		{
			return pValid;
		}

	private:
		//! Font face
		::FT_Face pFace;

		//! Is the font valid ?
		bool pValid;

	private:
		//! Cache of glyphs
		mutable Glyph::Cache pCache;

	}; // class FTFontImpl





	FTFont::FTFont(const AnyString& name, float size, bool bold, bool italic, bool underline, bool strikeout):
		Font(name, size, bold, italic, underline, strikeout),
		pImpl(nullptr)
	{
		initialize();
	}


	FTFont::~FTFont()
	{
		if (pImpl and pImpl->valid())
			delete pImpl;
	}


	void FTFont::draw(const AnyString& text, Gfx3D::Texture::Ptr& texture, bool useKerning) const
	{
		if (not valid())
			return;

		uint width = 0u;
		uint height = 0u;
		uint highestYBearing = 0u;
		uint lowestUnderBaseline = 0u;
		int xDelta = 0;
		int yDelta = 0;
		Glyph::Ptr glyph;
		Glyph::Ptr prev;

		// Loop on characters once to calculate image dimensions
		auto end = text.utf8end();
		for (auto i = text.utf8begin(); i != end; ++i)
		{
			prev = glyph;
			glyph = pImpl->getGlyph((unsigned long)i->value());
			if (!glyph)
				continue;
			if (useKerning and !(!prev))
				pImpl->getKerning(prev->index(), glyph->index(), xDelta, yDelta);
			width += glyph->advance() + xDelta;
			highestYBearing = Math::Max(highestYBearing, glyph->yBearing());
			lowestUnderBaseline = Math::Max(lowestUnderBaseline, glyph->height() - glyph->yBearing());
		}

		height = highestYBearing + lowestUnderBaseline + 1;
		// Always resize the texture, fail if one dimension is zero
		if (!width || !height)
			return;
		texture->resize(width, height);
		texture->clear();

		uint xPen = 0;
		// Loop on characters
		for (auto i = text.utf8begin(); i != end; ++i)
		{
			prev = glyph;
			glyph = pImpl->getGlyph((unsigned long)i->value());

			if (!glyph)
			{
				//std::cout << "Unknown character '" << *i << "' !" << std::endl;
				continue;
			}
			if (useKerning and !(!prev))
				pImpl->getKerning(prev->index(), glyph->index(), xDelta, yDelta);
			// glyph->bitmap is null for spaces e.g.
			if (glyph->bitmap())
			{
				// Draw to our target surface
				texture->update(xPen, highestYBearing - glyph->yBearing(),
					glyph->width(), glyph->height(), 1, glyph->bitmap());
			}
			// Increment pen position
			xPen += glyph->advance() + xDelta;
		}
	}


	bool FTFont::initialize()
	{
		delete pImpl;
		pImpl = new FTFontImpl(pName, pSize);
		if (!pImpl->valid())
		{
			delete pImpl;
			pImpl = nullptr;
			return false;
		}
		return true;
	}


	void FTFont::reset()
	{
		if (pImpl)
			pImpl->clearCache();
	}


	bool FTFont::valid() const
	{
		return pImpl and FT() and pImpl->valid();
	}




} // namespace UI
} // namespace Yuni
