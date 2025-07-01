#pragma once
#include <Geode/Geode.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>

struct BindableInfo {
    std::string id;
    std::string name;
    cocos2d::enumKeyCodes key;
    cocos2d::enumKeyCodes controllerKey;
};

struct KeybindRegister {
    public:
        static KeybindRegister* create();

        void loadKeybinds(std::vector<BindableInfo>& bindables);
        void listenEvents(std::vector<BindableInfo>& bindables);
};