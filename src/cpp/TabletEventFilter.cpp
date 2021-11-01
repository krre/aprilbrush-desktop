#include "TabletEventFilter.h"
#include <QtGui>

bool TabletEventFilter::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::TabletPress ||
            event->type() == QEvent::TabletMove ||
            event->type() == QEvent::TabletRelease ||
            event->type() == QEvent::TabletEnterProximity ||
            event->type() == QEvent::TabletLeaveProximity) {
        auto tabletEvent = dynamic_cast<QTabletEvent*>(event);
        QVariantMap map;
        map["posX"] = tabletEvent->position().x();
        map["posY"] = tabletEvent->position().y();
        map["globalX"] = tabletEvent->globalPosition().x();
        map["globalY"] = tabletEvent->globalPosition().x();
        map["pressure"] = tabletEvent->pressure();
        map["press"] = event->type() == QEvent::TabletPress;
        map["release"] = event->type() == QEvent::TabletRelease;
        emit action(map);
        return true;
    }

    return QObject::eventFilter(obj, event);
}
