/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Implementation of the interface for executing XML/JSON requests on the strus bindings
/// \file "webRequestHandler.hpp"
#ifndef _STRUS_WEB_REQUEST_HANDLER_IMPL_HPP_INCLUDED
#define _STRUS_WEB_REQUEST_HANDLER_IMPL_HPP_INCLUDED
#include "strus/webRequestHandlerInterface.hpp"
#include "configurationHandler.hpp"
#include "strus/base/thread.hpp"
#include "strus/base/periodicTimerEvent.hpp"
#include "papuga/requestHandler.h"
#include "papuga/requestLogger.h"
#include "transaction.hpp"
#include <cstddef>
#include <utility>
#include <set>

#define ROOT_CONTEXT_NAME "context"

namespace strus
{
/// \brief Forward declaration
class WebRequestLoggerInterface;
/// \brief Forward declaration
class WebRequestContext;

/// \brief Implementation of the interface for executing XML/JSON requests on the strus bindings
class WebRequestHandler
	:public WebRequestHandlerInterface
{
public:
	WebRequestHandler( 
			WebRequestLoggerInterface* logger_,
			const std::string& html_head_,
			const std::string& config_store_dir_,
			const std::string& configstr_,
			int maxIdleTime_,
			int nofTransactionsPerSeconds);
	virtual ~WebRequestHandler();

	virtual WebRequestContextInterface* createContext(
			const char* accepted_charset,
			const char* accepted_doctype,
			const char* html_base_href,
			WebRequestAnswer& status);

public:/*WebRequestContext*/
	enum MethodParamType {ParamEnd=0,ParamPathString,ParamPathArray,ParamDocumentClass,ParamContent};

	const papuga_RequestHandler* impl()				{return m_impl;}
	const char* html_head() const					{return m_html_head.c_str();}
	int debug_maxdepth() const					{return m_debug_maxdepth;}
	int maxIdleTime() const						{return m_maxIdleTime;}
	bool transferContext(
			const char* contextType,
			const char* contextName,
			papuga_RequestContext* context,
			WebRequestAnswer& status);
	bool removeContext(
			const char* contextType,
			const char* contextName,
			WebRequestAnswer& status);

public:/*Ticker*/
	void tick();

private:/*Constructor/Destructor*/
	void loadConfiguration( const std::string& configstr);
	void clear();

private:
	typedef std::pair<std::string,std::string> ContextNameDef;

	class Ticker
		:public PeriodicTimerEvent
	{
	public:
		Ticker( WebRequestHandler* handler_, int seconds_)
			:PeriodicTimerEvent(seconds_),m_handler(handler_){}
		virtual void tick()
		{
			m_handler->tick();
		}
	private:
		WebRequestHandler* m_handler;
	};

private:
	strus::mutex m_mutex_context_transfer;		//< mutual exclusion of request context access
	int m_debug_maxdepth;				//< maximum depth for debug structures
	WebRequestLoggerInterface* m_logger;		//< request logger 
	papuga_RequestHandler* m_impl;			//< request handler
	ConfigurationHandler m_configHandler;		//< configuration handler
	std::string m_html_head;			//< header include for HTML output (for stylesheets, meta data etc.)
	std::string m_config_store_dir;			//< directory where to store configurations loaded as request
	TransactionPool m_transactionPool;		//< transaction pool
	int m_maxIdleTime;				//< maximum idle time transactions
	Ticker m_ticker;				//< periodic timer event to handle timeout of transactions
};

}//namespace
#endif


