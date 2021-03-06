#pragma once
#include <random>

//class Rng
//{
//public:
//	Rng();
//	~Rng();
//
//
//	std::default_random_engine& global_urng()
//	{
//		static std::default_random_engine u;
//		return u;
//	}
//
//	void randomize()
//	{
//		static std::random_device rd{};
//		global_urng().seed(rd());
//	}
//
//	int random(int from, int thru)
//	{
//		static std::uniform_int_distribution<>d{};
//
//		using parm_t = decltype(d)::param_type;
//		return d(global_urng(), parm_t{ from, thru });
//	}
//
//	double random(double from, double upto)
//	{
//		static std::uniform_real_distribution<>	d{};
//
//		using parm_t = decltype(d)::param_type;
//
//		return d(global_urng(), parm_t{ from, upto });
//	};
//};

//#pragma once
//#include <random>
//
//class Rng
//{
//public:
//	Rng();
//	~Rng();
//
//
//	std::default_random_engine& global_urng()
//	{
//		static std::default_random_engine u;
//		return u;
//	}
//
//	void randomize()
//	{
//		static std::random_device rd{};
//		global_urng().seed(rd());
//	}
//
//	int random(int from, int thru)
//	{
//		static std::uniform_int_distribution<>d{};
//
//		using parm_t = decltype(d)::param_type;
//		return d(global_urng(), parm_t{ from, thru });
//	}
//
//	float nextFloat()
//	{
//		return random<float>(0.f, 1.f);
//	}
//
//	float nextDouble()
//	{
//		return random<>(0., 1.);
//	}
//
//	template<class T = double>
//	double random(double from, double upto)
//	{
//		static std::uniform_real_distribution<T>	d{};
//
//		using parm_t = decltype(d)::param_type;
//
//		return d(global_urng(), parm_t{ (T)from, (T)upto });
//	};
//};



#ifndef __PCG32_H
#define __PCG32_H 1

#define PCG32_DEFAULT_STATE  0x853c49e6748fea9bULL
#define PCG32_DEFAULT_STREAM 0xda3e39cb94b95bdbULL
#define PCG32_MULT           0x5851f42d4c957f2dULL

#include <inttypes.h>
#include <cmath>
#include <cassert>

/// PCG32 Pseudorandom number generator
struct Rng {
	/// Initialize the pseudorandom number generator with default seed
	Rng() : state(PCG32_DEFAULT_STATE), inc(PCG32_DEFAULT_STREAM) {}

	/// Initialize the pseudorandom number generator with the \ref seed() function
	Rng(uint64_t initstate, uint64_t initseq = 1u) { seed(initstate, initseq); }

	/**
	* \brief Seed the pseudorandom number generator
	*
	* Specified in two parts: a state initializer and a sequence selection
	* constant (a.k.a. stream id)
	*/
	void seed(uint64_t initstate, uint64_t initseq = 1) {
		state = 0U;
		inc = (initseq << 1u) | 1u;
		nextUInt();
		state += initstate;
		nextUInt();
	}

	/// Generate a uniformly distributed unsigned 32-bit random number
	uint32_t nextUInt() {
		uint64_t oldstate = state;
		state = oldstate * PCG32_MULT + inc;
		uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
		uint32_t rot = (uint32_t)(oldstate >> 59u);
		return (xorshifted >> rot) | (xorshifted << ((~rot + 1u) & 31));
	}

	/// Generate a uniformly distributed number, r, where 0 <= r < bound
	uint32_t nextUInt(uint32_t bound) {
		// To avoid bias, we need to make the range of the RNG a multiple of
		// bound, which we do by dropping output less than a threshold.
		// A naive scheme to calculate the threshold would be to do
		//
		//     uint32_t threshold = 0x100000000ull % bound;
		//
		// but 64-bit div/mod is slower than 32-bit div/mod (especially on
		// 32-bit platforms).  In essence, we do
		//
		//     uint32_t threshold = (0x100000000ull-bound) % bound;
		//
		// because this version will calculate the same modulus, but the LHS
		// value is less than 2^32.

		uint32_t threshold = (~bound + 1u) % bound;

		// Uniformity guarantees that this loop will terminate.  In practice, it
		// should usually terminate quickly; on average (assuming all bounds are
		// equally likely), 82.25% of the time, we can expect it to require just
		// one iteration.  In the worst case, someone passes a bound of 2^31 + 1
		// (i.e., 2147483649), which invalidates almost 50% of the range.  In
		// practice, bounds are typically small and only a tiny amount of the range
		// is eliminated.
		for (;;) {
			uint32_t r = nextUInt();
			if (r >= threshold)
				return r % bound;
		}
	}

//#ifndef DOUBLE_PRECISION
//	/// Generate a single precision floating point value on the interval [0, 1)
//	real nextReal() {
//		/* Trick from MTGP: generate an uniformly distributed
//		single precision number in [1,2) and subtract 1. */
//		union {
//			uint32_t u;
//			float f;
//		} x;
//		x.u = (nextUInt() >> 9) | 0x3f800000UL;
//		return x.f - 1.0f;
//	}
//
//#else

	/**
	* \brief Generate a double precision floating point value on the interval [0, 1)
	*
	* \remark Since the underlying random number generator produces 32 bit output,
	* only the first 32 mantissa bits will be filled (however, the resolution is still
	* finer than in \ref nextFloat(), which only uses 23 mantissa bits)
	*/
	double nextDouble() {
		/* Trick from MTGP: generate an uniformly distributed
		double precision number in [1,2) and subtract 1. */
		union {
			uint64_t u;
			double d;
		} x;
		x.u = ((uint64_t)nextUInt() << 20) | 0x3ff0000000000000ULL;
		return x.d - 1.0;
	}
//#endif

	/**
	* \brief Multi-step advance function (jump-ahead, jump-back)
	*
	* The method used here is based on Brown, "Random Number Generation
	* with Arbitrary Stride", Transactions of the American Nuclear
	* Society (Nov. 1994). The algorithm is very similar to fast
	* exponentiation.
	*/
	void advance(int64_t delta_) {
		uint64_t
			cur_mult = PCG32_MULT,
			cur_plus = inc,
			acc_mult = 1u,
			acc_plus = 0u;

		/* Even though delta is an unsigned integer, we can pass a signed
		integer to go backwards, it just goes "the long way round". */
		uint64_t delta = (uint64_t)delta_;

		while (delta > 0) {
			if (delta & 1) {
				acc_mult *= cur_mult;
				acc_plus = acc_plus * cur_mult + cur_plus;
			}
			cur_plus = (cur_mult + 1) * cur_plus;
			cur_mult *= cur_mult;
			delta /= 2;
		}
		state = acc_mult * state + acc_plus;
	}

	/**
	* \brief Draw uniformly distributed permutation and permute the
	* given STL container
	*
	* From: Knuth, TAoCP Vol. 2 (3rd 3d), Section 3.4.2
	*/
	template <typename Iterator> void shuffle(Iterator begin, Iterator end) {
		for (Iterator it = end - 1; it > begin; --it)
			std::iter_swap(it, begin + nextUInt((uint32_t)(it - begin + 1)));
	}

	/// Compute the distance between two PCG32 pseudorandom number generators
	int64_t operator-(const Rng &other) const {
		assert(inc == other.inc);

		uint64_t
			cur_mult = PCG32_MULT,
			cur_plus = inc,
			cur_state = other.state,
			the_bit = 1u,
			distance = 0u;

		while (state != cur_state) {
			if ((state & the_bit) != (cur_state & the_bit)) {
				cur_state = cur_state * cur_mult + cur_plus;
				distance |= the_bit;
			}
			assert((state & the_bit) == (cur_state & the_bit));
			the_bit <<= 1;
			cur_plus = (cur_mult + 1ULL) * cur_plus;
			cur_mult *= cur_mult;
		}

		return (int64_t)distance;
	}

	uint64_t state;  // RNG state.  All values are possible.
	uint64_t inc;    // Controls which RNG sequence (stream) is selected. Must *always* be odd.
};

#endif // __PCG32_H

