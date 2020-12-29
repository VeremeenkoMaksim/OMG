#include "UIClass.h"
#include "StoreUI.h"
USING_NS_CC;

Node * UIClass::CreateStoreUI() {

	return StoreUI::Create();
}