#include "stdafx.h"
#include <direct.h>
#include "LOG.h"

LOG::LOG(void)
	{
	time_t t = time(NULL);
	struct tm *t_m = localtime(&t);

	char buff[100];
	sprintf(buff, "%02d_%02d_%02d_%02d_%02d.log", t_m->tm_mon, t_m->tm_mday, t_m->tm_hour, t_m->tm_min, t_m->tm_sec);

	logName = "..\\Logs\\";

	if ( !_mkdir(logName.c_str()) )
		AfxMessageBox("Can't create Log files directory", MB_OK | MB_ICONWARNING);

	logName += buff;

	logFile.open(logName.c_str(), ios::out);
	}
LOG::~LOG(void)
	{
	logFile.close();
	}
void LOG::RecordLine(string _logMessage, bool _isConsoleRecord)
	{
	time_t t = time(NULL);
	struct tm *t_m = localtime(&t);
	LOG_locker.lock();
	logFile << t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << " " << _logMessage << "\n";
	if (_isConsoleRecord) logBuffer.push_back(_logMessage);
	LOG_locker.unlock();
	};
string LOG::ReadLine()
	{
	string Temp = "";
	LOG_locker.lock();
	if (logBuffer.size())
		{
		Temp = logBuffer.front();
		logBuffer.pop_front();
		};
	LOG_locker.unlock();
	return Temp;
	};