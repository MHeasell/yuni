#ifndef __YUNI_CORE_COLOR_RGBA_HXX__
# define __YUNI_CORE_COLOR_RGBA_HXX__


namespace Yuni
{
namespace Extension
{
namespace Color
{


	template<class RGBType, class T>
	struct RGBA
	{
		typedef typename  RGBType::Type Type;
		typedef typename  RGBType::template Calculation<T>::Type CalculationType;

		static inline void Assign(RGBType& color, const T& value)
		{
			enum
			{
				upperBound = Yuni::Private::Color::DefaultValues<T>::upperBound,
				lowerBound = Yuni::Private::Color::DefaultValues<T>::lowerBound,
			};
			// new value
			const CalculationType v = ((int)RGBType::upperBound == (int)upperBound && (int)RGBType::lowerBound == (int)lowerBound)
				? static_cast<CalculationType>(value)
				: static_cast<CalculationType>(value) * RGBType::upperBound / upperBound;
			// assignment
			color.red   = v;
			color.green = v;
			color.blue  = v;
			color.alpha = v;
		}

		static bool IsEqual(RGBType& color, const T& value)
		{
			enum
			{
				upperBound = Yuni::Private::Color::DefaultValues<T>::upperBound,
				lowerBound = Yuni::Private::Color::DefaultValues<T>::lowerBound,
			};
			// new value
			const CalculationType v = ((int)RGBType::upperBound == (int)upperBound && (int)RGBType::lowerBound == (int)lowerBound)
				? static_cast<CalculationType>(value)
				: static_cast<CalculationType>(value) * RGBType::upperBound / upperBound;

			return color.red   == v
				&& color.green == v
				&& color.blue  == v
				&& color.alpha == v;
		}

		template<bool PlusT>
		static inline void Increase(RGBType& color, const T& value)
		{
			enum
			{
				upperBound = Yuni::Private::Color::DefaultValues<T>::upperBound,
				lowerBound = Yuni::Private::Color::DefaultValues<T>::lowerBound,
			};
			// new value
			const CalculationType v = ((int)RGBType::upperBound == (int)upperBound && (int)RGBType::lowerBound == (int)lowerBound)
				? static_cast<CalculationType>(value)
				: static_cast<CalculationType>(value) * RGBType::upperBound / upperBound;
			// assignment
			if (PlusT)
			{
				color.red   = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.red)   + v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.green = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.green) + v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.blue  = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.blue)  + v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.alpha = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.alpha) + v, (CalculationType)lowerBound, (CalculationType)upperBound);
			}
			else
			{
				color.red   = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.red)   - v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.green = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.green) - v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.blue  = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.blue)  - v, (CalculationType)lowerBound, (CalculationType)upperBound);
				color.alpha = Math::MinMaxEx<Type>(static_cast<CalculationType>(color.alpha) - v, (CalculationType)lowerBound, (CalculationType)upperBound);
			}
		}

	}; // class RGBA


	template<class U, class V>
	struct RGBA<Yuni::Color::RGBA<U>, Yuni::Color::RGBA<V> >
	{
		typedef typename Yuni::Color::RGBA<U>::template Calculation<V>::Type CalculationType;

		static inline void Assign(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGBA<V>& value)
		{

			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGBA<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGBA<V>::lowerBound)
			{
				color.red   = static_cast<U>(value.red);
				color.green = static_cast<U>(value.green);
				color.blue  = static_cast<U>(value.blue);
				color.alpha = static_cast<U>(value.alpha);
			}
			else
			{
				color.red   = static_cast<U>(static_cast<CalculationType>(value.red)   * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound);
				color.green = static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound);
				color.blue  = static_cast<U>(static_cast<CalculationType>(value.blue)  * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound);
				color.alpha = static_cast<U>(static_cast<CalculationType>(value.alpha) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound);
			}
		}

		static inline bool IsEqual(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGBA<V>& value)
		{
			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGBA<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGBA<V>::lowerBound)
			{
				return
					color.red      == static_cast<U>(value.red)
					&& color.green == static_cast<U>(value.green)
					&& color.blue  == static_cast<U>(value.blue)
					&& color.alpha == static_cast<U>(value.alpha);
			}
			else
			{
				return
					color.red      == static_cast<U>(static_cast<CalculationType>(value.red)   * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound)
					&& color.green == static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound)
					&& color.blue  == static_cast<U>(static_cast<CalculationType>(value.blue)  * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound)
					&& color.alpha == static_cast<U>(static_cast<CalculationType>(value.alpha) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound);
			}
		}

		template<bool PlusT>
		static inline void Increase(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGBA<V>& value)
		{
			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGBA<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGBA<V>::lowerBound)
			{
				if (PlusT)
				{
					color.red   = Math::MinMaxEx<U>(static_cast<CalculationType>(color.red)   + static_cast<U>(value.red),   Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(static_cast<CalculationType>(color.green) + static_cast<U>(value.green), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue  = Math::MinMaxEx<U>(static_cast<CalculationType>(color.blue)  + static_cast<U>(value.blue),  Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.alpha = Math::MinMaxEx<U>(static_cast<CalculationType>(color.alpha) + static_cast<U>(value.alpha), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
				else
				{
					color.red   = Math::MinMaxEx<U>(static_cast<CalculationType>(color.red)   - static_cast<U>(value.red),   Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(static_cast<CalculationType>(color.green) - static_cast<U>(value.green), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue  = Math::MinMaxEx<U>(static_cast<CalculationType>(color.blue)  - static_cast<U>(value.blue),  Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.alpha = Math::MinMaxEx<U>(static_cast<CalculationType>(color.alpha) - static_cast<U>(value.alpha), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
			}
			else
			{
				if (PlusT)
				{
					color.red = Math::MinMaxEx<U>(
						color.red   + static_cast<U>(static_cast<CalculationType>(value.red) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(
						color.green + static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue = Math::MinMaxEx<U>(
						color.blue  + static_cast<U>(static_cast<CalculationType>(value.blue) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.alpha = Math::MinMaxEx<U>(
						color.alpha + static_cast<U>(static_cast<CalculationType>(value.alpha) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
				else
				{
					color.red = Math::MinMaxEx<U>(
						color.red   - static_cast<U>(static_cast<CalculationType>(value.red) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(
						color.green - static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue = Math::MinMaxEx<U>(
						color.blue  - static_cast<U>(static_cast<CalculationType>(value.blue) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.alpha = Math::MinMaxEx<U>(
						color.alpha - static_cast<U>(static_cast<CalculationType>(value.alpha) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGBA<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
			}
		}

	}; // class RGBA



	template<class U, class V>
	struct RGBA<Yuni::Color::RGBA<U>, Yuni::Color::RGB<V> >
	{
		typedef typename Yuni::Color::RGBA<U>::template Calculation<V>::Type CalculationType;

		static inline void Assign(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGB<V>& value)
		{
			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGB<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGB<V>::lowerBound)
			{
				color.red   = static_cast<U>(value.red);
				color.green = static_cast<U>(value.green);
				color.blue  = static_cast<U>(value.blue);
			}
			else
			{
				color.red   = static_cast<U>(static_cast<CalculationType>(value.red)   * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound);
				color.green = static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound);
				color.blue  = static_cast<U>(static_cast<CalculationType>(value.blue)  * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound);
			}
			color.alpha = static_cast<U>(Yuni::Color::RGBA<U>::upperBound);
		}

		static inline bool IsEqual(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGB<V>& value)
		{
			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGB<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGB<V>::lowerBound)
			{
				return
					value.alpha    == Yuni::Color::RGBA<U>::upperBound
					&& color.red   == static_cast<U>(value.red)
					&& color.green == static_cast<U>(value.green)
					&& color.blue  == static_cast<U>(value.blue);
			}
			else
			{
				return
					value.alpha    == Yuni::Color::RGBA<U>::upperBound
					&& color.red   == static_cast<U>(static_cast<CalculationType>(value.red)   * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound)
					&& color.green == static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound)
					&& color.blue  == static_cast<U>(static_cast<CalculationType>(value.blue)  * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound);
			}
		}

		template<bool PlusT>
		static inline void Increase(Yuni::Color::RGBA<U>& color, const Yuni::Color::RGB<V>& value)
		{
			if ((int)Yuni::Color::RGBA<U>::upperBound == (int)Yuni::Color::RGB<V>::upperBound
				&& (int)Yuni::Color::RGBA<U>::lowerBound == (int)Yuni::Color::RGB<V>::lowerBound)
			{
				if (PlusT)
				{
					color.red   = Math::MinMaxEx<U>(static_cast<CalculationType>(color.red)   + static_cast<U>(value.red),   Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(static_cast<CalculationType>(color.green) + static_cast<U>(value.green), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue  = Math::MinMaxEx<U>(static_cast<CalculationType>(color.blue)  + static_cast<U>(value.blue),  Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
				else
				{
					color.red   = Math::MinMaxEx<U>(static_cast<CalculationType>(color.red)   - static_cast<U>(value.red),   Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(static_cast<CalculationType>(color.green) - static_cast<U>(value.green), Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue  = Math::MinMaxEx<U>(static_cast<CalculationType>(color.blue)  - static_cast<U>(value.blue),  Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
			}
			else
			{
				if (PlusT)
				{
					color.red = Math::MinMaxEx<U>(
						color.red   + static_cast<U>(static_cast<CalculationType>(value.red) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(
						color.green + static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue = Math::MinMaxEx<U>(
						color.blue  + static_cast<U>(static_cast<CalculationType>(value.blue) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
				else
				{
					color.red = Math::MinMaxEx<U>(
						color.red   - static_cast<U>(static_cast<CalculationType>(value.red) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.green = Math::MinMaxEx<U>(
						color.green - static_cast<U>(static_cast<CalculationType>(value.green) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
					color.blue = Math::MinMaxEx<U>(
						color.blue  - static_cast<U>(static_cast<CalculationType>(value.blue) * Yuni::Color::RGBA<U>::upperBound / Yuni::Color::RGB<V>::upperBound),
						Yuni::Color::RGBA<U>::lowerBound, Yuni::Color::RGBA<U>::upperBound);
				}
			}
		}

	}; // class RGBA



} // namespace Color
} // namespace Extension
} // namespace Yuni


namespace Yuni
{
namespace Color
{

	template<class T>
	inline RGBA<T>::RGBA()
		:red(), green(), blue(), alpha()
	{}
	

	template<class T>
	inline RGBA<T>::RGBA(const RGBA<T>& rhs)
		:red(rhs.red), green(rhs.green), blue(rhs.blue), alpha(rhs.alpha)
	{}
	

	template<class T>
	template<class U>
	inline RGBA<T>::RGBA(const U& value)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, U>::Assign(*this, value);
	}
	

	template<class T>
	template<class R, class G, class B, class A>
	inline RGBA<T>::RGBA(R r, G g, B b, A a)
		:red( Math::MinMaxEx<T>(r, static_cast<R>(lowerBound), static_cast<R>(upperBound))),
		green(Math::MinMaxEx<T>(g, static_cast<G>(lowerBound), static_cast<G>(upperBound))),
		blue( Math::MinMaxEx<T>(b, static_cast<B>(lowerBound), static_cast<B>(upperBound))),
		alpha(Math::MinMaxEx<T>(a, static_cast<A>(lowerBound), static_cast<A>(upperBound)))
	{}


	template<class T>
	template<class R, class G, class B>
	inline RGBA<T>::RGBA(R r, G g, B b)
		:red( Math::MinMaxEx<T>(r, static_cast<R>(lowerBound), static_cast<R>(upperBound))),
		green(Math::MinMaxEx<T>(g, static_cast<G>(lowerBound), static_cast<G>(upperBound))),
		blue( Math::MinMaxEx<T>(b, static_cast<B>(lowerBound), static_cast<B>(upperBound))),
		alpha(static_cast<T>(Yuni::Private::Color::DefaultValues<T>::upperBound))
	{}


	template<class T>
	template<class R, class G, class B, class A>
	inline void RGBA<T>::assign(R r, G g, B b, A a)
	{
		red   = Math::MinMaxEx<T>(r, static_cast<R>(lowerBound), static_cast<R>(upperBound));
		green = Math::MinMaxEx<T>(g, static_cast<G>(lowerBound), static_cast<G>(upperBound));
		blue  = Math::MinMaxEx<T>(b, static_cast<B>(lowerBound), static_cast<B>(upperBound));
		alpha = Math::MinMaxEx<T>(a, static_cast<A>(lowerBound), static_cast<A>(upperBound));
	}


	template<class T>
	template<class R, class G, class B>
	inline void RGBA<T>::assign(R r, G g, B b)
	{
		red   = Math::MinMaxEx<T>(r, static_cast<R>(lowerBound), static_cast<R>(upperBound));
		green = Math::MinMaxEx<T>(g, static_cast<G>(lowerBound), static_cast<G>(upperBound));
		blue  = Math::MinMaxEx<T>(b, static_cast<B>(lowerBound), static_cast<B>(upperBound));
		alpha = static_cast<T>(Yuni::Private::Color::DefaultValues<T>::upperBound);
	}


	template<class T>
	template<class U>
	inline void RGBA<T>::assign(const U& value)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, U>::Assign(*this, value);
	}


	template<class T>
	inline bool RGBA<T>::valid() const
	{
		return
			(   red   >= static_cast<T>(lowerBound) && red   <= static_cast<T>(upperBound))
			&& (green >= static_cast<T>(lowerBound) && green <= static_cast<T>(upperBound))
			&& (blue  >= static_cast<T>(lowerBound) && blue  <= static_cast<T>(upperBound))
			&& (alpha >= static_cast<T>(lowerBound) && alpha <= static_cast<T>(upperBound));
	}


	template<class T>
	inline bool RGBA<T>::visible() const
	{
		return Yuni::Math::Equals<T>(alpha, static_cast<T>(lowerBound));
	}



	template<class T>
	inline RGBA<T>& RGBA<T>::operator = (const RGBA<T>& rhs)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, RGBA<T> >::Assign(*this, rhs);
		return *this;
	}


	template<class T>
	template<class U>
	inline RGBA<T>& RGBA<T>::operator = (const U& rhs)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, U>::Assign(*this, rhs);
		return *this;
	}


	template<class T>
	template<class U>
	inline bool RGBA<T>::operator != (const U& rhs) const
	{
		return ! Yuni::Extension::Color::RGBA<RGBA<T>, U>::IsEqual(*this, rhs);
	}


	template<class T>
	template<class U>
	inline bool RGBA<T>::operator == (const U& rhs) const
	{
		return Yuni::Extension::Color::RGBA<RGBA<T>, U>::IsEqual(*this, rhs);
	}


	template<class T>
	template<class U>
	inline RGBA<T>& RGBA<T>::operator += (const U& rhs)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, U>::template Increase<true>(*this, rhs);
		return *this;
	}


	template<class T>
	template<class U>
	inline RGBA<T>& RGBA<T>::operator -= (const U& rhs)
	{
		Yuni::Extension::Color::RGBA<RGBA<T>, U>::template Increase<false>(*this, rhs);
		return *this;
	}


	template<class T>
	template<unsigned int ChunkSizeT, bool ExpandableT, bool ZeroT>
	void RGBA<T>::print(CustomString<ChunkSizeT, ExpandableT, ZeroT>& string) const
	{
		string << "rgba("
			<< static_cast<PrintType>(red) << ','
			<< static_cast<PrintType>(green) << ','
			<< static_cast<PrintType>(blue) << ','
			<< static_cast<PrintType>(alpha) << ')';
	}

	template<class T>
	template<class StreamT>
	void RGBA<T>::print(StreamT& out) const
	{
		CustomString<64, false, true> string;
		string
			<< static_cast<PrintType>(red) << ','
			<< static_cast<PrintType>(green) << ','
			<< static_cast<PrintType>(blue) << ','
			<< static_cast<PrintType>(alpha) << ')';
		out << "rgba(" << string;
	}




} // namespace Color
} // namespace Yuni



template<class T>
inline std::ostream& operator << (std::ostream& out, const Yuni::Color::RGBA<T>& rhs)
{
	rhs.print(out);
	return out;
}


template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator + (const Yuni::Color::RGBA<U> a, const Yuni::Color::RGBA<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r += b;
	return r;
}

template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator - (const Yuni::Color::RGBA<U>& a, const Yuni::Color::RGBA<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r -= b;
	return r;
}


template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator + (const Yuni::Color::RGB<U> a, const Yuni::Color::RGBA<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r += b;
	return r;
}

template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator - (const Yuni::Color::RGB<U>& a, const Yuni::Color::RGBA<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r -= b;
	return r;
}

template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator + (const Yuni::Color::RGBA<U> a, const Yuni::Color::RGB<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r += b;
	return r;
}

template<class U, class V>
inline
Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type>
operator - (const Yuni::Color::RGBA<U>& a, const Yuni::Color::RGB<V>& b)
{
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<U>::template Calculation<V>::Type> r = a;
	r -= b;
	return r;
}



# define YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(V) \
	template<class T> \
	inline \
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> \
	operator + (V v, const Yuni::Color::RGBA<T>& rhs) \
	{ \
		Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> r = rhs; \
		r += v; \
		return r; \
	} \
	template<class T> \
	inline \
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> \
	operator - (V v, const Yuni::Color::RGBA<T>& rhs) \
	{ \
		Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> r = rhs; \
		r -= v; \
		return r; \
	}


# define YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(V) \
	template<class T> \
	inline \
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> \
	operator + (const Yuni::Color::RGBA<T>& rhs, V v) \
	{ \
		Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> r = rhs; \
		r += v; \
		return r; \
	} \
	template<class T> \
	inline \
	Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> \
	operator - (const Yuni::Color::RGBA<T>& rhs, V v) \
	{ \
		Yuni::Color::RGBA<typename Yuni::Color::template RGBA<T>::template Calculation<V>::Type> r = rhs; \
		r -= v; \
		return r; \
	}


YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::sint8)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::sint16)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::sint32)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::sint64)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::uint8)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::uint16)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::uint32)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(Yuni::uint64)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(float)
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(double)
# ifdef YUNI_HAS_LONG_DOUBLE
YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA(long double)
# endif

YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::sint8)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::sint16)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::sint32)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::sint64)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::uint8)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::uint16)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::uint32)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(Yuni::uint64)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(float)
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(double)
# ifdef YUNI_HAS_LONG_DOUBLE
YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE(long double)
# endif

# undef YUNI_COLOR_RGBA_OPERATOR_TYPE_RGBA
# undef YUNI_COLOR_RGBA_OPERATOR_RGBA_TYPE


#endif // __YUNI_CORE_COLOR_RGBA_HXX__
