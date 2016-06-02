#pragma once
#include "ALL.h"

static mutex LOG_locker;           // mutex for critical section

class LOG
	{
public:
	static LOG& Instance()
		{
		static LOG theSingleInstance;
		return theSingleInstance;
		}

private:

	ofstream		logFile;
	string			logName;
	list<string>	logBuffer;

private:
	LOG(void);
	~LOG(void);

public: 

	void RecordLine(string _logMessage, bool _isConsoleRecord = false);

	string ReadLine();

	};

