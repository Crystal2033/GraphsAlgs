#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H
#include <QtWidgets>
#include <QMouseEvent>

class ContextMenu
{
private:
    QMenu* menu_ptr;
protected:
virtual void contextMenuEvent(QContextMenuEvent* menu_ev)
{
    menu_ptr->exec(menu_ev->globalPos());
}
public:
ContextMenu()
{
    menu_ptr = new QMenu();
    menu_ptr->addAction("Set START.");
    menu_ptr->addAction("Set END.");
}
};

#endif // CONTEXTMENU_H
