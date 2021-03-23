#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include "scene.h"

class View : public QGraphicsView {
    Q_OBJECT

    public:
        View(Scene* s, QWidget* parent);
        ~View();
        Scene* get_scene();
        void resizeEvent(QResizeEvent* event) override;

    private:
        Scene* scene;
};

#endif
