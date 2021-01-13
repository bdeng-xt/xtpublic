#pragma once
#ifndef XT_LOESS_H
#define XT_LOESS_H

/**
* \file Loess.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a class to do Loess interpolation.
*
* \description
*	Modified from https://code.google.com/p/variationtoolkit/source/browse/trunk/src/loess.h
 Implementation of the loess algorithm in C++
 original code R project: http://www.r-project.org/
 http://svn.r-project.org/R/trunk/src/library/stats/src/lowess.c

 TEST:

Using #RStats

    > T<-read.table('data.txt')
    > T
      V1   V2
    1  1  1.5
    2  3  2.0
    3  6  7.0
    4  9  8.0
    5 12 15.0

    > lowess(T$V1,T$V2)
    $x
    [1]  1  3  6  9 12

    $y
    [1] 1.5 2.0 7.0 8.0 8.0

The same dataset, but using this class


    $ ./a.out < data.txt
    1   1.5     1.5
    3   2       2
    6   7       7
    9   8       8
    12  15      8

 */


#include <stdint.h>
#include <vector>
#include <memory>

#include <algorithm>
#include <cmath>
#include <cstring>
//#include "throw.h"
#include "XTConfig.h"
#include "Util.h"

#include <boost/smart_ptr.hpp>
#include "safe_ptr.h"

using namespace std;
//#define TRUE true
//#define FALSE false
//typedef bool Rboolean;
#define imin2(a,b) std::min(a,b)
#define imax2(a,b) std::max(a,b)
#define fmax2(a,b) std::max(a,b)


#define rPsort(x,n,k) std::partial_sort(&x[0],&x[n],&x[k]);

namespace XT {

	class Loess;
	//////typedef for Loess
#if defined(USE_BOOST_SHARED_PTR)

	typedef ::boost::shared_ptr<Loess> LoessPtr;

#elif defined(USE_STD_SHARED_PTR)

	typedef ::std::shared_ptr<Loess> LoessPtr;

#elif defined(USE_SAFE_PTR)

	typedef ::sf::safe_ptr<Loess> LoessPtr;

#else

	typedef ::boost::shared_ptr<Loess> LoessPtr;
#endif


	typedef ::sf::safe_ptr<Loess> LoessSafePtr;

	typedef sf::contfree_safe_ptr<Loess> LoessContFreePtr;
	//////end typedef for Loess

class XT_COMMON_API Loess
    {
    public:
		/**
		*  @name Constructor and Destructor
		*/
		///@{
		/**
		* @brief constructor
		*/
        Loess();

		/**
		* @brief default copy constructor
		*/
		Loess(const Loess& from) = default;

		/**
		* @brief default copy assignment
		*/
		Loess& operator=(const Loess& from) = default;

		/**
		* @brief destructor
		*/
        ~Loess();
		///@}

        /** roportion of points in the plot which influence the smooth at each value */
        double smoother_span; ///< smooth span
        /** the number of ‘robustifying’ iterations which should be performed. */
        int32_t nsteps; ///< number of steps
        /** used to speed up computation */
        double delta_speed; ///< delta speed
        /** perform some basic checks */
        bool paranoid; ///< is paranoid or not

//        std::auto_ptr<std::vector<double> > lowess(const double *x, const double *y, int32_t n);
		 
		std::vector<double> yh; ///< y estimation

		/**
		* @brief calculate
		*
		* @param x as input x axis values
		* @param y as input y axis values
		*/
		void calc(const std::vector<double>& x, const std::vector<double>& y);

		/**
		* @brief get curve point y value
		*
		* @param i as index
		* 
		* @return y value at index i
		*/
		inline double getValue(int i) { return (i>=0 && i< (int)(yh.size()) ) ? yh[i] : 0.0; }

		/**
		* @brief create
		*
		* @return loess function pointer
		*/
		inline static LoessPtr create() { return LoessPtr (new Loess());}

    private:
		/**
		* @brief fsquare function
		*
		* @param x as double value
		*
		* @return fsquare function value
		*/
        static double fsquare(double x);

		/**
		* @brief fcube function
		*
		* @param x as double value
		*
		* @return fcube function value
		*/
        static double fcube(double x);

		/**
		* @brief lowest function
		*/
        void lowest(const double *x, const double *y, int n, const double *xs, double *ys,
                int nleft, int nright, double *w,
                bool userw, double *rw, bool *ok);

		/**
		* @brief c lowess function
		*/
        void clowess(const double  *x, const double *y, int n,
                     double f, int nsteps, double delta,
                     double *ys, double *rw, double *res);

		/**
		* @brief get median from a double array
		*
		* @param daArray as double array
		* @param iSize as size
		*
		* @return median value
		*/
		double getMedian(double daArray[], int iSize);

    };

//////////////////////////////////////



} //end namespace XT
#endif