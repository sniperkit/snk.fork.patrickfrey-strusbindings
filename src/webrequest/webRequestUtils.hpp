/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Helper functions and classes for executing XML/JSON requests on the strus bindings
/// \file "webRequestUtils.hpp"
#ifndef _STRUS_WEB_REQUEST_UTILS_HPP_INCLUDED
#define _STRUS_WEB_REQUEST_UTILS_HPP_INCLUDED
#include "papuga/typedefs.h"
#include "papuga/requestParser.h"
#include "strus/errorCodes.hpp"
#include "strus/webRequestContent.hpp"
#include "strus/webRequestAnswer.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <map>

namespace strus {

// \brief Maps a papuga error code to a strus error number
// \param[in] errcode papuga error code
// \return strus error number
ErrorCause papugaErrorToErrorCause( papuga_ErrorCode errcode);

// \brief Maps an error cause (part of error codes defined in strusBase or errno) to an HTTP request status code
// \param[in] content web request content
// \return HTTP status c
int errorCauseToHttpStatus( ErrorCause cause);

// \brief Contert a web request content to an UTF-8 string for printing and logging
// \param[in] content web request content
// \return content as UTF-8 string
std::string webRequestContent_tostring( const WebRequestContent& content);

// \brief Parse a content type from a string
// \param[in] name content type as string
// \return type id or WebRequestContent::Unknown
WebRequestContent::Type webRequestContentFromTypeName( const char* name);

// \brief Get the best choice for the character encoding type of a request result
// \param[in] http_accept_charset value of HTTP header "Accept-Charset"
// \return chosen charset
papuga_StringEncoding getResultStringEncoding( const char* http_accept_charset, papuga_StringEncoding inputenc);

// \brief Get the best choice for the content type of a request result
// \param[in] http_accept value of HTTP header "Accept"
// \note does not handle '*' for any in the HTTP header "Accept" (e.g. "application/*" or "*/*" etc. not respected)
// \return chosen content type
WebRequestContent::Type getResultContentType( const char* http_accept, WebRequestContent::Type inputdoctype);

// \brief Get the best choice for the content type of a request result
// \param[in] http_accept value of HTTP header "Accept"
// \note does not handle '*' for any in the HTTP header "Accept" (e.g. "application/*" or "*/*" etc. not respected)
// \return chosen content type
papuga_ContentType getPapugaResultContentType( const char* http_accept, papuga_ContentType inputdoctype);

// \brief Get the papuga request content type from a web content type
// \param[in] doctype web content type
// \return the correspoding papuga request content type or papuga_ContentType_Unknown if mapping failed
papuga_ContentType papugaContentType( WebRequestContent::Type doctype);

// \brief Map a papuga request content type to its correspoding web content type
// \param[in] type papuga request content type
// \return the correspoding web content type
WebRequestContent::Type papugaTranslatedContentType( papuga_ContentType doctype);

// \brief Map a string as content to an answer
// \param[out] answer initialized answer object
// \param[in] allocator allocator to use
// \param[in] name name of the result
// \param[in] encoding encoding of the result
// \param[in] doctype content type of the result
// \param[in] input input to map
bool mapStringToAnswer(
		WebRequestAnswer& answer,
		papuga_Allocator* allocator,
		const char* html_head,
		const char* name,
		papuga_StringEncoding encoding,
		WebRequestContent::Type doctype,
		const std::string& input);

// \brief Map a string vector as content to an answer
// \param[out] answer initialized answer object
// \param[in] allocator allocator to use
// \param[in] name name of the result
// \param[in] encoding encoding of the result
// \param[in] doctype content type of the result
// \param[in] input input to map
bool mapStringArrayToAnswer(
		WebRequestAnswer& answer,
		papuga_Allocator* allocator,
		const char* html_head,
		const char* rootname,
		const char* elemname,
		papuga_StringEncoding encoding,
		WebRequestContent::Type doctype,
		const std::vector<std::string>& input);

// \brief Map a NULL terminated C string array as content to an answer
// \param[out] answer initialized answer object
// \param[in] allocator allocator to use
// \param[in] name name of the result
// \param[in] encoding encoding of the result
// \param[in] doctype content type of the result
// \param[in] input input to map
bool mapStringArrayToAnswer(
		WebRequestAnswer& answer,
		papuga_Allocator* allocator,
		const char* html_head,
		const char* rootname,
		const char* elemname,
		papuga_StringEncoding encoding,
		WebRequestContent::Type doctype,
		const char** input);

// \brief Map a string to string map as content to an answer
// \param[out] answer initialized answer object
// \param[in] allocator allocator to use
// \param[in] name name of the result
// \param[in] encoding encoding of the result
// \param[in] doctype content type of the result
// \param[in] input input to map
bool mapStringMapToAnswer(
		WebRequestAnswer& answer,
		papuga_Allocator* allocator,
		const char* html_head,
		const char* name,
		papuga_StringEncoding encoding,
		WebRequestContent::Type doctype,
		const std::map<std::string,std::string>& input);

// \brief Map a value variant to an answer
// \param[out] answer initialized answer object
// \param[in] name name of the result
// \param[in] encoding encoding of the result
// \param[in] doctype content type of the result
// \param[in] input input to map
bool mapValueVariantToAnswer(
		WebRequestAnswer& answer,
		papuga_Allocator* allocator,
		const char* html_head,
		const char* rootname,
		const char* elemname,
		papuga_StringEncoding encoding,
		WebRequestContent::Type doctype,
		const papuga_ValueVariant& input);

}//namespace
#endif


