#include "WebModule.h"
#include "NetworkUtils.h"
#include <mutex>
#include "InvitationAcceptance.h"

std::string Network::WebModule::myIp;
std::string Network::WebModule::port;
zmq::context_t Network::WebModule::context;
std::vector<std::vector<zmq::message_t> > Network::WebModule::ReceivedMessages;
std::future<void> Network::WebModule::listenerThread;
std::map<int, zmq::socket_t> Network::WebModule::players;
std::map<int, std::string> Network::WebModule::playersIps;
std::map<std::string, zmq::socket_t> Network::WebModule::invitedPlayers;
std::mutex m;

void ListenerThread(zmq::context_t* ctx, std::vector<std::vector<zmq::message_t> >* messages,
    std::map<int, zmq::socket_t>* players , std::string ip, std::string port, std::map<int, std::string>* playersIps) {

    zmq::socket_t listener(*ctx, zmq::socket_type::pull);
    //listener.set(zmq::sockopt::ipv6, true);
    try{
        listener.bind("tcp://" + ip + ":" + port);
    }
    catch (zmq::error_t e) { std::cout << e.what() << std::endl; return; }
    const std::string last_endpoint =
        listener.get(zmq::sockopt::last_endpoint);

    std::cout << "Listening on " << last_endpoint << std::endl;


    while (true) {
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result =
            zmq::recv_multipart(listener, std::back_inserter(recv_msgs));
        assert(result && "recv failed");
        assert(*result > 0);

        //std::cout << "Received message of type " << *recv_msgs[0].data<MessType>() << std::endl;
        //std::cout << "  " << recv_msgs[1].str() << std::endl;
        bool saveMess = true;
        switch (*recv_msgs[0].data<Network::MessType>())
        {
        case Network::JoinAccepted: {

            // TODO: we cant trust someone who send JoinAccept just like that. 
            // Logic should first check if Join was send (Maybe it is protected somehow and I dont see it). 
            // Same about other requests here
            // Those answers should be added as FastResponses probably

            int playerId = *(recv_msgs[2].data<int>());           
            std::string playerIp = recv_msgs[1].to_string();
            //printf("%d  %s\n", playerId,playerIp.c_str());
            players->insert(std::pair<int, zmq::socket_t>(playerId, zmq::socket_t(*ctx, zmq::socket_type::push)));
            playersIps->insert(std::pair<int, std::string>(playerId, playerIp));
            zmq::socket_ref pushSock = (*players)[playerId];
            pushSock.set(zmq::sockopt::linger, 0);
            pushSock.connect("tcp://" + playerIp + ":" + port);
            int hostId = 0; // zakladam ze jestem hostem i moje id == 0
            Network::WebModule::SendById(playerId, Network::MessType::AddPlayer, ip, &hostId, sizeof(hostId));
            for (auto& kv : *players)
            {
                if (kv.first == playerId)
                    continue;
                int key = kv.first;
                std::string val = (*playersIps)[key];
                Network::WebModule::SendById(kv.first, Network::MessType::AddPlayer, playerIp, &playerId, sizeof(playerId));
                Network::WebModule::SendById(playerId, Network::MessType::AddPlayer, val, &key, sizeof(key));
            }          
            break;
        }
        case Network::Join: {
            Network::WebModule::SendByIp(recv_msgs[1].to_string(), Network::MessType::JoinAccepted, ip, recv_msgs[2].data(), recv_msgs[2].size());
            break;
        }
        case Network::AddPlayer: {
            int playerId = *(recv_msgs[2].data<int>());
            std::string playerIp = recv_msgs[1].to_string();
            players->insert(std::pair<int, zmq::socket_t>(playerId, zmq::socket_t(*ctx, zmq::socket_type::push)));
            playersIps->insert(std::pair<int, std::string>(playerId, playerIp));
            zmq::socket_ref pushSock = (*players)[playerId];
            pushSock.set(zmq::sockopt::linger, 0);    
            pushSock.connect("tcp://" + playerIp + ":" + port);
            //pushSock.send(zmq::str_buffer("hello me"));
            break;
        }
        default:
            break;
        }
        
        //fast response goes here (probably)

        if (saveMess) {
            std::vector<zmq::message_t> mess;
            auto ins = std::back_inserter(mess);
            for (int i = 0; i < *result; i++)
                *ins++ = std::move(recv_msgs[i]);
            m.lock();
            messages->push_back(std::move(mess));
            m.unlock();
        }    
    }
}

void Network::WebModule::Init(std::string ip)
{
    myIp = ip;
    port = "16669";
    context = zmq::context_t();
    listenerThread = std::async(std::launch::async, ListenerThread, &context, &ReceivedMessages, &players, myIp, port, &playersIps);   
}

void Network::WebModule::Init()
{
    Init(NetworkUtils::getIpAddress());
}

void Network::WebModule::Stop()
{
    for (auto& kv : players)
        kv.second.close();
    players.clear();
    CloseInviteSockets();
    playersIps.clear();
    context.shutdown();
    context.close();
}

void Network::WebModule::CloseInviteSockets()
{
    for (auto& kv : invitedPlayers)
        kv.second.close();
    invitedPlayers.clear();
}

void Network::WebModule::Invite(std::string ip, std::string name)
{
    SendByIp(ip, Invitation, myIp, name);
}

void Network::WebModule::AcceptInvitation(std::string ip, std::string name, std::string hash, int hotseatCount)
{
    InvitationAcceptance acceptance(ip, name, hash, hotseatCount);

    SendByIp(ip, InvitationAccepted, myIp, acceptance.serialize());
}

void Network::WebModule::Join(std::string ip, int playerId)
{
    SendByIp(ip, MessType::Join, myIp, &playerId, sizeof(playerId));
   /* for (const auto& kv : players)
    {

    }
    players.insert(std::pair<int, zmq::socket_t>(playerId, zmq::socket_t(context, zmq::socket_type::push)));
    zmq::socket_ref pushSock = players[playerId];
    pushSock.set(zmq::sockopt::linger, 0);
    pushSock.connect("tcp://" + ip + ":" + port);

    int myId = 0;
    int Id1 = 1;
    SendById(playerId, MessType::Join, &playerId, sizeof(playerId));

    SendByIp(myIp, AddPlayer, &Id1, sizeof(Id1), &myIp, sizeof(myIp));*/
    //SendById(playerId, MessType::AddPlayer, &myId, sizeof(myId), &myIp, sizeof(myIp)); //zak³adamy ¿e host ma id = 0
}

void Network::WebModule::SendPatch(std::string patch)
{
    SendToAll(Network::Patch, patch);
}

void Network::WebModule::SendByIp(std::string ip, MessType type, void* data, size_t size, void* data2, size_t size2)
{
    if (invitedPlayers.find(ip) == invitedPlayers.end())
    {
        invitedPlayers.insert(std::pair<std::string, zmq::socket_t>(ip, zmq::socket_t(context, zmq::socket_type::push)));
        invitedPlayers[ip].set(zmq::sockopt::linger, 0);
        invitedPlayers[ip].connect("tcp://" + ip + ":" + port);
    }

    zmq::socket_ref pushSock = invitedPlayers[ip];    
    std::array<zmq::const_buffer, 3> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(data, size),
       zmq::buffer(data2, size2),
    };
    auto res = zmq::send_multipart(pushSock, send_msgs);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //pushSock.close();
}

void Network::WebModule::SendByIp(std::string ip, MessType type, std::string dataString, void* data, size_t size)
{
    if (invitedPlayers.find(ip) == invitedPlayers.end())
    {
        invitedPlayers.insert(std::pair<std::string, zmq::socket_t>(ip, zmq::socket_t(context, zmq::socket_type::push)));
        invitedPlayers[ip].set(zmq::sockopt::linger, 0);
        invitedPlayers[ip].connect("tcp://" + ip + ":" + port);
    }

    zmq::socket_ref pushSock = invitedPlayers[ip];
    std::array<zmq::const_buffer, 3> send_msgs = {
       zmq::buffer(&type, sizeof(type)),      
       zmq::buffer(std::string_view(dataString)),
       zmq::buffer(data, size),
    };
    auto res = zmq::send_multipart(pushSock, send_msgs);
}

void Network::WebModule::SendByIp(std::string ip, MessType type, std::string dataString1, std::string dataString2)
{
    if (invitedPlayers.find(ip) == invitedPlayers.end())
    {
        invitedPlayers.insert(std::pair<std::string, zmq::socket_t>(ip, zmq::socket_t(context, zmq::socket_type::push)));
        invitedPlayers[ip].set(zmq::sockopt::linger, 0);
        invitedPlayers[ip].connect("tcp://" + ip + ":" + port);
    }

    zmq::socket_ref pushSock = invitedPlayers[ip];
    std::array<zmq::const_buffer, 3> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(std::string_view(dataString1)),
       zmq::buffer(std::string_view(dataString2)),
    };
    auto res = zmq::send_multipart(pushSock, send_msgs);
}

void Network::WebModule::SendToAll( MessType type, std::string dataString, void* data, size_t size)
{
    for (const auto& logic : players)
        SendById(logic.first, type, dataString, data, size);
}

void Network::WebModule::SendById(int playerId, MessType type, void* data, size_t size, void* data2, size_t size2)
{
    std::array<zmq::const_buffer, 3> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(data, size),
       zmq::buffer(data2, size2),
    };
    zmq::send_multipart(players[playerId], send_msgs);
}

void Network::WebModule::SendById(int playerId, MessType type, std::string dataString, void* data, size_t size)
{
    std::array<zmq::const_buffer, 3> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(std::string_view(dataString)),
       zmq::buffer(data, size),
    };
    zmq::send_multipart(players[playerId], send_msgs);
}

std::vector<zmq::message_t> Network::WebModule::ReceiveMessage()
{
    std::vector<zmq::message_t> mess;
    if (!ReceivedMessages.empty())
    {
        auto ins = std::back_inserter(mess);
        for (int i = 0; i < ReceivedMessages[0].size(); i++)
            *ins++ = std::move(ReceivedMessages[0][i]);
        m.lock();
        ReceivedMessages.erase(ReceivedMessages.begin());
        m.unlock();
    }
    return std::vector<zmq::message_t>(std::move(mess));
}

Network::m_message Network::WebModule::ReceiveMessageStruct()
{
    std::vector<zmq::message_t> mess;
    if (!ReceivedMessages.empty())
    {
        auto ins = std::back_inserter(mess);
        for (int i = 0; i < ReceivedMessages[0].size(); i++)
            *ins++ = std::move(ReceivedMessages[0][i]);
        m.lock();
        ReceivedMessages.erase(ReceivedMessages.begin());
        m.unlock();
    }
    return m_message(std::move(mess));
}
