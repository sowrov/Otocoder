#ifndef COM_SOWROV_UTIL_STRINGUTIL_H_
#define COM_SOWROV_UTIL_STRINGUTIL_H_

#include "PrimitiveData.h"

#include <string>

namespace com{
namespace sowrov{
namespace util{

/**
 * <p><code>String</code> has some static methods on string that doesn't 
 * available in <code>std::string</code> class</p>
 *
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
class StringUtil{
public:

    /**
     * <p>Make a whole string to uppercase</p>
     *
     * @param str input string
     * @return Uppercase version of the input string
     */
    static std::string toUpperCase(std::string str){
        for(UInt32 i=0; i<str.length(); i++){
            str[i]=toupper(str[i]);
        }
        return str;
    }

    /**
     * <p>Make a whole string to lowercase</p>
     *
     * @param str input string
     * @return Lowercase version of the input string
     */
    static std::string toLowerCase(std::string str){
        for(UInt32 i=0; i<str.length(); i++){
            str[i]=tolower(str[i]);
        }
        return str;
    }
    
    /**
     * <p>
     * checks whether a character is in a string
     * </p>
     *
     * @param str string where to check
     * @param ch the character
     * @return boolean
     */
    static bool isInString(const std::string& str, char ch){
        if(str.find(ch)!=std::string::npos){
            return true;
        }
        return false;
    }

    /**
     * check whether c is any of the given space character
     * default space characters are "\t\n " (tab, newline, whitespace)
     *
     * @param c character to check
     * @param space string of space character
     */
    static bool isSpace(const char c,const std::string space="\t\n "){
        
        for (int i=0;space[i]!='\0';i++) {
            if (c==space[i]) {
                return true;
            }
        }
        if(c==10 || c== 13 || c<=0){
            return true;
        }
        return false;
    }

    /**
     * remove all left and right side white spaces
     * complexity O(n)
     *
     * @param str string to trim
     * @return trimmed string
     */
    static std::string trimStr(std::string str){
        int s,e,len;
        len=str.length();
        s=0;e=len-1;
        while (s<len && isSpace(str[s])) {
            s++;
        }
        while (e>-1 && isSpace(str[e])) {
            e--;
        }
        if (s>e) {
            return "";
        }
        else {
            return str.substr(s,e-s+1);
        }
    }
};

}//util
}//sowrov
}//com
#endif
