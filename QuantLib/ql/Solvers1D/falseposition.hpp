
/*
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

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

/*! \file falseposition.hpp
    \brief false-position 1-D solver
*/

#ifndef quantlib_solver1d_falseposition_h
#define quantlib_solver1d_falseposition_h

#include <ql/solver1d.hpp>

namespace QuantLib {

    //! False position 1-D solver
    class FalsePosition : public Solver1D<FalsePosition> {
      public:
        template <class F>
        double solveImpl(const F& f, double xAccuracy) const {

            /* The implementation of the algorithm was inspired by
               Press, Teukolsky, Vetterling, and Flannery,
               "Numerical Recipes in C", 2nd edition, 
               Cambridge University Press
            */

            double fl, fh, xl, xh, dx, del, froot;

            // Identify the limits so that xl corresponds to the low side
            if (fxMin_ < 0.0) {
                xl=xMin_;
                fl = fxMin_;
                xh=xMax_;
                fh = fxMax_;
            } else {
                xl=xMax_;
                fl = fxMax_;
                xh=xMin_;
                fh = fxMin_;
            }
            dx=xh-xl;

            while (evaluationNumber_<=maxEvaluations_) {
                // Increment with respect to latest value
                root_=xl+dx*fl/(fl-fh);
                froot=f(root_);
                evaluationNumber_++;
                if (froot < 0.0) {       // Replace appropriate limit
                    del=xl-root_;
                    xl=root_;
                    fl=froot;
                } else {
                    del=xh-root_;
                    xh=root_;
                    fh=froot;
                }
                dx=xh-xl;
                // Convergence criterion
                if (QL_FABS(del) < xAccuracy || froot == 0.0)  {
                    return root_;
                }
            }

            QL_FAIL("maximum number of function evaluations (" +
                    SizeFormatter::toString(maxEvaluations_) +
                    ") exceeded");
            QL_DUMMY_RETURN(0.0);
        }
    };

}


#endif
