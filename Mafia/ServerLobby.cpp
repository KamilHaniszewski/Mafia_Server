#include "Game.h"


ServerLobby::ServerLobby()
{
    iNextRoomNum = 0;
}

void ServerLobby::v_start(int iAction)
{
	
}

std::list<Player*>* ServerLobby::GetPlayerList()
{
    return &lPlayers;
}

void ServerLobby::v_DoCommand(sf::Packet* ptrPacket, Player* ptrPlayer)
{
    sf::Uint8 sf_iCommand;
    (*ptrPacket) >> sf_iCommand;
    std::string kappa;
    switch (sf_iCommand)
    {
    case (int)ServerReceive::Hello:
        std::cout << "Hello: " << (int)sf_iCommand << " \n";
        break;
    case (int)ServerReceive::NickNameChange:
        
        *ptrPacket >> kappa;
        ptrPlayer->v_ChangeNick(&kappa);
        
        break;
    case (int)ServerReceive::CreateGame:
        v_MakeGroup(iNextRoomNum++, ptrPlayer->i_GetId(), ptrPlayer);
        std::cout << "Hello: " << (int)sf_iCommand << " \n";
        break;

    case (int)ServerReceive::JoinGame:
        v_JoinGroup(ptrPacket, ptrPlayer);
        std::cout << "Hello: " << (int)sf_iCommand << " \n";
        break;

    case (int)ServerReceive::LeaveServer:
        v_Disconnect(ptrPacket, ptrPlayer);
        std::cout << "Hello: " << (int)sf_iCommand << " \n";
        break;

    }
    
        
}

void ServerLobby::v_MakeGroup(int iId, int iHost,Player* ptrPlayer)
{
    printf("lPlayers size: %3d|vGameGroup size: %3d\n", lPlayers.size(), vGameGroup.size());
    GameGroup* ggGroup;
    ggGroup = new GameGroup(iId, iHost, ptrPlayer);
    vGameGroup.push_back(ggGroup);

    lPlayers.remove(ptrPlayer);
    

    printf("lPlayers size: %3d|vGameGroup size: %3d\n", lPlayers.size(), vGameGroup.size());
}

void ServerLobby::v_JoinGroup(sf::Packet* ptrPacket, Player* ptrPlayer)
{
    sf::Uint8 sf_iRoomNum;
    bool bJoined = false;
    *ptrPacket >> sf_iRoomNum;
    if (vGameGroup.size() != 0)
    {
        for (std::list<GameGroup*>::iterator it = vGameGroup.begin(); it != vGameGroup.end(); it++)
        {
            GameGroup* gg = *it;
            if (gg->i_GetID() == (int)sf_iRoomNum)
            {
                gg->v_PlayerJoin(ptrPlayer);
                lPlayers.remove(ptrPlayer);
                bJoined = true;
            }
        }
    }

    if (!bJoined)
    {
        //wysylamy ze blad
    }
}

void ServerLobby::v_Disconnect(sf::Packet* ptrPacket, Player* ptrPlayer)
{
    //Dodaj do jakies listy/vectora z osobami do dc'ka.
}

void ServerLobby::v_PrintGroups()
{
    if (vGameGroup.size() != 0)
    {
        for (std::list<GameGroup*>::iterator it = vGameGroup.begin(); it != vGameGroup.end(); it++)
        {
            GameGroup* ptrGG = *it;
            ptrGG->v_PrintGroup();
        }
    }
}



void v_RunServer(int iPort, ServerLobby* slServer)
{
    


    std::list<Player*> lPlayers = *(slServer->GetPlayerList());
    //std::cout << "\nStertuje server na porcie " << iPort << "\n\nK: " << k << "\n";
    sf::TcpListener sflistener;
    sf::SocketSelector sfselector;
    std::list<sf::TcpSocket*> clients;

    int iNextPlayerId = 0;

    bool running = true;

    sflistener.listen(iPort);
    sfselector.add(sflistener);

    while (running)
    {
        if (sfselector.wait())
        {
          
            if (sfselector.isReady(sflistener))
            {
              
                sf::TcpSocket* client = new sf::TcpSocket;
                if (sflistener.accept(*client) == sf::Socket::Done)
                {
                  
                    lPlayers.push_back(new Player(iNextPlayerId,client));
                    
                    sfselector.add(*client);
                    std::cout << "Polaczono nowego \n";
                }
                else
                {
                    delete client;
                }
            }
            else
            {
                
                for (std::list<Player*>::iterator it = lPlayers.begin(); it != lPlayers.end(); ++it)
                {
                    Player* player = *it;
                    sf::TcpSocket* client = player->s_GetTcpSocket();
                    /*
                    sf::Packet p;
                    p.clear();
                    p << 4;
                    if (client->send(p) == sf::Socket::Status::Disconnected)
                    {
                        printf("Blad\n");
                        sfselector.remove(*client);
                        
                    }
                    */
                    if (sfselector.isReady(*client))
                    {
                        sf::Packet *packet;
                        packet = new sf::Packet();
                        packet->clear();

                        if (client->receive(*packet) == sf::Socket::Done)
                        {
                            slServer->v_DoCommand(packet,player);
                        }

                        delete packet;

                    }
                   
                    
                }
            }

        }
    }
}

