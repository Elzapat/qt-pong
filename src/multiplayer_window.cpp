#include "../include/multiplayer_window.h"

MultiplayerWindow::MultiplayerWindow(QWidget* parent) : socket(nullptr),
        QWidget(parent), is_in_lobby(false), joined_lobby_id(-1),
        port(2929), host_address("54.36.100.67") {

    main_layout = new QGridLayout;
    lobbies_layout = new QVBoxLayout(this);

    main_layout->setSizeConstraint(QLayout::SetFixedSize);

    current_host_label = new QLabel;
    update_current_host_label();

    lobbies_box = new QGroupBox(tr("Lobbies"), this);
    create_lobby_button = new QPushButton(tr("Create Lobby"), this);
    refresh_button = new QPushButton(tr("Refresh"), this);
    reconnect_button = new QPushButton(tr("Reconnect"), this);
    change_host_button = new QPushButton(tr("Change host"), this);
    reconnect_button->hide();

    main_layout->addWidget(current_host_label, 0, 0, 1, 2);
    main_layout->addWidget(lobbies_box, 1, 0, 1, 2);
    main_layout->addWidget(create_lobby_button, 2, 0);
    main_layout->addWidget(refresh_button, 2, 1);
    main_layout->addWidget(change_host_button, 3, 0, 1, 2);
    main_layout->addWidget(reconnect_button, 4, 0, 1, 2);

    this->connect(create_lobby_button, &QPushButton::clicked, this, [this]() {
        send_command("create_lobby");
    });
    this->connect(refresh_button, &QPushButton::clicked, this, [this]() {
        send_command("lobbies");
    });
    this->connect(change_host_button, &QPushButton::clicked, this, &MultiplayerWindow::change_host);
    this->connect(reconnect_button, &QPushButton::clicked, this, &MultiplayerWindow::connect_to_host);

    lobbies_box->setLayout(lobbies_layout);
    this->setLayout(main_layout);

    // Timer to refresh to lobby list, started when the multiplayer window is shown
    refresh_timer = new QTimer(this);
    this->connect(refresh_timer, &QTimer::timeout, this, [this]() { send_command("lobbies"); });
}

MultiplayerWindow::~MultiplayerWindow() {
    delete main_layout;
    delete refresh_timer;
    for (Lobby& lobby : lobbies)
        delete lobby.frame;
}

void MultiplayerWindow::ready_read() {
    QByteArray data = socket->readAll();

    QStringList packets;
    for (QByteArray packet_bytes : data.split('%'))
        packets.append(QString::fromLocal8Bit(packet_bytes));

    for (QString packet : packets) {
        QStringList args = packet.split(';');

        if (args[0] == "lobbies") {
            int number = args[1].toInt();
            args.pop_front(); args.pop_front();
            show_lobbies(number, args);
        } else if (args[0] == "join_lobby")
            join_lobby(args[1].toInt());
        else if (args[0] == "leave_lobby")
            leave_lobby(args[1].toInt());
        else if (args[0] == "lobby_died")
            remove_lobby(args[1].toInt());
        else if (args[0] == "game_start") {
            emit start_game(socket);
            this->hide();
            this->disconnect(socket, SIGNAL(readyRead()), this, SLOT(ready_read()));
            this->disconnect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(socket_error(QAbstractSocket::SocketError)));

            refresh_timer->stop();
            socket = nullptr;
            for (int id : lobbies.keys())
                remove_lobby(id);
            lobbies.clear();
        }
    }
}

void MultiplayerWindow::send_command(QString command, QStringList args) {
    QString packet = command + ';';
    for (const QString& arg : args)
        packet += arg + ';';

    socket->write((packet + '%').toLocal8Bit());
}

void MultiplayerWindow::show_lobbies(int number, QStringList lobbies_str) {
    int idx = 0;
    QVector<int> lobby_ids;
    for (int i = 0; i < number; ++i) {
        QString id = lobbies_str[idx++];
        QString player_count = lobbies_str[idx++];
        lobby_ids.push_back(id.toInt());

        if (lobbies.contains(id.toInt())) {
            lobbies[id.toInt()].player_count->setText(tr("Players: ") + player_count + "/2");
            continue;
        }

        Lobby lobby;

        lobby.frame = new QFrame;
        lobby.frame->setFrameShape(QFrame::Box);
        lobby.frame->setLineWidth(1);
        lobby.frame->setMidLineWidth(2);
        lobby.frame->setFrameShadow(QFrame::Raised);

        lobby.id = new QLabel("Lobby ID: " + id, lobby.frame);
        lobby.player_count = new QLabel(tr("Players: ") + player_count + "/2", lobby.frame);

        lobby.button = new QPushButton(tr("Join"), lobby.frame);
        this->connect(lobby.button, &QPushButton::clicked, this, [this, id]() {
            lobby_button_click(id.toInt());
        });

        lobby.layout = new QGridLayout;
        lobby.layout->addWidget(lobby.id, 0, 0);
        lobby.layout->addWidget(lobby.player_count, 1, 0);
        lobby.layout->addWidget(lobby.button, 0, 1, 2, 1);

        lobby.frame->setLayout(lobby.layout);

        lobbies_layout->addWidget(lobby.frame);

        lobbies.insert(id.toInt(), lobby);
    }

    // If a lobby is shown but is not in the list sent, delete it.
    for (int id : lobbies.keys()) {
        if (!lobby_ids.contains(id))
            remove_lobby(id);
    }
}

void MultiplayerWindow::join_lobby(int lobby_id) {
    for (auto& [id, lobby] : lobbies.toStdMap()) {
        lobby.joined = false;
        lobby.button->setText(tr("Join"));
        lobby.frame->setFrameShadow(QFrame::Raised);
        if (id == joined_lobby_id)
            send_command("leave_lobby", { QString::number(id) });
    }

    is_in_lobby = true;
    joined_lobby_id = lobby_id;

    lobbies[lobby_id].joined = true;
    lobbies[lobby_id].button->setText(tr("Leave"));
    lobbies[lobby_id].frame->setFrameShadow(QFrame::Sunken);

    send_command("lobbies");
}

void MultiplayerWindow::leave_lobby(int lobby_id) {
    lobbies[lobby_id].joined = false;
    lobbies[lobby_id].button->setText(tr("Join"));
    lobbies[lobby_id].frame->setFrameShadow(QFrame::Raised);

    send_command("lobbies");
}

void MultiplayerWindow::lobby_button_click(int id) {
    if (!lobbies[id].joined) {
        send_command("join_lobby", { QString::number(id) });
    } else {
        is_in_lobby = false;
        joined_lobby_id = -1;
        send_command("leave_lobby", { QString::number(id) });
    }
}

void MultiplayerWindow::socket_error(QAbstractSocket::SocketError error) {
    QString error_str = QMetaEnum::fromType<QAbstractSocket::SocketError>().valueToKey(error);
    QMessageBox::information(this, tr("Error"), "Error: " + error_str);  
}

void MultiplayerWindow::socket_state_change(QAbstractSocket::SocketState state) {
    if (state == QAbstractSocket::UnconnectedState)
        reconnect_button->show();
    else if (state == QAbstractSocket::ConnectedState)
        reconnect_button->hide();
}

void MultiplayerWindow::show_window(bool multiplayer_active) {
    if (multiplayer_active) {
        QMessageBox::information(nullptr, tr("Info"), tr("You're already in a multiplayer game"));
        return;
    }

    if (socket == nullptr) {
        socket = new QTcpSocket;
        connect_to_host();

        this->connect(socket, SIGNAL(readyRead()), this, SLOT(ready_read()));
        this->connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socket_state_change(QAbstractSocket::SocketState)));
        this->connect(socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this, SLOT(socket_error(QAbstractSocket::SocketError)));
    }

    refresh_timer->start(3000);
    this->show();
}

void MultiplayerWindow::remove_lobby(int lobby_id) {
    lobbies_layout->removeWidget(lobbies[lobby_id].frame);
    delete lobbies[lobby_id].frame;
    lobbies.remove(lobby_id);
}

void MultiplayerWindow::change_host() {
    QDialog dialog;
    QFormLayout form(&dialog);

    form.addRow(new QLabel("Change the host IP address and port."));
    QLabel host_address_label("Host address");
    QLineEdit host_address_input(host_address.toString(), &dialog);
    QLabel port_label("Port");
    QLineEdit port_input(QString::number(port), &dialog);
    port_input.setValidator(new QIntValidator(0, 65536, this));

    form.addRow(&host_address_label, &host_address_input);
    form.addRow(&port_label, &port_input);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
            Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    this->connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    this->connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        host_address = QHostAddress(host_address_input.text());
        port = port_input.text().toInt();
    }

    update_current_host_label();
    connect_to_host();
}

void MultiplayerWindow::connect_to_host() {
    socket->connectToHost(host_address, port);
    if (!socket->waitForConnected(2000))
        socket_error(socket->error());
}

void MultiplayerWindow::update_current_host_label() {
    current_host_label->setText("Current host: "
            + host_address.toString() + ':' + QString::number(port));
}
