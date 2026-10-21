#include "incl.h"

// Simple example mod
// Simple example mod
// Simple example mod

// we're gonna hook the main menu (MenuLayer)
// and add a "Hello World" text in the top corner
// and replace the "News" button with an alert

// pointer to the original function
bool (*MenuLayer_initO)(MenuLayer*);

// our custom version of init
bool MenuLayer_initH(MenuLayer* self) {

    // always call the original first
    if(!MenuLayer_initO(self)) 
        return false;

    // get screen size
    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    // make a text label
    auto label = CCLabelBMFont::create("Hello World", "bigFont.fnt");

    // make it a bit smaller and put it in the top corner
    label->setScale(0.8f);
    label->setAnchorPoint({0, 1});
    label->setPosition({5, winSize.height - 5});

    // add it to the menu
    self->addChild(label, 100);

    return true;
}


// ==============================
// replacing a button
// ==============================

// this one completely replaces the original function
// no need to call the original here

void MenuLayer_onNews() {

    // when "News" is clicked, show a popup instead
    FLAlertLayer::create(
        nullptr,
        "News",
        "This is an test",
        "OK",
        nullptr,
        300
    )->show();
}


// ==============================
// entry point (runs when mod loads)
// ==============================

[[gnu::constructor]]
void mod_init() {

    // you usually get these names from tools like
    // ghidra or ida (or just from Addr.txt if you have it)

    // hook the menu init
    hook(
        "_ZN9MenuLayer4initEv",
        MenuLayer_initH,
        MenuLayer_initO
    );

    // hook the "News" button
    _hook(
        "_ZN9MenuLayer6onNewsEPN7cocos2d8CCObjectE",
        MenuLayer_onNews
    );
}