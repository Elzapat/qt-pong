#ifndef MULTIPLAYER_WINDOW_H
#define MULTIPLAYER_WINDOW_H

#include <QtWidgets>
#include <QtNetwork>

class MultiplayerWindow : public QWidget {
    Q_OBJECT

    public:
        explicit MultiplayerWindow(QWidget* parent = 0);
        ~MultiplayerWindow();

    public slots:
        void ready_read();
        void socket_error(QAbstractSocket::SocketError error);
        void socket_state_change(QAbstractSocket::SocketState state);
        void show_window();

    private:
        struct Lobby {
            QFrame* frame;
            QGridLayout* layout;
            QLabel* id;
            QLabel* player_count;
            QPushButton* button;
            bool joined = false;
        };
        void send_command(QString command, QStringList args = QStringList());
        void show_lobbies(int number, QStringList lobbies_str);
        void join_lobby(int lobby_id);
        void leave_lobby(int lobby_id);
        void remove_lobby(int lobby_id);
        void lobby_button_click(int id);
        QTcpSocket socket;
        QGridLayout* main_layout;
        QGroupBox* lobbies_box;
        QVBoxLayout* lobbies_layout;
        QPushButton* create_lobby_button;
        QPushButton* refresh_button;
        QPushButton* reconnect_button;
        QTimer* refresh_timer;
        QMap<int, Lobby> lobbies;
        bool is_in_lobby;
        int joined_lobby_id;
};

#endif // MULTIPLAYER_WINDOW_H
