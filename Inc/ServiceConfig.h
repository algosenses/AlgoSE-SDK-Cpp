#ifndef ALGOSE_SERVICE_CONFIG_H
#define ALGOSE_SERVICE_CONFIG_H

#include "Defines.h"

namespace AlgoSE
{

class ServiceConfigImpl;

class ALGOSE_API ServiceConfig
{
public:
    ServiceConfig();
    ServiceConfig(const ServiceConfig& other);
    ~ServiceConfig();
    ServiceConfig &operator=(const ServiceConfig& other);

    void        setType(int type);
    int         getType() const;
    void        setName(const char* name);
    const char* getName() const;
    void        setConfigFile(const char* file);
    const char* getConfigFile() const;
    void        setSharedLibrary(const char* library);
    const char* getSharedLibrary() const;
    void        setServiceObject(void* object);
    void*       getServiceObject() const;
    void        setParameter(const char* name, const char* value);

    const ServiceConfigImpl& getImplementor() const;

private:
    ServiceConfigImpl* m_implementor;
};

} // namespace AlgoSE

#endif // ALGOSE_SERVICE_CONFIG_H