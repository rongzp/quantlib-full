
/*
 Copyright (C) 2005 Eric Ehlers

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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qla/config.hpp>
#endif
#include <qla/objects/barrieroption.hpp>
#include <qla/objects/optionutils.hpp>

namespace QuantLibAddin {

    QuantLib::Barrier::Type IDtoBarrierType(const std::string &typeBarrier) {
        std::string idUpper = QuantLib::StringFormatter::toUppercase(typeBarrier);
        if (idUpper.compare("DOWNIN") ==0)
            return QuantLib::Barrier::DownIn;
        else if (idUpper.compare("UPIN") == 0)
            return QuantLib::Barrier::UpIn;
        else if (idUpper.compare("DOWNOUT") == 0)
            return QuantLib::Barrier::DownOut;
        else if (idUpper.compare("UPOUT") == 0)
            return QuantLib::Barrier::UpOut;
        else
            QL_FAIL("IDtoBarrierType: unrecognized typeID: " + typeBarrier);
    }

    BarrierOption::BarrierOption(
            const boost::shared_ptr<StochasticProcess> &stochasticProcess,
            const std::string &typeBarrier,
            const double &barrier,
            const double &rebate,
            const std::string &optionTypeID,
            const std::string &payoffID,
            const double &strike,
            const std::string &exerciseID,
            const long &exerciseDate,
            const long &settlementDate,
            const std::string &engineID,
            const long &timeSteps) {
        QuantLib::Barrier::Type barrierType = 
            IDtoBarrierType(typeBarrier);
        boost::shared_ptr<QuantLib::StrikedTypePayoff> payoff =
            IDtoPayoff(optionTypeID, payoffID, strike);
        boost::shared_ptr<QuantLib::Exercise> exercise = 
            IDtoExercise(exerciseID, exerciseDate, settlementDate);
        boost::shared_ptr<QuantLib::PricingEngine> pricingEngine =
            IDtoEngine(engineID, timeSteps);
        const boost::shared_ptr<QuantLib::BlackScholesProcess> stochasticProcessQL = 
            boost::static_pointer_cast<QuantLib::BlackScholesProcess>
            (stochasticProcess->getReference());
        barrierOption_ = boost::shared_ptr<QuantLib::BarrierOption>(
            new QuantLib::BarrierOption(
                barrierType,
                barrier,
                rebate,
                stochasticProcessQL, 
                payoff, 
                exercise, 
                pricingEngine));
        ObjHandler::any_ptr any_npv(new boost::any(barrierOption_->NPV()));
        ObjHandler::any_ptr any_engine(new boost::any(std::string(engineID)));
        ObjHandler::ObjectProperty prop_npv(FIELD_NPV, any_npv);
        ObjHandler::ObjectProperty prop_engine(FIELD_ENGINE, any_engine);
        properties_.push_back(prop_npv);
        properties_.push_back(prop_engine);
    }

}

