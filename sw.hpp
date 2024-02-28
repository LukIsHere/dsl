#pragma once

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#else
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#endif

#include <functional>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <iostream>

#include <stdint.h>

#include "mutex.hpp"
#include "ctx.hpp"



namespace dsl{
    struct mousePos{
        int32_t x;
        int32_t y;
    };
    enum mouseButton{
        left=0,middle=1,right=2
    };

    class simpleWindow{
            //zmienne okna
            #ifdef _WIN32
            HWND hwnd;
            WNDCLASSEX wc;
            char getChar(WPARAM wParam);
            static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        public:
            void _winHandleEvents(UINT uMsg, WPARAM wParam, LPARAM lParam);
        private:
            #else
            Display *display;
            int screen;
            Window window;
            XImage *image;
            GC gc;
            Atom wmDeleteMessage;
            #endif
            //mysz
            mousePos lastMousePosition = {0, 0};
            //klawiatura i mysz
            bool mouseBtns[3] = { false };
            
            bool keys[256] = { false };
            //dziala
            bool running = true;
            //kontekst
            dsl::ctx ctx;
            //eventy
            std::function<void(dsl::ctx&)> frameF = [](dsl::ctx& ctx){};
            std::function<void(char)> keyDownF = [](char key){};
            std::function<void(char)> keyUpF = [](char key){};
            std::function<void(mousePos,mouseButton)> mouseDownF = [](mousePos mouse,mouseButton button){};
            std::function<void(mousePos,mouseButton)> mouseUpF = [](mousePos mouse,mouseButton button){};
            std::function<void(mousePos)> mouseMoveF = [](mousePos mouse){};
            
            void triggerKeyDown(char key);
            void triggerKeyUp(char key);
            void triggerMouseDown(mousePos mouse,mouseButton button);
            void triggerMouseUp(mousePos mouse,mouseButton button);
            void triggerMouseMove(mousePos mouse);
            bool isRunning = true;
        public:
            const uint32_t width;
            const uint32_t height;
            
            //konstruktor
            simpleWindow(uint32_t width,uint32_t height,const char* name = " ");
            ~simpleWindow();
            //klawisze i mysz

            //to-reinplement
            bool isKeyDown(char key){return keys[key];};
            mousePos getMousePositon(){return lastMousePosition;};
            bool isMouseButtonDown(mouseButton button=left){return mouseBtns[button];};
            //zwrace kontekst


            //dodaje callback
            simpleWindow& setFrame(std::function<void(dsl::ctx&)> frame);
            simpleWindow& setKeyDown(std::function<void(char)> keyDown);
            simpleWindow& setKeyUp(std::function<void(char)> keyDown);
            simpleWindow& setMouseDown(std::function<void(mousePos,mouseButton)> mouseDown);
            simpleWindow& setMouseUp(std::function<void(mousePos,mouseButton)> mouseUp);
            simpleWindow& setMouseMove(std::function<void(mousePos)> mouseMove);
            //czeka na zamkniecie okna
            void start();
        private:
            void drawBuffer();
            void handleEvents();
    };
}



//definicje

#ifdef _WIN32

inline dsl::simpleWindow::simpleWindow(uint32_t width,uint32_t height,const char* name):ctx(width,height),width(width),height(height){
    

    HINSTANCE hInstance = GetModuleHandle(NULL);

    wc = {0};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "simpleWindowClass";
    RegisterClassEx(&wc);

    RECT windowRect = { 0, 0, (int32_t)this->width, (int32_t)this->height };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    int adjustedWidth = windowRect.right - windowRect.left;
    int adjustedHeight = windowRect.bottom - windowRect.top;

    hwnd = CreateWindowEx(
        0,
        "simpleWindowClass",
        name,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, adjustedWidth, adjustedHeight,
        NULL, NULL, hInstance, NULL
    );

    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style &= ~WS_THICKFRAME;
    SetWindowLongPtr(hwnd, GWL_STYLE, style);
        
    SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);
        
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    //UpdateWindow(hwnd);
}

inline dsl::simpleWindow::~simpleWindow(){
    UnregisterClass("simpleWindowClass", GetModuleHandle(NULL));
    DestroyWindow(hwnd);

}

inline LRESULT CALLBACK dsl::simpleWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    simpleWindow* pThis = (simpleWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    pThis->_winHandleEvents(uMsg, wParam, lParam);
    switch (uMsg) {
        case WM_DESTROY:
        case WM_PAINT:
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_MOUSEMOVE:
        default:
             return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
   
}

void dsl::simpleWindow::_winHandleEvents(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        isRunning = false;
        break;
    case WM_PAINT: {
        //odwierza obraz
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        uint32_t* framebuffer = (uint32_t*)ctx.getData();

        BITMAPINFO bmi = {};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -(int32_t)height;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biSizeImage = width * height * sizeof(uint32_t);
        StretchDIBits(hdc, 0, 0, width, height,
            0, 0, width, height,
            framebuffer, &bmi, DIB_RGB_COLORS, SRCCOPY
        );

        ReleaseDC(hwnd, hdc);

        EndPaint(hwnd, &ps);
    }
        break;
    case WM_KEYDOWN:
        triggerKeyDown(getChar(wParam));
        break;
    case WM_KEYUP:
        triggerKeyUp(getChar(wParam));
        break;
    case WM_LBUTTONDOWN:
        triggerMouseDown({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, left);
        break;
    case WM_RBUTTONDOWN:
        triggerMouseDown({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, right);
        break;
    case WM_MBUTTONDOWN:
        triggerMouseDown({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) },middle);
        break;

    case WM_LBUTTONUP:
        triggerMouseUp({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, left);
        break;
    case WM_RBUTTONUP:
        triggerMouseUp({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }, right);
        break;
    case WM_MBUTTONUP:
        triggerMouseUp({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) },middle);
        break;

    case WM_MOUSEMOVE:
        triggerMouseMove({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
        break;
    }
}

void dsl::simpleWindow::handleEvents() {
    MSG msg = { 0 };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void dsl::simpleWindow::drawBuffer() {
    frameF(this->ctx);

    InvalidateRect(hwnd, nullptr, 0);
}

char dsl::simpleWindow::getChar(WPARAM wParam) {
    char ch = '\0';
    BYTE keyboardState[256];
    GetKeyboardState(keyboardState);
    WORD wVirtualKeyCode = static_cast<WORD>(wParam);
    WORD wScanCode = MapVirtualKey(wVirtualKeyCode, MAPVK_VK_TO_VSC);
    int result = ToAscii(wVirtualKeyCode, wScanCode, keyboardState, reinterpret_cast<LPWORD>(&ch), 0);
    return ch;
}

#else

inline dsl::simpleWindow::simpleWindow(uint32_t width,uint32_t height,const char* name):ctx(width,height),width(width),height(height){
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw std::runtime_error("Could not open display");
    }

    screen = DefaultScreen(display);
    window = XCreateWindow(display, RootWindow(display, screen), 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, 0, nullptr);

    //non resizable
    unsigned int borderWidth;
    Window rootWindow;
    int x, y;
    uint32_t depth;
    XGetGeometry(display, window, &rootWindow, &x, &y, &width, &height, &borderWidth, &depth);
    
    XSizeHints sizeHints;
    sizeHints.flags = PMinSize | PMaxSize;
    sizeHints.min_width = sizeHints.max_width = width + 2 * borderWidth;
    sizeHints.min_height = sizeHints.max_height = height + 2 * borderWidth;
    XSetWMNormalHints(display, window, &sizeHints);

    //close prevention
    wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    if (window == None) {
        XCloseDisplay(display);
        throw std::runtime_error("Could not create window");
    }

    XStoreName(display, window, name);
    XSelectInput(display, window, StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    XMapWindow(display, window);

    //wait till window map
    XEvent eve;
    do {
        XNextEvent(display, &eve);
    } while (eve.type != MapNotify || eve.xmap.event != window);

    //graphic context stuff
    image = XCreateImage(display, DefaultVisual(display, screen), 24, ZPixmap, 0, (char *)ctx.getData(), width, height, 8, 0);
    gc = XCreateGC(display, window, 0, nullptr);
    
};

void dsl::simpleWindow::drawBuffer(){
    frameF(this->ctx);
    
    XPutImage(this->display, this->window, this->gc, this->image, 0, 0, 0, 0, this->width, this->height);
    XFlush(this->display);
}

void dsl::simpleWindow::handleEvents(){
        XEvent event;
        while (XPending(display) > 0) {
            XNextEvent(display, &event);
            switch (event.type) {
                case KeyPress:{
                    char key = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
                    triggerKeyDown(key);
                    break;
                }
                case KeyRelease:{
                    char key = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
                    triggerKeyUp(key);
                    break;
                }
                case ButtonPress: {
                    //event.xbutton.button 1 - left,2 - middle, 3 - right
                    lastMousePosition.x = event.xbutton.x;
                    lastMousePosition.y = event.xbutton.y;
                    triggerMouseDown(lastMousePosition,mouseButton(event.xbutton.button-1));
                    break;
                }
                case ButtonRelease: {
                    //event.xbutton.button 1 - left,2 - middle, 3 - right
                    lastMousePosition.x = event.xbutton.x;
                    lastMousePosition.y = event.xbutton.y;
                    triggerMouseUp(lastMousePosition,mouseButton(event.xbutton.button-1));
                    break;
                }
                case MotionNotify: {
                    lastMousePosition.x = event.xmotion.x;
                    lastMousePosition.y = event.xmotion.y;
                    triggerMouseMove(lastMousePosition);
                    break;
                }
                case ClientMessage:
                    if (event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", True)
                        && (Atom)event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
                        isRunning = false;
                        return;
                        break;
                    }
            }
        }
    }
inline dsl::simpleWindow::~simpleWindow(){
    XDestroyWindow(display, window);
    image->data = nullptr;
    XDestroyImage(image);
    XFreeGC(display, gc);
    XCloseDisplay(display);
}

#endif

inline dsl::simpleWindow& dsl::simpleWindow::setFrame(std::function<void(dsl::ctx&)> frame){
    this->frameF = frame;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setKeyDown(std::function<void(char)> keyDown){
    this->keyDownF = keyDown;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setKeyUp(std::function<void(char)> keyUp){
    this->keyUpF = keyUp;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseDown(std::function<void(mousePos,mouseButton)> mouseDown){
    this->mouseDownF = mouseDown;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseUp(std::function<void(mousePos,mouseButton)> mouseUp){
    this->mouseUpF = mouseUp;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseMove(std::function<void(mousePos)> mouseMove){
    this->mouseMoveF = mouseMove;
    return *this;
};

void dsl::simpleWindow::triggerKeyDown(char key){
    keys[key] = true;
    keyDownF(key);
};
void dsl::simpleWindow::triggerKeyUp(char key){
    keys[key] = false;
    keyUpF(key);
};
void dsl::simpleWindow::triggerMouseDown(mousePos mouse,mouseButton button){
    mouseBtns[button] = true;
    mouseDownF(mouse,button);
};
void dsl::simpleWindow::triggerMouseUp(mousePos mouse,mouseButton button){
    mouseBtns[button] = false;
    mouseUpF(mouse,button);
};
void dsl::simpleWindow::triggerMouseMove(mousePos mouse){
    mouseMoveF(mouse);
};

inline void dsl::simpleWindow::start(){
    using namespace std::chrono;
    auto lastFrameTime = high_resolution_clock::now();
    constexpr auto frameDuration = microseconds(16666);

    while (isRunning) {
        auto currentFrameTime = high_resolution_clock::now();
        auto deltaTime = duration_cast<microseconds>(currentFrameTime - lastFrameTime);

        if (deltaTime < frameDuration) {
            std::this_thread::sleep_for(frameDuration - deltaTime);
            continue;
        }

        lastFrameTime = currentFrameTime;
        
        drawBuffer();
        handleEvents();
        
    }
}