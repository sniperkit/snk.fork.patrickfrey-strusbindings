/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "impl/query.hpp"
#include "impl/storage.hpp"
#include "papuga/serialization.h"
#include "strus/queryEvalInterface.hpp"
#include "strus/queryInterface.hpp"
#include "strus/errorBufferInterface.hpp"
#include "strus/storageObjectBuilderInterface.hpp"
#include "private/internationalization.hpp"
#include "valueVariantWrap.hpp"
#include "callResultUtils.hpp"
#include "deserializer.hpp"
#include "serializer.hpp"
#include "structDefs.hpp"

using namespace strus;
using namespace strus::bindings;

QueryEvalImpl::QueryEvalImpl( const ObjectRef& trace, const ObjectRef& objbuilder, const ObjectRef& errorhnd)
	:m_errorhnd_impl(errorhnd)
	,m_trace_impl(trace)
	,m_objbuilder_impl(objbuilder)
	,m_queryeval_impl()
{
	const StorageObjectBuilderInterface* objBuilder = m_objbuilder_impl.getObject<const StorageObjectBuilderInterface>();
	m_queryproc = objBuilder->getQueryProcessor();
	if (!m_queryproc)
	{
		ErrorBufferInterface* ehnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
		throw strus::runtime_error( "%s", ehnd->fetchError());
	}
	m_queryeval_impl.resetOwnership( objBuilder->createQueryEval(), "QueryEval");
	if (!m_queryeval_impl.get())
	{
		ErrorBufferInterface* ehnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
		throw strus::runtime_error( "%s", ehnd->fetchError());
	}
}

void QueryEvalImpl::addTerm(
		const std::string& set_,
		const std::string& type_,
		const std::string& value_)
{
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();
	queryeval->addTerm( set_, type_, value_);
}

void QueryEvalImpl::addSelectionFeature( const std::string& set_)
{
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();
	queryeval->addSelectionFeature( set_);
}

void QueryEvalImpl::addRestrictionFeature( const std::string& set_)
{
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();
	queryeval->addRestrictionFeature( set_);
}

void QueryEvalImpl::addExclusionFeature( const std::string& set_)
{
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();
	queryeval->addExclusionFeature( set_);
}

void QueryEvalImpl::addSummarizer(
		const std::string& name,
		const ValueVariant& parameters,
		const ValueVariant& resultnames)
{
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();

	Deserializer::buildSummarizerFunction(
		queryeval, name, parameters, resultnames, m_queryproc, errorhnd);
}

void QueryEvalImpl::addWeightingFunction(
		const std::string& name,
		const ValueVariant& parameter)
{
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();

	Deserializer::buildWeightingFunction(
		queryeval, name, parameter, m_queryproc, errorhnd);
}

void QueryEvalImpl::defineWeightingFormula(
		const std::string& source,
		const ValueVariant& parameter)
{
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	QueryEvalInterface* queryeval = m_queryeval_impl.getObject<QueryEvalInterface>();

	Deserializer::buildWeightingFormula( queryeval, source, parameter, m_queryproc, errorhnd);
}

QueryImpl* QueryEvalImpl::createQuery( StorageClientImpl* storage) const
{
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	const QueryEvalInterface* qe = m_queryeval_impl.getObject<QueryEvalInterface>();
	const StorageClientInterface* st = storage->m_storage_impl.getObject<StorageClientInterface>();
	ObjectRef query;
	query.resetOwnership( qe->createQuery( st), "Query");
	if (!query.get()) throw strus::runtime_error( "%s", errorhnd->fetchError());

	return new QueryImpl( m_trace_impl, m_objbuilder_impl, m_errorhnd_impl, storage->m_storage_impl, m_queryeval_impl, query, m_queryproc);
}

void QueryImpl::addFeature( const std::string& set_, const ValueVariant& expr_, double weight_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	QueryExpressionBuilder exprbuilder( THIS, m_queryproc, errorhnd);

	Deserializer::buildExpression( exprbuilder, expr_, errorhnd, true);
	if (errorhnd->hasError()) throw strus::runtime_error( "%s", errorhnd->fetchError());
	unsigned int ii=0, nn = exprbuilder.stackSize();
	if (nn == 0) throw strus::runtime_error( _TXT("feature defined without expression"));
	for (; ii<nn; ++ii)
	{
		THIS->defineFeature( set_, weight_);
	}
}

void QueryImpl::addMetaDataRestriction( const ValueVariant& expression)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	Deserializer::buildMetaDataRestriction( THIS, expression, errorhnd);
}

void QueryImpl::defineTermStatistics( const std::string& type_, const std::string& value_, const ValueVariant& stats_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	TermStatistics stats = Deserializer::getTermStatistics( stats_);
	THIS->defineTermStatistics( type_, value_, stats);
}

void QueryImpl::defineGlobalStatistics( const ValueVariant& stats_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	GlobalStatistics stats = Deserializer::getGlobalStatistics( stats_);
	THIS->defineGlobalStatistics( stats);
}

void QueryImpl::addDocumentEvaluationSet( const ValueVariant& docnolist_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	std::vector<Index> docnolist = Deserializer::getIndexList( docnolist_);
	THIS->addDocumentEvaluationSet( docnolist);
}

void QueryImpl::setMaxNofRanks( unsigned int maxNofRanks_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	THIS->setMaxNofRanks( maxNofRanks_);
}

void QueryImpl::setMinRank( unsigned int minRank_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	THIS->setMinRank( minRank_);
}

void QueryImpl::addAccess( const ValueVariant& userlist_)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	std::vector<std::string> userlist = Deserializer::getStringList( userlist_);
	std::vector<std::string>::const_iterator ui = userlist.begin(), ue = userlist.end();
	for (; ui != ue; ++ui)
	{
		THIS->addAccess( *ui);
	}
}

void QueryImpl::setWeightingVariables(
		const ValueVariant& parameter)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();

	KeyValueList kvlist( parameter);
	KeyValueList::const_iterator ki = kvlist.begin(), ke = kvlist.end();
	for (; ki != ke; ++ki)
	{
		THIS->setWeightingVariableValue( ki->first, ValueVariantWrap::todouble( *ki->second));
	}
}

void QueryImpl::setDebugMode( bool debug)
{
	QueryInterface* THIS = m_query_impl.getObject<QueryInterface>();
	THIS->setDebugMode( debug);
}

QueryResult* QueryImpl::evaluate() const
{
	const QueryInterface* THIS = m_query_impl.getObject<const QueryInterface>();
	Reference<QueryResult> result( new QueryResult( THIS->evaluate()));
	ErrorBufferInterface* errorhnd = m_errorhnd_impl.getObject<ErrorBufferInterface>();
	if (errorhnd->hasError())
	{
		throw strus::runtime_error( "%s", errorhnd->fetchError());
	}
	return result.release();
}

std::string QueryImpl::tostring() const
{
	const QueryInterface* THIS = m_query_impl.getObject<const QueryInterface>();
	return THIS->tostring();
}



