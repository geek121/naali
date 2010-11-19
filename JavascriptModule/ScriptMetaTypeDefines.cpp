/**
 *  For conditions of distribution and use, see copyright notice in license.txt
 *
 *  @file   ScriptMetaTypeDefines.cpp
 *  @brief  Registration of Naali Core API to Javascript.
 */

#include "StableHeaders.h"
#include "DebugOperatorNew.h"
#include "ScriptMetaTypeDefines.h"

#include "Entity.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "UiProxyWidget.h"
#include "Frame.h"
#include "Console.h"
#include "SceneManager.h"
#include "ISoundService.h"
#include "InputContext.h"
#include "RenderServiceInterface.h"
#include "CommunicationsService.h"

#include "EntityAction.h"

#include "LoggingFunctions.h"

#include <QUiLoader>
#include <QFile>
#include "MemoryLeakCheck.h"

DEFINE_POCO_LOGGING_FUNCTIONS("Script")

//! Qt defines
Q_SCRIPT_DECLARE_QMETAOBJECT(QPushButton, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QWidget, QWidget*)
Q_SCRIPT_DECLARE_QMETAOBJECT(QTimer, QObject*);


///\todo Remove these two and move to Input API once NaaliCore is merged.
//! Naali input defines
Q_DECLARE_METATYPE(MouseEvent*)
Q_DECLARE_METATYPE(KeyEvent*)
Q_DECLARE_METATYPE(InputContext*)

//! Naali Ui defines
Q_DECLARE_METATYPE(UiProxyWidget*);
Q_SCRIPT_DECLARE_QMETAOBJECT(UiProxyWidget, QWidget*)

//! Naali Scene defines.
Q_DECLARE_METATYPE(Scene::SceneManager*);
Q_DECLARE_METATYPE(Scene::Entity*);
Q_DECLARE_METATYPE(EntityAction*);
Q_DECLARE_METATYPE(EntityAction::ExecutionType);
Q_DECLARE_METATYPE(AttributeChange*);
Q_DECLARE_METATYPE(IComponent*);
Q_DECLARE_METATYPE(AttributeChange::Type);

//! Naali core API object defines.
Q_DECLARE_METATYPE(Foundation::Framework*);
Q_DECLARE_METATYPE(Frame*);
Q_DECLARE_METATYPE(ScriptConsole*);
Q_DECLARE_METATYPE(Command*);
Q_DECLARE_METATYPE(DelayedSignal*);

//! Naali renderer defines
Q_DECLARE_METATYPE(RaycastResult*);

//! Communications metatype
Q_DECLARE_METATYPE(Communications::InWorldVoice::SessionInterface*);

QScriptValue findChild(QScriptContext *ctx, QScriptEngine *eng)
{
    if(ctx->argumentCount() == 2)
    {
        QObject *object = qscriptvalue_cast<QObject*>(ctx->argument(0));
        QString childName = qscriptvalue_cast<QString>(ctx->argument(1));
        if(object)
        {
            QObject *obj = object->findChild<QObject*>(childName);
            if (obj)
                return eng->newQObject(obj);
        }
    }
    return QScriptValue();
}

void ExposeQtMetaTypes(QScriptEngine *engine)
{
    assert(engine);
    if (!engine)
        return;

    QScriptValue object = engine->scriptValueFromQMetaObject<QPushButton>();
    engine->globalObject().setProperty("QPushButton", object);
    object = engine->scriptValueFromQMetaObject<QWidget>();
    engine->globalObject().setProperty("QWidget", object);
    object = engine->scriptValueFromQMetaObject<QTimer>();
    engine->globalObject().setProperty("QTimer", object);
    engine->globalObject().setProperty("findChild", engine->newFunction(findChild));
/*
    ImportExtension(engine, "qt.core");
    ImportExtension(engine, "qt.gui");
    ImportExtension(engine, "qt.network");
    ImportExtension(engine, "qt.uitools");
    ImportExtension(engine, "qt.xml");
    ImportExtension(engine, "qt.xmlpatterns");
*/
//  Our deps contain these plugins as well, but we don't use them (for now at least).
//    ImportExtension(engine, "qt.opengl");
//    ImportExtension(engine, "qt.phonon");
//    ImportExtension(engine, "qt.webkit"); // The webkit plugin of QtScriptGenerator fails to load.

}

void ExposeCoreApiMetaTypes(QScriptEngine *engine)
{
    // Input metatypes.
    qScriptRegisterQObjectMetaType<MouseEvent*>(engine);
    qScriptRegisterQObjectMetaType<KeyEvent*>(engine);
    qScriptRegisterQObjectMetaType<InputContext*>(engine);
    qRegisterMetaType<KeyEvent::EventType>("KeyEvent::EventType");
    qRegisterMetaType<MouseEvent::EventType>("MouseEvent::EventType");
    qRegisterMetaType<MouseEvent::MouseButton>("MouseEvent::MouseButton");

    // Scene metatypes.
    qScriptRegisterQObjectMetaType<Scene::SceneManager*>(engine);
    qScriptRegisterQObjectMetaType<Scene::Entity*>(engine);
    qScriptRegisterQObjectMetaType<EntityAction*>(engine);
    qScriptRegisterQObjectMetaType<AttributeChange*>(engine);
    qScriptRegisterQObjectMetaType<IComponent*>(engine);
    //qRegisterMetaType<AttributeChange::Type>("AttributeChange::Type");
    qScriptRegisterMetaType(engine, toScriptValueEnum<AttributeChange::Type>, fromScriptValueEnum<AttributeChange::Type>);
    //qRegisterMetaType<EntityAction::ExecutionType>("EntityAction::ExecutionType");
    qScriptRegisterMetaType(engine, toScriptValueEnum<EntityAction::ExecutionType>, fromScriptValueEnum<EntityAction::ExecutionType>);

    // Framework metatype
    qScriptRegisterQObjectMetaType<Foundation::Framework*>(engine);
    
    // Console metatypes.
    qScriptRegisterQObjectMetaType<ScriptConsole*>(engine);
    qScriptRegisterQObjectMetaType<Command*>(engine);

    // Frame metatypes.
    qScriptRegisterQObjectMetaType<Frame*>(engine);
    qScriptRegisterQObjectMetaType<DelayedSignal*>(engine);

    // Ui metatypes.
    qScriptRegisterQObjectMetaType<UiProxyWidget*>(engine);
    qScriptRegisterQObjectMetaType<QGraphicsScene*>(engine);
    //Add support to create proxy widgets in javascript side.
    QScriptValue object = engine->scriptValueFromQMetaObject<UiProxyWidget>();
    engine->globalObject().setProperty("UiProxyWidget", object);
    
    // Sound metatypes.
    qRegisterMetaType<sound_id_t>("sound_id_t");
    qRegisterMetaType<ISoundService::SoundState>("SoundState");
    qRegisterMetaType<ISoundService::SoundState>("ISoundService::SoundState");
    qRegisterMetaType<ISoundService::SoundType>("SoundType");
    qRegisterMetaType<ISoundService::SoundType>("ISoundService::SoundType");

    // Renderer metatypes
    qScriptRegisterQObjectMetaType<RaycastResult*>(engine);

    // Communications metatypes
    qScriptRegisterQObjectMetaType<Communications::InWorldVoice::SessionInterface*>(engine);
}


