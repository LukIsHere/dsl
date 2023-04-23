/*
a great pice of code part of
dsl diffrent standard library
(wip as i write it so no links)

coded and delivered by L team
code by luk the oop programmer
debbugged by zoz the glaceon
(not really since he is just
pokemon in the game but we
can treat him as a rubber
duck right?)

it may break everything it touches
or something i dont know why
some people state that in their
comment thingies but yes

also no touch touch credits
without premission but if
you want you can modify code
itself so yes i hope it's
helpfull my guy and you
will be able to make great
things with it
*/
/*
    hello aditional info here
    this header file on linux
    requiers libx11-dev to be
    to be installed and have
    to be compiled with flags
    -lX11 -pthread
*/
#pragma once

#ifdef _WIN32
#include <windows.h>
#include <windowsx.h>
#else
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#endif

#include <stdint.h>
#include "mutex.hpp"
#include "ctx.hpp"
#include <functional>
#include <thread>


namespace dsl{
    struct mousePos{
        int32_t x;
        int32_t y;
    };

    class simpleWindow{
            //zmienne okna
            #ifdef _WIN32
            HWND hwnd;
            WNDCLASSEX wc;
            static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
        private:
            #else
            Display *display;
            int screen;
            Window window;
            XImage *image;
            GC gc;
            Atom wmDeleteMessage;
            #endif
            //watki i bezpieczenstwo
            Lock mutex;
            std::thread* eventThread;
            std::thread* graphicThread;
            std::thread* frameRateThread;
            //mysz
            mousePos lastMousePosition = {0, 0};
            mousePos currentMousePosition = {0, 0};
            //klawiatura i mysz
            bool mouseDown = false;
            bool keys[256] = { false };
            //performance
            bool noFrameRateLock;
            uint32_t frames = 0;
            uint32_t fps = 0;
            //dziala
            bool running = true;
            //kontekst
            dsl::ctx8888 ctx;
            //eventy
            std::function<void(dsl::ctx8888&)> frameF = [](dsl::ctx8888& ctx){};
            std::function<void(char)> keyDownF = [](char key){};
            std::function<void(char)> keyUpF = [](char key){};
            std::function<void(mousePos)> mouseDownF = [](mousePos mouse){};
            std::function<void(mousePos)> mouseUpF = [](mousePos mouse){};
            std::function<void(mousePos)> mouseMoveF = [](mousePos mouse){};
            bool isRunning();
        public:
            const uint32_t width;
            const uint32_t height;
            //konstruktor
            simpleWindow(uint32_t width,uint32_t height,const char* name = " ",bool transparent = false/*to-implement*/,bool borderless = false/*to-implement*/,bool noFrameRateLock = false);
            ~simpleWindow();
            //manipulacja rozmiarem
            void resize(uint32_t width,uint32_t height);//to-implement
            //no event will be called as long as you have this lock
            //just do WriteLock l(lock);
            //don't recomend trying to do it manually
            Lock& getLock(){return mutex;};
            int32_t getFps(){return fps;};
            //klawisze i mysz
            bool isKeyDown(char key){return keys[key];};
            mousePos getMousePositon(){return currentMousePosition;};
            bool isMouseDown(){return mouseDown;};
            //zamyka okno
            void close();
            //zwrace kontekst
            dsl::ctx8888& getCTX(){return ctx;};
            //dodaje callback
            simpleWindow& setFrame(std::function<void(dsl::ctx8888&)> frame);
            //nie jestem pewien czym char będzie na jakim systemie
            //bo narazie nie skończyłem implementacji ale kiedy klikniesz
            //guzik to informuje że to zrobiłeś
            simpleWindow& setKeyDown(std::function<void(char)> keyDown);
            simpleWindow& setKeyUp(std::function<void(char)> keyDown);
            simpleWindow& setMouseDown(std::function<void(mousePos)> mouseDown);
            simpleWindow& setMouseUp(std::function<void(mousePos)> mouseUp);
            simpleWindow& setMouseMove(std::function<void(mousePos)> mouseMove);
            //możesz wywołąć na oknie
            void move(mousePos p);//to implement
            //sprawdza czy okno jest otwarte
            
            //czeka na zamkniecie okna
            void wait();
            //wywoluje event
            void tframe(){
                WriteLock lock(mutex);
                frameF(ctx);
            }
            void tkeyDown(char c){
                WriteLock lock(mutex);
                if(!keys[c]){
                    keys[c] = true;
                    keyDownF(c);
                }
            };
            void tkeyUp(char c){
                WriteLock lock(mutex);
                if(keys[c]){
                    keys[c] = false;
                    keyUpF(c);
                }
            };
            void tmouseDown(mousePos p){
                WriteLock lock(mutex);
                mouseDown = true;
                currentMousePosition = p;
                mouseDownF(p);
            };
            void tmouseUp(mousePos p){
                WriteLock lock(mutex);
                mouseDown = false;
                currentMousePosition = p;
                mouseUpF(p);
            };
            void tmouseMove(mousePos p){
                WriteLock lock(mutex);
                currentMousePosition = p;
                mouseMoveF(p);
            };
    };
}



//definicje

#ifdef _WIN32

inline dsl::simpleWindow::simpleWindow(uint32_t width,uint32_t height,const char* name,bool transparent,bool borderless):ctx(width,height),width(width),height(height){
    

    eventThread = new std::thread([&](){
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

        HWND hwnd = CreateWindowEx(
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
        UpdateWindow(hwnd);
        
        graphicThread = new std::thread([&](){
            while(isRunning()){
                std::thread time([](){
                    std::this_thread::sleep_for(std::chrono::milliseconds(16));
                });
                tframe();
                InvalidateRect(hwnd,nullptr,0);
                time.join();
            }
            
        });
        
        MSG msg = { 0 };
        while (GetMessage(&msg, NULL, 0, 0) > 0&&isRunning()) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        
    });
}

inline dsl::simpleWindow::~simpleWindow(){
    close();
    eventThread->join();
    UnregisterClass("simpleWindowClass", GetModuleHandle(NULL));

}

inline void dsl::simpleWindow::close(){
    WriteLock lock(mutex);
    if(running==false)return;
    running = false;
    lock.unlock();
    graphicThread->join();
    lock.lock();
    DestroyWindow(hwnd);
}

inline LRESULT CALLBACK dsl::simpleWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    simpleWindow* pThis = (simpleWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    switch (uMsg) {
        case WM_DESTROY:
            pThis->close();
        case WM_PAINT: {
            //odwierza obraz
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            uint32_t* framebuffer = (uint32_t*)pThis->getCTX().getData();

            BITMAPINFO bmi = {};
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = pThis->width;
            bmi.bmiHeader.biHeight = -(int32_t)pThis->height;
            bmi.bmiHeader.biPlanes = 1;
            bmi.bmiHeader.biBitCount = 32;
            bmi.bmiHeader.biCompression = BI_RGB;
            bmi.bmiHeader.biSizeImage = pThis->width * pThis->height * sizeof(uint32_t);
            StretchDIBits(hdc,0,0,pThis->width,pThis->height,
                0,0,pThis->width,pThis->height,
                framebuffer,&bmi,DIB_RGB_COLORS,SRCCOPY
            );

            ReleaseDC(hwnd,hdc);

            EndPaint(hwnd, &ps);
            }
            break;
        case WM_KEYDOWN:
            tkeyDown((char)wParam);
            break;
        case WM_KEYUP:
            tkeyUp((char)wParam);
            break;
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
            pThis->tmouseDown({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            pThis->tmouseUp({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
            break;

        case WM_MOUSEMOVE:
            pThis->tmouseMove({ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) });
            break;
        default:
             return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
   
}

inline void dsl::simpleWindow::move(mousePos pos){
    SetWindowPos(hwnd, NULL, pos.x, pox.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
}

#else

inline dsl::simpleWindow::simpleWindow(uint32_t width,uint32_t height,const char* name,bool transparent,bool borderless,bool noFrameRateLockB):ctx(width,height),width(width),height(height){
    noFrameRateLock = noFrameRateLockB;
    display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        throw std::runtime_error("Could not open display");
    }

    screen = DefaultScreen(display);
    window = XCreateWindow(display, RootWindow(display, screen), 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, 0, nullptr);

    //stały rozmiar okna
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

    wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    if (window == None) {
        throw std::runtime_error("Could not create window");
        XCloseDisplay(display);
    }

    XStoreName(display, window, name);

    XSelectInput(display, window, StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    XMapWindow(display, window);

    XEvent eve;
    do {
        XNextEvent(display, &eve);
    } while (eve.type != MapNotify || eve.xmap.event != window);

    image = XCreateImage(display, DefaultVisual(display, screen), 24, ZPixmap, 0, (char *)ctx.getData(), width, height, 8, 0);

    gc = XCreateGC(display, window, 0, nullptr);
    frameRateThread = new std::thread([this](){
        while (isRunning()){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            WriteLock lock(this->mutex);
            fps = frames;
            frames = 0;
        }
    });
    graphicThread = new std::thread([&](){
        if(noFrameRateLock){
            while (isRunning()){
                WriteLock lock(this->mutex);
                frameF(this->ctx);
                //odswierza okno
                XPutImage(this->display, this->window, this->gc, this->image, 0, 0, 0, 0, this->width, this->height);
                XFlush(this->display);
                frames++;
                lock.unlock();
            }
        }else{
            while (isRunning()){
                std::thread time([](){
                    std::this_thread::sleep_for(std::chrono::milliseconds(16));
                });
                WriteLock lock(this->mutex);
                frameF(this->ctx);
                //odswierza okno
                XPutImage(this->display, this->window, this->gc, this->image, 0, 0, 0, 0, this->width, this->height);
                XFlush(this->display);
                frames++;
                lock.unlock();
                time.join();
            }
        }
        
    });

    eventThread = new std::thread([&](){
        XEvent event;
        while (isRunning()) {
            XNextEvent(display, &event);
            switch (event.type) {
                case KeyPress:{
                    char key = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
                    tkeyDown(key);
                    break;
                }
                case KeyRelease:{
                    char key = XkbKeycodeToKeysym(display, event.xkey.keycode, 0, 0);
                    tkeyUp(key);
                    break;
                }
                case ButtonPress: {
                    lastMousePosition.x = event.xbutton.x;
                    lastMousePosition.y = event.xbutton.y;
                    tmouseDown(lastMousePosition);
                    break;
                }
                case ButtonRelease: {
                    lastMousePosition.x = event.xbutton.x;
                    lastMousePosition.y = event.xbutton.y;
                    tmouseUp(lastMousePosition);
                    break;
                }
                case MotionNotify: {
                    currentMousePosition.x = event.xmotion.x;
                    currentMousePosition.y = event.xmotion.y;
                    tmouseMove(currentMousePosition);
                    lastMousePosition.x = currentMousePosition.x;
                    lastMousePosition.y = currentMousePosition.y;
                    break;
                }
                case ClientMessage:
                    if (event.xclient.message_type == XInternAtom(display, "WM_PROTOCOLS", True)
                        && (Atom)event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
                        close();
                        return;
                        break;
                    }
            }
        }
    });
    
};
inline dsl::simpleWindow::~simpleWindow(){
    close();
    eventThread->join();
}

inline void dsl::simpleWindow::close(){
    WriteLock lock(mutex);
    if(running==false)return;
    running = false;
    lock.unlock();
    graphicThread->join();
    frameRateThread->join();
    lock.lock();
    XDestroyWindow(display, window);
    image->data = nullptr;
    XDestroyImage(image);
    XFreeGC(display, gc);
    XCloseDisplay(display);
}

inline void dsl::simpleWindow::move(mousePos pos){
    XMoveWindow(display, window, pos.x, pos.y);
}

#endif

inline bool dsl::simpleWindow::isRunning(){
    WriteLock lock(mutex);
    return running;
}

inline dsl::simpleWindow& dsl::simpleWindow::setFrame(std::function<void(dsl::ctx8888&)> frame){
    WriteLock lock(mutex);
    this->frameF = frame;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setKeyDown(std::function<void(char)> keyDown){
    WriteLock lock(mutex);
    this->keyDownF = keyDown;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setKeyUp(std::function<void(char)> keyUp){
    WriteLock lock(mutex);
    this->keyUpF = keyUp;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseDown(std::function<void(mousePos)> mouseDown){
    WriteLock lock(mutex);
    this->mouseDownF = mouseDown;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseUp(std::function<void(mousePos)> mouseUp){
    WriteLock lock(mutex);
    this->mouseUpF = mouseUp;
    return *this;
};
inline dsl::simpleWindow& dsl::simpleWindow::setMouseMove(std::function<void(mousePos)> mouseMove){
    WriteLock lock(mutex);
    this->mouseMoveF = mouseMove;
    return *this;
};

inline void dsl::simpleWindow::wait(){
    while (true){
        if(!isRunning())return;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}