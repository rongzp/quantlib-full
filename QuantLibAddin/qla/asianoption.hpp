
/*
 Copyright (C) 2005, 2006 Eric Ehlers

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

#ifndef qla_asianoption_hpp
#define qla_asianoption_hpp

#include <qla/baseinstruments.hpp>
#include <qla/processes.hpp>
#include <ql/Instruments/asianoption.hpp>

namespace QuantLibAddin {

    class ContinuousAveragingAsianOption : public OneAssetOption {
    public:
        ContinuousAveragingAsianOption(
            const QuantLib::Average::Type &averageType,
            const std::string &handleBlackScholes,
            const std::string &optionTypeID,
            const std::string &payoffID,
            const double &strike,
            const std::string &handleExercise,
            const std::string &engineID,
            const long &timeSteps);

        EXPORT_UNDERLYING_OBJECT(QuantLib::ContinuousAveragingAsianOption, mInstrument)
    };

    class DiscreteAveragingAsianOption : public OneAssetOption {
    public:
        DiscreteAveragingAsianOption(
            const QuantLib::Average::Type &averageType,
            const double &runningAccumulator,
            const long &pastFixings,
            const std::vector < QuantLib::Date > &fixingDates,
            const std::string &handleBlackScholes,
            const std::string &optionTypeID,
            const std::string &payoffID,
            const double &strike,
            const std::string &handleExercise,
            const std::string &engineID,
            const long &timeSteps);

        EXPORT_UNDERLYING_OBJECT(QuantLib::DiscreteAveragingAsianOption, mInstrument)
    };

}

#endif

