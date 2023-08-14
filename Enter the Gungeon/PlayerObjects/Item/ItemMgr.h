#pragma once
#include "Singleton.h"
#include "AnimationController.h"
#include "Item.h"

class ItemMgr : public Singleton<ItemMgr>
{
	friend Singleton<ItemMgr>;


protected:

	ItemMgr() = default;
	virtual ~ItemMgr() override = default;

	std::unordered_map<Item::Types, Item*> mapItem;

public:

	void SetItem();
	void Init();
	
	std::unordered_map<Item::Types, Item*>::iterator GetItem(Item::Types type);


};

#define ITEM_MGR (ItemMgr::Instance())