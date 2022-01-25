#pragma once
#include "IMoveDescription.h"
class AcceptInvitationMoveDescription :
    public IMoveDescription
{
    std::string ip;
    int hotseatCount;
public:
    AcceptInvitationMoveDescription(std::string ip, int hotseatCount)
        : ip(ip), hotseatCount(hotseatCount) {}
    virtual std::string getMoveType() const override { return "accept_invitation"; }

    int getHotseatCount() const { return hotseatCount; }
    std::string getIp() const { return ip; }
};
