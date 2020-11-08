#include "Level_1.h"
#include "Field.h"
#include "enemies/Goblin.h"
#include "../Classes/cocos2d-x-imgui/CCImGuiLayer.h"
#include "../Classes/cocos2d-x-imgui/CCIMGUI.h"
#include "../Classes/cocos2d-x-imgui/imgui/imgui.h"
USING_NS_CC;

Scene* Level_1::createScene()
{
    return Level_1::create();
}

bool Level_1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto resolution = Label::create();
    resolution->setString(std::to_string(visibleSize.height) + " " + std::to_string(visibleSize.width));
    resolution->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - resolution->getContentSize().height + 10));
    this->addChild(resolution);

	this->addChild(Field::GetInstance()->CreateField(13,10), -1);
	Enemy * goblin = new Goblin();
	this->addChild(goblin, 10);
    this->scheduleUpdate();
    return true;
}

void Level_1::update(float dt) {
	//imgui();
}

void Level_1::imgui() {
	std::string layerName = "ImGUILayer";
	auto order = INT_MAX;
	auto layer = ImGuiLayer::create();
	//layer->setPosition(500, 350);
	this->addChild(layer, order, layerName);


	auto& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	auto sp = Sprite::create("HelloWorld.png");
	layer->addChild(sp);
	// add ui callbacks
	CCIMGUI::getInstance()->addCallback([=]() {
		ImGui::Text("Hello, world!");
		// create button with Sprite, auto pushID / popID with texture id
		CCIMGUI::getInstance()->imageButton(sp, ImVec2(0, 0));
		}, "hello");
	// remove ui callbacks to stop rendering
	CCIMGUI::getInstance()->removeCallback("hello");
	// add chinese font
	//io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("D:/CocosWorkspaces/TowerDefense/Classes/cocos2d-x-imgui/imgui/misc/fonts/Roboto-Medium.ttf", 16.0f, 0, io.Fonts->GetGlyphRangesDefault());

	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

	io.DisplaySize.x = 100;
	io.DisplaySize.y = 100;


	ImGui::NewFrame();
	ImGui::Begin("Window");
	ImGui::End();
	ImGui::EndFrame();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}