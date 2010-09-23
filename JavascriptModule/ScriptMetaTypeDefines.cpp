/**
 *  For conditions of distribution and use, see copyright notice in license.txt
 *
 *  @file   ScriptMetaTypeDefines.cpp
 *  @brief  Registration of Naali Core API to Javascript.
 */

#include "StableHeaders.h"
#include "ScriptMetaTypeDefines.h"

#include "Entity.h"
#include "QtInputMouseEvent.h"
#include "QtInputKeyEvent.h"
#include "UiProxyWidget.h"
#include "Frame.h"
#include "Console.h"

#include "QtInputMouseEvent.h"
#include "QtInputKeyEvent.h"
#include "EntityAction.h"

#include <QUiLoader>
#include <QFile>

//! Qt defines
Q_SCRIPT_DECLARE_QMETAOBJECT(QPushButton, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QWidget, QWidget*)

//! Naali input defines
Q_DECLARE_METATYPE(MouseEvent*)
Q_DECLARE_METATYPE(KeyEvent*)

//! Naali Ui defines
Q_DECLARE_METATYPE(UiProxyWidget*);

//! Naali Scene defines.
Q_DECLARE_METATYPE(Scene::Entity*);
Q_DECLARE_METATYPE(EntityAction*);
Q_DECLARE_METATYPE(AttributeChange*);
Q_DECLARE_METATYPE(IComponent*);

//! Naali core API object defines.
Q_DECLARE_METATYPE(Frame*);
Q_DECLARE_METATYPE(ScriptConsole*);
Q_DECLARE_METATYPE(Command*);
Q_DECLARE_METATYPE(DelayedSignal*);

void ReqisterQtMetaTypes(QScriptEngine *engine)
{
    QScriptValue object = engine->scriptValueFromQMetaObject<QPushButton>();
    engine->globalObject().setProperty("QPushButton", object);
    object = engine->scriptValueFromQMetaObject<QWidget>();
    engine->globalObject().setProperty("QWidget", object);
    
    /*object = engine->newFunction(LoadWidgetFromFile, 2);
    engine->globalObject().setProperty("LoadWidgetFromFile", object);*/
}

void ReqisterInputMetaTypes(QScriptEngine *engine)
{
    qScriptRegisterQObjectMetaType<MouseEvent*>(engine);
    qScriptRegisterQObjectMetaType<KeyEvent*>(engine);

    qRegisterMetaType<KeyEvent::EventType>("KeyEvent::EventType");
    qRegisterMetaType<MouseEvent::EventType>("MouseEvent::EventType");
    qRegisterMetaType<MouseEvent::MouseButton>("MouseEvent::MouseButton");
}

void ReqisterSceneMetaTypes(QScriptEngine *engine)
{
    qScriptRegisterQObjectMetaType<Scene::Entity*>(engine);
    qScriptRegisterQObjectMetaType<EntityAction*>(engine);
    qScriptRegisterQObjectMetaType<AttributeChange*>(engine);
    qScriptRegisterQObjectMetaType<IComponent*>(engine);

    qRegisterMetaType<AttributeChange::Type>("AttributeChange::Type");
    qRegisterMetaType<EntityAction::ExecutionType>("EntityAction::ExecutionType");
}

void ReqisterUiMetaTypes(QScriptEngine *engine)
{
    qScriptRegisterQObjectMetaType<UiProxyWidget*>(engine);
}

void ReqisterCoreApiMetaTypes(QScriptEngine *engine)
{
    qScriptRegisterQObjectMetaType<Frame*>(engine);
    qScriptRegisterQObjectMetaType<ScriptConsole*>(engine);
    qScriptRegisterQObjectMetaType<Command*>(engine);
    qScriptRegisterQObjectMetaType<DelayedSignal*>(engine);
}

/*QScriptValue LoadWidgetFromFile(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue value;
    if(!context->argumentCount() && !context->argument(0).isString())
        return engine->newQObject(0);

    QUiLoader loader;
    QFile file(context->argument(0).toString());
    file.open(QFile::ReadOnly);
    if(context->argumentCount() >= 2 && context->argument(1).isQObject())
        value.setData(engine->newQObject(loader.load(&file, dynamic_cast<QWidget*>(context->argument(1).toQObject()))));
    else
        value.setData(engine->newQObject(loader.load(&file)));
    return value;
}*/


