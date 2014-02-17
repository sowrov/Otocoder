#ifndef COM_SOWROV_UTIL_THREAD_THREADLOCKER_H_
#define COM_SOWROV_UTIL_THREAD_THREADLOCKER_H_
//If you use the pthread uncomment the following block of code
/* //PThreadBlock
#define _P_THREAD
#include <pthread/pthread.h>

extern pthread_mutex_t Global_Mutex_Lock;

#define _CLThreadLock() pthread_mutex_lock(&Global_Mutex_Lock)
#define _CLThreadUnLock() pthread_mutex_unlock(&Global_Mutex_Lock)

//*/ //PThreadBlock

//For Boost Thread uncomment the following block of code

/* //BoostThreadBlock
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
extern boost::mutex Global_Mutex_Lock;
#define _CLThreadLock() boost::mutex::scoped_lock lock(Global_Mutex_Lock)
#define _CLThreadUnLock() 
//*/ 


//define this two macros according to the threaded system you are using
//for your application

#endif //COM_SOWROV_UTIL_THREAD_THREADLOCKER_H_
