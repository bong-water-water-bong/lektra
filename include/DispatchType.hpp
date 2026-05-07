#pragma once

#include <QHash>
#include <QString>

enum class DispatchType
{
    OnAppReady = 0,
    OnReady,
    OnFileOpen,
    OnFileClose,
    OnPageChanged,
    OnZoomChanged,
    OnLinkClicked,
    OnTextSelected,
    OnTabChanged,
    OnSearchStarted,
    OnSearchFinished,
    OnAnnotationAdded,
    OnAnnotationRemoved,
    OnRegionSelectionContextMenuRequested,
    OnTextSelectionContextMenuRequested,
    COUNT
};

static const QHash<QString, DispatchType> __dispatchEventMap = {
    {"OnAppReady", DispatchType::OnAppReady},
    {"OnReady", DispatchType::OnReady},
    {"OnFileOpen", DispatchType::OnFileOpen},
    {"OnFileClose", DispatchType::OnFileClose},
    {"OnPageChanged", DispatchType::OnPageChanged},
    {"OnZoomChanged", DispatchType::OnZoomChanged},
    {"OnLinkClicked", DispatchType::OnLinkClicked},
    {"OnTabChanged", DispatchType::OnTabChanged},
    {"OnTextSelected", DispatchType::OnTextSelected},
    {"OnPageChanged", DispatchType::OnPageChanged},
    {"OnSearchStarted", DispatchType::OnSearchStarted},
    {"OnSearchFinished", DispatchType::OnSearchFinished},
    {"OnAnnotationAdded", DispatchType::OnAnnotationAdded},
    {"OnAnnotationRemoved", DispatchType::OnAnnotationRemoved},
    {"OnRegionSelectionContextMenuRequested",
     DispatchType::OnRegionSelectionContextMenuRequested},
    {"OnTextSelectionContextMenuRequested",
     DispatchType::OnTextSelectionContextMenuRequested},
};

inline static DispatchType
stringToDispatchType(const QString &name)
{
    if (!__dispatchEventMap.contains(name))
        throw std::invalid_argument(
            QString("Unknown event name: %1").arg(name).toStdString());

    return __dispatchEventMap.value(name);
}

inline static QString
dispatchTypeToString(DispatchType type)
{
    for (auto it = __dispatchEventMap.constBegin();
         it != __dispatchEventMap.constEnd(); ++it)
    {
        if (it.value() == type)
            return it.key();
    }
    return QString("Unknown");
}
