
#include "elastos/droid/calculator2/CalculatorExpressionEvaluator.h"
#include "R.h"
#include "org/javia/arity/Util.h"
#include <Elastos.CoreLibrary.h>
#include <elastos/core/StringUtils.h>
#include <elastos/core/CoreUtils.h>
#include <elastos/utility/logging/Slogger.h>

using Elastos::Utility::Logging::Slogger;

using Elastos::Core::StringUtils;
using Elastos::Core::CoreUtils;
using Elastos::Core::IDouble;
using Org::Javia::Arity::CSymbols;
using Org::Javia::Arity::Util;

namespace Elastos {
namespace Droid {
namespace Calculator2 {

const Int32 CalculatorExpressionEvaluator::MAX_DIGITS = 12;
const Int32 CalculatorExpressionEvaluator::ROUNDING_DIGITS = 2;

CalculatorExpressionEvaluator::CalculatorExpressionEvaluator()
{}

CalculatorExpressionEvaluator::~CalculatorExpressionEvaluator()
{}

CAR_INTERFACE_IMPL(CalculatorExpressionEvaluator, Object, ICalculatorExpressionEvaluator)

ECode CalculatorExpressionEvaluator::constructor(
    /* [in] */ ICalculatorExpressionTokenizer* tokenizer)
{
    CSymbols::New((ISymbols**)&mSymbols);
    mTokenizer = tokenizer;
    return NOERROR;
}

ECode CalculatorExpressionEvaluator::Evaluate(
    /* [in] */ ICharSequence* expr,
    /* [in] */ IEvaluateCallback* callback)
{
    String str;
    expr->ToString(&str);
    return Evaluate(str, callback);
}

ECode CalculatorExpressionEvaluator::Evaluate(
    /* [in] */ const String& expr,
    /* [in] */ IEvaluateCallback* callback)
{
    String strexpr;
    mTokenizer->GetNormalizedExpression(expr, &strexpr);
    // remove any trailing operators
    while (strexpr.GetLength() > 0 && String("+-/*").IndexOf(strexpr.GetChar(strexpr.GetLength() - 1)) != -1) {
        strexpr = strexpr.Substring(0, strexpr.GetLength() - 1);
    }

    // try {
    Double value;
    if (strexpr.GetLength() == 0 || StringUtils::Parse(strexpr, &value) == (ECode)NOERROR) {
        callback->OnEvaluate(strexpr, String(NULL), ICalculator::INVALID_RES_ID);
        return NOERROR;
    }
    // } catch (NumberFormatException e) {
        // strexpr is not a simple number
    // }

    // try {
    Double result;
    FAIL_RETURN(mSymbols->Eval(strexpr, &result))
    Boolean flag = FALSE;
    if ((CoreUtils::Convert(result)->IsNaN(&flag), flag)) {
        ECode ec = callback->OnEvaluate(strexpr, String(NULL), R::string::error_nan);
        if (ec == (ECode)E_SYNTAX_EXCEPTION) {
            return callback->OnEvaluate(strexpr, String(NULL), R::string::error_syntax);
        }
    }
    else {
        // The arity library uses floating point arithmetic when evaluating the expression
        // leading to precision errors in the result. The method doubleToString hides these
        // errors; rounding the result by dropping N digits of precision.
        String temp = Util::DoubleToString(result, MAX_DIGITS, ROUNDING_DIGITS);
        String resultString;
        mTokenizer->GetLocalizedExpression(
                Util::DoubleToString(result, MAX_DIGITS, ROUNDING_DIGITS), &resultString);
        ECode ec = callback->OnEvaluate(strexpr, resultString, ICalculator::INVALID_RES_ID);
        if (ec == (ECode)E_SYNTAX_EXCEPTION) {
            return callback->OnEvaluate(strexpr, String(NULL), R::string::error_syntax);
        }
    }
    // } catch (SyntaxException e) {
    // return callback->OnEvaluate(strexpr, String(NULL), R::string::error_syntax);
    // }
    return NOERROR;
}

} // namespace Calculator2
} // namespace Droid
} // namespace Elastos