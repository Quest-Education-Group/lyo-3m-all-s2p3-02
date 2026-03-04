#ifndef ORE_EVENT_MANAGER__H_
#define ORE_EVENT_MANAGER__H_

#include "Define.h"
#include "Event.hpp"
#include "Window.h"

enum class GamepadId
{
    GAMEPAD_1,
    GAMEPAD_2,
    GAMEPAD_MAX
};

enum class EventInput
{
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_ESCAPE,
    KEY_SPACE,
    KEY_ENTER,
    KEY_SHIFT,
    KEY_CTRL,
    KEY_ALT,
    KEY_TAB,

    MOUSE_LEFT,
    MOUSE_RIGHT,
    MOUSE_MIDDLE,
    MOUSE_X1,
    MOUSE_X2,

    GAMEPAD_A,
    GAMEPAD_B,
    GAMEPAD_X,
    GAMEPAD_Y,
    GAMEPAD_LEFT_BUMPER,
    GAMEPAD_RIGHT_BUMPER,
    GAMEPAD_BACK,
    GAMEPAD_START,
    GAMEPAD_LEFT_STICK,
    GAMEPAD_RIGHT_STICK,
    GAMEPAD_DPAD_UP,
    GAMEPAD_DPAD_DOWN,
    GAMEPAD_DPAD_LEFT,
    GAMEPAD_DPAD_RIGHT,
    GAMEPAD_LEFT_TRIGGER,
    GAMEPAD_RIGHT_TRIGGER,
    GAMEPAD_LEFT_THUMB_UP,
    GAMEPAD_LEFT_THUMB_DOWN,
    GAMEPAD_LEFT_THUMB_LEFT,
    GAMEPAD_LEFT_THUMB_RIGHT,
    GAMEPAD_RIGHT_THUMB_UP,
    GAMEPAD_RIGHT_THUMB_DOWN,
    GAMEPAD_RIGHT_THUMB_LEFT,
    GAMEPAD_RIGHT_THUMB_RIGHT,
};

enum class EventAction
{
    PRESS,
    RELEASE,
    HOLD,
    DOUBLE_CLICK,
    WHEEL_UP,
    WHEEL_DOWN,
    MOVE,
    DRAG,
    FOCUS,
    BLUR,
    CHANGE,
    UNKNOWN
};

ENUM_CLASS_FLAGS(GamepadId)
ENUM_CLASS_FLAGS(EventInput)
ENUM_CLASS_FLAGS(EventAction)

namespace EventManager
{

    static bool GetKey(EventInput key, EventAction event);

    static GamepadId AddGamepad();
    static std::string_view GetGamepadName(GamepadId id);
    static std::vector<float> GetGamepadAxes(GamepadId);
    static bool GetButton(GamepadId id, EventInput button, EventAction event);

    static Event<void(GamepadId)> gamepadConnected;
    static Event<void(GamepadId)> gamepadDisconnected;

};

#endif // !ORE_EVENT_MANAGER__H_
