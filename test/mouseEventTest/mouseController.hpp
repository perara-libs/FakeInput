#ifndef TEST_MOUSECONTROLLER_HPP
#define TEST_MOUSECONTROLLER_HPP

#include "config.hpp"

#include <QDialog>
#include <QSpinBox>

class MouseController : public QDialog
{
    Q_OBJECT

public:
    MouseController();
    virtual ~MouseController() {}

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

#ifdef UNIX
    bool x11Event(XEvent* event);
#elif WIN32
    bool winEvent(MSG* message, long* result);
#endif

public slots:
    void setMousePos();

private:
    QSpinBox* xPos_;
    QSpinBox* yPos_;
};


#endif