/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_
#define JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_

#include "ModularServer.h"

namespace dev
{
namespace rpc
{
class ServerBaseFace : public ServerInterface<ServerBaseFace>
{
public:
    ServerBaseFace()
    {
        this->bindAndAddMethod(jsonrpc::Procedure("ping", jsonrpc::PARAMS_BY_POSITION,
                                   jsonrpc::JSON_STRING, "param01", jsonrpc::JSON_STRING, NULL),
            &AbstractStubServer::pingI);
    }

    inline virtual void pingI(const Json::Value& request, Json::Value& response)
    {
        response = this->ping(request[0u].asString());
    }
    virtual std::string ping(const std::string& param01) = 0;
};
}  // namespace rpc
}  // namespace dev

#endif  // JSONRPC_CPP_STUB_ABSTRACTSTUBSERVER_H_
