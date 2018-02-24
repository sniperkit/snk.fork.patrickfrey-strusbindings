/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Interface for executing XML/JSON requests on the strus bindings
/// \file "webRequestContextInterface.hpp"
#ifndef _STRUS_WEB_REQUEST_CONTEXT_INTERFACE_HPP_INCLUDED
#define _STRUS_WEB_REQUEST_CONTEXT_INTERFACE_HPP_INCLUDED
#include "strus/webRequestAnswer.hpp"
#include "strus/webRequestContent.hpp"
#include <cstddef>

namespace strus
{

/// \brief Interface for executing an XML/JSON request on the strus bindings
class WebRequestContextInterface
{
public:
	/// \brief Destructor
	virtual ~WebRequestContextInterface(){}

	/// \brief Run the content request
	/// \param[in] contextType identifier defining the type of the context where to execute the request
	/// \param[in] contextName identifier defining the name of the context where to execute the request
	/// \param[in] schema identifier identifying the request to execute
	/// \param[in] content content of the request
	/// \param[out] answer the data of the answer of the request
	/// \return bool if succeeded, false else
	virtual bool executeContent(
			const char* contextType,
			const char* contextName,
			const char* schema,
			const WebRequestContent& content,
			WebRequestAnswer& answer)=0;

	/// \brief Describe in plain text what would be done to fulfill the content request without executing anything
	/// \param[in] contextType identifier defining the type of the context where to execute the request
	/// \param[in] contextName identifier defining the name of the context where to execute the request
	/// \param[in] schema identifier identifying the request to execute
	/// \param[in] content content of the request
	/// \param[out] answer the data of the answer of the request
	/// \return bool if request succeeded, false else
	virtual bool debugContent(
			const char* contextType,
			const char* contextName,
			const char* schema,
			const WebRequestContent& content,
			WebRequestAnswer& answer)=0;

	/// \brief Execute a list command for introspection defined by a path (URL)
	/// \param[in] path path of the object to list contents
	/// \return bool if succeeded, false else
	virtual bool executeList(
			const char* path,
			WebRequestAnswer& answer)=0;

	/// \brief Execute a view command for introspection defined by a path (URL)
	/// \param[in] path path of the object to view content
	/// \return bool if succeeded, false else
	virtual bool executeView(
			const char* path,
			WebRequestAnswer& answer)=0;
};

}//namespace
#endif


