#include "WebModule.h"

std::string Network::WebModule::myIp;
std::string Network::WebModule::port;
zmq::context_t Network::WebModule::context;
std::vector<std::vector<zmq::message_t> > Network::WebModule::ReceivedMessages;
std::future<void> Network::WebModule::listenerThread;
std::map<int, zmq::socket_t> Network::WebModule::players;
//std::map<std::string, zmq::socket_t> Network::WebModule::invitedPlayers;

void ListenerThread(zmq::context_t* ctx, std::vector<std::vector<zmq::message_t> >* messeges, std::string ip, std::string port) {

    zmq::socket_t listener(*ctx, zmq::socket_type::pull);
    try{
        listener.bind("tcp://" + ip + ":" + port);
    }
    catch (zmq::error_t e) { std::cout << e.what() << std::endl; return; }
    const std::string last_endpoint =
        listener.get(zmq::sockopt::last_endpoint);

    std::cout << "Listening on " << last_endpoint << std::endl;

    //subscriber.connect("inproc://#1");

    while (true) {
        // Receive all parts of the message
        std::vector<zmq::message_t> recv_msgs;
        zmq::recv_result_t result =
            zmq::recv_multipart(listener, std::back_inserter(recv_msgs));
        assert(result && "recv failed");
        assert(*result > 0);

        bool saveMess = true;
        switch (*recv_msgs[0].data<MessType>())
        {
        case Invitation:
        case InvitationAccepted:
        case InvitationRejected: break;
        case Join: {
             std::cout << "as Player " << recv_msgs[1].to_string() << " joined" << std::endl;
             Network::WebModule::Join("192.168.0.80", 3);
             break;
        }
        default:
            break;
        }

        if (saveMess) {
            std::vector<zmq::message_t> mess;
            auto ins = std::back_inserter(mess);
            for (int i = 0; i < *result; i++)
            {
                std::cout << recv_msgs[i].to_string() << "  ";
                *ins++ = std::move(recv_msgs[i]);
            }
            std::cout << std::endl;
            messeges->push_back(std::move(mess));
        }    
    }
}

void Network::WebModule::Init(std::string ip)
{
    myIp = ip;
    port = "16669";
    context = zmq::context_t();
    listenerThread = std::async(std::launch::async, ListenerThread, &context, &ReceivedMessages, myIp, port);   
   /* pushSock = zmq::socket_t(context, zmq::socket_type::push);
    pushSock.bind("tcp://127.0.0.1:10669");
    pushSock.bind(address);
    const std::string last_endpoint =
        pushSock.get(zmq::sockopt::last_endpoint);
    std::cout << "Connecting to "
        << last_endpoint << std::endl;*/
}

void Network::WebModule::Stop()
{
    //invitedPlayers["192.168.0.880"].disconnect("tcp://192.168.0.880:16669");
    //invitedPlayers["192.168.0.880"].close();
    context.shutdown();
    context.close();
}

//void Network::WebModule::Invite(std::string ip)
//{
//    invitedPlayers.insert(std::pair<std::string, zmq::socket_t>(ip, zmq::socket_t(context, zmq::socket_type::push)));
//    zmq::socket_ref pushSock = invitedPlayers[ip];
//    pushSock.connect("tcp://" + ip + ":16669");
//
//    auto type = MessType::Invitation;
//    std::string myIp = "192.168.0.80";
//    std::array<zmq::const_buffer, 2> send_msgs = {
//       zmq::buffer(&type, sizeof(type)),
//       zmq::buffer(&myIp, sizeof(myIp))
//    };
//    auto res = zmq::send_multipart(pushSock, send_msgs);
//    invitedPlayers[ip].set(zmq::sockopt::linger, 0);
//}

void Network::WebModule::Invite(std::string ip)
{
    SendByIp(ip, Invitation, &myIp, sizeof(myIp));
}

void Network::WebModule::AcceptInvitation(std::string ip)
{
    SendByIp(ip, InvitationAccepted, &myIp, sizeof(myIp));
}

void Network::WebModule::Join(std::string ip, int playerId)
{
    players.insert(std::pair(playerId, zmq::socket_t(context, zmq::socket_type::push)));
    zmq::socket_ref pushSock = players[playerId];
    pushSock.set(zmq::sockopt::linger, 0);
    pushSock.connect("tcp://" + ip + ":" + port);

    SendById(playerId, MessType::Join, &playerId, sizeof(playerId));
}

void Network::WebModule::SendByIp(std::string ip, MessType type, void* data, size_t size)
{
    zmq::socket_t pushSock = zmq::socket_t(context, zmq::socket_type::push);
    pushSock.set(zmq::sockopt::linger, 0);
    pushSock.connect("tcp://" + ip + ":" + port);

    std::array<zmq::const_buffer, 2> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(data, size)
    };
    auto res = zmq::send_multipart(pushSock, send_msgs);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    pushSock.close();
}

void Network::WebModule::SendById(int playerId, MessType type, void* data = nullptr, size_t size = 0)
{
    std::array<zmq::const_buffer, 2> send_msgs = {
       zmq::buffer(&type, sizeof(type)),
       zmq::buffer(data, size),
    };
    zmq::send_multipart(players[playerId], send_msgs);
    //return pushSock.send(zmq::buffer(message), zmq::send_flags::none);
}

std::vector<zmq::message_t> Network::WebModule::ReceiveMessage()
{
    std::vector<zmq::message_t> mess;

    if (!ReceivedMessages.empty())
    {
        auto ins = std::back_inserter(mess);
        for (int i = 0; i < ReceivedMessages[0].size(); i++)
            *ins++ = std::move(ReceivedMessages[0][i]);
        ReceivedMessages.erase(ReceivedMessages.begin());
    }
    return std::vector<zmq::message_t>(std::move(mess));
}