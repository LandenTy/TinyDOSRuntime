#ifndef GAMEPAD_H
#define GAMEPAD_H

typedef struct {
    int x;
    int y;
    int button1;
    int button2;
} JoystickState;

void joystick_init(void);
void joystick_read(JoystickState* js);

#endif
