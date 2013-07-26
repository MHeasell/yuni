#pragma once

namespace Yuni
{
namespace UI
{


	//! Multisampling is a full screen anti-aliasing system that rests on multiplying rendering size
	class MultiSampling
	{
	public:
		//! Available types
		enum Type
		{
			//! No multi-sampling
			msNone,

			//! 2x multi-sampling
			ms2x,

			//! 4x multi-sampling
			ms4x,

			//! 8x multi-sampling
			ms8x

		}; // enum Type


		//! Get the multiplier for a given sampling type
		static uint Multiplier(Type type)
		{
			switch (type)
			{
				case msNone:
					return 1;
				case ms2x:
					return 2;
				case ms4x:
					return 4;
				case ms8x:
					return 8;
			}
			return 1;
		}

	}; // class MultiSampling



} // namespace UI
} // namespace Yuni
