#include "../include/multiplayer_window.h"

const QHostAddress HOST_ADDRESS("127.0.0.1");

MultiplayerWindow::MultiplayerWindow(QWidget* parent) : QWidget(parent), is_in_lobby(false) {
    socket = new QUdpSocket(this);
    socket->connectToHost(HOST_ADDRESS, 2929);

    main_layout = new QGridLayout;
    lobbies_layout = new QVBoxLayout;

    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    // QLabel* label = new QLabel;
    // label->setFrameShape(QFrame::Box);
    // label->setFrameShadow(QFrame::Sunken);
    // label->setMidLineWidth(2);
    // label->setLineWidth(1);

    // QFrame* frame = new QFrame;
    // frame->setFrameShape(QFrame::Box);
    // frame->setFrameShadow(QFrame::Sunken);
    // frame->setLineWidth(1);
    // frame->setMidLineWidth(2);
    // // frame->setStyleSheet("padding: 100px;");
    // frame->setLayout(main_layout);

    // command_input = new QLineEdit(frame);
    // command_input->setFrame(true);
    // send_button = new QPushButton("Send command", frame);
    lobbies_box = new QGroupBox(tr("Lobbies"));
    create_lobby_button = new QPushButton(tr("Create Lobby"));
    refresh_button = new QPushButton(tr("Refresh"));

    main_layout->addWidget(lobbies_box, 0, 0, 1, 2);
    main_layout->addWidget(create_lobby_button, 1, 0);
    main_layout->addWidget(refresh_button, 1, 1);

    // main_layout->addWidget(frame, 0, 0, 2, 1);
    // main_layout->addWidget(command_input, 0, 0);
    // main_layout->addWidget(send_button, 1, 0);
    // main_layout->setContentsMargins(QMargins(50, 50, 50, 50));

    this->connect(socket, SIGNAL(readyRead()), this, SLOT(read_socket()));
    this->connect(create_lobby_button, &QPushButton::clicked, this, [this]() { send_command("create_lobby"); });
    this->connect(refresh_button, &QPushButton::clicked, this, [this]() { send_command("lobbies"); });
    // connect(send_button, SIGNAL(clicked()), this, SLOT(send_command()));

    lobbies_box->setLayout(lobbies_layout);
    this->setLayout(main_layout);
    // QHBoxLayout* layout = new QHBoxLayout;
    // layout->addWidget(frame);
    // this->setLayout(layout);
    
    refresh_timer = new QTimer(this);
    this->connect(refresh_timer, &QTimer::timeout, this, [this]() { send_command("lobbies"); });
    refresh_timer->start(3000);
}

MultiplayerWindow::~MultiplayerWindow() {
    delete main_layout;
    delete refresh_timer;
    delete lobbies_layout;
    delete lobbies_box;
    delete socket;
    delete refresh_button;
    delete create_lobby_button;
}

void MultiplayerWindow::read_socket() {
    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        QList<QByteArray> args_bytes = datagram.data().split(';');

        QStringList args;
        foreach(const QByteArray& arg, args_bytes) {
            args.append(QString::fromLocal8Bit(arg));
        }

        qDebug() << args;

        if (args[0] == "lobbies") {
            int number = args[1].toInt();
            args.pop_front(); args.pop_front();
            show_lobbies(number, args);
        } else if (args[0] == "lobby_joined") {
            join_lobby(args[1].toInt());
        }
    }
}

void MultiplayerWindow::send_command(QString command, QStringList args) {
    QString datagram = command + ';';
    for (const QString& arg : args)
        datagram += arg + ';';

    socket->writeDatagram(datagram.toLocal8Bit());
}

void MultiplayerWindow::show_lobbies(int number, QStringList lobbies_str) {
    // if (number == lobbies.size()) return;

    // Remove all the present lobbies widget
    auto it = lobbies.begin();
    while (it != lobbies.end()) {
        lobbies_layout->removeWidget(it->frame);
        delete it->frame;
        // Segmentation fault if I add those back, I guess qt deletes them
        // delete it->layout;
        // delete it->id;
        // delete it->player_count;
        it = lobbies.erase(it);
    }

    int idx = 0;
    for (int i = 0; i < number; ++i) {
        QString id = lobbies_str[idx++];
        QString player_count = lobbies_str[idx++];

        Lobby lobby;

        lobby.frame = new QFrame;
        lobby.frame->setFrameShape(QFrame::Box);
        lobby.frame->setFrameShadow(QFrame::Raised);
        lobby.frame->setLineWidth(2);
        lobby.frame->setMidLineWidth(2);

        lobby.id = new QLabel("Lobby ID: " + id, lobby.frame);
        lobby.player_count = new QLabel(tr("Players: ") + player_count + "/2", lobby.frame);


        lobby.join_button = new QPushButton(tr("Join"), lobby.frame);
        this->connect(lobby.join_button, &QPushButton::clicked, this, [this, id]() {
            send_command("join_lobby", { id });
            QTimer::singleShot(3000, this, [this]() {
                if (!is_in_lobby)
                    QMessageBox::information(this, tr("Error"), tr("Joining lobby failed."));
            });
        });

        lobby.layout = new QGridLayout;
        lobby.layout->addWidget(lobby.id, 0, 0);
        lobby.layout->addWidget(lobby.player_count, 1, 0);
        lobby.layout->addWidget(lobby.join_button, 0, 1, 2, 1);

        lobby.frame->setLayout(lobby.layout);

        lobbies_layout->addWidget(lobby.frame);

        lobbies.push_back(lobby);
    }
}

void MultiplayerWindow::join_lobby(int lobby_id) {
    refresh_timer->stop();

    auto it = lobbies.begin();
    while (it != lobbies.end()) {
        lobbies_layout->removeWidget(it->frame);
        delete it->frame;
        it = lobbies.erase(it);
    }
}
