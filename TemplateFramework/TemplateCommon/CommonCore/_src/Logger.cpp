#include "../_inc/Logger.h"
#include <direct.h>

using namespace DEBUGLOGCODE;

#define LOGFILENAMEFORMAT "%02d_%02d - %02d_%02d_%02d.log"
#define LOGCREATEDIRFAILMSG "Can't create Log files directory"
#define LOGCREATEDIRFAILCAPTION "Log file creation error"

int getArgsCount( string format )
	{
	return (int) count( format.begin(), format.end(), '%' );
	}

DEBUGLOG::_record DEBUGLOG::record = &DEBUGLOG::initLog;
vector<string> DEBUGLOG::LogRecords = vector<string>( );
CRITICAL_SECTION DEBUGLOG::LoggerCriticalSection = CRITICAL_SECTION();
time_t		DEBUGLOG::timeData = time_t();
tm			DEBUGLOG::timeInfo = tm();
string		DEBUGLOG::logFileName = string();
FILE *		DEBUGLOG::logFile = NULL;

DEBUGLOG::DEBUGLOG() { }

DEBUGLOG::~DEBUGLOG() { }

void 	DEBUGLOG::getLogTime()
	{
	timeData = time( NULL );
	localtime_s( &timeInfo, &timeData );
	};

void DEBUGLOG::logExit( )
	{
	//if (strlen(logFileName.c_str())) recordLogToDisk( &offLog ); //If logfile physically exists, let him write info in itself and close afterwards
	if (strlen(logFileName.c_str())) recordLogToDisk( &initLog ); //If logfile physically exists, let him write info in itself and close afterwards
	}

void DEBUGLOG::initLog( char * _str, HWND _hwnd )
	{
	InitializeCriticalSection( &LoggerCriticalSection ); //инициализациия критической секции
	EnterCriticalSection( &LoggerCriticalSection );

	if ( logFileName == "" )
		{
		getLogTime();

		char buff[ 100 ];
		sprintf_s( buff, LOGFILENAMEFORMAT,
				 timeInfo.tm_mon,
				 timeInfo.tm_mday,
				 timeInfo.tm_hour,
				 timeInfo.tm_min,
				 timeInfo.tm_sec );

		logFileName = "..\\Logs\\";

		if ( !_mkdir( logFileName.c_str() ) )
			if ( !_hwnd ) 
				return;
			else
				MessageBox( _hwnd, LOGCREATEDIRFAILMSG, LOGCREATEDIRFAILCAPTION, MB_OK | MB_ICONWARNING );

		logFileName += buff;
		}

	record = &recordInfo;
	LogRecords.reserve( LOG_CAPACITY );
	recordInfo(_str, _hwnd);
	}

void DEBUGLOG::recordInfo( char * _str, HWND _hwnd )
	{
	EnterCriticalSection( &LoggerCriticalSection );
	LogRecords.push_back( _str );
	if ( LogRecords.size() == LOG_CAPACITY )
		{
		//recordLogToDisk( &initLog );
		recordLogToDisk( &recordInfo );
		}
	LeaveCriticalSection( &LoggerCriticalSection ); //ôóíêöèÿ âûõîäà èç êðèòè÷åñêîé ñåêöèè
	}

void DEBUGLOG::recordLogToDisk( DEBUGLOG::_record _func )
	{
	//Record to file
	fopen_s( &logFile, logFileName.c_str(), "a+" );
	for ( size_t i = 0; i < LogRecords.size(); i++ )
		{
		fputs( LogRecords[ i ].c_str(), logFile );
		fputs( "\n", logFile );
		}
	fclose( logFile );
	LogRecords.clear();
	record = _func;
	LeaveCriticalSection( &LoggerCriticalSection ); //ôóíêöèÿ âûõîäà èç êðèòè÷åñêîé ñåêöèè
	DeleteCriticalSection( &LoggerCriticalSection ); //Удаление(деинициализация) критической секции
	}

void DEBUGLOG::offLog( char * _str, HWND _hwnd ) {}

#pragma endregion