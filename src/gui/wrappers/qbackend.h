#ifndef HARF_BISIM_SRC_GUI_WRAPPERS_QBACKEND_H_
#define HARF_BISIM_SRC_GUI_WRAPPERS_QBACKEND_H_

#include <QObject>

#include "net/client.h"
#include "audio/mic.h"

namespace gui {

class QBackend : public QObject
{
  Q_OBJECT

 public:
  QBackend(net::Client& client, audio::Mic &mic);
  void SendSignalConnected();

 public slots:
  void OnConnectClicked(QString host, QString ip);
  void OnCaptureStart();
  void OnCaptureStop();

 signals:
  void ConnectedToHost();

 private:
  net::Client &client_;
  audio::Mic &mic_;

};

}  // namespace gui

#endif  // HARF_BISIM_SRC_GUI_WRAPPERS_QBACKEND_H_
