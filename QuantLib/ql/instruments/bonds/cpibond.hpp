/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2010, 2011 Chris Kenyon
 
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

/*! \file cpibond.hpp
 \brief zero-inflation-indexed-ratio-with-base bond
 */

#ifndef quantlib_cpibond_hpp
#define quantlib_cpibond_hpp


#include <ql/instruments/bond.hpp>
#include <ql/time/dategenerationrule.hpp>
#include <ql/time/daycounter.hpp>
#include <ql/interestrate.hpp>

#include <ql/cashflows/baseindexedcashflow.hpp>

namespace QuantLib {
	
    class Schedule;
	
    //! cpi bond; if there is only one date in the schedule it 
	//! is a zero bond returning an inflated notional.
    /*! \ingroup instruments
	 
	 */
    class CPIbond : public Bond {
	public:
        CPIbond(Natural settlementDays,
				Real faceAmount,
				bool growthOnly,
				Real baseCPI,
				const Period& observationLag,
				const boost::shared_ptr<ZeroInflationIndex>& cpiIndex,
				indexInterpolationType observationInterpolation,
                const Schedule& schedule,
                const std::vector<Rate>& coupons,
                const DayCounter& accrualDayCounter,
                BusinessDayConvention paymentConvention = ModifiedFollowing,
				const Date& issueDate = Date());
        
        Frequency frequency() const { return frequency_; }
        const DayCounter& dayCounter() const { return dayCounter_; }
		bool growthOnly() const { return growthOnly_; }
		Real baseCPI() const { return baseCPI_; }
		Period observationLag() const { return observationLag_; }
		const boost::shared_ptr<ZeroInflationIndex>& cpiIndex() const { return cpiIndex_; }
		indexInterpolationType observationInterpolation() const { return observationInterpolation_; }
		
		// other
        virtual ~CPIbond() {}
		
	protected:
        Frequency frequency_;
        DayCounter dayCounter_;
		bool growthOnly_;
		Real baseCPI_;
		Period observationLag_;
		boost::shared_ptr<ZeroInflationIndex> cpiIndex_;
		indexInterpolationType observationInterpolation_;
    };
	
	
};






#endif
