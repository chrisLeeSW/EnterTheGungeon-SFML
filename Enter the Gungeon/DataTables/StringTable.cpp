#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

const std::string& StringTable::Get(const std::string& id, Languages lang) const
{
	static const std::string error = "ERR: Undefined ID";
	auto& table = tables[(int)lang];
	auto find = table.find(id);
	if (find == table.end())
	{
		return error;
	}
	return find->second;
}

bool StringTable::Load()
{
	std::vector<std::string> filenames;
	for (int i = 0; i < tables.size(); ++i)
	{
		rapidcsv::Document doc(filenames[i]);
		std::vector<std::string> ids = doc.GetColumn<std::string>(0);
		std::vector<std::string> values = doc.GetColumn<std::string>(1);

		for (int j = 0; j < ids.size(); ++j)
		{
			tables[i].insert({ ids[j], values[j] });
		}
	}

	return true;
}

void StringTable::Release()
{
	for (auto table : tables)
	{
		table.clear();
	}
	//tables.clear();
}
