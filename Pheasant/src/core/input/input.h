#pragma once

#include "common.h"
#include "GLFW/glfw3.h"

/* From glfw3.h:
*  Key Codes mapped into Pheasant code system. 
*  Keyboard keys:
*/
#define PHS_KEY_SPACE              32
#define PHS_KEY_APOSTROPHE         39  /* ' */
#define PHS_KEY_COMMA              44  /* , */
#define PHS_KEY_MINUS              45  /* - */
#define PHS_KEY_PERIOD             46  /* . */
#define PHS_KEY_SLASH              47  /* / */
#define PHS_KEY_0                  48
#define PHS_KEY_1                  49
#define PHS_KEY_2                  50
#define PHS_KEY_3                  51
#define PHS_KEY_4                  52
#define PHS_KEY_5                  53
#define PHS_KEY_6                  54
#define PHS_KEY_7                  55
#define PHS_KEY_8                  56
#define PHS_KEY_9                  57
#define PHS_KEY_SEMICOLON          59  /* ; */
#define PHS_KEY_EQUAL              61  /* = */
#define PHS_KEY_A                  65
#define PHS_KEY_B                  66
#define PHS_KEY_C                  67
#define PHS_KEY_D                  68
#define PHS_KEY_E                  69
#define PHS_KEY_F                  70
#define PHS_KEY_G                  71
#define PHS_KEY_H                  72
#define PHS_KEY_I                  73
#define PHS_KEY_J                  74
#define PHS_KEY_K                  75
#define PHS_KEY_L                  76
#define PHS_KEY_M                  77
#define PHS_KEY_N                  78
#define PHS_KEY_O                  79
#define PHS_KEY_P                  80
#define PHS_KEY_Q                  81
#define PHS_KEY_R                  82
#define PHS_KEY_S                  83
#define PHS_KEY_T                  84
#define PHS_KEY_U                  85
#define PHS_KEY_V                  86
#define PHS_KEY_W                  87
#define PHS_KEY_X                  88
#define PHS_KEY_Y                  89
#define PHS_KEY_Z                  90
#define PHS_KEY_LEFT_BRACKET       91  /* [ */
#define PHS_KEY_BACKSLASH          92  /* \ */
#define PHS_KEY_RIGHT_BRACKET      93  /* ] */
#define PHS_KEY_GRAVE_ACCENT       96  /* ` */
#define PHS_KEY_WORLD_1            161 /* non-US #1 */
#define PHS_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define PHS_KEY_ESCAPE             256
#define PHS_KEY_ENTER              257
#define PHS_KEY_TAB                258
#define PHS_KEY_BACKSPACE          259
#define PHS_KEY_INSERT             260
#define PHS_KEY_DELETE             261
#define PHS_KEY_RIGHT              262
#define PHS_KEY_LEFT               263
#define PHS_KEY_DOWN               264
#define PHS_KEY_UP                 265
#define PHS_KEY_PAGE_UP            266
#define PHS_KEY_PAGE_DOWN          267
#define PHS_KEY_HOME               268
#define PHS_KEY_END                269
#define PHS_KEY_CAPS_LOCK          280
#define PHS_KEY_SCROLL_LOCK        281
#define PHS_KEY_NUM_LOCK           282
#define PHS_KEY_PRINT_SCREEN       283
#define PHS_KEY_PAUSE              284
#define PHS_KEY_F1                 290
#define PHS_KEY_F2                 291
#define PHS_KEY_F3                 292
#define PHS_KEY_F4                 293
#define PHS_KEY_F5                 294
#define PHS_KEY_F6                 295
#define PHS_KEY_F7                 296
#define PHS_KEY_F8                 297
#define PHS_KEY_F9                 298
#define PHS_KEY_F10                299
#define PHS_KEY_F11                300
#define PHS_KEY_F12                301
#define PHS_KEY_F13                302
#define PHS_KEY_F14                303
#define PHS_KEY_F15                304
#define PHS_KEY_F16                305
#define PHS_KEY_F17                306
#define PHS_KEY_F18                307
#define PHS_KEY_F19                308
#define PHS_KEY_F20                309
#define PHS_KEY_F21                310
#define PHS_KEY_F22                311
#define PHS_KEY_F23                312
#define PHS_KEY_F24                313
#define PHS_KEY_F25                314
#define PHS_KEY_KP_0               320
#define PHS_KEY_KP_1               321
#define PHS_KEY_KP_2               322
#define PHS_KEY_KP_3               323
#define PHS_KEY_KP_4               324
#define PHS_KEY_KP_5               325
#define PHS_KEY_KP_6               326
#define PHS_KEY_KP_7               327
#define PHS_KEY_KP_8               328
#define PHS_KEY_KP_9               329
#define PHS_KEY_KP_DECIMAL         330
#define PHS_KEY_KP_DIVIDE          331
#define PHS_KEY_KP_MULTIPLY        332
#define PHS_KEY_KP_SUBTRACT        333
#define PHS_KEY_KP_ADD             334
#define PHS_KEY_KP_ENTER           335
#define PHS_KEY_KP_EQUAL           336
#define PHS_KEY_LEFT_SHIFT         340
#define PHS_KEY_LEFT_CONTROL       341
#define PHS_KEY_LEFT_ALT           342
#define PHS_KEY_LEFT_SUPER         343
#define PHS_KEY_RIGHT_SHIFT        344
#define PHS_KEY_RIGHT_CONTROL      345
#define PHS_KEY_RIGHT_ALT          346
#define PHS_KEY_RIGHT_SUPER        347
#define PHS_KEY_MENU               348

/* From glfw3.h:
*  Modifier key codes:
*/
#define PHS_MOD_SHIFT              0x0001
#define PHS_MOD_CONTROL            0x0002
#define PHS_MOD_ALT                0x0004
#define PHS_MOD_SUPER              0x0008
#define PHS_MOD_CAPS_LOCK          0x0010
#define PHS_MOD_NUM_LOCK           0x0020

/* From glfw3.h:
*  Mouse button key codes:
*/
#define 	PHS_MOUSE_BUTTON_1        0
#define 	PHS_MOUSE_BUTTON_2        1
#define 	PHS_MOUSE_BUTTON_3        2
#define 	PHS_MOUSE_BUTTON_4        3
#define 	PHS_MOUSE_BUTTON_5        4
#define 	PHS_MOUSE_BUTTON_6        5
#define 	PHS_MOUSE_BUTTON_7        6
#define 	PHS_MOUSE_BUTTON_8        7
#define 	PHS_MOUSE_BUTTON_LAST     PHS_MOUSE_BUTTON_8
#define 	PHS_MOUSE_BUTTON_LEFT     PHS_MOUSE_BUTTON_1
#define 	PHS_MOUSE_BUTTON_RIGHT    PHS_MOUSE_BUTTON_2
#define 	PHS_MOUSE_BUTTON_MIDDLE   PHS_MOUSE_BUTTON_3


namespace Phs
{

// Keycode datatype
using key_int_t              = int;
// Keymode datatype (key/mouse modifiers - CTRL, SHIFT ...)
using key_mode_int_t         = int;
// Mouse button-code datatype
using mouse_button_key_int_t = int;
// Datatype for unicode-encoded character that was typed, shifted to 16 bits 
// (that's is propably more than enought)
using type_char_t            = char16_t;

/* Input system managing the current state of the input devices for 
*  single window. It's a part of the window implementation.
*/
class Input
{
public:
   Input() = default;
   Input(GLFWwindow* window);

   // set handled window
   void        setWindow(GLFWwindow* window);

   bool        isMouseButtonDown(mouse_button_key_int_t button);
   bool        isMouseButtonUp(mouse_button_key_int_t button);

   // TODO: Implement mousePos function returning a (x, y) vector
   double      mousePosX();
   double      mousePosY();

   bool        isKeyDown(key_int_t key);
   bool        isKeyUp(key_int_t key);

   // TODO: move it to a proper place (EventQueue)
   void        pollEvents();
private:
   using state_int_t = int;

   state_int_t mouseButtonState(mouse_button_key_int_t button);
   state_int_t keyState(key_int_t key);

   GLFWwindow* _window;
};

} // namespace Phs
