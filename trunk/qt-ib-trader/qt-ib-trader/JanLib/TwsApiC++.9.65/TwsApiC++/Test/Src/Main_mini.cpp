//============================================================================
// TwsApi Test
//============================================================================
#include "TwsApiL0.h"

// to use the Sleep function
#ifdef WIN32
	#include <windows.h>		// Sleep(), in miliseconds
#else
	#include <unistd.h>			// usleep(), in microseconds
	#define Sleep( m ) usleep( m*1000 )
#endif

//----------------------------------------------------------------------------
// MyEWrapper
//----------------------------------------------------------------------------
class MyEWrapper: public EWrapperL0
{
	// Handle the errors.
	virtual void winError( const IBString& str, int lastError )
	{
		printf( "WinError: %d = %s\n", lastError, (const char*)str );
	}

	virtual void error( const int id, const int errorCode, const IBString errorString )
	{
		printf( "Error for id=%d: %d = %s\n", id, errorCode, (const char*)errorString );
	}

	// Should store the nextValidId for future calls to EClient
	virtual void nextValidId( OrderId orderId )
	{
		printf( "nextValidId = %d\n", orderId );
	}

	// following events are optional, just for the flow
	virtual void connectionClosed()
	{
		printf( "Connection Closed\n");
	}

	virtual void connectionOpened()
	{
		printf( "Connection Opened\n");
	}
};

//----------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------
int main( void )
{

	MyEWrapper	EW;
	EClientL0*	EC = EClientL0::New( &EW );

	printf( "ClientVersion = %d\n", EC->clientVersion() );

	if( EC->eConnect( "", 7496, 100 ) )
	{
		printf( "ServerVersion = %d\n", EC->serverVersion() );

		Sleep( 5000 );	// Wait 5 seconds to let send TWS some events

		EC->eDisconnect();
	}

	delete EC;

	printf("Press return key to continue\n" ); getc( stdin );
	return 0;
}
