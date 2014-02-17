#include "Html.h"

namespace com {
namespace sowrov {
namespace util {
namespace logsystem {

	std::string Html::getIntroFormat() {
		std::string intro = "<html><head><title>";
			intro += Calendar::getCalendar ().getFormattedDate ("D d F Y H:i:s");
			intro += "</title><style type=\"text/css\">\
<!--\
table, td\
{\
    border-color: #000;\
}\
\
table\
{\
	margin:auto;\
	table-layout: fixed;\
    border-width: 1px;\
    border-spacing: 0;\
    border-collapse: collapse;\
	width: 90%;\
}\
\
td\
{\
    margin: 0;\
    padding: 4px;\
    border-width: 1px 1px 0 0;\
}\
a:link, a:visited, a:hover {\
	color:#FF3333;\
}\
\
#headRow {\
	background-color:#000033;\
	color:#FFFFCC;\
	font-size:large;\
}\
\
.fatalError{\
	background-color:#660000;\
	color:#009900;\
	word-wrap:break-word;\
}\
\
.error{\
	background-color:#003366;\
	color:#9999CC;\
	word-wrap:break-word;\
}\
\
.warning{\
	background-color:#663366;\
	color:#FFCCCC;\
	word-wrap:break-word;\
}\
\
.info{\
	background-color:#FFFFCC;\
	color:#000000;\
	word-wrap:break-word;\
}\
\
.debug{\
	background-color:#CCFFCC;\
	color:#000000;\
	word-wrap:break-word;\
}\
\
.endRow {\
	background-color:#CCCCFF;\
}\
\
.timestamp{\
	font-size: 0.7em;\
	text-align:right;\
	font-style:normal;\
}\
-->\
</style>\
\
<script type=\"text/javascript\">\
\
function OnOffSwitch(className){\
	var allClassName = ['fatalError', 'error', 'warning', 'info', 'debug'];\
	for (var it=0; it<allClassName.length; it++) {\
		if (allClassName[it]==className || className=='') {\
			OnOff(allClassName[it], true);\
		}\
		else {\
			OnOff(allClassName[it], false);\
		}\
	}\
}\
\
function OnOff (className, boolVal) {\
	var rows = document.getElementsByClassName(className);\
	for(var i=0; i<rows.length; i++){\
		if (boolVal == true) {\
			rows[i].style.display = '';\
		}\
		else {\
			rows[i].style.display = 'none';\
		}\
	}\
}\
</script></head><body><center><h1>Chronicle Logger</h1><sub>Compile time: ";
				intro += __DATE__;
				intro += ", ";
				intro += __TIME__;
				intro += "</sub></center>";
				intro += "<div style='margin:auto; width: 90%'>\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"\")'>Show All</a>|\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"fatalError\")'>Show Fatal Only</a>|\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"error\")'>Show Error Only</a>|\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"warning\")'>Show Warning Only</a>|\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"info\")'>Show Information Only</a>|\
<a href='javascript:void(0)' onclick='OnOffSwitch(\"debug\")'>Show Debug Only</a>\
</div>\
<table border='3'; cellpadding='5px'>\
  <tr id='headRow'>\
    <th width='50%'>Filepath</th>\
    <th width='30%' >Function():LineNo</th>\
    <th width='20%' >Timestamp</th>\
  </tr>";
		return intro;
	}

	std::string Html::getFinalFormat() {
		Calendar::getCalendar ().updateCalender ();
		std::string text ="<tr class='endRow'>\
		<td colspan='3'>Application Terminated at: ";
		text += Calendar::getCalendar ().getFormattedDate ("d F Y H:i:s");
		text += "</td> </tr> </table> </body> </html>";
		return text;
	}

	std::string Html::getFormat(std::string className, std::string message, int lineNo, std::string functionName, std::string fileName) {

		char lineStr [10];
		sprintf(lineStr, "%d", lineNo);

		std::string text = "<tr class='"+className+"'> \
						<td width='50%' > <a href='"+fileName+"'>"+fileName+"</a></td>\
						<td width='30%'>"+functionName+"(): "+lineStr+"</td>\
						<td width='20%' class='timestamp'>"+
						Calendar::getCalendar ().getFormattedDate ("d F Y H:i:s")+
						"</td>\
						</tr>\
						<tr class='"+className+"'>\
						<td colspan='3' width='100%'>"+message+"</td>\
						</tr>";
		return text;
	}
	std::string Html::getFatalFormat(std::string str, int lineNo, std::string functionName, std::string fileName ) {
		Calendar::getCalendar ().updateCalender ();
		return this->getFormat ("fatalError", str, lineNo, functionName, fileName);
	}

	std::string Html::getCriticalFormat(std::string str, int lineNo, std::string functionName, std::string fileName ) {
		Calendar::getCalendar ().updateCalender ();
		return this->getFormat ("error", str, lineNo, functionName, fileName);;
	}

	std::string Html::getWarningFormat(std::string str, int lineNo, std::string functionName, std::string fileName ) {
		Calendar::getCalendar ().updateCalender ();
		return this->getFormat ("warning", str, lineNo, functionName, fileName);
	}

	std::string Html::getInfoFormat(std::string str, int lineNo, std::string functionName, std::string fileName ) {
		Calendar::getCalendar ().updateCalender ();
		return this->getFormat ("info", str, lineNo, functionName, fileName);
	}

	std::string Html::getDebugFormat(std::string str, int lineNo, std::string functionName, std::string fileName ) {
		Calendar::getCalendar ().updateCalender ();
		return this->getFormat ("debug", str, lineNo, functionName, fileName);
	}

}
}
}
}

