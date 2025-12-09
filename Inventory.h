#pragma once

class Inventory
{
public: 
	enum class typeItem {
		NONE,
		KEY,
		BOMB,
	};
private:
	typeItem slot = typeItem::NONE;
public:
	typeItem getItem() const { return slot; }
	bool isEmpty() const { return slot == typeItem::NONE; }
	void setItem(typeItem item) { slot = item; }
	bool canUseItem(typeItem item) const { return slot == item;}

};


