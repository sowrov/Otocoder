#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Otocoder/src/com/sowrov/io/File.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Method.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Problem.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/ProblemInfo.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/TestData.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Variable.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/VariableValue.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/argvparser.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/CppCode.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/JavaCode.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/http/PageDownloader.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/main.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/parser/TcHtmlParser.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Calendar.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/ChronicleLogger.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Console.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/DiskFile.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Html.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/LevelManager.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/PlainText.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/thread/ThreadLocker.o \
	${OBJECTDIR}/Otocoder/src/com/sowrov/util/visualstudio/VSProject2008.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/otocoder.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/otocoder.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/otocoder ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Otocoder/src/com/sowrov/io/File.o: Otocoder/src/com/sowrov/io/File.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/io
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/io/File.o Otocoder/src/com/sowrov/io/File.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Method.o: Otocoder/src/com/sowrov/otocoder/Method.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Method.o Otocoder/src/com/sowrov/otocoder/Method.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Problem.o: Otocoder/src/com/sowrov/otocoder/Problem.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Problem.o Otocoder/src/com/sowrov/otocoder/Problem.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/ProblemInfo.o: Otocoder/src/com/sowrov/otocoder/ProblemInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/ProblemInfo.o Otocoder/src/com/sowrov/otocoder/ProblemInfo.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/TestData.o: Otocoder/src/com/sowrov/otocoder/TestData.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/TestData.o Otocoder/src/com/sowrov/otocoder/TestData.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Variable.o: Otocoder/src/com/sowrov/otocoder/Variable.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/Variable.o Otocoder/src/com/sowrov/otocoder/Variable.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/VariableValue.o: Otocoder/src/com/sowrov/otocoder/VariableValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/VariableValue.o Otocoder/src/com/sowrov/otocoder/VariableValue.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/argvparser.o: Otocoder/src/com/sowrov/otocoder/argvparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/argvparser.o Otocoder/src/com/sowrov/otocoder/argvparser.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/CppCode.o: Otocoder/src/com/sowrov/otocoder/codegen/CppCode.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/CppCode.o Otocoder/src/com/sowrov/otocoder/codegen/CppCode.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/JavaCode.o: Otocoder/src/com/sowrov/otocoder/codegen/JavaCode.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/codegen/JavaCode.o Otocoder/src/com/sowrov/otocoder/codegen/JavaCode.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/http/PageDownloader.o: Otocoder/src/com/sowrov/otocoder/http/PageDownloader.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/http
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/http/PageDownloader.o Otocoder/src/com/sowrov/otocoder/http/PageDownloader.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/main.o: Otocoder/src/com/sowrov/otocoder/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/main.o Otocoder/src/com/sowrov/otocoder/main.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/parser/TcHtmlParser.o: Otocoder/src/com/sowrov/otocoder/parser/TcHtmlParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/parser
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/otocoder/parser/TcHtmlParser.o Otocoder/src/com/sowrov/otocoder/parser/TcHtmlParser.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Calendar.o: Otocoder/src/com/sowrov/util/logsystem/Calendar.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Calendar.o Otocoder/src/com/sowrov/util/logsystem/Calendar.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/ChronicleLogger.o: Otocoder/src/com/sowrov/util/logsystem/ChronicleLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/ChronicleLogger.o Otocoder/src/com/sowrov/util/logsystem/ChronicleLogger.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Console.o: Otocoder/src/com/sowrov/util/logsystem/Console.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Console.o Otocoder/src/com/sowrov/util/logsystem/Console.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/DiskFile.o: Otocoder/src/com/sowrov/util/logsystem/DiskFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/DiskFile.o Otocoder/src/com/sowrov/util/logsystem/DiskFile.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Html.o: Otocoder/src/com/sowrov/util/logsystem/Html.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/Html.o Otocoder/src/com/sowrov/util/logsystem/Html.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/LevelManager.o: Otocoder/src/com/sowrov/util/logsystem/LevelManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/LevelManager.o Otocoder/src/com/sowrov/util/logsystem/LevelManager.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/PlainText.o: Otocoder/src/com/sowrov/util/logsystem/PlainText.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/logsystem/PlainText.o Otocoder/src/com/sowrov/util/logsystem/PlainText.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/thread/ThreadLocker.o: Otocoder/src/com/sowrov/util/thread/ThreadLocker.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/thread
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/thread/ThreadLocker.o Otocoder/src/com/sowrov/util/thread/ThreadLocker.cpp

${OBJECTDIR}/Otocoder/src/com/sowrov/util/visualstudio/VSProject2008.o: Otocoder/src/com/sowrov/util/visualstudio/VSProject2008.cpp 
	${MKDIR} -p ${OBJECTDIR}/Otocoder/src/com/sowrov/util/visualstudio
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Otocoder/src/com/sowrov/util/visualstudio/VSProject2008.o Otocoder/src/com/sowrov/util/visualstudio/VSProject2008.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/otocoder.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
