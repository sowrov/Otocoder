#ifndef COM_SOWROV_UTIL_STRINGTOKENIZER_H_
#define COM_SOWROV_UTIL_STRINGTOKENIZER_H_

#include <string>
#include <com/sowrov/util/PrimitiveData.h>
#include <com/sowrov/util/StringUtil.h>
#include "NoSuchElementException.h"

namespace com {
namespace sowrov {
namespace util {

/**
 * <p>A java type StringTokenizer implementation</p>
 *
 * <p>
 * The string tokenizer class allows an application to break a string into
 * tokens. The <code>StringTokenizer</code> methods do not distinguish among
 * identifiers, numbers, and quoted strings, nor do they recognize and skip
 * comments.
 * </p>
 *
 * <p>The set of delimiters (the characters that separate tokens) may be
 * specified either at creation time or on a per-token basis.
 * </p>
 * <p>
 *  An instance of <code>StringTokenizer</code> behaves in one of two ways,
 *  depending on whether it was created with the <code>returnDelims</code> flag
 *  having the value <code>true</code> or <code>false</code>:
 * <ul>
 *   <li>
 *      If the flag is false, delimiter characters serve to separate tokens. A
 *      token is a maximal sequence of consecutive characters that are not
 *      delimiters.</li>
 *   <li>
 *      If the flag is true, delimiter characters are themselves considered to
 *      be tokens. A token is thus either one delimiter character, or a maximal
 *      sequence of consecutive characters that are not delimiters.</li>
 * </ul>
 * <p>
 * A <code>StringTokenizer</code> object internally maintains a current position
 * within the string to be tokenized. Some operations advance this current
 * position past the characters processed.
 * </p>
 * A token is returned by taking a substring of the string that was used to
 * create the <code>StringTokenizer</code> object.
 * </p>
 * <p><b>Requirements:</b>
 * <ul>
 *   <li>Standard ANSI C++, 32-bit compiler</li>
 * </ul>
 * </p>
 *
 * <p>Copyright &copy; 1997, Inc. All rights reserved.</p>
 *
 * @author  Sowrov
 * @date    09-06-2009
 * @version 1.0.0
 */
class StringTokenizer {
private:
    std::string str;
    std::string currentDelim;
    bool returnDelims;
    int tokenCount;
public:

    /**
     * <p>
     * Constructs an empty tokenizer
     * </p>
     */
    StringTokenizer() {
        str = currentDelim = "";
        tokenCount = -1;
    }

    /**
     * <p>
     * Constructs a string tokenizer for the specified string. The tokenizer
     * uses the default delimiter set, which is <code>" \t\n\r"</code>: the
     * space character, the tab character, the newline character, and the
     * carriage-return character. Delimiter characters themselves will not be
     * treated as tokens.
     * </p>
     *
     * @param str a string to parse
     */
    StringTokenizer(const std::string& str) {
        this->str = str;
        this->currentDelim = " \n\r\t";
        this->returnDelims = false;
        this->tokenCount = -1;
    }

    /**
     * <p>
     * @overloaded
     * Constructs a string tokenizer for the specified string. The tokenizer
     * uses the default delimiter set, which is <code>" \t\n\r"</code>: the
     * space character, the tab character, the newline character, and the
     * carriage-return character. Delimiter characters themselves will not be
     * treated as tokens.
     * </p>
     *
     * @param str a string to parse
     */
    StringTokenizer(const char* str) {
        this->str = str;
        this->currentDelim = " \n\r\t";
        this->returnDelims = false;
        this->tokenCount = -1;
    }


    /**
     * <p>
     * Constructs a string tokenizer for the specified string. The characters in
     * the <code>delim</code> argument are the delimiters for separating tokens.
     * Delimiter characters themselves will not be treated as tokens.
     * </p>
     *
     * @param str String to Parse
     * @param delim the delimiters
     */
    StringTokenizer(const std::string& str,const std::string& delim) {
        this->str = str;
        this->currentDelim = delim;
        this->returnDelims = false;
        this->tokenCount = -1;
    }

    /**
     * <p>
     * @overloaded
     * Constructs a string tokenizer for the specified string. The characters in
     * the <code>delim</code> argument are the delimiters for separating tokens.
     * Delimiter characters themselves will not be treated as tokens.
     * </p>
     *
     * @param str String to Parse
     * @param delim the delimiters
     */
    StringTokenizer(const char* str,const char* delim) {
        this->str = str;
        this->currentDelim = delim;
        this->returnDelims = false;
        this->tokenCount = -1;
    }

    /**
     * <p>
     * Constructs a string tokenizer for the specified string. All characters in
     * the <code>delim</code> argument are the delimiters for separating tokens.
     * </p>
     * <p>
     * If the <code>returnDelims</code> flag is <code>true</code>, then the
     * delimiter characters are also returned as tokens. Each delimiter is
     * returned as a string of length one. If the flag is <code>false</code>,
     * the delimiter characters are skipped and only serve as separators between
     * tokens.
     * </p>
     *
     * @param str           a string to parse
     * @param delim         the delimiters
     * @param returnDelims  flag indicating whether to return the delimiters as tokens.
     */
    StringTokenizer(const std::string& str,const std::string& delim, bool returnDelims) {
        this->str = str;
        this->currentDelim = delim;
        this->returnDelims = returnDelims;
        this->tokenCount = -1;
    }

    /**
     * <p>
     * @overloaded
     * Constructs a string tokenizer for the specified string. All characters in
     * the <code>delim</code> argument are the delimiters for separating tokens.
     * </p>
     * <p>
     * If the <code>returnDelims</code> flag is <code>true</code>, then the
     * delimiter characters are also returned as tokens. Each delimiter is
     * returned as a string of length one. If the flag is <code>false</code>,
     * the delimiter characters are skipped and only serve as separators between
     * tokens.
     * </p>
     *
     * @param str           a string to parse
     * @param delim         the delimiters
     * @param returnDelims  flag indicating whether to return the delimiters as tokens.
     */
    StringTokenizer(const char* str,const char* delim, bool returnDelims) {
        this->str = str;
        this->currentDelim = delim;
        this->returnDelims = returnDelims;
        this->tokenCount = -1;
    }

    /**
     * <p>
     * Calculates the number of times that this tokenizer's <code>nextToken</code> method can
     * be called before it generates an exception. The current position is not
     * advanced.
     * </p>
     *
     * @return number of token remain in the string using the current delimiter set
     */
    int countTokens() {
        if(this->tokenCount>-1){
            return this->tokenCount;
        }
        this->tokenCount = 0;
        //flag to check whether the previous character was a delimiter character
        bool lastCharDelim = true;

        UInt32 length = this->str.length();

        for (UInt32 i = 0; i <= length; i++) {
            if (i == length ||
                    (i < length && StringUtil::isInString(this->currentDelim, this->str.at(i)))) {

                if (i == length) {
                    //for end of the string, if last character was not a Delimiter character
                    if(!lastCharDelim){
                        this->tokenCount++;
                    }                    
                } else {
                    if (this->returnDelims) {
                        this->tokenCount++;
                    }
                    if (!lastCharDelim) {
                        this->tokenCount++;
                    }
                    lastCharDelim = true;
                }
            } else {
                lastCharDelim = false;
            }
        }
        return this->tokenCount;
    }

    /**
     * <p>
     * Tests if there are more tokens available from this tokenizer's string. If
     * this method returns <code>true</code>, then a subsequent call to <code>nextToken</code> with no
     * argument will successfully return a token.
     * </p>
     *
     * @return
     */
    bool hasMoreTokens() {
        //if delimiters are not token then we have to skip initial delimiters
        if(this->tokenCount>-1){
            return this->tokenCount>0;
        }

        if (!this->returnDelims) {
            for (UInt32 i = 0; i<this->str.length(); i++) {

                if (!StringUtil::isInString(this->currentDelim, this->str.at(i))) {
                        return true;
                    }
            }
            return false;
        } else {            
            return this->str.length() > 0;
        }
    }

    /**
     * <p>
     * Returns the next token from this string tokenizer.
     * </p>
     *
     * @return The next token from the string tokenizer
     * @throws NoSuchElementException if there are no more tokens in this
     *		   tokenizer's string.
     */
    std::string nextToken() {
        std::string str;

        if (this->currentDelim == "") {
            //in case of blank string NoSuchElementException will be thrown
            if (this->str == "") {
                throw NoSuchElementException();
            }

            //if delimiters are empty then we return the whole sting
            str = this->str;
            this->str = "";
            return str;
        }

        //if delimiters are not token then we have to remove initial delimiters
        if (!this->returnDelims) {
            UInt32 i = 0;
            for (; i<this->str.length(); i++) {

                if (!StringUtil::isInString(this->currentDelim, this->str[i])) {                        
                        break;
                    }
            }
            this->str.erase(0, i);
        }
        
        //now if the string is blank then throw exception
        if (this->str == "") {
            throw NoSuchElementException();
        }
        UInt32 i = 0;
        bool flag = false;
        for (; i<this->str.length(); i++) {
            if (StringUtil::isInString(this->currentDelim, this->str[i])){
                flag = true;
                break;
            }                            
        }
        if(i==0 && flag && this->returnDelims){
            i++;
        }
        str = this->str.substr(0, i);
        this->str.erase(0, i);
        
        //if token count was already done then reduce one
        if(this->tokenCount>0){
            this->tokenCount--;
        }

        return str;
    }
    
    /**
     * <p>
     * Returns the next token from this string tokenizer.
     * </p>
     *
     * @return The next token from the string tokenizer
     * @throws NoSuchElementException if there are no more tokens in this
     *		   tokenizer's string.
     */
    std::string nextToken(std::string& delim) {
        this->currentDelim = delim;
        this->tokenCount = -1;
        return this->nextToken();
    }
    
    /**
     * <p>
     * @overloaded
     * Returns the next token from this string tokenizer.
     * </p>
     *
     * @return The next token from the string tokenizer
     * @throws NoSuchElementException if there are no more tokens in this
     *		   tokenizer's string.
     */
    std::string nextToken(const char* delim) {
        this->currentDelim = delim;
        this->tokenCount = -1;
        return this->nextToken();
    }
};
}//util
}//sowrov
}//com


#endif //COM_SOWROV_UTIL_STRINGTOKENIZER_H_
