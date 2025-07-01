#include <Geode/Geode.hpp>
#include "./Keybinds/KeybindRegister.hpp"

using namespace geode::prelude;

$execute {
    auto application = CCApplication::get(); // Get application

    /* If true, means that no controller is connected */
    if (!application->getControllerConnected()) {
        /* Set controller controls to true */
        application->m_pControllerHandler->m_controllerConnected = true;
        application->m_pController2Handler->m_controllerConnected = true;
        application->m_bControllerConnected = true;

        auto modId = Mod::get()->getID();

        std::vector<BindableInfo> bindables = {
            // Normal buttons
            {modId + "-xbutton", "X", KEY_X, CONTROLLER_X},
            {modId + "-ybutton", "Y", KEY_Y, CONTROLLER_Y},
            {modId + "-abutton", "A", KEY_A, CONTROLLER_A},
            {modId + "-bbutton", "B", KEY_B, CONTROLLER_B},

            // Specials
            {modId + "-startbutton", "Start", KEY_Enter, CONTROLLER_Start},

            {modId + "-leftbutton", "Left", KEY_ArrowLeft, CONTROLLER_Left},
            {modId + "-rightbutton", "Right", KEY_ArrowRight, CONTROLLER_Right},
            {modId + "-upbutton", "Up", KEY_ArrowUp, CONTROLLER_RTHUMBSTICK_UP},
            {modId + "-downbutton", "Down", KEY_ArrowDown, CONTROLLER_RTHUMBSTICK_DOWN}};

        auto keybindRegister = new KeybindRegister();

        keybindRegister->loadKeybinds(bindables);
        keybindRegister->listenEvents(bindables);
    } else {
        /* If a controller is connected */
        log::info("A controller is connected, this mod will not work !");
    }
    
}