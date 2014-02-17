#ifndef COM_SOWROV_UTIL_NOSUCHELEMENTEXCEPTION_H_
#define COM_SOWROV_UTIL_NOSUCHELEMENTEXCEPTION_H_

#include <string>
#include <exception>

namespace com{
namespace sowrov{
namespace util{

/**
 * <p>
 *  Thrown by the nextElement method of an Enumeration to indicate that there
 *  are no more elements in the enumeration. 
 * </p> 
 * <p><b>Requirements:</b>
 * <ul>
 *   <li>Standard ANSI C++, 32-bit compiler</li>
 * </ul>
 * </p>
 *
 * <p>Copyright &copy; 1997. All rights reserved.</p>
 * 
 * @author  Sowrov
 * @date    09-08-2009
 * @version 1.0.0
 */
class NoSuchElementException : public std::exception{
    //Exception Message
    const std::string msg;

public:
    
    /**
     * <p>
     * Default Constructor, set default message as "com::afrigis::util::NoSuchElementException"
     * </p>          
	 */
    NoSuchElementException() : msg("com::afrigis::util::NoSuchElementException"){}
    
    /**
     * <p>
     * Set Exception message
     * </p>
     *
     * @param str message to set     
     */
    NoSuchElementException(std::string str):
    msg(std::string("com::afrigis::util::NoSuchElementException, ")+str){}
    
    ~NoSuchElementException() throw(){
        //Noting
    }
    
    //@override

    /**
     * <p>
     * Override method from std::exception class
     * </p>
     *
     * @return exception message char pointer
     */
    const char* what() throw(){
        return msg.c_str();
    }
};
}//util
}//sowrov
}//com
#endif //COM_SOWROV_UTIL_NOSUCHELEMENTEXCEPTION_H_
