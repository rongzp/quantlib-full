
/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email ferdinando@ametrano.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
/*! \file swaptionvolmatrix.hpp
    \brief Swaption volatility matrix

    \fullpath
    ql/Volatilities/%swaptionvolmatrix.hpp
*/

// $Id$

#ifndef quantlib_volatility_matrix_h
#define quantlib_volatility_matrix_h

#include "ql/swaptionvolsurface.hpp"
#include "ql/Math/matrix.hpp"
#include "ql/Math/bilinearinterpolation.hpp"
#include <vector>

namespace QuantLib {

    namespace Volatilities {
        
        //! Swaption volatility matrix
        /*! This class provides the volatility for a given swaption by
            interpolating a volatility matrix whose elements are the market
            volatilities of a set of swaption with given exercise and length
            
            \todo Either add correct copy behavior or inhibit copy. Right now,
                  a copied instance would end up with its own copy of the
                  exercise date and length vector but an interpolation pointing
                  to the original ones.
        */
        class SwaptionVolatilityMatrix : public SwaptionVolatilitySurface {
          public:
            SwaptionVolatilityMatrix(
                const Date& todaysDate,
                const std::vector<Date>& exerciseDates, 
                const std::vector<Time>& lengths, 
                const Math::Matrix& volatilities);
            // inspectors
            Date todaysDate() const;
            Time dateToTime(const Date&) const;
            const std::vector<Date>& exerciseDates() const;
            const std::vector<Time>& lengths() const;
          private:
            Date todaysDate_;
            std::vector<Date> exerciseDates_;
            std::vector<Time> exerciseTimes_;
            std::vector<Time> lengths_;
            Math::Matrix volatilities_;
            // interpolation
            typedef Math::BilinearInterpolation<
                std::vector<Time>::const_iterator,
                std::vector<Time>::const_iterator,
                Math::Matrix> VolInterpolation;
            Handle<VolInterpolation> interpolation_;
            double volatilityImpl(Time start, Time length) const;
        };


        // inline definitions
    
        inline SwaptionVolatilityMatrix::SwaptionVolatilityMatrix(
            const Date& today, const std::vector<Date>& dates, 
            const std::vector<Time>& lengths, const Math::Matrix& vols)
        : todaysDate_(today), exerciseDates_(dates), lengths_(lengths), 
          volatilities_(vols) {
            exerciseTimes_.resize(exerciseDates_.size());
            for (Size i=0; i<exerciseDates_.size(); i++)
                exerciseTimes_[i] = dateToTime(exerciseDates_[i]);
            interpolation_ = Handle<VolInterpolation>(
                new VolInterpolation(exerciseTimes_.begin(),
                                     exerciseTimes_.end(),
                                     lengths_.begin(),
                                     lengths_.end(),
                                     volatilities_));
        }

        inline Date SwaptionVolatilityMatrix::todaysDate() const {
            return todaysDate_;
        }
        
        inline const std::vector<Date>& 
        SwaptionVolatilityMatrix::exerciseDates() const { 
            return exerciseDates_;
        }
        
        inline const std::vector<Time>& 
        SwaptionVolatilityMatrix::lengths() const { 
            return lengths_;
        }

        inline double SwaptionVolatilityMatrix::volatilityImpl(
            Time start, Time length) const {
                return (*interpolation_)(start,length);
        }
        
        inline Time SwaptionVolatilityMatrix::dateToTime(const Date& d) const {
            // keep time linear in the date
            return (d-todaysDate_)/365.25;
        }

    }

}


#endif

