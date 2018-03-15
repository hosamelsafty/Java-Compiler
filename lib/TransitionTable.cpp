#include "TransitionTable.h"

#define RAPIDJSON_HAS_STDSTRING 1

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include <map>
#include <set>


struct TransitionTable::impl
{
	std::map < std::set<State>, std::map<char, std::set<State> > > table;
};

TransitionTable::TransitionTable()
	: m_d(std::make_unique<impl>())
{

}

TransitionTable::TransitionTable(const TransitionTable & t)
	: m_d(std::make_unique<impl>())
{
	m_d->table = t.m_d->table;
}

TransitionTable::~TransitionTable()
{

}

void TransitionTable::add(const std::set<State> &currentStates, char input, const std::set<State> &nextStates)
{
	auto rowIt = m_d->table.find(currentStates);
	if (rowIt == m_d->table.end())
	{
		m_d->table.insert(std::pair<std::set<State>, std::map<char, std::set<State> > >(currentStates, std::map<char, std::set<State> >()));
	}

	m_d->table[currentStates].insert_or_assign(input, nextStates);
	//rowIt->second.insert_or_assign(input, nextStates);
}

std::set<State> TransitionTable::nextStates(const std::set<State> &currentStates, char input) const
{
	return m_d->table[currentStates][input];
}

std::ostream& operator<<(std::ostream& out, const TransitionTable &transitionTable)
{
	using namespace rapidjson;
	Document d;
	d.SetObject();
	Document::AllocatorType& allocator = d.GetAllocator();
	
	d.AddMember("tt", Value(), allocator);
	d["tt"].SetArray();
	for (const std::pair<std::set<State>, std::map<char, std::set<State> >> & transitionTableRow : transitionTable.m_d->table)
	{
		Value & row = d["tt"].PushBack(Value(), allocator);
		row.SetObject();

		row.AddMember("currentStates", Value(), allocator);
		row["currentStates"].SetArray();

		for (const State &currentState : transitionTableRow.first)
		{
			Value value(currentState.name.c_str(), currentState.name.size(), allocator);
			row["currentStates"].PushBack(value, allocator);
		}

		for (const std::pair<char, std::set<State>> &inputResultPair : transitionTableRow.second)
		{
			std::string charString(1, inputResultPair.first);
			Value input(charString.c_str(), charString.size(), allocator);
			row.AddMember(input, Value(), allocator);

			Value input2(charString.c_str(), charString.size(), allocator);
			Value & nextStatesArray = row[input2];
			nextStatesArray.SetArray();

			for (const State &nextState : inputResultPair.second)
			{
				Value value(nextState.name.c_str(), nextState.name.size(), allocator);
				nextStatesArray.PushBack(value, allocator);
			}
		}

	}

	StringBuffer sb;
	PrettyWriter<StringBuffer> writer(sb);
	d.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
	
	out << sb.GetString();
	return out;
}

std::istream& operator>>(std::istream& in, TransitionTable &transitionTable)
{

	return in;
}
