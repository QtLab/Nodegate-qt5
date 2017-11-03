#include "usersservice.h"

//
// CONSTRUCTOR
//---------------------------------------------------------------------
UsersService::UsersService(QObject * parent) : m_service("users", "http://localhost:3000", "api"), QObject(parent)
{
    // Récupère la ressource /api/users/
    m_users = m_service.getRessource();

    // Récupère la ressource /api/users/:userId
    m_user  = m_service.getRessource(":userId");

    // Appel le slot users() a chaque reponse d'une requete sur la ressource m_users
    connect(m_users, SIGNAL(finished(Network::HTTPResponse)), this, SLOT(users(Network::HTTPResponse)));

    // Appel le slot user() a chaque reponse d'une requete sur la ressource m_user
    connect(m_user,  SIGNAL(finished(Network::HTTPResponse)), this, SLOT(user (Network::HTTPResponse)));
}


//
// CREATE A NEW USER
//---------------------------------------------------------------------
void UsersService::create(QString username, QString password)
{
    QByteArray postData;
    postData.append("username=" + username);
    postData.append("&password=" + password);

    m_users->post({}, postData);
}


//
// REFRESH LIST
//---------------------------------------------------------------------
void UsersService::list()
{
    m_users->get();
}


//
// RESPONSES /api/users
//---------------------------------------------------------------------
void UsersService::users(Network::HTTPResponse res)
{
    //
    // GET (LIST)
    //
    if (res.operation() == Network::Method::GetOperation)
    {
        QJson::Parser parser;
        QVariant json = parser.parse(res.data());

        emit usersListReceived(json);
    }
}


//
// READ USER
//---------------------------------------------------------------------
void UsersService::read(int id)
{
    // Envoi une requête GET sur la ressource /api/users/:userId
    m_user->get({{"userId", QString::number(id)}});
}


//
// RESPONSES /api/users/:userId (Single user routes)
//---------------------------------------------------------------------
void UsersService::user(Network::HTTPResponse res)
{
    //
    // GET (READ)
    //
    if (res.operation() == Network::Method::GetOperation)
    {
        if (res.status() == 200)
        {
            QJson::Parser parser;
            QVariant json = parser.parse(res.data());

            emit userReadReceived(json);
        }
    }
}
