#include "service.h"

namespace Network
{
    //
    // CONSTRUCTOR
    //---------------------------------------------------------------------
    Service::Service(QString name, QString webServiceHost, QString webServiceAPI, QObject *parent) :
        m_name(name),
        m_webServiceHost(webServiceHost),
        m_webServiceAPI(webServiceAPI),
        QObject(parent)
    {
        m_fullpath = m_webServiceHost + "/" + m_webServiceAPI + "/" + m_name;
    }


    //
    // DESTRUCTOR
    //---------------------------------------------------------------------
    Service::~Service()
    {
        qDeleteAll(m_ressources);
    }


    //
    // GET THE ROOT RESSOURCE
    //---------------------------------------------------------------------
    HTTPRequest * Service::getRessource()
    {
        return getRessource("");
    }


    //
    // GET RESSOURCE
    //---------------------------------------------------------------------
    HTTPRequest * Service::getRessource(const QString & ressource)
    {
        if (m_ressources.find(ressource) == m_ressources.end())
        {
            if (ressource.isEmpty())
            {
                m_ressources[ressource] = new HTTPRequest(m_fullpath);
            }
            else
            {
                m_ressources[ressource] = new HTTPRequest(m_fullpath + "/" + ressource);
            }
        }

        return m_ressources[ressource];
    }


    //
    // GET API OF WEBSERVICE TARGETED
    //---------------------------------------------------------------------
    QString Service::getWebServiceAPI() const
    {
        return m_webServiceAPI;
    }


    //
    // GET HOST OF WEBSERVICE TARGETED
    //---------------------------------------------------------------------
    QString Service::getWebServiceHost() const
    {
        return m_webServiceHost;
    }


    //
    // GET NAME
    //---------------------------------------------------------------------
    QString Service::getName() const
    {
        return m_name;
    }


    //
    // GET FULLPATH
    //---------------------------------------------------------------------
    QString Service::getFullpath() const
    {
        return m_fullpath;
    }
}
