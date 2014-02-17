#include "ThreadLocker.h"

#ifdef _P_THREAD
pthread_mutex_t Global_Mutex_Lock = PTHREAD_MUTEX_INITIALIZER;
#elif defined(_BOOST_THREAD)
boost::mutex Global_Mutex_Lock;
#endif
