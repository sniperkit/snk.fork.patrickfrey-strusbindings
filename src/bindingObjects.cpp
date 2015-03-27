/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#include "strus/bindingObjects.hpp"
#include "strus/strus.hpp"
#include "strus/lib/module.hpp"
#include "strus/moduleLoaderInterface.hpp"
#include "strus/objectBuilderInterface.hpp"
#include "strus/private/arithmeticVariantAsString.hpp"
#include "strus/private/configParser.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>
#include <limits>

template <class Object>
struct ReferenceDeleter
{
	static void function( void* obj)
	{
		delete (Object*)obj;
	}
};

typedef std::vector<strus::NormalizerConfig> NormalizerConfigListImpl;
NormalizerConfig::NormalizerConfig( const NormalizerConfig& o)
{
	m_impl = (void*)new NormalizerConfigListImpl( *(NormalizerConfigListImpl*)o.m_impl);
}

NormalizerConfig::NormalizerConfig( const std::string& name_, const std::string& arg1)
{
	NormalizerConfigListImpl* THIS = new NormalizerConfigListImpl();
	m_impl = (void*)THIS;
	std::vector<std::string> args;
	args.push_back( arg1);
	THIS->push_back( strus::NormalizerConfig( name_, args));
}

NormalizerConfig::NormalizerConfig( const std::string& name_, const std::string& arg1, const std::string& arg2)
{
	NormalizerConfigListImpl* THIS = new NormalizerConfigListImpl();
	m_impl = (void*)THIS;
	std::vector<std::string> args;
	args.push_back( arg1);
	args.push_back( arg2);
	THIS->push_back( strus::NormalizerConfig( name_, args));
}

NormalizerConfig::NormalizerConfig( const std::string& name_)
{
	NormalizerConfigListImpl* THIS = new NormalizerConfigListImpl();
	m_impl = (void*)THIS;
	std::vector<std::string> args;
	THIS->push_back( strus::NormalizerConfig( name_, args));
}

NormalizerConfig::~NormalizerConfig()
{
	delete (NormalizerConfigListImpl*)m_impl;
}

NormalizerConfig& NormalizerConfig::operator()( const std::string& name_, const std::string& arg1)
{
	NormalizerConfigListImpl* THIS = (NormalizerConfigListImpl*)m_impl;
	std::vector<std::string> args;
	args.push_back( arg1);
	THIS->insert( THIS->begin(), strus::NormalizerConfig( name_, args));
	return *this;
}

NormalizerConfig& NormalizerConfig::operator()( const std::string& name_, const std::string& arg1, const std::string& arg2)
{
	NormalizerConfigListImpl* THIS = (NormalizerConfigListImpl*)m_impl;
	std::vector<std::string> args;
	args.push_back( arg1);
	args.push_back( arg2);
	THIS->insert( THIS->begin(), strus::NormalizerConfig( name_, args));
	return *this;
}

NormalizerConfig& NormalizerConfig::operator()( const std::string& name_)
{
	NormalizerConfigListImpl* THIS = (NormalizerConfigListImpl*)m_impl;
	std::vector<std::string> args;
	THIS->insert( THIS->begin(), strus::NormalizerConfig( name_, args));
	return *this;
}


Variant::Variant()
	:m_type(UNDEFINED){}

Variant::Variant( const Variant& o)
	:m_type(o.m_type),m_buf(o.m_buf)
{
	if (m_type == TEXT)
	{
		m_value.TEXT = m_buf.c_str();
	}
	else
	{
		std::memcpy( &m_value, &o.m_value, sizeof(m_value));
	}
}

Variant::Variant( unsigned int v)
	:m_type(UINT)
{
	m_value.UINT = v;
}

Variant::Variant( int v)
	:m_type(INT)
{
	m_value.INT = v;
}

Variant::Variant( float v)
	:m_type(FLOAT)
{
	m_value.FLOAT = v;
}

Variant::Variant( double v)
	:m_type(FLOAT)
{
	m_value.FLOAT = (float)v;
}

Variant::Variant( const char* v)
	:m_type(TEXT),m_buf(v)
{
	m_value.TEXT = m_buf.c_str();
}

Variant::Variant( const std::string& v)
	:m_type(TEXT),m_buf(v)
{
	m_value.TEXT = m_buf.c_str();
}

unsigned int Variant::getUInt() const
{
	if (m_type == UINT) return m_value.UINT;
	throw std::logic_error( "illegal access of variant value");
}

int Variant::getInt() const
{
	if (m_type == INT) return m_value.INT;
	throw std::logic_error( "illegal access of variant value");
}

float Variant::getFloat() const
{
	if (m_type == FLOAT) return m_value.FLOAT;
	throw std::logic_error( "illegal access of variant value");
}

const char* Variant::getText() const
{
	if (m_type == TEXT) return m_value.TEXT;
	throw std::logic_error( "illegal access of variant value");
}

Document::Document( const Document& o)
	:m_searchIndexTerms(o.m_searchIndexTerms)
	,m_forwardIndexTerms(o.m_forwardIndexTerms)
	,m_metaData(o.m_metaData)
	,m_attributes(o.m_attributes)
	,m_users(o.m_users)
{}

void Document::addSearchIndexTerm(
		const std::string& type_,
		const std::string& value_,
		const Index& position_)
{
	m_searchIndexTerms.push_back( Term( type_,value_,position_));
}

void Document::addForwardIndexTerm(
		const std::string& type_,
		const std::string& value_,
		const Index& position_)
{
	m_forwardIndexTerms.push_back( Term( type_,value_,position_));
}

void Document::setMetaData( const std::string& name_, Variant value_)
{
	m_metaData.push_back( MetaData( name_,value_));
}

void Document::setAttribute( const std::string& name_, const std::string& value_)
{
	m_attributes.push_back( Attribute( name_, value_));
}

void Document::setDocid( const std::string& docid_)
{
	m_docid = docid_;
	m_attributes.push_back( Attribute( "docid", docid_));
}

void Document::setUserAccessRight( const std::string& username_)
{
	m_users.push_back( username_);
}

DocumentAnalyzer::DocumentAnalyzer( const Reference& moduleloader, const std::string& segmentername)
	:m_moduleloader_impl(moduleloader)
	,m_analyzer_impl(ReferenceDeleter<strus::DocumentAnalyzerInterface>::function)
{
	const strus::ModuleLoaderInterface* moduleLoader = (const strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	m_analyzer_impl.reset( moduleLoader->builder().createDocumentAnalyzer( segmentername));
}

DocumentAnalyzer::DocumentAnalyzer( const DocumentAnalyzer& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
	,m_analyzer_impl(o.m_analyzer_impl)
{}


static strus::DocumentAnalyzerInterface::FeatureOptions getFeatureOptions(
	const std::vector<std::string>& options)
{
	strus::DocumentAnalyzerInterface::FeatureOptions rt;
	std::vector<std::string>::const_iterator
		oi = options.begin(), oe = options.end();
	for (; oi != oe; ++oi)
	{
		if (strus::utils::caseInsensitiveEquals( *oi, "BindPosSucc"))
		{
			rt.definePositionBind( strus::DocumentAnalyzerInterface::FeatureOptions::BindSuccessor);
		}
		else if (strus::utils::caseInsensitiveEquals( *oi, "BindPosPred"))
		{
			rt.definePositionBind( strus::DocumentAnalyzerInterface::FeatureOptions::BindPredecessor);
		}
		else
		{
			throw std::runtime_error( std::string( "unknown feature option '") + *oi + "'");
		}
	}
	return rt;
}

void DocumentAnalyzer::addSearchIndexFeature(
	const std::string& type,
	const std::string& selectexpr,
	const TokenizerConfig& tokenizer,
	const NormalizerConfig& normalizer,
	const std::vector<std::string>& options)
{
	NormalizerConfigListImpl* nl = (NormalizerConfigListImpl*)normalizer.m_impl;
	((strus::DocumentAnalyzerInterface*)m_analyzer_impl.get())->addSearchIndexFeature(
		type, selectexpr,
		strus::TokenizerConfig( tokenizer.name(), tokenizer.arguments()), 
		*nl, getFeatureOptions( options));
}

void DocumentAnalyzer::addForwardIndexFeature(
	const std::string& type,
	const std::string& selectexpr,
	const TokenizerConfig& tokenizer,
	const NormalizerConfig& normalizer,
	const std::vector<std::string>& options)
{
	NormalizerConfigListImpl* nl = (NormalizerConfigListImpl*)normalizer.m_impl;
	((strus::DocumentAnalyzerInterface*)m_analyzer_impl.get())->addForwardIndexFeature(
		type, selectexpr,
		strus::TokenizerConfig( tokenizer.name(), tokenizer.arguments()), 
		*nl, getFeatureOptions( options));
}

void DocumentAnalyzer::defineMetaData(
	const std::string& fieldname,
	const std::string& selectexpr,
	const TokenizerConfig& tokenizer,
	const NormalizerConfig& normalizer)
{
	NormalizerConfigListImpl* nl = (NormalizerConfigListImpl*)normalizer.m_impl;
	((strus::DocumentAnalyzerInterface*)m_analyzer_impl.get())->defineMetaData(
		fieldname, selectexpr,
		strus::TokenizerConfig( tokenizer.name(), tokenizer.arguments()), *nl);
}

void DocumentAnalyzer::defineAttribute(
	const std::string& attribname,
	const std::string& selectexpr,
	const TokenizerConfig& tokenizer,
	const NormalizerConfig& normalizer)
{
	NormalizerConfigListImpl* nl = (NormalizerConfigListImpl*)normalizer.m_impl;
	((strus::DocumentAnalyzerInterface*)m_analyzer_impl.get())->defineAttribute(
		attribname, selectexpr,
		strus::TokenizerConfig( tokenizer.name(), tokenizer.arguments()), *nl);
}

static Variant getNumericVariantFromString( const std::string& value)
{
	strus::ArithmeticVariant val( strus::arithmeticVariantFromString( value));
	switch (val.type)
	{
		case strus::ArithmeticVariant::Null:
			return Variant();
		case strus::ArithmeticVariant::Int:
			return Variant( (int)val);
		case strus::ArithmeticVariant::UInt:
			return Variant( (unsigned int)val);
		case strus::ArithmeticVariant::Float:
			return Variant( (float)val);
	}
	throw std::runtime_error( std::string("cannot create numeric variant type from string: '") + value + "'");
}

static strus::ArithmeticVariant arithmeticVariant( const Variant& val)
{
	strus::ArithmeticVariant rt;
	switch (val.type())
	{
		case Variant::UNDEFINED:
			break;
		case Variant::INT:
			rt = val.getInt();
			break;
		case Variant::UINT:
			rt = val.getUInt();
			break;
		case Variant::FLOAT:
			rt = val.getFloat();
			break;
		case Variant::TEXT:
			rt = strus::arithmeticVariantFromString( val.getText());
			break;
	}
	return rt;
}

Document DocumentAnalyzer::analyze( const std::string& content)
{
	Document rt;
	strus::DocumentAnalyzerInterface* THIS = (strus::DocumentAnalyzerInterface*)m_analyzer_impl.get();

	strus::analyzer::Document doc = THIS->analyze( content);

	std::vector<strus::analyzer::Attribute>::const_iterator
		ai = doc.attributes().begin(), ae = doc.attributes().end();
	for (; ai != ae; ++ai)
	{
		if (ai->name() == strus::Constants::attribute_docid())
		{
			rt.setDocid( ai->value());
		}
		else
		{
			rt.setAttribute( ai->name(), ai->value());
		}
	}
	std::vector<strus::analyzer::MetaData>::const_iterator
		mi = doc.metadata().begin(), me = doc.metadata().end();
	for (; mi != me; ++mi)
	{
		Variant val = getNumericVariantFromString( mi->value());
		rt.setMetaData( mi->name(), val);
	}
	std::vector<strus::analyzer::Term>::const_iterator
		ti = doc.searchIndexTerms().begin(), te = doc.searchIndexTerms().end();
	for (; ti != te; ++ti)
	{
		rt.addSearchIndexTerm( ti->type(), ti->value(), ti->pos());
	}
	std::vector<strus::analyzer::Term>::const_iterator
		fi = doc.forwardIndexTerms().begin(), fe = doc.forwardIndexTerms().end();
	for (; fi != fe; ++fi)
	{
		rt.addForwardIndexTerm( fi->type(), fi->value(), fi->pos());
	}
	return rt;
}


QueryAnalyzer::QueryAnalyzer( const Reference& moduleloader)
	:m_moduleloader_impl(moduleloader)
	,m_analyzer_impl(ReferenceDeleter<strus::QueryAnalyzerInterface>::function)
{
	const strus::ModuleLoaderInterface* moduleLoader = (const strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	m_analyzer_impl.reset( moduleLoader->builder().createQueryAnalyzer());
}

QueryAnalyzer::QueryAnalyzer( const QueryAnalyzer& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
	,m_analyzer_impl(o.m_analyzer_impl)
{}

void QueryAnalyzer::definePhraseType(
		const std::string& phraseType,
		const std::string& featureType,
		const TokenizerConfig& tokenizer,
		const NormalizerConfig& normalizer)
{
	NormalizerConfigListImpl* nl = (NormalizerConfigListImpl*)normalizer.m_impl;
	strus::QueryAnalyzerInterface* THIS = (strus::QueryAnalyzerInterface*)m_analyzer_impl.get();
	THIS->definePhraseType(
		phraseType, featureType,
		strus::TokenizerConfig( tokenizer.name(), tokenizer.arguments()), *nl);
}

std::vector<Term> QueryAnalyzer::analyzePhrase(
		const std::string& phraseType,
		const std::string& phraseContent) const
{
	std::vector<Term> rt;
	strus::QueryAnalyzerInterface* THIS = (strus::QueryAnalyzerInterface*)m_analyzer_impl.get();
	std::vector<strus::analyzer::Term>
		terms = THIS->analyzePhrase( phraseType, phraseContent);
	std::vector<strus::analyzer::Term>::const_iterator
		ti = terms.begin(), te = terms.end();
	for (; ti != te; ++ti)
	{
		rt.push_back( Term( ti->type(), ti->value(), ti->pos()));
	}
	return rt;
}


StorageClient::StorageClient( const Reference& moduleloader, const std::string& config_)
	:m_moduleloader_impl( moduleloader)
	,m_storage_impl(ReferenceDeleter<strus::StorageClientInterface>::function)
	,m_transaction_impl(ReferenceDeleter<strus::StorageTransactionInterface>::function)
{
	const strus::ModuleLoaderInterface* moduleLoader = (const strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	m_storage_impl.reset( moduleLoader->builder().createStorageClient( config_));
}

StorageClient::StorageClient( const StorageClient& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
	,m_storage_impl(o.m_storage_impl)
	,m_transaction_impl(ReferenceDeleter<strus::StorageTransactionInterface>::function)
{
	if (o.m_transaction_impl.get())
	{
		throw std::runtime_error("try to create a storage interface clone of a storage with an open transaction");
	}
}

GlobalCounter StorageClient::nofDocumentsInserted() const
{
	strus::StorageClientInterface* THIS = (strus::StorageClientInterface*)m_storage_impl.get();
	return THIS->globalNofDocumentsInserted();
}

void StorageClient::insertDocument( const std::string& docid, const Document& doc)
{
	strus::StorageClientInterface* THIS = (strus::StorageClientInterface*)m_storage_impl.get();
	if (!m_transaction_impl.get())
	{
		m_transaction_impl.reset( (strus::StorageTransactionInterface*)THIS->createTransaction());
	}
	strus::StorageTransactionInterface* transaction = (strus::StorageTransactionInterface*)m_transaction_impl.get();
	std::auto_ptr<strus::StorageDocumentInterface> document( transaction->createDocument( docid));

	std::vector<Attribute>::const_iterator
		ai = doc.attributes().begin(), ae = doc.attributes().end();
	for (; ai != ae; ++ai)
	{
		document->setAttribute( ai->name(), ai->value());
	}
	std::vector<MetaData>::const_iterator
		mi = doc.metaData().begin(), me = doc.metaData().end();
	for (; mi != me; ++mi)
	{
		document->setMetaData( mi->name(), arithmeticVariant( mi->value()));
	}
	std::vector<Term>::const_iterator
		ti = doc.searchIndexTerms().begin(), te = doc.searchIndexTerms().end();
	for (; ti != te; ++ti)
	{
		document->addSearchIndexTerm( ti->name(), ti->value(), ti->position());
	}
	std::vector<Term>::const_iterator
		fi = doc.forwardIndexTerms().begin(), fe = doc.forwardIndexTerms().end();
	for (; fi != fe; ++fi)
	{
		document->addForwardIndexTerm( fi->name(), fi->value(), fi->position());
	}
	std::vector<std::string>::const_iterator
		ui = doc.users().begin(), ue = doc.users().end();
	for (; ui != ue; ++ui)
	{
		document->setUserAccessRight( *ui);
	}
	document->done();
}

void StorageClient::deleteDocument( const std::string& docId)
{
	strus::StorageClientInterface* THIS = (strus::StorageClientInterface*)m_storage_impl.get();
	if (!m_transaction_impl.get())
	{
		m_transaction_impl.reset( (strus::StorageTransactionInterface*)THIS->createTransaction());
	}
	strus::StorageTransactionInterface* transaction = (strus::StorageTransactionInterface*)m_transaction_impl.get();
	transaction->deleteDocument( docId);
}

void StorageClient::deleteUserAccessRights( const std::string& username)
{
	strus::StorageClientInterface* THIS = (strus::StorageClientInterface*)m_storage_impl.get();
	if (!m_transaction_impl.get())
	{
		m_transaction_impl.reset( (strus::StorageTransactionInterface*)THIS->createTransaction());
	}
	strus::StorageTransactionInterface* transaction = (strus::StorageTransactionInterface*)m_transaction_impl.get();
	transaction->deleteUserAccessRights( username);
}

void StorageClient::flush()
{
	strus::StorageTransactionInterface* transaction = (strus::StorageTransactionInterface*)m_transaction_impl.get();
	if (transaction)
	{
		transaction->commit();
		m_transaction_impl.reset();
	}
}

void StorageClient::close()
{
	strus::StorageClientInterface* THIS = (strus::StorageClientInterface*)m_storage_impl.get();
	THIS->close();
}

QueryEval::QueryEval( const Reference& moduleloader)
	:m_moduleloader_impl(moduleloader)
	,m_queryeval_impl(ReferenceDeleter<strus::QueryEvalInterface>::function)
{
	const strus::ModuleLoaderInterface* moduleLoader = (const strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	m_queryeval_impl.reset( moduleLoader->builder().createQueryEval());
}

QueryEval::QueryEval( const QueryEval& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
	,m_queryeval_impl(o.m_queryeval_impl)
{}

void QueryEval::addTerm(
		const std::string& set_,
		const std::string& type_,
		const std::string& value_)
{
	strus::QueryEvalInterface* queryeval = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	queryeval->addTerm( set_, type_, value_);
}

void QueryEval::addSelectionFeature( const std::string& set_)
{
	strus::QueryEvalInterface* queryeval = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	queryeval->addSelectionFeature( set_);
}

void QueryEval::addRestrictionFeature( const std::string& set_)
{
	strus::QueryEvalInterface* queryeval = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	queryeval->addRestrictionFeature( set_);
}

void QueryEval::addSummarizer(
		const std::string& resultAttribute,
		const Summarizer& summarizer)
{
	strus::QueryEvalInterface* queryeval = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	strus::SummarizerConfig config;
	std::map<std::string,Variant>::const_iterator
		pi = summarizer.m_parameters.begin(), pe = summarizer.m_parameters.end();
	for (; pi != pe; ++pi)
	{
		if (pi->second.m_type == Variant::TEXT)
		{
			config.defineTextualParameter( pi->first, pi->second.m_value.TEXT);
		}
		else
		{
			config.defineNumericParameter( pi->first, arithmeticVariant( pi->second));
		}
	}
	std::map<std::string,std::string>::const_iterator
		fi = summarizer.m_features.begin(), fe = summarizer.m_features.end();
	for (; fi != fe; ++fi)
	{
		config.defineFeatureParameter( fi->first, fi->second);
	}
	queryeval->addSummarizer( resultAttribute, summarizer.m_name, config);
}

void QueryEval::addWeightingFunction(
		const WeightingFunction& weightingFunction,
		const std::vector<std::string>& weightingFeatureSets)
{
	strus::QueryEvalInterface* queryeval = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	strus::WeightingConfig config;
	std::map<std::string,Variant>::const_iterator
		pi = weightingFunction.m_parameters.begin(), pe = weightingFunction.m_parameters.end();
	for (; pi != pe; ++pi)
	{
		config.defineNumericParameter( pi->first, arithmeticVariant( pi->second));
	}
	queryeval->addWeightingFunction( weightingFunction.m_name, config, weightingFeatureSets);
}


Query::Query( const QueryEval& queryeval, const StorageClient& storage)
	:m_moduleloader_impl(queryeval.m_moduleloader_impl)
	,m_storage_impl(storage.m_storage_impl)
	,m_queryeval_impl(queryeval.m_queryeval_impl)
	,m_query_impl( ReferenceDeleter<strus::QueryInterface>::function)
{
	strus::QueryEvalInterface* qe = (strus::QueryEvalInterface*)m_queryeval_impl.get();
	strus::StorageClientInterface* st = (strus::StorageClientInterface*)m_storage_impl.get();
	m_query_impl.reset( qe->createQuery( st));
}

Query::Query( const Query& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
	,m_storage_impl(o.m_storage_impl)
	,m_queryeval_impl(o.m_queryeval_impl)
	,m_query_impl(o.m_query_impl)
{}

void Query::pushTerm( const std::string& type_, const std::string& value_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->pushTerm( type_, value_);
}

void Query::pushExpression( const std::string& opname_, unsigned int argc, int range_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->pushExpression( opname_, argc, range_);
}

void Query::attachVariable( const std::string& name_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->attachVariable( name_);
}

void Query::defineFeature( const std::string& set_, float weight_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->defineFeature( set_, weight_);
}

void Query::defineMetaDataRestriction(
		const char* compareOp, const std::string& name,
		const Variant& operand, bool newGroup)
{
	strus::QueryInterface::CompareOperator cmpop;
	if (std::strcmp( compareOp, "<") == 0)
	{
		cmpop = strus::QueryInterface::CompareLess;
	}
	else if (std::strcmp( compareOp, "<=") == 0)
	{
		cmpop = strus::QueryInterface::CompareLessEqual;
	}
	else if (std::strcmp( compareOp, "=") == 0)
	{
		cmpop = strus::QueryInterface::CompareEqual;
	}
	else if (std::strcmp( compareOp, "!=") == 0)
	{
		cmpop = strus::QueryInterface::CompareNotEqual;
	}
	else if (std::strcmp( compareOp, ">") == 0)
	{
		cmpop = strus::QueryInterface::CompareGreater;
	}
	else if (std::strcmp( compareOp, ">=") == 0)
	{
		cmpop = strus::QueryInterface::CompareGreaterEqual;
	}
	else
	{
		throw std::runtime_error( std::string("unknown compare operator '") + compareOp + "', expected one of '=','!=','>','<','<=','>='");
	}

	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->defineMetaDataRestriction( cmpop, name, arithmeticVariant(operand), newGroup);
}

void Query::setMaxNofRanks( unsigned int maxNofRanks_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->setMaxNofRanks( maxNofRanks_);
}

void Query::setMinRank( unsigned int minRank_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->setMinRank( minRank_);
}

void Query::setUserName( const std::string& username_)
{
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	THIS->setUserName( username_);
}

std::vector<Rank> Query::evaluate() const
{
	std::vector<Rank> rt;
	strus::QueryInterface* THIS = (strus::QueryInterface*)m_query_impl.get();
	std::vector<strus::ResultDocument> res = THIS->evaluate();

	std::vector<strus::ResultDocument>::const_iterator
		ri = res.begin(), re = res.end();
	for (;ri != re; ++ri)
	{
		Rank reselem;
		reselem.m_docno = (unsigned int)ri->docno();
		reselem.m_weight = ri->weight();
		std::vector<strus::ResultDocument::Attribute>::const_iterator
			ai = ri->attributes().begin(), ae = ri->attributes().end();
	
		for (;ai != ae; ++ai)
		{
			RankAttribute attr;
			attr.m_name = ai->name();
			attr.m_value = ai->value();
			reselem.m_attributes.push_back( attr);
		}
		rt.push_back( reselem);
	}
	return rt;
}


StrusContext::StrusContext()
	:m_moduleloader_impl( ReferenceDeleter<strus::ModuleLoaderInterface>::function)
{
	m_moduleloader_impl.reset( strus::createModuleLoader());
}

StrusContext::StrusContext( const StrusContext& o)
	:m_moduleloader_impl(o.m_moduleloader_impl)
{}

void StrusContext::loadModule( const std::string& name_)
{
	strus::ModuleLoaderInterface* moduleLoader = (strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	moduleLoader->loadModule( name_);
}

void StrusContext::setPath( const std::string& paths_)
{
	strus::ModuleLoaderInterface* moduleLoader = (strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	moduleLoader->addModulePath( paths_);
}

StorageClient StrusContext::createStorageClient( const std::string& config_)
{
	return StorageClient( m_moduleloader_impl, config_);
}

DocumentAnalyzer StrusContext::createDocumentAnalyzer( const std::string& segmentername_)
{
	return DocumentAnalyzer( m_moduleloader_impl, segmentername_);
}

QueryAnalyzer StrusContext::createQueryAnalyzer()
{
	return QueryAnalyzer( m_moduleloader_impl);
}

QueryEval StrusContext::createQueryEval()
{
	return QueryEval( m_moduleloader_impl);
}

void StrusContext::createStorage( const char* config)
{
	strus::ModuleLoaderInterface* moduleLoader = (strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	const strus::DatabaseInterface* dbi = moduleLoader->builder().getDatabase( config);
	const strus::StorageInterface* sti = moduleLoader->builder().getStorage();

	std::string dbname;
	std::string databasecfg( config);
	(void)strus::extractStringFromConfigString( dbname, databasecfg, "database");
	std::string storagecfg( databasecfg);

	strus::removeKeysFromConfigString(
			databasecfg,
			sti->getConfigParameters( strus::StorageInterface::CmdCreateClient));
	//... In database_cfg is now the pure database configuration without the storage settings

	strus::removeKeysFromConfigString(
			storagecfg,
			dbi->getConfigParameters( strus::DatabaseInterface::CmdCreateClient));
	//... In storage_cfg is now the pure storage configuration without the database settings

	dbi->createDatabase( databasecfg);

	std::auto_ptr<strus::DatabaseClientInterface>
		database( dbi->createClient( databasecfg));

	sti->createStorage( storagecfg, database.get());
}

void StrusContext::destroyStorage( const char* config)
{
	strus::ModuleLoaderInterface* moduleLoader = (strus::ModuleLoaderInterface*)m_moduleloader_impl.get();
	const strus::DatabaseInterface* dbi = moduleLoader->builder().getDatabase( config);
	dbi->destroyDatabase( config);
}


