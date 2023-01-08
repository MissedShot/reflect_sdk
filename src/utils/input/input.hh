#pragma once

// ref: https://www.kernel.org/doc/html/v4.12/input/uinput.html#
namespace input {
    void init();
    void undo();

    void emit_event(int fd, int type, int code, int val);

    extern int fd_mouse;
    extern int fd_keyboard;
}