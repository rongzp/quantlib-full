
/*
 Copyright (C) 2000, 2001, 2002 RiskMap srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software developed by the QuantLib Group; you can
 redistribute it and/or modify it under the terms of the QuantLib License;
 either version 1.0, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 QuantLib License for more details.

 You should have received a copy of the QuantLib License along with this
 program; if not, please email ferdinando@ametrano.net

 The QuantLib License is also available at http://quantlib.org/license.html
 The members of the QuantLib Group are listed in the QuantLib License
*/
/*! \file arithmeticasopathpricer.hpp
    \brief arithmetic average strike option path pricer

    \fullpath
    ql/MonteCarlo/%arithmeticasopathpricer.hpp
*/

// $Id$

#ifndef quantlib_montecarlo_arithmetic_average_strike_option_path_pricer_h
#define quantlib_montecarlo_arithmetic_average_strike_option_path_pricer_h

#include <ql/MonteCarlo/pathpricer.hpp>
#include <ql/MonteCarlo/path.hpp>

namespace QuantLib {

    namespace MonteCarlo {

        //! %path pricer for average strike Asian options
        class ArithmeticASOPathPricer : public PathPricer<Path> {
          public:
            ArithmeticASOPathPricer(Option::Type type,
                                    double underlying,
                                    DiscountFactor discount,
                                    bool useAntitheticVariance);
            double operator()(const Path& path) const;
          private:
            Option::Type type_;
            double underlying_;
        };

    }

}


#endif
