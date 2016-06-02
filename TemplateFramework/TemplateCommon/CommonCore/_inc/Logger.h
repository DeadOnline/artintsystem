#ifndef Logger_h
#define Logger_h

#include <iostream>
#include <mutex>
#include <vector>
#include <Windows.h>

using namespace std;

namespace DEBUGLOGCODE
	{
	class DEBUGLOG;

	#define LOG(HWND, ...) { char buff[1024]; sprintf_s(buff, __VA_ARGS__); DEBUGLOG::record(buff, HWND); }
	#define LOG_STOP() { DEBUGLOG::logExit( ); } //Needs to be hidden
	#define LOG_CAPACITY 8196

	class DEBUGLOG
		{
	public:
		typedef void( *_record )( char * _str, HWND _hwnd );
		static _record record;
		static void	logExit();

	private:
		DEBUGLOG();
		~DEBUGLOG();
		DEBUGLOG( const DEBUGLOG& );
		DEBUGLOG& operator=( DEBUGLOG& );

		static void	initLog( char * _str, HWND _hwnd );
		static void	recordInfo( char * _str, HWND _hwnd );
		static void	recordLogToDisk( DEBUGLOG::_record _func );
		static void	offLog( char * _str, HWND _hwnd );
		
		static void	getLogTime();

		static CRITICAL_SECTION LoggerCriticalSection; //объявление критической секции
		
		static vector<string> LogRecords;
		
		static time_t	timeData;
		static tm		timeInfo;

		static string	logFileName;
		static FILE	 *	logFile;
		};
	};

#endif