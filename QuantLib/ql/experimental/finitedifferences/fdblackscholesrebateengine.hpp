/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2008 Andreas Gaida
 Copyright (C) 2008 Ralph Schreyer
 Copyright (C) 2008, 2009 Klaus Spanderen

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*! \file fdblackscholesrebateengine.hpp
    \brief Finite-Differences Black Scholes barrier option rebate helper engine
*/

#ifndef quantlib_fd_black_scholes_rebate_engine_hpp
#define quantlib_fd_black_scholes_rebate_engine_hpp

#include <ql/experimental/finitedifferences/dividendbarrieroption.hpp>
#include <ql/processes/blackscholesprocess.hpp>

namespace QuantLib {

    //! Finite-Differences Black Scholes barrier option rebate helper engine

    /*!
        \ingroup barrierengines
    */
    class FdBlackScholesRebateEngine
        : public GenericEngine<DividendBarrierOption::arguments,
                               DividendBarrierOption::results> {
      public:
        // Constructor
          FdBlackScholesRebateEngine(
                const boost::shared_ptr<GeneralizedBlackScholesProcess>& process,
                Size tGrid = 100, Size xGrid = 100,
                Real theta = 0.5,
                bool localVol = false, 
                Real illegalLocalVolOverwrite = -Null<Real>());

        void calculate() const;

      private:
        const boost::shared_ptr<GeneralizedBlackScholesProcess> process_;
        const Size tGrid_, xGrid_;
        const Real theta_;
        const bool localVol_;
        const Real illegalLocalVolOverwrite_;
};


}

#endif /*quantlib_fd_black_scholes_rebate_engine_hpp*/
