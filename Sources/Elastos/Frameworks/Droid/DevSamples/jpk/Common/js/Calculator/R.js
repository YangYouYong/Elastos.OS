/* AUTO-GENERATED FILE.  DO NOT MODIFY.
 *
 * This class was automatically generated by the
 * aapt tool from the resource data it found.  It
 * should not be modified by hand.
 */

// #ifndef __Elastos_DevSamples_Node_JSCalculator_R_H__
// #define __Elastos_DevSamples_Node_JSCalculator_R_H__
// #include <elatypes.h>
// namespace Elastos {
// namespace DevSamples {
// namespace Node {
// namespace JSCalculator {
// class ECO_PUBLIC R {
module.exports = {
    //public: class array {
    array : {
        operatorDescs : 0x7f080000,
    },
    //public: class attr {
    attr : {
        /** <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        maxTextSize : 0x7f010001,
        /** <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        minTextSize : 0x7f010000,
        /** <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
         */
        stepTextSize : 0x7f010002,
    },
    //public: class color {
    color : {
        /**  Default background color for the status bar.
         */
        calculator_accent_color : 0x7f050000,
        /**  Color to indicate an error has occured.
         */
        calculator_error_color : 0x7f050001,
        /**  Background color of the calculator display.
         */
        display_background_color : 0x7f050002,
        /**  Text color for the formula in the calculator display.
         */
        display_formula_text_color : 0x7f050003,
        /**  Text color for the result in the calculator display.
         */
        display_result_text_color : 0x7f050004,
        /**  Background color for the advanced pad.
         */
        pad_advanced_background_color : 0x7f050007,
        /**  Ripple color when a button is pressed in a pad.
         */
        pad_button_advanced_ripple_color : 0x7f05000b,
        /**  Text color for a button in the advanced pad.
         */
        pad_button_advanced_text_color : 0x7f050009,
        /**  Ripple color when a button is pressed in a pad.
         */
        pad_button_ripple_color : 0x7f05000a,
        /**  Text color for a button in a pad.
         */
        pad_button_text_color : 0x7f050008,
        /**  Background color for the numeric pad.
         */
        pad_numeric_background_color : 0x7f050005,
        /**  Background color for the operator pad.
         */
        pad_operator_background_color : 0x7f050006,
    },
    //public: class dimen {
    dimen : {
        /**  The margin between the pad pages when displayed using a view pager.
         */
        pad_page_margin : 0x7f060000,
    },
    //public: class drawable {
    drawable : {
        pad_button_advanced_background : 0x7f020000,
        pad_button_background : 0x7f020001,
    },
    //public: class id {
    id : {
        clr : 0x7f0a0020,
        const_e : 0x7f0a000c,
        const_pi : 0x7f0a000b,
        dec_point : 0x7f0a001b,
        del : 0x7f0a001f,
        digit_0 : 0x7f0a001c,
        digit_1 : 0x7f0a0018,
        digit_2 : 0x7f0a0019,
        digit_3 : 0x7f0a001a,
        digit_4 : 0x7f0a0015,
        digit_5 : 0x7f0a0016,
        digit_6 : 0x7f0a0017,
        digit_7 : 0x7f0a0012,
        digit_8 : 0x7f0a0013,
        digit_9 : 0x7f0a0014,
        display : 0x7f0a0001,
        eq : 0x7f0a001d,
        formula : 0x7f0a0002,
        fun_cos : 0x7f0a0006,
        fun_ln : 0x7f0a0008,
        fun_log : 0x7f0a0009,
        fun_sin : 0x7f0a0005,
        fun_tan : 0x7f0a0007,
        lparen : 0x7f0a000e,
        op_add : 0x7f0a0024,
        op_div : 0x7f0a0021,
        op_fact : 0x7f0a000a,
        op_mul : 0x7f0a0022,
        op_pow : 0x7f0a000d,
        op_sqrt : 0x7f0a0010,
        op_sub : 0x7f0a0023,
        pad_advanced : 0x7f0a0004,
        pad_numeric : 0x7f0a0011,
        pad_operator : 0x7f0a001e,
        pad_pager : 0x7f0a0000,
        result : 0x7f0a0003,
        rparen : 0x7f0a000f,
    },
    //public: class layout {
    layout : {
        activity_calculator : 0x7f040008,
        activity_calculator_land : 0x7f040000,
        activity_calculator_port : 0x7f040001,
        activity_calculator_tablet_port : 0x7f040002,
        display : 0x7f040003,
        pad_advanced : 0x7f040004,
        pad_numeric : 0x7f040005,
        pad_operator_one_col : 0x7f040006,
        pad_operator_two_col : 0x7f040007,
    },
    //public: class mipmap {
    mipmap : {
        ic_launcher_calculator : 0x7f030000,
    },
    //public: class string {
    string : {
        advanced : 0x7f07004b,
        /**  Name of the application. [CHAR_LIMIT=NONE]
         */
        app_name : 0x7f07000d,
        basic : 0x7f07004a,
        clear : 0x7f070041,
        clearDesc : 0x7f07005b,
        clear_history : 0x7f07004c,
        /**  Clear operation to clear the currently entered expression. [CHAR_LIMIT=3]
         */
        clr : 0x7f070020,
        /**  Constant for Euler's number (i.e. "2.7182…"). [CHAR_LIMIT=1]
         */
        const_e : 0x7f070000,
        /**  Constant for pi (i.e. "3.1415…"). [CHAR_LIMIT=1]
         */
        const_pi : 0x7f070001,
        cos : 0x7f070043,
        cosDesc : 0x7f07005e,
        /**  Decimal separator (e.g. "1.23"). [CHAR_LIMIT=1]
         */
        dec_point : 0x7f070010,
        /**  Delete operation to remove last entered token. [CHAR_LIMIT=3]
         */
        del : 0x7f070021,
        delDesc : 0x7f07005a,
        /**  Content description for "clr" button. [CHAR_LIMIT=NONE]
         */
        desc_clr : 0x7f070033,
        /**  Content description for 'e' button. [CHAR_LIMIT=NONE]
         */
        desc_const_e : 0x7f070022,
        /**  Content description for 'π' button. [CHAR_LIMIT=NONE]
         */
        desc_const_pi : 0x7f070023,
        /**  Content description for '.' button. [CHAR_LIMIT=NONE]
         */
        desc_dec_point : 0x7f070024,
        /**  Content description for "del" button. [CHAR_LIMIT=NONE]
         */
        desc_del : 0x7f070034,
        /**  Content description for '=' button. [CHAR_LIMIT=NONE]
         */
        desc_eq : 0x7f070035,
        /**  Content description for 'cos' button. [CHAR_LIMIT=NONE]
         */
        desc_fun_cos : 0x7f070027,
        /**  Content description for 'ln' button. [CHAR_LIMIT=NONE]
         */
        desc_fun_ln : 0x7f070028,
        /**  Content description for 'log' button. [CHAR_LIMIT=NONE]
         */
        desc_fun_log : 0x7f070029,
        /**  Content description for 'sin' button. [CHAR_LIMIT=NONE]
         */
        desc_fun_sin : 0x7f07002a,
        /**  Content description for 'tan' button. [CHAR_LIMIT=NONE]
         */
        desc_fun_tan : 0x7f07002b,
        /**  Content description for '(' button. [CHAR_LIMIT=NONE]
         */
        desc_lparen : 0x7f070025,
        /**  Content description for '+' button. [CHAR_LIMIT=NONE]
         */
        desc_op_add : 0x7f07002c,
        /**  Content description for '÷' button. [CHAR_LIMIT=NONE]
         */
        desc_op_div : 0x7f07002d,
        /**  Content description for '!' button. [CHAR_LIMIT=NONE]
         */
        desc_op_fact : 0x7f07002e,
        /**  Content description for '×' button. [CHAR_LIMIT=NONE]
         */
        desc_op_mul : 0x7f07002f,
        /**  Content description for '^' button. [CHAR_LIMIT=NONE]
         */
        desc_op_pow : 0x7f070030,
        /**  Content description for '√' button. [CHAR_LIMIT=NONE]
         */
        desc_op_sqrt : 0x7f070031,
        /**  Content description for '-' button. [CHAR_LIMIT=NONE]
         */
        desc_op_sub : 0x7f070032,
        /**  Content description for ')' button. [CHAR_LIMIT=NONE]
         */
        desc_rparen : 0x7f070026,
        digit0 : 0x7f070037,
        digit1 : 0x7f070038,
        digit2 : 0x7f070039,
        digit3 : 0x7f07003a,
        digit4 : 0x7f07003b,
        digit5 : 0x7f07003c,
        digit6 : 0x7f07003d,
        digit7 : 0x7f07003e,
        digit8 : 0x7f07003f,
        digit9 : 0x7f070040,
        /**  Decimal representation of zero (e.g. "0", "10", "1.0", "1e0"). [CHAR_LIMIT=1]
         */
        digit_0 : 0x7f070011,
        /**  Decimal representation of one (e.g. "1", "11", "1.1", "1e1"). [CHAR_LIMIT=1]
         */
        digit_1 : 0x7f070012,
        /**  Decimal representation of two (e.g. "2", "22", "2.2", "2e2"). [CHAR_LIMIT=1]
         */
        digit_2 : 0x7f070013,
        /**  Decimal representation of three (e.g. "3", "33", "3.3", "3e3"). [CHAR_LIMIT=1]
         */
        digit_3 : 0x7f070014,
        /**  Decimal representation of four (e.g. "4", "44", "4.4", "4e4"). [CHAR_LIMIT=1]
         */
        digit_4 : 0x7f070015,
        /**  Decimal representation of five (e.g. "5", "55", "5.5", "5e5"). [CHAR_LIMIT=1]
         */
        digit_5 : 0x7f070016,
        /**  Decimal representation of six (e.g. "6", "66", "6.6", "6e6"). [CHAR_LIMIT=1]
         */
        digit_6 : 0x7f070017,
        /**  Decimal representation of seven (e.g. "7", "77", "7.7", "7e7"). [CHAR_LIMIT=1]
         */
        digit_7 : 0x7f070018,
        /**  Decimal representation of eight (e.g. "8", "88", "8.8", "8e8"). [CHAR_LIMIT=1]
         */
        digit_8 : 0x7f070019,
        /**  Decimal representation of eight (e.g. "9", "99", "9.9", "9e9"). [CHAR_LIMIT=1]
         */
        digit_9 : 0x7f07001a,
        divDesc : 0x7f070054,
        dotDesc : 0x7f070058,
        e : 0x7f070045,
        eDesc : 0x7f07005f,
        /**  Equals operator (e.g. "1 + 2 : ?"). [CHAR_LIMIT=1]
         */
        eq : 0x7f07000b,
        equalDesc : 0x7f070061,
        error : 0x7f070036,
        /**  Error displayed when expression evaluates to NaN. [CHAR_LIMIT=14]
         */
        error_nan : 0x7f07000e,
        /**  Error displayed when expression contains a syntax error. [CHAR_LIMIT=14]
         */
        error_syntax : 0x7f07000f,
        factorialDesc : 0x7f070050,
        /**  Abbrev. name of cosine function (e.g. "cos(π)". [CHAR_LIMIT=3]
         */
        fun_cos : 0x7f07001b,
        /**  Natural logarithm function (e.g. "ln(2)"). [CHAR_LIMIT=3]
         */
        fun_ln : 0x7f07001c,
        /**  Logarithm function (e.g. "log(10)"). [CHAR_LIMIT=3]
         */
        fun_log : 0x7f07001d,
        /**  Abbrev. name of sine function (e.g. "sin(π)". [CHAR_LIMIT=3]
         */
        fun_sin : 0x7f07001e,
        /**  Abbrev. name of tangent function (e.g. "tan(π)". [CHAR_LIMIT=3]
         */
        fun_tan : 0x7f07001f,
        /**  Result displayed when expression evaluates to infinity. [CHAR_LIMIT=1]
         */
        inf : 0x7f07000c,
        leftParen : 0x7f070048,
        leftParenDesc : 0x7f07004e,
        lg : 0x7f070047,
        lgDesc : 0x7f070052,
        ln : 0x7f070046,
        lnDesc : 0x7f070051,
        /**  Left parenthesis (e.g. "log(", "2 × (3 - 1)". [CHAR_LIMIT=1]
         */
        lparen : 0x7f070002,
        minusDesc : 0x7f070057,
        mulDesc : 0x7f070055,
        /**  Addition operator (e.g. "1 + 2"). [CHAR_LIMIT=1]
         */
        op_add : 0x7f070004,
        /**  Divide operator (e.g. "1 ÷ 2"). [CHAR_LIMIT=1]
         */
        op_div : 0x7f070005,
        /**  Factorial operator (e.g. "2!"). [CHAR_LIMIT=1]
         */
        op_fact : 0x7f070006,
        /**  Multiply operator (e.g. "1 × 2"). [CHAR_LIMIT=1]
         */
        op_mul : 0x7f070007,
        /**  Power operator (e.g. "1 ^ 2"). [CHAR_LIMIT=1]
         */
        op_pow : 0x7f070008,
        /**  Square root operator (e.g. "√1"). [CHAR_LIMIT=1]
         */
        op_sqrt : 0x7f070009,
        /**  Subtraction operator (e.g. "1 - 2"). [CHAR_LIMIT=1]
         */
        op_sub : 0x7f07000a,
        piDesc : 0x7f070060,
        plusDesc : 0x7f070056,
        powerDesc : 0x7f070059,
        rightParen : 0x7f070049,
        rightParenDesc : 0x7f07004f,
        /**  Right parenthesis (e.g. "log(2)", "(3 - 1) × 2". [CHAR_LIMIT=1]
         */
        rparen : 0x7f070003,
        sin : 0x7f070042,
        sinDesc : 0x7f07005d,
        sqrtDesc : 0x7f070053,
        tan : 0x7f070044,
        tanDesc : 0x7f07005c,
        text_copied_toast : 0x7f07004d,
    },
    //public: class style {
    style : {
        CalculatorTheme : 0x7f090000,
        DisplayEditTextStyle : 0x7f090001,
        DisplayEditTextStyle_Formula : 0x7f090004,
        DisplayEditTextStyle_Result : 0x7f090005,
        PadButtonStyle : 0x7f090002,
        PadButtonStyle_Advanced : 0x7f090006,
        PadButtonStyle_Numeric : 0x7f090007,
        PadButtonStyle_Numeric_Equals : 0x7f090008,
        PadButtonStyle_Operator : 0x7f090009,
        PadButtonStyle_Operator_Text : 0x7f09000a,
        PadLayoutStyle : 0x7f090003,
        PadLayoutStyle_Advanced : 0x7f09000b,
        PadLayoutStyle_Numeric : 0x7f09000c,
        PadLayoutStyle_Operator : 0x7f09000d,
        PadLinearLayoutStyle : 0x7f09000e,
    },
    //public: class styleable {
    styleable : {
        /** Attributes that can be used with a CalculatorEditText.
           <p>Includes the following attributes:</p>
           <table>
           <colgroup align="left" />
           <colgroup align="left" />
           <tr><th>Attribute</th><th>Description</th></tr>
           <tr><td><code>{@link #CalculatorEditText_maxTextSize Elastos.DevSamples.Node.JSCalculator:maxTextSize}</code></td><td></td></tr>
           <tr><td><code>{@link #CalculatorEditText_minTextSize Elastos.DevSamples.Node.JSCalculator:minTextSize}</code></td><td></td></tr>
           <tr><td><code>{@link #CalculatorEditText_stepTextSize Elastos.DevSamples.Node.JSCalculator:stepTextSize}</code></td><td></td></tr>
           </table>
           @see #CalculatorEditText_maxTextSize
           @see #CalculatorEditText_minTextSize
           @see #CalculatorEditText_stepTextSize
         */
        CalculatorEditText : [],
        /**
          <p>This symbol is the offset where the {@link Elastos.DevSamples.Node.JSCalculator.R.attr#maxTextSize}
          attribute's value can be found in the {@link #CalculatorEditText} array.


          <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          @attr name android:maxTextSize
        */
        CalculatorEditText_maxTextSize : 1,
        /**
          <p>This symbol is the offset where the {@link Elastos.DevSamples.Node.JSCalculator.R.attr#minTextSize}
          attribute's value can be found in the {@link #CalculatorEditText} array.


          <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          @attr name android:minTextSize
        */
        CalculatorEditText_minTextSize : 0,
        /**
          <p>This symbol is the offset where the {@link Elastos.DevSamples.Node.JSCalculator.R.attr#stepTextSize}
          attribute's value can be found in the {@link #CalculatorEditText} array.


          <p>Must be a dimension value, which is a floating point number appended with a unit such as "<code>14.5sp</code>".
Available units are: px (pixels), dp (density-independent pixels), sp (scaled pixels based on preferred font size),
in (inches), mm (millimeters).
<p>This may also be a reference to a resource (in the form
"<code>@[<i>package</i>:]<i>type</i>:<i>name</i></code>") or
theme attribute (in the form
"<code>?[<i>package</i>:][<i>type</i>:]<i>name</i></code>")
containing a value of this type.
          @attr name android:stepTextSize
        */
        CalculatorEditText_stepTextSize : 2,
    },
}
// },
// },
// },
// },

// #endif // __Elastos_DevSamples_Node_JSCalculator_R_H__
