
/*
 Copyright (C) 2002, 2003 Ferdinando Ametrano
 Copyright (C) 2003 StatPro Italia srl

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

/*! \file blackconstantvol.hpp
    \brief Black constant volatility, no time dependence, no strike dependence
*/

#ifndef quantlib_blackconstantvol_hpp
#define quantlib_blackconstantvol_hpp

#include <ql/voltermstructure.hpp>
#include <ql/DayCounters/actual365.hpp>
#include <ql/dataformatters.hpp>

namespace QuantLib {

    //! Constant Black volatility, no time-strike dependence
    /*! This class implements the BlackVolatilityTermStructure
        interface for a constant Black volatility (no time/strike
        dependence).
    */
    class BlackConstantVol : public BlackVolatilityTermStructure,
                             public Observer {
      public:
        BlackConstantVol(const Date& referenceDate,
                         Volatility volatility,
                         const DayCounter& dayCounter = Actual365());
        BlackConstantVol(const Date& referenceDate,
                         const RelinkableHandle<Quote>& volatility,
                         const DayCounter& dayCounter = Actual365());
        //! \name BlackVolTermStructure interface
        //@{
        Date referenceDate() const;
        DayCounter dayCounter() const;
        Date maxDate() const;
        Real minStrike() const;
        Real maxStrike() const;
        //@}
        //! \name Observer interface
        //@{
        void update();
        //@}
        //! \name Visitability
        //@{
        virtual void accept(AcyclicVisitor&);
        //@}
      protected:
        virtual Volatility blackVolImpl(Time t, Real) const;
      private:
        Date referenceDate_;
        RelinkableHandle<Quote> volatility_;
        DayCounter dayCounter_;
    };


    // inline definitions

    inline BlackConstantVol::BlackConstantVol(const Date& referenceDate,
                                              Volatility volatility, 
                                              const DayCounter& dayCounter)
    : referenceDate_(referenceDate), dayCounter_(dayCounter) {
        volatility_.linkTo(
                       boost::shared_ptr<Quote>(new SimpleQuote(volatility)));
        registerWith(volatility_);
    }

    inline BlackConstantVol::BlackConstantVol(
                            const Date& referenceDate,
                            const RelinkableHandle<Quote>& volatility,
                            const DayCounter& dayCounter)
    : referenceDate_(referenceDate), volatility_(volatility),
      dayCounter_(dayCounter) {
        registerWith(volatility_);
    }

    inline DayCounter BlackConstantVol::dayCounter() const {
        return dayCounter_;
    }

    inline Date BlackConstantVol::referenceDate() const {
        return referenceDate_;
    }

    inline Date BlackConstantVol::maxDate() const {
        return Date::maxDate();
    }

    inline Real BlackConstantVol::minStrike() const {
        return QL_MIN_REAL;
    }

    inline Real BlackConstantVol::maxStrike() const {
        return QL_MAX_REAL;
    }

    inline void BlackConstantVol::update() {
        notifyObservers();
    }

    inline void BlackConstantVol::accept(AcyclicVisitor& v) {
        Visitor<BlackConstantVol>* v1 = 
            dynamic_cast<Visitor<BlackConstantVol>*>(&v);
        if (v1 != 0)
            v1->visit(*this);
        else
            BlackVolatilityTermStructure::accept(v);
    }

    inline Volatility BlackConstantVol::blackVolImpl(Time t, Real) const {
        return volatility_->value();
    }

}


#endif
