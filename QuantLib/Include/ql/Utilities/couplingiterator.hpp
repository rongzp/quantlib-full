
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 * The license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.sourceforge.net/Authors.txt
*/

/*! \file couplingiterator.hpp
    \brief Iterator mapping a function to a pair of underlying sequences

    $Source$
    $Name$
    $Log$
    Revision 1.2  2001/04/12 14:22:19  lballabio
    Optimized operator++/--

    Revision 1.1  2001/04/09 14:07:00  nando
    all the *.hpp moved below the Include/ql level

    Revision 1.2  2001/04/06 18:46:20  nando
    changed Authors, Contributors, Licence and copyright header

    Revision 1.1  2001/04/04 11:07:23  nando
    Headers policy part 1:
    Headers should have a .hpp (lowercase) filename extension
    All *.h renamed to *.hpp

    Revision 1.2  2001/02/16 15:33:03  lballabio
    Used QL_ITERATOR_TRAITS macro

    Revision 1.1  2001/02/14 18:43:07  lballabio
    Added coupling iterators

*/

#ifndef quantlib_coupling_iterator_h
#define quantlib_coupling_iterator_h

#include <iterator>
#include "ql/Utilities/iteratorcategories.hpp"

namespace QuantLib {

    namespace Utilities {

        //! Iterator mapping a function to a pair of underlying sequences
        /*! This iterator advances two underlying iterators and returns the
            values obtained by applying a function to the two values such
            iterators point to.
        */
        template <class Iterator1, class Iterator2, class Function>
        class coupling_iterator : public QL_ITERATOR<
            typename lowest_category_iterator<
                typename QL_ITERATOR_TRAITS<Iterator1>::iterator_category,
                typename QL_ITERATOR_TRAITS<Iterator2>::iterator_category>::
                iterator_category,
            typename Function::result_type,
            typename QL_ITERATOR_TRAITS<Iterator1>::difference_type,
            const typename Function::result_type*,
            const typename Function::result_type&>
        {
          public:
            /* These typedefs are needed even though inherited from QL_ITERATOR
               (see 14.6.2.3 of the standard).  */
            typedef typename Function::result_type value_type;
            typedef typename QL_ITERATOR_TRAITS<Iterator1>::difference_type
                difference_type;
            typedef const typename Function::result_type* pointer;
            typedef const typename Function::result_type& reference;

            coupling_iterator(Iterator1 it1, Iterator2 it2, Function f)
            : it1_(it1), it2_(it2), f_(f) {}
            //! \name Dereferencing
            //@{
            reference operator*()  const {
                x_ = f_(*it1_,*it2_);
                return x_;
            }
            pointer   operator->() const {
                x_ = f_(*it1_,*it2_);
                return &x_;
            }
            //@}
            //! \name Random access
            //@{
            value_type operator[](difference_type n) const {
                return *(*this+n) ;
            }
            //@}
            //! \name Increment and decrement
            //@{
            coupling_iterator& operator++() {
                ++it1_; ++it2_;
                return *this;
            }
            coupling_iterator  operator++(int) {
                coupling_iterator tmp = *this;
                ++it1_; ++it2_;
                return tmp;
            }
            coupling_iterator& operator--() {
                --it1_; --it2_;
                return *this;
            }
            coupling_iterator  operator--(int) {
                coupling_iterator tmp = *this;
                --it1_; --it2_;
                return tmp;
            }
            coupling_iterator& operator+=(difference_type n) {
                it1_+=n; it2_+=n;
                return *this;
            }
            coupling_iterator& operator-=(difference_type n) {
                it1_-=n; it2_-=n;
                return *this;
            }
            coupling_iterator  operator+ (difference_type n) const {
                return coupling_iterator(it1_+n,it2_+n,f_);
            }
            coupling_iterator  operator- (difference_type n) const {
                return coupling_iterator(it1_-n,it2_-n,f_);
            }
            //@}
            //! \name Difference
            //@{
            difference_type operator-(const coupling_iterator& rhs) const {
                return it1_-rhs.it1_;
            }
            //@}
            //! \name Comparisons
            //@{
            bool operator==(const coupling_iterator& rhs) const {
                return it1_ == rhs.it1_;
            }
            bool operator!=(const coupling_iterator& rhs) const {
                return it1_ != rhs.it1_;
            }
            //@}
          private:
            Iterator1 it1_;
            Iterator2 it2_;
            Function f_;
            mutable value_type x_;
        };


        //! helper function to create combining iterators
        /*! \relates coupling_iterator */
        template <class It1, class It2, class Function>
        coupling_iterator<It1,It2,Function>
        make_coupling_iterator(It1 it1, It2 it2, Function f);


        // inline definitions


        template <class It1, class It2, class Function>
        inline coupling_iterator<It1,It2,Function>
        make_coupling_iterator(It1 it1, It2 it2, Function f) {
            return coupling_iterator<It1,It2,Function>(it1,it2,f);
        }

    }

}


#endif
