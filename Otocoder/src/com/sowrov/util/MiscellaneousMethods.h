#ifndef COM_SOWROV_UTIL_MISCELLANEOUSMETHODS_H_
#define COM_SOWROV_UTIL_MISCELLANEOUSMETHODS_H_

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <com/sowrov/util/PrimitiveData.h>
#include <com/sowrov/util/StringUtil.h>
#include "NoSuchElementException.h"

namespace com {
namespace sowrov {
namespace util {

class MiscellaneousMethods {
public:
    /**
     * check whether a given file name exist as a file in the disk
     */
    static bool isFileExist(const std::string& fileName){
        std::ifstream FileL;
        FileL.open(fileName.c_str());
        if(!FileL){
            FileL.close();
            return false;
        }else{
            FileL.close();
            return true;
        }
    }

    /**
     * find a file name which do not exist in the disk
     */
    std::string nextFileName(const std::string& file, const std::string& ext){//get filename and extention
        char nx[10];
        std::string num="";
        int i=0;
        
        while(isFileExist(file+num+ext)){
            sprintf(nx,"%d",i);
            num=nx;
            i++;
        }
        return file+num;
    }

    /**
     * Check all kind of file reading error
     */
    bool isFileReadError(FILE *fp){
        if(ferror(fp)||feof(fp))
            return true;
        return false;
    }

    //bool nextKeyWord(std::istringstream& iss, char *key,char *errorIfNotFound){
        //char in[100];
        //while(true){
            //fscanf(fp,"%s",in);
            //if(isFileReadError(fp)){
                //return false;
            //}
    //if(strcmp(key,in)=='\0')return true;
        //}
    //return false;
    //}

    //string nextLine(FILE *fp, bool isErrorIfNotFound,char *errorIfNotFound){
        //char in[Max_v];
        //bool iseof=false;
        //string s="";
//
     //while(!iseof){
            //fgets(in,Max_v,fp);
            //iseof = isFileReadError(fp);
            //if(isErrorIfNotFound && iseof){
                //errorExit(errorIfNotFound);
            //}
    //s=trimStr(in);
            //if(s!=""){
                //break;
            //}
//}
    //return s;
    //}
};
}
}
}

#endif