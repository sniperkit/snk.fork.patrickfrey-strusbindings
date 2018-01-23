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
#include "strus/errorCodes.hpp"
#include <cstddef>

namespace strus {

ErrorCause papugaErrorToErrorCause( papuga_ErrorCode errcode);
int errorCauseToHttpStatus( ErrorCause cause);

}//namespace
#endif


