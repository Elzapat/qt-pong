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

    private:
        struct Lobby {
            QFrame* frame;
            QGridLayout* layout;
            QLabel* id;
            QLabel* player_count;
            QPushButton* join_button;
        };
        void send_command(QString command, QStringList args = QStringList());
        void show_lobbies(int number, QStringList lobbies_str);
        void join_lobby(int lobby_id);
        QTcpSocket socket;
        QGridLayout* main_layout;
        QGroupBox* lobbies_box;
        QVBoxLayout* lobbies_layout;
        QPushButton* create_lobby_button;
        QPushButton* refresh_button;
        QTimer* refresh_timer;
        QVector<Lobby> lobbies;
        bool is_in_lobby;
};

#endif // MULTIPLAYER_WINDOW_H
