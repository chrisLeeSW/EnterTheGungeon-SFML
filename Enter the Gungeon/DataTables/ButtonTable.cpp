#include "stdafx.h"
#include "ButtonTable.h"
#include "ItemButton.h"

ItemButton* ButtonTable::Get(Item::Types id)
{
	auto find = table.find(id);
	if (find == table.end())
	{
		std::cout << "¿¡·¯" << std::endl;
		return nullptr;
	}

	return find->second;
}


bool ButtonTable::Load()
{
	std::string buttonfile = "tables/ButtonTable.csv";

	rapidcsv::Document doc(buttonfile);
	std::vector<int> itemType = doc.GetColumn<int>(0);
	std::vector<std::string> buttonTextures = doc.GetColumn<std::string>(1);
	std::vector<std::string> itemnames = doc.GetColumn<std::string>(2);
	std::vector<std::string> manuals1 = doc.GetColumn<std::string>(3);
	std::vector<std::string> manuals2 = doc.GetColumn<std::string>(4);
	std::vector<std::string> manuals3 = doc.GetColumn<std::string>(5);
	std::vector<std::string> manuals4 = doc.GetColumn<std::string>(6);
	std::vector<std::string> itemsprites = doc.GetColumn<std::string>(7);
	std::vector<float> nameposx = doc.GetColumn<float>(8);
	std::vector<float> nameposy = doc.GetColumn<float>(9);
	std::vector<float> manualposx = doc.GetColumn<float>(10);
	std::vector<float> manualposy = doc.GetColumn<float>(11);
	std::vector<std::string> buttonfont = doc.GetColumn<std::string>(12);
	std::vector<int> textsize = doc.GetColumn<int>(13);
	std::vector<int> namesize = doc.GetColumn<int>(14);

	for (int i = 0; i < buttonTextures.size(); ++i)
	{
		ItemButton* itembutton = new ItemButton();
		itembutton->textureId = buttonTextures[i];
		itembutton->itemname = itemnames[i];
		itembutton->manual.push_back(manuals1[i]);
		itembutton->manual.push_back(manuals2[i]);
		itembutton->manual.push_back(manuals3[i]);
		itembutton->manual.push_back(manuals4[i]);
		itembutton->itemspriteId = itemsprites[i];
		itembutton->namepos.x = nameposx[i];
		itembutton->namepos.y = nameposy[i];
		itembutton->manualpos.x = manualposx[i];
		itembutton->manualpos.y = manualposy[i];
		itembutton->fontId = buttonfont[i];
		itembutton->textsize = textsize[i];
		itembutton->namesize = namesize[i];
		

		//itembutton->Reset();

		table.insert({(Item::Types)itemType[i] , itembutton });
	}
	return true;
}

void ButtonTable::Release()
{
	table.clear();
}
