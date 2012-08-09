/*===========================================================================*\
TwsApiL0.h

Provide a portable and a platform/vendor independant C++ API based on the
POSIX C++ API provided by IB, that is backward compatible with version 9.60
and before.

In the default mode, a seperate thread reads the incoming data from TWS and
calls the EWrapper events automatically. Calling checkMessages() is not
needed and doing so would make no difference. 

Changing this default mode is possible, see constructor of EWrapperL0, and
in that case, checkMessages() MUST be called periodically.

EWrapperL0 extends EWrapper with a connectionOpened() event for reasons of 
symmetry with connectionClosed().  It is called just before eConnect() returns
if the connection was established successfuly.

Each EWrapperL0 event has a default empty implementation for convenience.

Internally, a layer protects the TwsApi from untrapped exceptions thrown by
the user implemented EWrapper methods. When such exception is trapped, this
internal layer calls the new method EWrapper::OnCatch().

EClientL0 extends EClient with clientVersion() that returns the client version
currently in use, this in symmetry with serverVersion().

\*===========================================================================*/
#ifndef _TwsApiL0_h
#define _TwsApiL0_h


// The other includes from shared
#include "EWrapper.h"
#include "EClient.h"
#include "Contract.h"
#include "Execution.h"
#include "OrderState.h"					// includes order.h
#include "ScannerSubscription.h"

#include "TwsSocketClientErrors.h"

// An extra error to indicate a thread couldn't start during eConnect when asked for
static const CodeMsgPair COULD_NOT_START_THREAD( 700, "Couldn't start thread to read incomming messages." );

//----------------------------------------------------------------------------
// EClientL0
//----------------------------------------------------------------------------
class EClientL0: public EClient
{
public:

	// A static member that allocates an instance of this EClientL0
	static	EClientL0*	New( class EWrapperL0* Wrapper );

	// See all members declared in EClient

	//---- Extra Methods -----------------------------------------------------

	// Access to the EWrapper
	virtual EWrapper*	GetEWrapper( void ) = 0;

	// Besides a Server version, there is a client version as well
	virtual int			clientVersion( void ) = 0;

	// Returns true when the Api is connected to TWS.
	virtual bool		IsConnected( void ) = 0;
};

//----------------------------------------------------------------------------
// EWrapperL0
// The posix implementation nevr call winError.
//----------------------------------------------------------------------------
class EWrapperL0: public EWrapper
{
public:
	// Default empty implementations for each method in the callback class
	virtual void tickPrice             ( TickerId tickerId, TickType field, double price, int canAutoExecute ) {} 
	virtual void tickSize              ( TickerId tickerId, TickType field, int size ) {}
	virtual void tickOptionComputation ( TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice) {}
	virtual void tickGeneric           ( TickerId tickerId, TickType tickType, double value ) {}
	virtual void tickString            ( TickerId tickerId, TickType tickType, const std::string& value ) {}
	virtual void tickEFP               ( TickerId tickerId, TickType tickType, double basisPoints, const std::string& formattedBasisPoints, double totalDividends, int holdDays, const std::string& futureExpiry, double dividendImpact, double dividendsToExpiry) {}
	virtual void orderStatus           ( OrderId orderId, const std::string& status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const std::string& whyHeld ) {} 
	virtual void openOrder             ( OrderId orderId, const Contract& contract, const Order& order, const OrderState& orderState ) {} 
	virtual void openOrderEnd          () {}
	virtual void winError              ( const std::string& str, int lastError ) {}
	virtual void connectionClosed      () {}
	virtual void updateAccountValue    ( const std::string& key, const std::string& val, const std::string& currency, const std::string& accountName ) {}
	virtual void updatePortfolio       ( const Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const std::string& accountName ) {}
	virtual void updateAccountTime     ( const std::string& timeStamp ) {}
	virtual void accountDownloadEnd    ( const std::string& accountName ) {}
	virtual void nextValidId           ( OrderId orderId ) {}
	virtual void contractDetails       ( int reqId, const ContractDetails& contractDetails ) {}
	virtual void bondContractDetails   ( int reqId, const ContractDetails& contractDetails ) {}
	virtual void contractDetailsEnd    ( int reqId ) {}
	virtual void execDetails           ( int reqId, const Contract& contract, const Execution& execution ) {}
	virtual void execDetailsEnd        ( int reqId ) {}
	virtual void error                 ( const int id, const int errorCode, const std::string errorString ) {}
	virtual void updateMktDepth        ( TickerId id, int position, int operation, int side, double price, int size ) {}
	virtual void updateMktDepthL2      ( TickerId id, int position, std::string marketMaker, int operation, int side, double price, int size ) {}
	virtual void updateNewsBulletin    ( int msgId, int msgType, const std::string& newsMessage, const std::string& originExch ) {}
	virtual void managedAccounts       ( const std::string& accountsList ) {}
	virtual void receiveFA             ( faDataType pFaDataType, const std::string& cxml ) {}
	virtual void historicalData        ( TickerId reqId, const std::string& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps ) {}
	virtual void scannerParameters     ( const std::string& xml ) {}
	virtual void scannerData           ( int reqId, int rank, const ContractDetails &contractDetails, const std::string &distance, const std::string &benchmark, const std::string &projection, const std::string &legsStr) {}
	virtual void scannerDataEnd        ( int reqId) {}
	virtual void realtimeBar           ( TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count) {}
	virtual void currentTime           ( long time ) {}
	virtual void fundamentalData       ( TickerId reqId, const std::string& data ) {}
	virtual void deltaNeutralValidation( int reqId, const UnderComp& underComp ) {}
	virtual void tickSnapshotEnd       ( int reqId ) {}

	//---- Extra Methods -----------------------------------------------------

	// To keep symmetry with other requests that have an End method:
	// openOrderEnd, accountDownloadEnd, contractDetailsEnd, execDetailsEnd, scannerDataEnd, tickSnapshotEnd
//	virtual void historicalDataEnd     ( TickerId reqId ) {}

	// To keep symmetry with connectionClosed().
	// Is called just before the eConnect returns when connecting succeeded.
	virtual void connectionOpened( void ) {}

	static const char* Finished( void ) { return "finished"; }

	// The flow of historical data ends with a row holding a date field == 'finished'
	static bool IsEndOfHistoricalData( const std::string& Date )
	{
		return 0 == strncmp( (const char*)Date.data(), Finished(), 8 );
	}

	// The internal protection system reports via this method an unhandled exception
	// The Id is the tickerId, the orderId, or the reqId,, or -1 when no id known
	virtual void OnCatch( const char* MethodName, const long Id )
	{
		fprintf( stderr, "*** Catch in EWrapper::%s( Id=%d, ...) \n", MethodName, Id );
	}

	//---- To be Threaded or not to be Threaded-------------------------------
	// This allows the choice between a treaded or non threaded execution.
	// When non threaded, one must call checkMessages periodically.
	// The choice is made during creation only! Default it is set to true.
	// The users derived EWrapper must define a similar constructor in order to
	// set it to non-threaded, or just change the default to false.
	EWrapperL0( bool CalledFromThread = true ): m_CalledFromThread( CalledFromThread ) {}
	bool IsCalledFromThread( void ) { return m_CalledFromThread; }

protected:
	bool	m_CalledFromThread;
};


//----------------------------------------------------------------------------
#endif	// _TwsApiL0_h
