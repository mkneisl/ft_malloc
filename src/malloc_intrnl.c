#include "malloc_intrnl.h"

void exitHandler()
{
    t_zone* zone;
    t_zone_type zoneType = zone_tiny;
    t_context* context = getContext();

    while (zoneType <= zone_large)
    {
        zone = context->zones[zoneType];
        while (zone)
        {
            if (zone->next)
            {
                zone = zone->next;
                unmapZone(context, zone->prev);
                continue;
            }
            unmapZone(context, zone);
            break;
        }
        zoneType++;
    }
    releaseContext(context);
}

void loadEnvOptions(t_context* context)
{
    char* envVar;

    context->mode = 0;
    envVar = getenv("MALLOC_MODE");
    if (!envVar)
        return;
    context->mode = ft_atoi(envVar);
}

t_context* getContext()
{
    static t_context context = { 0 };

    if (!context.mtxInit)
    {
        pthread_mutex_init(&context.mtx, NULL);
        context.mtxInit = 1;
        loadEnvOptions(&context);
        if (context.mode & M_MODE_CLEAN)
            atexit(exitHandler);
    }
    pthread_mutex_lock(&context.mtx);
    return &context;
}

void releaseContext(t_context* context)
{
    pthread_mutex_unlock(&context->mtx);
}

