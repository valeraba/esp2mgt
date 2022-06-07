/*
Copyright � 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#ifndef _MgtClient_H_
#define _MgtClient_H_

#include "Types.h"

#define CRYPTO_ON
#define ATTACHED_MODE
#define WEBSOCKET

#ifdef ESP8266
#define RX_BUF_SIZE	4096
#define TX_BUF_SIZE	4096
#elif ARDUINO
#define RX_BUF_SIZE	128
#define TX_BUF_SIZE	128
#else
#define RX_BUF_SIZE	4096
#define TX_BUF_SIZE	4096
#endif


#ifdef _WIN32 // Windows
	#define MGT_CONSTANT 8616
#elif ESP8266
	#define MGT_CONSTANT 8616
#elif __ICCAVR__ // IAR AVR
	#define MGT_CONSTANT 628
#elif ARDUINO
	#define MGT_CONSTANT 628
#else // FreeBSD	
	#define MGT_CONSTANT 8600
#endif

#ifndef COUNT_SIGNALS
	#define COUNT_SIGNALS 1 
#endif

#ifndef COUNT_STORE
	#define COUNT_STORE 1
#endif


//The security level of the signal that restrict acts ordinary consumers (who are not supervisors)
#define SEC_LEV_FULL_ACCESS			0x00	// listening, reading and writing
#define SEC_LEV_READ				0x01	// listening and reading
#define SEC_LEV_LISTEN				0x02	// only listening
#define SEC_LEV_NO_ACCESS			0x03	// signal not available

// Access to the signal
#define SIG_ACCESS_READ				0x04	// read on request
#define SIG_ACCESS_WRITE			0x08	// write on request
#define SIG_ACCESS_ASYNC_WRITE		0x10	// asynchronous writes without confirmation
#define SIG_ACCESS_SIGNATURE		0x20	// customer ID (signature)
#define SIG_ACCESS_STREAM_READ		0x44	// stream read
#define SIG_ACCESS_STREAM_WRITE		0x88	// stream write

// Unit for interval
#define STORE_UNIT_MS				0x0000	// milliseconds
#define STORE_UNIT_SEC				0x0400	// seconds
#define STORE_UNIT_MIN				0x0800	// minutes
#define STORE_UNIT_HAUR				0x0c00	// hours
#define STORE_UNIT_DAY				0x1000	// days

// Mode of recording in storage
#define STORE_MODE_OFF				0x0000	// off
#define STORE_MODE_CHANGE			0x2000	// when changing
#define STORE_MODE_SAMPLING			0x4000	// sampling
#define STORE_MODE_AVERAGE			0x6000	// weighted average
#define STORE_MODE_RMS				0x8000	// weighted RMS


enum ErrorCode {
	erOk = 0, // the operation was successful
	erReadFailed = 2, // read failed
	erWriteFailed = 3, // write failed
	erBusySignal = 4, // busy signal
};

enum SignalType {
	tpBool = 0,
	tpInt8 = 1,
	tpUInt8 = 2,
	tpInt16 = 3,
	tpUInt16 = 4,
	tpInt32 = 5,
	tpUInt32 = 6,
	tpFloat = 7,
	tpDouble = 8,
	tpString = 9,
	tpBlob = 10,
	tpFile = 11,
	tpEvent = 12
};

enum WayTransfer {
	wUserOnly = 0,
	wUserPriority = 1,
	wAnyone = 2,
	wCloudOnly = 3
};

struct ChunkedTransfer {
	void* m_obj;
	//-----callbacks is called in the function "readAns" if aError = erOk or "send" (class MgtSource)------
	__int16 (*getExpectedSize) (void* aObj); // if error return -1
	__int16 (*read)(void* aObj, __uint8* aBuf, __uint16 aSize, bool* aEnd); // if error return -1
	void (*abort)(void* aObj);
};

struct SignalValue {
	__int64 m_time : 56;
	__int64 m_reg  : 8;
	union {
		bool		m_bool;
		__int8		m_int8;
		__uint8		m_uint8;
		__int16		m_int16;
		__uint16	m_uint16;
		__int32		m_int32;
		__uint32	m_uint32;
		float		m_float;
		double		m_double;
		char*		m_string; // null-terminated string
		__uint8*	m_blob; // size of data is stored in the first two bytes
		struct ChunkedTransfer* m_chunk; // m_chunkRead = 1 or m_chunkWrite = 1
	} u;
};

struct Event {
	__int64	m_time : 56;
};


enum OpCode {
	opRead = 0, // the read request
	opWrite = 1, // the write request
	opWriteAsync = 2, // asynchronous writes without confirmation
	opRecv = 3,
	opAttach = 4,
	opDetach = 5
};

struct StoreSetting {
	__uint16	m_interval : 10; // interval
	__uint16	m_unit     : 3; // unit for interval (0 - ms, 1 - sec, 2 - min, 3 - haur, 4 - day)
	__uint16	m_mode   : 3; // 0 - off, 1 - when changing, 2 - sampling, 3 - weighted average, 4 - weighted RMS
};

/*struct StoreField {
	__uint64	m_data1;
	__uint32	m_data2;
	struct StoreSetting m_setting;
};*/


struct Signal {
	struct SignalValue m_value; // value of the signal
	const char* m_name; // name in UTF8 format
	struct {
		__uint8 m_type : 5; // signal type
		__uint8 m_isAttach : 1; // there is an attached consumer
		__uint8 m_reserved : 2; // not to change
	} st;

	__uint8 m_access; // signal access
};

bool signal_updateInt(struct Signal* aSignal, __int64 aValue, TimeStamp aTime); 
bool signal_updateDouble(struct Signal* aSignal, double aValue, TimeStamp aTime);
bool signal_updatePtr(struct Signal* aSignal, const void* aPtr, TimeStamp aTime);
bool signal_updateTime(struct Signal* aSignal, TimeStamp aTime);

struct DeviceConfig {
	__uint32 m_deviceId; // ID device
	const char* m_login; // user login
	const char* m_password; // user password
	void (*m_handler)(enum OpCode aOpCode, struct Signal* aSignal, struct SignalValue* aWriteValue);
	DebugLogFunc m_debugLog; // the event log
//	struct StoreField* m_storeFields;
	struct StoreSetting* m_storeFields;
	int m_regSize;
};

struct PortableSocket {
	bool (*open)(const char* aHost, __uint16 aPort);
	int (*receive)(void* aBuf, __uint16 aSize);
	bool (*send)(const void* aBuf, __uint16 aSize);
	void (*shutdown)(void);
	void (*close)(void);
	bool (*isTxBusy)(void); // if transmiter busy
	bool (*isConnected)(void);
};

struct MgtClient {
	__uint8 m_reserv[MGT_CONSTANT];
	struct Signal m_signals[COUNT_SIGNALS + 1];
//	struct StoreField m_storeFields[COUNT_STORE];
	struct StoreSetting m_storeFields[COUNT_STORE];
};

enum MgtState {
	stOff = 0, // turned off
	stWait = 1, // waiting for connection
	stEstablished = 2, // connection is established
	stConnected = 3, // connected
	stTxBusy = 4, // transmiter busy
	stDisconnect = 5 // disconnect
};

bool mgt_init(struct MgtClient* aClient, struct DeviceConfig* aDeviceConfig, struct PortableSocket* aSocket);
struct Signal* mgt_createSignal(struct MgtClient* aClient, const char* aName, enum SignalType aType, __uint8 aAccess, __uint16 aStoreSetting, struct ChunkedTransfer* aChunk);
#ifdef ATTACHED_MODE
struct Signal* mgt_attachSignal(struct MgtClient* aClient, const char* aName);
void mgt_detachAll(struct MgtClient* aClient);
#endif
void mgt_start(struct MgtClient* aClient, const char* aHostname, enum WayTransfer aWay); // aHostname: "mgt24.ru" or "127.0.0.1"
void mgt_stop(struct MgtClient* aClient, __uint16 aInterval); // go to offline mode for a specified interval (in seconds)
enum MgtState mgt_run(struct MgtClient* aClient); // function turns the client network stack, recommended frequency from 1 to 20 Hz
enum MgtState mgt_getState(struct MgtClient* aClient); // get client state

void mgt_send(struct MgtClient* aClient, struct Signal* aSignal); // send signal value

void mgt_eventSend(struct MgtClient* aClient, struct Event* aEvent, const char* aMarker, TimeStamp aTime, ...); // short form for sending group of signals, and their binding to the event
void mgt_eventBegin(struct MgtClient* aClient, struct Event* aEvent, const char* aMarker, TimeStamp aTime); // start the grouping of signals, attached to the event
void mgt_eventEnd(struct MgtClient* aClient, struct Event* aEvent); // finish the grouping of signals, attached to the event

void mgt_readAns(struct MgtClient* aClient, struct Signal* aSignal, enum ErrorCode aError); // send the result to the request read
void mgt_writeAns(struct MgtClient* aClient, struct Signal* aSignal, enum ErrorCode aError); // send the result to the request write

extern TimeStamp shiftTime; // use where there is no real time clock
TimeStamp getUTCTime(void); // UTC time (ms)
void sleepms(__uint32 aMilliseconds);

#endif //_MgtClient_H_
