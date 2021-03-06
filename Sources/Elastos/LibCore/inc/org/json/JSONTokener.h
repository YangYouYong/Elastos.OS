//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ORG_JSON_JSONTOKENER_H__
#define __ORG_JSON_JSONTOKENER_H__

#include "Elastos.CoreLibrary.External.h"
#include "Elastos.CoreLibrary.Utility.h"
#include "Object.h"

namespace Org {
namespace Json {

// Note: this class was written without inspecting the non-free org.json sourcecode.

/**
 * Parses a JSON (<a href="http://www.ietf.org/rfc/rfc4627.txt">RFC 4627</a>)
 * encoded string into the corresponding object. Most clients of
 * this class will use only need the {@link #JSONTokener(String) constructor}
 * and {@link #nextValue} method. Example usage: <pre>
 * String json = "{"
 *         + "  \"query\": \"Pizza\", "
 *         + "  \"locations\": [ 94043, 90210 ] "
 *         + "}";
 *
 * JSONObject object = (JSONObject) new JSONTokener(json).nextValue();
 * String query = object.getString("query");
 * JSONArray locations = object.getJSONArray("locations");</pre>
 *
 * <p>For best interoperability and performance use JSON that complies with
 * RFC 4627, such as that generated by {@link JSONStringer}. For legacy reasons
 * this parser is lenient, so a successful parse does not indicate that the
 * input string was valid JSON. All of the following syntax errors will be
 * ignored:
 * <ul>
 *   <li>End of line comments starting with {@code //} or {@code #} and ending
 *       with a newline character.
 *   <li>C-style comments starting with {@code //} and ending with
 *       {@code *}{@code /}. Such comments may not be nested.
 *   <li>Strings that are unquoted or {@code 'single quoted'}.
 *   <li>Hexadecimal integers prefixed with {@code 0x} or {@code 0X}.
 *   <li>Octal integers prefixed with {@code 0}.
 *   <li>Array elements separated by {@code ;}.
 *   <li>Unnecessary array separators. These are interpreted as if null was the
 *       omitted value.
 *   <li>Key-value pairs separated by {@code =} or {@code =>}.
 *   <li>Key-value pairs separated by {@code ;}.
 * </ul>
 *
 * <p>Each tokener may be used to parse a single JSON string. Instances of this
 * class are not thread safe. Although this class is nonfinal, it was not
 * designed for inheritance and should not be subclassed. In particular,
 * self-use by overrideable methods is not specified. See <i>Effective Java</i>
 * Item 17, "Design and Document or inheritance or else prohibit it" for further
 * information.
 */

class JSONTokener
    : public Object
    , public IJSONTokener
{
public:
    CAR_INTERFACE_DECL()

    JSONTokener();

    ~JSONTokener();

    /**
     * @param in JSON encoded string. Null is not permitted and will yield a
     *     tokener that throws {@code NullPointerExceptions} when methods are
     *     called.
     */
    CARAPI constructor(
        /* [in] */ const String& in);

    /**
     * Returns the next value from the input.
     *
     * @return a {@link JSONObject}, {@link JSONArray}, String, Boolean,
     *     Integer, Long, Double or {@link JSONObject#NULL}.
     * @throws JSONException if the input is malformed.
     */
    CARAPI NextValue(
        /* [out] */ IInterface** obj);

    /**
     * Returns the string up to but not including {@code quote}, unescaping any
     * character escape sequences encountered along the way. The opening quote
     * should have already been read. This consumes the closing quote, but does
     * not include it in the returned string.
     *
     * @param quote either ' or ".
     * @throws NumberFormatException if any unicode escape sequences are
     *     malformed.
     */
    CARAPI NextString(
        /* [in] */ Char32 quote,
        /* [out] */ String* result);

    /**
     * Returns an exception containing the given message plus the current
     * position and the entire input string.
     */
    CARAPI SyntaxError(
        /* [in] */ const String& message);

    /**
     * Returns the current position and the entire input string.
     */
    // @Override
    CARAPI ToString(
        /* [out] */ String* str);

    /*
     * Legacy APIs.
     *
     * None of the methods below are on the critical path of parsing JSON
     * documents. They exist only because they were exposed by the original
     * implementation and may be used by some clients.
     */

    /**
     * Returns true until the input has been exhausted.
     */
    CARAPI More(
        /* [out] */ Boolean* result);

    /**
     * Returns the next available character, or the null character '\0' if all
     * input has been exhausted. The return value of this method is ambiguous
     * for JSON strings that contain the character '\0'.
     */
    CARAPI Next(
        /* [out] */ Char32* ca);

    /**
     * Returns the next available character if it equals {@code c}. Otherwise an
     * exception is thrown.
     */
    CARAPI Next(
        /* [in] */ Char32 c,
        /* [out] */ Char32* ca);

    /**
     * Returns the next character that is not whitespace and does not belong to
     * a comment. If the input is exhausted before such a character can be
     * found, the null character '\0' is returned. The return value of this
     * method is ambiguous for JSON strings that contain the character '\0'.
     */
    CARAPI NextClean(
        /* [out] */ Char32* ca);

    /**
     * Returns the next {@code length} characters of the input.
     *
     * <p>The returned string shares its backing character array with this
     * tokener's input string. If a reference to the returned string may be held
     * indefinitely, you should use {@code new String(result)} to copy it first
     * to avoid memory leaks.
     *
     * @throws JSONException if the remaining input is not long enough to
     *     satisfy this request.
     */
    CARAPI Next(
        /* [in] */ Int32 length,
        /* [out] */ String* str);

    /**
     * Returns the {@link String#trim trimmed} string holding the characters up
     * to but not including the first of:
     * <ul>
     *   <li>any character in {@code excluded}
     *   <li>a newline character '\n'
     *   <li>a carriage return '\r'
     * </ul>
     *
     * <p>The returned string shares its backing character array with this
     * tokener's input string. If a reference to the returned string may be held
     * indefinitely, you should use {@code new String(result)} to copy it first
     * to avoid memory leaks.
     *
     * @return a possibly-empty string
     */
    CARAPI NextTo(
        /* [in] */ const String& excluded,
        /* [out] */ String* str);

    /**
     * Equivalent to {@code nextTo(String.valueOf(excluded))}.
     */
    CARAPI NextTo(
        /* [in] */ Char32 excluded,
        /* [out] */ String* str);

    /**
     * Advances past all input up to and including the next occurrence of
     * {@code thru}. If the remaining input doesn't contain {@code thru}, the
     * input is exhausted.
     */
    CARAPI SkipPast(
        /* [in] */ const String& thru);

    /**
     * Advances past all input up to but not including the next occurrence of
     * {@code to}. If the remaining input doesn't contain {@code to}, the input
     * is unchanged.
     */
    CARAPI SkipTo(
        /* [in] */ Char32 to,
        /* [out] */ Char32* ca);

    /**
     * Unreads the most recent character of input. If no input characters have
     * been read, the input is unchanged.
     */
    CARAPI Back();

    /**
     * Returns the integer [0..15] value for the given hex character, or -1
     * for non-hex input.
     *
     * @param hex a character in the ranges [0-9], [A-F] or [a-f]. Any other
     *     character will yield a -1 result.
     */
    static CARAPI_(Int32) Dehexchar(
        /* [in] */ Char32 hex);

private:
    CARAPI NextCleanInternal(
        /* [out] */ Int32* result);

    /**
     * Advances the position until after the next newline character. If the line
     * is terminated by "\r\n", the '\n' must be consumed as whitespace by the
     * caller.
     */
    CARAPI_(void) SkipToEndOfLine();

    /**
     * Unescapes the character identified by the character or characters that
     * immediately follow a backslash. The backslash '\' should have already
     * been read. This supports both unicode escapes "u000A" and two-character
     * escapes "\n".
     *
     * @throws NumberFormatException if any unicode escape sequences are
     *     malformed.
     */
    CARAPI ReadEscapeCharacter(
        /* [out] */ Char32* c);

    /**
     * Reads a null, boolean, numeric or unquoted string literal value. Numeric
     * values will be returned as an Integer, Long, or Double, in that order of
     * preference.
     */
    CARAPI ReadLiteral(
        /* [out] */ IInterface** obj);

    /**
     * Returns the string up to but not including any of the given characters or
     * a newline character. This does not consume the excluded character.
     */
    CARAPI_(String) NextToInternal(
        /* [in] */ const String& excluded);

    /**
     * Reads a sequence of key/value pairs and the trailing closing brace '}' of
     * an object. The opening brace '{' should have already been read.
     */
    CARAPI ReadObject(
        /* [out] */ IJSONObject** obj);

    /**
     * Reads a sequence of values and the trailing closing brace ']' of an
     * array. The opening brace '[' should have already been read. Note that
     * "[]" yields an empty array, but "[,]" returns a two-element array
     * equivalent to "[null,null]".
     */
    CARAPI ReadArray(
        /* [out] */ IJSONArray** obj);

private:
    /** The input JSON. */
    String mIn;

    /**
     * The index of the next character to be returned by {@link #next}. When
     * the input is exhausted, this equals the input's length.
     */
    Int32 mPos;
};

} //namespace Json
} //namespace Org

#endif //__ORG_JSON_JSONTOKENER_H__
