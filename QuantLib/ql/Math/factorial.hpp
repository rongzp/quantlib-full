
/*
 Copyright (C) 2003 Ferdinando Ametrano

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it under the
 terms of the QuantLib license.  You should have received a copy of the
 license along with this program; if not, please email quantlib-dev@lists.sf.net
 The license is also available online at http://quantlib.org/html/license.html

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file factorial.hpp
    \brief Factorial numbers calculator
*/

#ifndef quantlib_factorial_h
#define quantlib_factorial_h

#include <ql/types.hpp>

namespace QuantLib {

    //! %Factorial numbers calculator
    class Factorial {
      public:
        static Real get(Natural n);
        static Real ln(Natural n);
      private:
        Factorial() {}
    };

}


#endif
