/*
* Copyright (c) 2017 Patrick P. Frey
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
/// \brief Identifiers for objects and methods for serialization
/// \note PROGRAM (strusBindingsGen) GENERATED FILE! DO NOT MODIFY!!!
/// \file bindingObjects.cpp
#include "strus/bindingObjects.h"
#include "strus/base/dll_tags.hpp"
#include "impl/context.hpp"
#include "impl/storage.hpp"
#include "impl/vector.hpp"
#include "impl/analyzer.hpp"
#include "impl/query.hpp"
#include "impl/statistics.hpp"
#include "internationalization.hpp"
#include "callResultUtils.hpp"
#include "valueVariantWrap.hpp"

using namespace strus;
using namespace strus::bindings;

#define CATCH_METHOD_CALL_ERROR( retval, classnam, methodnam)\
	catch (const std::runtime_error& err)\
	{\
		papuga_CallResult_reportError( retval, _TXT("error calling method %s::%s(): %s"), classnam, methodnam, err.what());\
	}\
	catch (const std::bad_alloc& err)\
	{\
		papuga_CallResult_reportError( retval, _TXT("out of memory calling method %s::%s()"), classnam, methodnam);\
	}\
	catch (const std::exception& err)\
	{\
		papuga_CallResult_reportError( retval, _TXT("uncaught exception calling method %s::%s(): %s"), classnam, methodnam, err.what());\
	}\
	return false;

extern "C" DLL_PUBLIC void _strus_bindings_destructor__Context( void* self)
{
	delete reinterpret_cast<ContextImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_constructor__Context( papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		switch (argc)
		{
			case 0: initCallResultObjectOwnership( retval, new ContextImpl( ValueVariant())); break;
			case 1: initCallResultObjectOwnership( retval, new ContextImpl( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "constructor")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__getLastError( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		papuga_set_CallResult_charp_const( &retval, THIS->getLastError());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "getLastError")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__loadModule( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->loadModule( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "loadModule")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__addModulePath( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addModulePath( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "addModulePath")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__addResourcePath( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addResourcePath( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "addResourcePath")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createStatisticsProcessor( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultObjectOwnership( retval, THIS->createStatisticsProcessor( ValueVariantWrap::tostring( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createStatisticsProcessor")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createStorageClient( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		switch (argc)
		{
			case 0: initCallResultObjectOwnership( retval, THIS->createStorageClient( ValueVariant())); break;
			case 1: initCallResultObjectOwnership( retval, THIS->createStorageClient( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createStorageClient")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createVectorStorageClient( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		switch (argc)
		{
			case 0: initCallResultObjectOwnership( retval, THIS->createVectorStorageClient( ValueVariant())); break;
			case 1: initCallResultObjectOwnership( retval, THIS->createVectorStorageClient( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createVectorStorageClient")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createStorage( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->createStorage( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createStorage")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createVectorStorage( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->createVectorStorage( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createVectorStorage")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__destroyStorage( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->destroyStorage( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "destroyStorage")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__detectDocumentClass( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultStructureOwnership( retval, THIS->detectDocumentClass( ValueVariantWrap::tostring( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "detectDocumentClass")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createDocumentAnalyzer( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultObjectOwnership( retval, THIS->createDocumentAnalyzer( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createDocumentAnalyzer")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createQueryAnalyzer( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createQueryAnalyzer());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createQueryAnalyzer")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__createQueryEval( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createQueryEval());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "createQueryEval")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Context__close( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		ContextImpl* THIS = (ContextImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->close();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Context", "close")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__StorageClient( void* self)
{
	delete reinterpret_cast<StorageClientImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__nofDocumentsInserted( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		papuga_set_CallResult_uint( &retval, THIS->nofDocumentsInserted());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "nofDocumentsInserted")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__createTransaction( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createTransaction());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "createTransaction")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__createInitStatisticsIterator( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultObjectOwnership( retval, THIS->createInitStatisticsIterator( ValueVariantWrap::tobool( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "createInitStatisticsIterator")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__createUpdateStatisticsIterator( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createUpdateStatisticsIterator());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "createUpdateStatisticsIterator")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__createDocumentBrowser( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createDocumentBrowser());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "createDocumentBrowser")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__config( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultStructureOwnership( retval, THIS->config());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "config")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__configstring( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		{std::string retvalstr = THIS->configstring(); papuga_set_CallResult_string( &retval, retvalstr.c_str(), retvalstr.size());}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "configstring")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageClient__close( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageClientImpl* THIS = (StorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->close();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageClient", "close")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__StorageTransaction( void* self)
{
	delete reinterpret_cast<StorageTransactionImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageTransaction__insertDocument( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageTransactionImpl* THIS = (StorageTransactionImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->insertDocument( ValueVariantWrap::tostring( argv[0]), argv[1]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageTransaction", "insertDocument")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageTransaction__deleteDocument( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageTransactionImpl* THIS = (StorageTransactionImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->deleteDocument( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageTransaction", "deleteDocument")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageTransaction__deleteUserAccessRights( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageTransactionImpl* THIS = (StorageTransactionImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->deleteUserAccessRights( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageTransaction", "deleteUserAccessRights")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageTransaction__commit( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageTransactionImpl* THIS = (StorageTransactionImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->commit();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageTransaction", "commit")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StorageTransaction__rollback( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StorageTransactionImpl* THIS = (StorageTransactionImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->rollback();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StorageTransaction", "rollback")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__DocumentBrowser( void* self)
{
	delete reinterpret_cast<DocumentBrowserImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentBrowser__addMetaDataRestrictionCondition( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentBrowserImpl* THIS = (DocumentBrowserImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		std::string conv_argv0;
		switch (argc)
		{
			case 4: THIS->addMetaDataRestrictionCondition( ValueVariantWrap::tocharp( conv_argv0, argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], ValueVariantWrap::tobool( argv[3])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentBrowser", "addMetaDataRestrictionCondition")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentBrowser__skipDoc( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentBrowserImpl* THIS = (DocumentBrowserImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: papuga_set_CallResult_int( &retval, THIS->skipDoc( ValueVariantWrap::toint( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentBrowser", "skipDoc")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentBrowser__get( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentBrowserImpl* THIS = (DocumentBrowserImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: initCallResultStructureOwnership( retval, THIS->get( ValueVariantWrap::toint( argv[0]), argv[1])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentBrowser", "get")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__StatisticsIterator( void* self)
{
	delete reinterpret_cast<StatisticsIteratorImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_StatisticsIterator__getNext( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StatisticsIteratorImpl* THIS = (StatisticsIteratorImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultStructureOwnership( retval, THIS->getNext());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StatisticsIterator", "getNext")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__StatisticsProcessor( void* self)
{
	delete reinterpret_cast<StatisticsProcessorImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_StatisticsProcessor__decode( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StatisticsProcessorImpl* THIS = (StatisticsProcessorImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultStructureOwnership( retval, THIS->decode( ValueVariantWrap::tostring( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StatisticsProcessor", "decode")
}

extern "C" DLL_PUBLIC bool _strus_bindings_StatisticsProcessor__encode( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		StatisticsProcessorImpl* THIS = (StatisticsProcessorImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultStructureOwnership( retval, THIS->encode( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "StatisticsProcessor", "encode")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__VectorStorageSearcher( void* self)
{
	delete reinterpret_cast<VectorStorageSearcherImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageSearcher__findSimilar( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageSearcherImpl* THIS = (VectorStorageSearcherImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: initCallResultNumericValues( retval, THIS->findSimilar( argv[0], ValueVariantWrap::touint( argv[1]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageSearcher", "findSimilar")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageSearcher__findSimilarFromSelection( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageSearcherImpl* THIS = (VectorStorageSearcherImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: initCallResultNumericValues( retval, THIS->findSimilarFromSelection( argv[0], argv[1], ValueVariantWrap::touint( argv[2]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageSearcher", "findSimilarFromSelection")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageSearcher__close( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageSearcherImpl* THIS = (VectorStorageSearcherImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->close();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageSearcher", "close")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__VectorStorageClient( void* self)
{
	delete reinterpret_cast<VectorStorageClientImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__createSearcher( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: initCallResultObjectOwnership( retval, THIS->createSearcher( ValueVariantWrap::toint( argv[0]), ValueVariantWrap::toint( argv[1]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "createSearcher")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__createTransaction( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultObjectOwnership( retval, THIS->createTransaction());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "createTransaction")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__conceptClassNames( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultStructureOwnership( retval, THIS->conceptClassNames());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "conceptClassNames")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__conceptFeatures( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: initCallResultNumericValues( retval, THIS->conceptFeatures( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::toint( argv[1]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "conceptFeatures")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__nofConcepts( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: papuga_set_CallResult_uint( &retval, THIS->nofConcepts( ValueVariantWrap::tostring( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "nofConcepts")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__featureConcepts( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: initCallResultNumericValues( retval, THIS->featureConcepts( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::toint( argv[1]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "featureConcepts")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__featureVector( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultNumericValues( retval, THIS->featureVector( ValueVariantWrap::toint( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "featureVector")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__featureName( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: {std::string retvalstr = THIS->featureName( ValueVariantWrap::toint( argv[0])); papuga_set_CallResult_string( &retval, retvalstr.c_str(), retvalstr.size());} break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "featureName")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__featureIndex( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: papuga_set_CallResult_int( &retval, THIS->featureIndex( ValueVariantWrap::tostring( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "featureIndex")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__nofFeatures( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		papuga_set_CallResult_uint( &retval, THIS->nofFeatures());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "nofFeatures")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__config( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultStructureOwnership( retval, THIS->config());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "config")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__configstring( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		{std::string retvalstr = THIS->configstring(); papuga_set_CallResult_string( &retval, retvalstr.c_str(), retvalstr.size());}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "configstring")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageClient__close( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageClientImpl* THIS = (VectorStorageClientImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->close();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageClient", "close")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__VectorStorageTransaction( void* self)
{
	delete reinterpret_cast<VectorStorageTransactionImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageTransaction__addFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageTransactionImpl* THIS = (VectorStorageTransactionImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->addFeature( ValueVariantWrap::tostring( argv[0]), argv[1]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageTransaction", "addFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageTransaction__defineFeatureConceptRelation( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageTransactionImpl* THIS = (VectorStorageTransactionImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->defineFeatureConceptRelation( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::toint( argv[1]), ValueVariantWrap::toint( argv[2])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageTransaction", "defineFeatureConceptRelation")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageTransaction__commit( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageTransactionImpl* THIS = (VectorStorageTransactionImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		papuga_set_CallResult_bool( &retval, THIS->commit());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageTransaction", "commit")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageTransaction__rollback( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageTransactionImpl* THIS = (VectorStorageTransactionImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->rollback();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageTransaction", "rollback")
}

extern "C" DLL_PUBLIC bool _strus_bindings_VectorStorageTransaction__close( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		VectorStorageTransactionImpl* THIS = (VectorStorageTransactionImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		THIS->close();
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "VectorStorageTransaction", "close")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__DocumentAnalyzer( void* self)
{
	delete reinterpret_cast<DocumentAnalyzerImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__addSearchIndexFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 5) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 5: THIS->addSearchIndexFeature( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3], argv[4]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "addSearchIndexFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__addForwardIndexFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 5) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 5: THIS->addForwardIndexFeature( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3], argv[4]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "addForwardIndexFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineMetaData( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->defineMetaData( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineMetaData")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineAggregatedMetaData( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->defineAggregatedMetaData( ValueVariantWrap::tostring( argv[0]), argv[1]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineAggregatedMetaData")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineAttribute( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->defineAttribute( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineAttribute")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__addSearchIndexFeatureFromPatternMatch( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->addSearchIndexFeatureFromPatternMatch( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "addSearchIndexFeatureFromPatternMatch")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__addForwardIndexFeatureFromPatternMatch( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->addForwardIndexFeatureFromPatternMatch( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "addForwardIndexFeatureFromPatternMatch")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineMetaDataFromPatternMatch( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->defineMetaDataFromPatternMatch( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineMetaDataFromPatternMatch")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineAttributeFromPatternMatch( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->defineAttributeFromPatternMatch( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineAttributeFromPatternMatch")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__definePatternMatcherPostProc( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->definePatternMatcherPostProc( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "definePatternMatcherPostProc")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__definePatternMatcherPostProcFromFile( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->definePatternMatcherPostProcFromFile( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), ValueVariantWrap::tostring( argv[2])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "definePatternMatcherPostProcFromFile")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__defineDocument( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->defineDocument( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "defineDocument")
}

extern "C" DLL_PUBLIC bool _strus_bindings_DocumentAnalyzer__analyze( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		DocumentAnalyzerImpl* THIS = (DocumentAnalyzerImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultStructureOwnership( retval, THIS->analyze( ValueVariantWrap::tostring( argv[0]), ValueVariant())); break;
			case 2: initCallResultStructureOwnership( retval, THIS->analyze( ValueVariantWrap::tostring( argv[0]), argv[1])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "DocumentAnalyzer", "analyze")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__QueryAnalyzer( void* self)
{
	delete reinterpret_cast<QueryAnalyzerImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__addSearchIndexElement( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->addSearchIndexElement( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "addSearchIndexElement")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__addSearchIndexElementFromPatternMatch( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->addSearchIndexElementFromPatternMatch( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "addSearchIndexElementFromPatternMatch")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__addPatternLexem( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->addPatternLexem( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "addPatternLexem")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__definePatternMatcherPostProc( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 4: THIS->definePatternMatcherPostProc( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], argv[3]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "definePatternMatcherPostProc")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__definePatternMatcherPostProcFromFile( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->definePatternMatcherPostProcFromFile( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), ValueVariantWrap::tostring( argv[2])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "definePatternMatcherPostProcFromFile")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__defineImplicitGroupBy( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 5) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 5: THIS->defineImplicitGroupBy( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), ValueVariantWrap::toint( argv[2]), ValueVariantWrap::touint( argv[3]), ValueVariantWrap::tostring( argv[4])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "defineImplicitGroupBy")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryAnalyzer__analyze( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryAnalyzerImpl* THIS = (QueryAnalyzerImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultStructureOwnership( retval, THIS->analyze( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryAnalyzer", "analyze")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__QueryEval( void* self)
{
	delete reinterpret_cast<QueryEvalImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addTerm( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->addTerm( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), ValueVariantWrap::tostring( argv[2])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addTerm")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addSelectionFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addSelectionFeature( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addSelectionFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addRestrictionFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addRestrictionFeature( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addRestrictionFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addExclusionFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addExclusionFeature( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addExclusionFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addSummarizer( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->addSummarizer( ValueVariantWrap::tostring( argv[0]), argv[1], argv[2]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addSummarizer")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addWeightingFunction( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->addWeightingFunction( ValueVariantWrap::tostring( argv[0]), argv[1]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addWeightingFunction")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__addWeightingFormula( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->addWeightingFormula( ValueVariantWrap::tostring( argv[0]), argv[1]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "addWeightingFormula")
}

extern "C" DLL_PUBLIC bool _strus_bindings_QueryEval__createQuery( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryEvalImpl* THIS = (QueryEvalImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: initCallResultObjectOwnership( retval, THIS->createQuery( implObjectCast<StorageClientImpl>( argv[0]))); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "QueryEval", "createQuery")
}

extern "C" DLL_PUBLIC void _strus_bindings_destructor__Query( void* self)
{
	delete reinterpret_cast<QueryImpl*>( self);
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__defineFeature( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 2) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 2: THIS->defineFeature( ValueVariantWrap::tostring( argv[0]), argv[1], 1.0); break;
			case 3: THIS->defineFeature( ValueVariantWrap::tostring( argv[0]), argv[1], ValueVariantWrap::todouble( argv[2])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "defineFeature")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__addMetaDataRestrictionCondition( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 4) throw strus::runtime_error(_TXT("too few arguments"));
		std::string conv_argv0;
		switch (argc)
		{
			case 4: THIS->addMetaDataRestrictionCondition( ValueVariantWrap::tocharp( conv_argv0, argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2], ValueVariantWrap::tobool( argv[3])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "addMetaDataRestrictionCondition")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__defineTermStatistics( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 3) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 3: THIS->defineTermStatistics( ValueVariantWrap::tostring( argv[0]), ValueVariantWrap::tostring( argv[1]), argv[2]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "defineTermStatistics")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__defineGlobalStatistics( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->defineGlobalStatistics( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "defineGlobalStatistics")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__addDocumentEvaluationSet( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addDocumentEvaluationSet( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "addDocumentEvaluationSet")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__setMaxNofRanks( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->setMaxNofRanks( ValueVariantWrap::touint( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "setMaxNofRanks")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__setMinRank( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->setMinRank( ValueVariantWrap::touint( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "setMinRank")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__addUserName( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->addUserName( ValueVariantWrap::tostring( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "addUserName")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__setWeightingVariables( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->setWeightingVariables( argv[0]); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "setWeightingVariables")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__setDebugMode( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc < 1) throw strus::runtime_error(_TXT("too few arguments"));
		switch (argc)
		{
			case 1: THIS->setDebugMode( ValueVariantWrap::tobool( argv[0])); break;
			default: throw strus::runtime_error(_TXT("too many arguments"));
		}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "setDebugMode")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__evaluate( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		initCallResultStructureOwnership( retval, THIS->evaluate());
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "evaluate")
}

extern "C" DLL_PUBLIC bool _strus_bindings_Query__tostring( void* self, papuga_CallResult* retval, size_t argc, const papuga_ValueVariant* argv)
{
	try {
		QueryImpl* THIS = (QueryImpl*)(self);
		if (argc > 0) throw strus::runtime_error(_TXT("no arguments expected"));
		{std::string retvalstr = THIS->tostring(); papuga_set_CallResult_string( &retval, retvalstr.c_str(), retvalstr.size());}
		return true;
	}
	CATCH_METHOD_CALL_ERROR( retval, "Query", "tostring")
}

