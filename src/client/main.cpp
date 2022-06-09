#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QTranslator>
#include <iostream>

#include "audio/device.h"
#include "audio/mic.h"
#include "audio/speaker.h"
#include "gui/wrappers/qbackend.h"
#include "net/client.h"

int main(int argc, char *argv[])
{
  /* Initialize network */
  net::Client socket;

  /* Setting up OpenAL Soft for capturing mic */
  audio::Device device;
  audio::Speaker speaker(device);
  audio::Mic mic(device, socket, speaker);

  gui::QBackend backend(socket, mic);
  socket.SetOnRead(
      [&speaker](net::Packet packet) { speaker.Play(packet.GetPayload()); });
  socket.SetOnConnect([&backend]() { backend.SendSignalConnected(); });

  /* Creating and showing GUI */
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "playpod" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/Main.qml"));

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.load(url);

  QObject *item = engine.rootObjects()[0];
  QObject::connect(item, SIGNAL(connectClickSignal(QString, QString)), &backend,
                   SLOT(OnConnectClicked(QString, QString)));
  QObject::connect(item, SIGNAL(captureStartSignal()), &backend,
                   SLOT(OnCaptureStart()));
  QObject::connect(item, SIGNAL(captureStopSignal()), &backend,
                   SLOT(OnCaptureStop()));
  QObject::connect(&backend, SIGNAL(ConnectedToHost()), item,
                   SLOT(onHostConnected()));

  return app.exec();
}
