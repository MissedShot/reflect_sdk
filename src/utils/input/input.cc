#include "../utils.hh"

namespace input {
    void init() {
        struct uinput_setup usetup;
        memset(&usetup, 0, sizeof(usetup));

        // setup mouse events.
        {
            fd_mouse = open(_("/dev/uinput"), O_WRONLY | O_NONBLOCK);

            /* enable mouse button left and relative events */
            ioctl(fd_mouse, UI_SET_EVBIT, EV_KEY);
            ioctl(fd_mouse, UI_SET_KEYBIT, BTN_LEFT);

            ioctl(fd_mouse, UI_SET_EVBIT, EV_REL);
            ioctl(fd_mouse, UI_SET_RELBIT, REL_X);
            ioctl(fd_mouse, UI_SET_RELBIT, REL_Y);

            usetup.id.bustype = BUS_USB;
            usetup.id.vendor = 0x1234; /* sample vendor */
            usetup.id.product = 0x5678; /* sample product */
            strcpy(usetup.name, _("USB-Mouse"));

            ioctl(fd_mouse, UI_DEV_SETUP, &usetup);
            ioctl(fd_mouse, UI_DEV_CREATE);
        }

        // setup keyboard events.
        {
            fd_keyboard = open(_("/dev/uinput"), O_WRONLY | O_NONBLOCK);

            /*
             * The ioctls below will enable the device that is about to be
             * created, to pass key events, in this case the space key.
             */
            ioctl(fd_keyboard, UI_SET_EVBIT, EV_KEY);
            ioctl(fd_keyboard, UI_SET_KEYBIT, KEY_SPACE);

            usetup.id.bustype = BUS_USB;
            usetup.id.vendor = 0x1234; /* sample vendor */
            usetup.id.product = 0x5678; /* sample product */
            strcpy(usetup.name, _("USB-Keyboard"));

            ioctl(fd_keyboard, UI_DEV_SETUP, &usetup);
            ioctl(fd_keyboard, UI_DEV_CREATE);
        }
    }

    void undo() {
        // destroy mouse fd.
        ioctl(fd_mouse, UI_DEV_DESTROY);
        close(fd_mouse);

        // destroy keyboard fd.
        ioctl(fd_keyboard, UI_DEV_DESTROY);
        close(fd_keyboard);
    }

    void emit_event(int fd, int type, int code, int val) {
        struct input_event ie;

        ie.type = type;
        ie.code = code;
        ie.value = val;

        /* timestamp values below are ignored */
        ie.time.tv_sec = 0;
        ie.time.tv_usec = 0;

        write(fd, &ie, sizeof(ie));
    }

    int fd_mouse{};
    int fd_keyboard{};
}