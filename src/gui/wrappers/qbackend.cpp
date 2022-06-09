#include "qbackend.h"

using namespace gui;

QBackend::QBackend(net::Client& client, audio::Mic& mic)
    : client_(client), mic_(mic)
{
}

void QBackend::OnConnectClicked(QString host, QString ip)
{
  client_.Connect(host.toStdString(), ip.toInt());
}

void QBackend::OnCaptureStart() { mic_.StartCapture(); }

void QBackend::OnCaptureStop() { mic_.StopCapture(); }

void QBackend::SendSignalConnected() { emit ConnectedToHost(); }
