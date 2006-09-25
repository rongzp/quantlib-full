/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Mark Joshi

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef quantlib_market_model_swap_basis_system_hpp
#define quantlib_market_model_swap_basis_system_hpp

#include <ql/MarketModels/lsbasisfunctions.hpp>

namespace QuantLib {

    class SwapBasisSystem : public MarketModelBasisSystem {
      public:
        SwapBasisSystem(const std::vector<Time>& rateTimes,
                        const std::vector<Time>& exerciseTimes);
        Size numberOfExercises() const;
        std::vector<Size> numberOfFunctions() const;
        const EvolutionDescription& evolution() const;
        void nextStep(const CurveState&);
        void reset();
        std::vector<bool> isExerciseTime() const;
        void values(const CurveState&,
                    std::vector<Real>& results) const;
      private:
        std::vector<Time> rateTimes_, exerciseTimes_;
        Size currentIndex_;
        std::vector<Size> rateIndex_;
        EvolutionDescription evolution_;
    };

}


#endif
