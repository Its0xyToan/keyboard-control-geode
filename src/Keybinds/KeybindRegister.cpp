#include "KeybindRegister.hpp"
#include <geode.custom-keybinds/include/Keybinds.hpp>

using namespace keybinds;
using namespace geode::prelude;

KeybindRegister *KeybindRegister::create()
{
    auto ret = new KeybindRegister();
    if (ret)
    {
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void KeybindRegister::loadKeybinds(std::vector<BindableInfo>& bindables)
{
    auto manager = BindManager::get();

    for (const auto &bindable : bindables)
    {
        /* Creates a new binding with an ID, a name, a description, and a Category */
        manager->registerBindable({
            bindable.id,
            bindable.name + " Button",
            "The key to simulate the " + bindable.name + " button on the controller",
            {Keybind::create(bindable.key, Modifier::Control)}, // The keybinds will always be ctrl + (x) by default
            "Keyboard Control"
        });

        log::info("Registered keybind: {}", bindable.id);
    }
}

void KeybindRegister::listenEvents(std::vector<BindableInfo>& bindables) {
    for (const auto &bindable : bindables)
    {
        new EventListener([=](InvokeBindEvent *event)
        {
            if (event->isDown()) {
                /* Executes if we press the button */
                CCKeyboardDispatcher::get()->dispatchKeyboardMSG(bindable.controllerKey, true, false);
                log::debug("Bind '{}' Pressed. Simulating controller key down: {}", bindable.id, static_cast<int>(bindable.controllerKey));
            } else {
                /* Executes if we release the button */
                CCKeyboardDispatcher::get()->dispatchKeyboardMSG(bindable.controllerKey, false, false);
                log::debug("Bind '{}' Released. Simulating controller key up: {}", bindable.id, static_cast<int>(bindable.controllerKey));
            }
            return ListenerResult::Propagate;
        }, InvokeBindFilter(nullptr, bindable.id));
    }
}