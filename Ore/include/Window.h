#ifndef ORE_WINDOW__H_
#define ORE_WINDOW__H_

#include "IWindow.h"


class GLFWwindow;
class Window : public IWindow
{
public:
    Window(int width, int height, std::string name);
    virtual ~Window() override;

    virtual void Close() override;
    virtual bool IsOpen() override;
    virtual void Present() override;

protected:
    virtual void Open() override;

private:
    GLFWwindow* m_pWindow;
};

void FrameBufferSizeCallback(GLFWwindow* pWindow, int width, int height);

#endif //!ORE_WINDOW__H_