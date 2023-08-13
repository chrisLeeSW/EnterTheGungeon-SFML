#include "stdafx.h"
#include "ItemMgr.h"
#include "Active.h"
#include "Passive.h"
#include "PilotActive.h"
#include "PrisonerActive.h"
#include "PrisonerPassive.h"
#include "PilotPassive.h"
#include "Item.h"

void ItemMgr::Init()
{
	PilotActive* pilotActive = new PilotActive();
	PilotPassive* pilotPassive = new PilotPassive();
	PrisonerActive* prisonerActive = new PrisonerActive();
	PrisonerPassive* prisonerPassive = new PrisonerPassive();

	mapItem.insert({Item::Types::PilotActive, pilotActive});
	mapItem.insert({ Item::Types::PilotPassvie, pilotPassive });
	mapItem.insert({ Item::Types::PrisonerActive, prisonerActive });
	mapItem.insert({ Item::Types::PrisonerPassive, prisonerPassive });

}


void ItemMgr::SetItem()
{
}

std::unordered_map<Item::Types, Item*>::iterator ItemMgr::GetItem(Item::Types id)
{
	auto find = mapItem.find(id);
	return find;
}