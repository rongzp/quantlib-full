
/* 
 Copyright (C) 2006, 2007 Eric Ehlers

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

// Excel functions coded by hand, to be registered with Excel
// alongside the autogenerated functions.

#include <oh/utilities.hpp>
#include <oh/exception.hpp>
#include <ohxl/objecthandlerxl.hpp>
#include <ohxl/Conversions/all.hpp>
#include <ohxl/functioncall.hpp>
#include <ohxl/Functions/functioncount.hpp>
#include <map>

#define XLL_DEC extern "C"

void operToOper(OPER *xTarget, const OPER *xSource) {
    if (xSource->xltype == xltypeNum) {
        xTarget->xltype = xltypeNum;
        xTarget->val.num = xSource->val.num;
        return;
    } else if (xSource->xltype == xltypeStr) {
        int len = xSource->val.str[0];
        xTarget->val.str = new char[ len + 1 ];
        if (!xTarget->val.str) 
            throw ObjHandler::Exception("operToOper: error calling new");
        xTarget->xltype = xltypeStr | xlbitDLLFree;
        xTarget->val.str[0] = len;
        if (len)
            strncpy(xTarget->val.str + 1, xSource->val.str + 1, len);
        return;
    } else if (xSource->xltype == xltypeErr) {
        xTarget->xltype = xltypeErr;
        xTarget->val.err = xSource->val.err;
        return;
    } else if (xSource->xltype == xltypeNil) {
        xTarget->xltype = xltypeNil;
        return;
    } else {
        std::ostringstream msg;
        msg << "operToOper: unexpected OPER type: " << xSource->xltype;
        throw ObjHandler::Exception(msg.str());
    }
}

void validateReference(const XLOPER *xReference, const std::string &name) {
    if (xReference->xltype == xltypeErr && xReference->val.err == xlerrRef) {
        std::ostringstream msg;
        msg << "parameter '" << name << "' is not a valid range reference";
        throw ObjHandler::Exception(msg.str());
    }
}

XLL_DEC long *ohTrigger(
        OPER *dummy0,
        OPER *dummy1,
        OPER *dummy2,
        OPER *dummy3,
        OPER *dummy4,
        OPER *dummy5,
        OPER *dummy6,
        OPER *dummy7,
        OPER *dummy8,
        OPER *dummy9) {

        // initialize Function Call object

#ifdef OHXL_ENABLE_GARBAGE_COLLECTION
    ObjHandler::FunctionCall functionCall("ohTrigger");
#endif // OHXL_ENABLE_GARBAGE_COLLECTION

    try {

        // reset the calling cell

#ifdef OHXL_ENABLE_GARBAGE_COLLECTION
        ObjHandler::ObjectHandlerXL::instance().resetCaller();
#endif // OHXL_ENABLE_GARBAGE_COLLECTION

        validateReference(dummy0, "dummy0");
        validateReference(dummy1, "dummy1");
        validateReference(dummy2, "dummy2");
        validateReference(dummy3, "dummy3");
        validateReference(dummy4, "dummy4");
        validateReference(dummy5, "dummy5");
        validateReference(dummy6, "dummy6");
        validateReference(dummy7, "dummy7");
        validateReference(dummy8, "dummy8");
        validateReference(dummy9, "dummy9");

        static long returnValue;
#ifdef OHXL_ENABLE_GARBAGE_COLLECTION
        static std::map<std::string, long> iterators;
        returnValue = iterators[ObjHandler::FunctionCall::instance().getAddressString()]++;
#else
        returnValue = 0;
#endif // OHXL_ENABLE_GARBAGE_COLLECTION
        return &returnValue;

    } catch (const std::exception &e) {
        ObjHandler::ObjectHandlerXL::instance().logError(e.what());
        return 0;
    }
}

XLL_DEC long *ohFunctionCount() {
    static long returnValue = FUNCTION_COUNT;
    return &returnValue;
}

int countValidRows(const OPER &xMulti) {
    for (int numValidRows=xMulti.val.array.rows; numValidRows; --numValidRows) {
        for (int i=0; i<xMulti.val.array.columns; ++i) {
            int index = (numValidRows - 1) * xMulti.val.array.columns + i;
            if (!(xMulti.val.array.lparray[index].xltype & (xltypeErr | xltypeNil)))
                return numValidRows;
        }
    }
    return 1;
}

int countValidCols(const OPER &xMulti) {
    for (int numValidCols=xMulti.val.array.columns; numValidCols; --numValidCols) {
        for (int i=0; i<xMulti.val.array.rows; ++i) {
            int index = (numValidCols - 1) + i * xMulti.val.array.columns;
            if (!(xMulti.val.array.lparray[index].xltype & (xltypeErr | xltypeNil)))
                return numValidCols;
        }
    }
    return 1;
}

XLL_DEC OPER *ohPack(OPER *xInputRange) {

        // initialize Function Call object

#ifdef OHXL_ENABLE_GARBAGE_COLLECTION
    ObjHandler::FunctionCall functionCall("ohPack");
#endif // OHXL_ENABLE_GARBAGE_COLLECTION

    OPER xMulti;
    static OPER xRet;
    xRet.val.array.lparray = 0;

    try {

        Excel(xlCoerce, &xMulti, 2, xInputRange, TempInt(xltypeMulti));

        int numValidRows = countValidRows(xMulti);
        int numValidCols = countValidCols(xMulti);

        xRet.val.array.rows = numValidRows;
        xRet.val.array.columns = numValidCols;
        xRet.val.array.lparray = new OPER[numValidRows * numValidCols]; 
        if (!xRet.val.array.lparray)
            throw ObjHandler::Exception("ohPack: error on call to new");
        xRet.xltype = xltypeMulti | xlbitDLLFree;

        for (int i=0; i<numValidRows; ++i) {
            for (int j=0; j<numValidCols; ++j) {
                int indexSource = i * xMulti.val.array.columns + j;
                int indexTarget = i * numValidCols + j;
                operToOper(&xRet.val.array.lparray[indexTarget], 
                    &xMulti.val.array.lparray[indexSource]);
            }
        }

        Excel(xlFree, 0, 1, &xMulti);
        return &xRet;
    } catch (const std::exception &e) {

        // free any memory that may have been allocated

        Excel(xlFree, 0, 1, &xMulti);

        if (xRet.xltype & xltypeMulti && xRet.val.array.lparray) {
            for (int i=0; i<xRet.val.array.columns * xRet.val.array.rows; ++i) {
                if (xRet.val.array.lparray[i].xltype & xltypeStr && xRet.val.array.lparray[i].val.str)
                    delete [] xRet.val.array.lparray[i].val.str;
            }
            delete [] xRet.val.array.lparray;
        }

        // log the exception and return a null pointer (#NUM!) to Excel

        ObjHandler::ObjectHandlerXL::instance().logError(e.what());
        return 0;
    }
}
