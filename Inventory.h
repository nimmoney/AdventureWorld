#pragma once
class Inventory
{
public: 
	enum class typeItem {
		NONE,
		KEY,
		RIDDLE,
		BOMB,
	};
private:
	typeItem slot = typeItem::NONE;
public:
	bool isEmpty() const { return slot == typeItem::NONE; }
	void setItem(typeItem item) { slot = item; }
	typeItem getItem() const { return slot; }
	bool canUseItem(typeItem item) const { return slot == item;}


};


