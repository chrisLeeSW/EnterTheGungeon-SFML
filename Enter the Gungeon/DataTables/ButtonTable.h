#pragma once

#include"DataTable.h"
#include"Player.h"
#include "Active.h"
#include "Passive.h"
#include "Weapon.h"
#include "ItemButton.h"


class ButtonTable : public DataTable
{

	std::unordered_map<Item::Types, ItemButton*> table;


public:

	ButtonTable() : DataTable(DataTable::Ids::Button) {};
	virtual ~ButtonTable() override = default;

	virtual bool Load() override;
	virtual void Release() override;

	ItemButton* Get(Item::Types id);
};

